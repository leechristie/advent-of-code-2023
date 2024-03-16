// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

using System.Data;
using System.Diagnostics;

namespace aoc23cs;

public class Day01
{
    
    private static readonly string[] Words
        = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];

    public static void Solve()
    {
        
        Console.WriteLine("Advent of Code 2023");
        Console.WriteLine("Day 1");

        var answer1 = 0;
        var answer2 = 0;
        foreach (var line in File.ReadLines("../input/input01.txt"))
        {
            answer1 += GetCalibrationValue(line, false);
            answer2 += GetCalibrationValue(line, true);
        }
        
        Console.WriteLine($"Part 1: {answer1}");
        Debug.Assert(54708 == answer1, "answer1 incorrect");
        
        Console.WriteLine($"Part 2: {answer2}");
        Debug.Assert(54087 == answer2, "answer2 incorrect");
        
    }
    
    private static int GetCalibrationValue(string line, bool includeWords)
    {
        
        int? first = null;
        int? last = null;

        for (var i = 0; i < line.Length; i++)
        {
            int? current = GetNumberAt(line, i);
            if (current == null && includeWords)
            {
                current = GetWordNumberAt(line, i);
            }
            if (current != null)
            {
                last = current;
                first ??= current;
            }
        }

        if (first == null)
            throw new DataException("missing first");
        if (last == null)
            throw new DataException("missing last");
        
        return (int) first * 10 + (int) last;
        
    }

    private static int? GetNumberAt(string line, int i)
    {
        try
        {
            return int.Parse(line[i].ToString());
        }
        catch (FormatException)
        {
            return null;
        }
    }

    private static int? GetWordNumberAt(string line, int i)
    {
        for (var wordIndex = 0; wordIndex < Words.Length; wordIndex++)
        {
            var current = GetWordNumberAt(line, i, Words[wordIndex], wordIndex);
            if (current != null)
            {
                return current;
            }
        }
        return null;
    }

    private static int? GetWordNumberAt(string line, int startIndex, string word, int wordIndex)
    {
        for (var i = 0; i < word.Length; i++)
        {
            var offset = i + startIndex;
            if (offset >= line.Length)
            {
                return null;
            }
            if (line[offset] != word[i])
            {
                return null;
            }
        }
        return wordIndex + 1;
    }
    
}
