# Logbook

## Day 4 - Scratchcards

I skipped Day 2 and 3 for now due to vacation being away from the computer. On returning, I decided to try solving Day 4 Part 1 in C first.

### 1. C (Part 1)

Whenever I solve these in C, I always have to write using a lot of small functions to abstract the code somewhat.

The main loop is:

```C
while (read_ticket(file, &card_number, picked, winning)) {
    assert(card_number == i);
    set_lookup(picked, lookup);
    answer1 += calc_score(lookup, winning);
    unset_lookup(picked, lookup);
}
```

The `read_ticket` function reads the ticket into an array of picked numbers and an array of winning numbers. I'm always bothered by the fact that passing a reference to an array in C does not use `&`. I think it should require you to put `&` to be consistent.

`set_lookup` and `unset_lookup` sets a boolean array to have `true` in the positions corresponding to the picked numbers, and unsets it back to `false` respectively (to reuse). This acts as a `set[int]`, but setting all of the numbers is in linear in the number of picked numbers rather than nlogn.

`calc_score` loops over the winning numbers an checks them against the lookup, again checking all the numbers is linear in the number of winning numbers rather than nlogn.

The use of a lookup boolean array should be faster than a hash set or binary tree. However, there real reason for this choice is that I'm using C and this is easier.

### 2. Swift (Part 1)

I implemented Part 1 in Swift. This is the first Swift I'm doing this AoC so far.

I don't like parsing strings in Swift. I'm sure there is a better way I don't know, but there seems to be no clear way to iterate lines of a file without reading the whole file, and when you split on lines you end up dealing with `Substring` and `SubSequence` objects which are really annoying.

I just create a `Card` struct for each line and eagerly compute the number of matches and score, then add them scores for Part 1.
