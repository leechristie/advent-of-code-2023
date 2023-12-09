# Logbook

## Day 1 - Trebuchet?!

I was not planning to try to speed-solve these puzzles but due to being awake at 5:00 a.m. (the release time of the puzzles in GMT) on this one occasion, I was able to complete the puzzle soon after release.

Personal leaderboard times:

- **Part 1**: 2min 29sec (410<sup>th</sup>)
- **Part 2**: 17min 13sec (1,332<sup>nd</sup>)

Part 2 seems to be slightly trickier that previous years. I did have a mistake in my solution that took a little while to spot.

Refactoring and pushing to GitHub was not done until after 9:00 a.m.

The next two days are busy for me so I expect to resume AoC 2023 on day 4, do catch up and hopefully start reimplementing day 1 in another language.

### 1. Python

I first solved the puzzle in Python.

For part one, I looped over the input line and checking each digit against `str.isdigit`, putting them into a list and returning `int(digits[0] + digits[-1])`. In refactoring, I changed the check to `string[0] in '123456789'` as I think zero is not a digit in this puzzle's definition.

For part two, I looped over a list of strings of digits as English words in a function which returned the string with digit stripped off, as in:

```Python
return value, string[len(digit):]
```

However, this was a mistake because the real input file contains overlapping English words. The quickest fix was:

```Python
return value, string[1:]
```

An alternative would be to find the possible merged words and add special cases, but I preferred the clearer implementation without special cases.

In refactoring, I extracted reading of the input to a generator function and created day-specific helper functions I can use in one pass of the input file:

```Python
for line in input_lines(day=1):
    answer1 += first_and_last_digits(find_digits(line))
    answer2 += first_and_last_digits(find_digits(line, include_words=True))
```

### 2. Java

I decided to do the second implementation the same day.

The solution is similar to my refactored Python solution. However, in my python `strip_digit` I return a tuple of the digit and the remaining string to be parsed. Now I know we always strip only one character off, I decided to use a `beginIndex` variable that lives in the loop instead of delegating incrementing to the strip function. This also means I don't need to find a way to return a tuple, and it means I don't keep creating substrings.

The main different idea here is the `getWrittenDigit` method:

```Java
int value = 1;
for (String s: DIGITS) {
    if (line.indexOf(s, beginIndex) == beginIndex)
        return OptionalInt.of(value);
    value++;
}
return OptionalInt.empty();
```

Although I'm not creating substrings, this is a still little inefficient as I'm searching all the way to the end of the string for each number.

I call two version of the get digit functions like this, however, I think there may be a less ugly way to combine the two resulting `OptionalInt` that I couldn't think of:

```Java
OptionalInt simple = getSimpleDigit(line, beginIndex);
if (simple.isPresent())
    return simple;
if (includeWords)
    return getWrittenDigit(line, beginIndex);
return OptionalInt.empty();
```

### 3. C

At this point I have encountered some minor spoilers on Mastodon for Day 1 Part 2 regarding a method some people are using where they reverse each number string e.g. `"four"` -> `"ruof"` to search for the last digit more quickly, however, it's not a method I was planning to consider as I don't think it's a good idea for such short strings, so I won't be using it in any of my solutions. Although I guess it does look good in functional style.

In this C solution, I loop over the digits in the string, updating two variables `firstDigit` and `lastDigit` and convert them with `10 * (firstDigit - '0') + (lastDigit - '0')`.

I added Part 2 to my C solution, and it took a lot more code than Part 1, but I still solve both parts in a single pass through the file. Solution looks at each character and does a constant amount of work per character.

The key to my Part 2 solution is to keep a `size_t[10]` array which tracks how far into each English word "one", "two" etc. we have read. If we encounter the next letter, we advance one. If we encounter a digit, we reset the pointer to 0. If we encounter a letter but not the correct next letter we reset the pointer to 0 then *(and not noticing the was a bug that took for a while to find)* importantly recheck the first letter again incase we encounter `"tt"`. With the pointers for `"two"` and `"three"` at `'w'` and `"h"`, and encountering a second `'t'` we need to recheck to see this is the first letter of `"two"` and `"three`.

### 4. Go (Part 1)

Wrote Part 1 in Go. This is my first Go, so it's not very good. I will have to revisit this later.

### 5. C++

For the C++ solution, I need to try not to just convert my C solution. This solution is actually similar to my Java solution. I had to look up a lot of string processing methods to figure out how to write this as I don't have experience with `std::string`.

In loading the file, I've defined a function which just gets the file as an `ifstream`.

```C++
std::ifstream get_input_stream(int day)
```

It returns a copy of the `ifstream`, and I realise I'm not familiar with how copy elision works in C++, I assume this doesn't actually copy anything because it doesn't have to, but I don't know if I should be using `std::move` or something here.

Like in the Java solution, I loop over the positions and check `line.find(digit, beginIndex)`

The English words are stored as `static constexpr std::array<std::string, 10>`, which I think is the right way to have a constant array of strings.

The loop over `beginIndex` in my implmentation this time uses two calls to a function that reads the basic digit `0` to `9` and one call to a functioin that reads the spelled digit.

```C++
read_basic_digit(line, beginIndex, firstDigit, lastDigit);
read_basic_digit(line, beginIndex, firstBasicDigit, lastBasicDigit);
read_spelled_digit(line, beginIndex, firstDigit, lastDigit);
```
