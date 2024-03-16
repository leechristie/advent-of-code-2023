// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

namespace aoc23cs;

public class Program
{

    private static void Main(string[] args)
    {
        
        const string err = "Valid day not specified in command line argument.";
        if (args.Length != 1)
            throw new ArgumentException(err);
        
        int day;
        try
        {
            day = int.Parse(args[0]);
        }
        catch (FormatException)
        {
            throw new ArgumentException(err);
        }

        switch (day)
        {
            case 1:
                Day01.Solve();
                break;
            default:
                throw new ArgumentException(err);
        }
            
    }

}
