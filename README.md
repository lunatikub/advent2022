# Advent of Code

## Concept

I solve the problematics (one by day) with a simple concept:
  + One part in **bash** to format the input.
  + One part in **C** to implement the logic.

Each day is composed from a template:

``` bash
$ ls
  main.c
  Makefile
  puzzle.sh
  puzzle.txt
  sample.txt
```

The **puzzle.sh** format the inputs (sample.txt and puzzle.txt) into an C header.  
The **main.c** implements the logic to solve the problem.  
The **Makefile** is calling a commun Makefile which is generate and compile everything we need.

Take a simple example to explain the concept:

> Find the number of the line with the maximum sum of each elements with the following inputs:

``` text
1 2 3
5 6
10 12 24
```

In this example the line ``3`` is the line with the max sum (46 = 10 + 12 + 24).

In a first time we format this input into a header with the script **puzzle.sh**:

``` c
static const input_t inputs[] = {
    { { 1, 2, 3 }, 3 },
    { { 5, 6 }, 2 },
    { { 10, 12, 24 }, 3 },
};

#define NR_INPUT 3
```

In the file **main.c** we have to adjust the structure input:

``` c
typedef struct input {
  unsigned *n;
  unsigned nr;
} input_t;
```

And now, it is really easy to process the inputs:

``` c
unsigned max = 0;
unsigned line = 0;
for (unsigned i = 0; i < NR_INPUT; ++i) {
  unsigned sum = 0;
  for (unsigned j = 0; j < inputs[i].nr; ++j) {
    sum += inputs[i].n[j];
  }
  if (sum > max) {
    max = sum;
    line = i;
  }
}
printf("line: %u\n", line);
```

## Days completed

> **Total days completed (34/200)**

![](https://geps.dev/progress/17)

### 2022 (5/25)

![](https://geps.dev/progress/20)

 + **Day 1**: Simple counter & arithmetic [(Calorie Counting)](https://adventofcode.com/2022/day/1)
 + **Day 2**: Simple logic [(Rock Paper Scissors)](https://adventofcode.com/2022/day/2)
 + **Day 3**: Simple string manipulation [(Rucksack Reorganization)](https://adventofcode.com/2022/day/3)
 + **Day 4**: Overlap intervals [(Camp Cleanup)](https://adventofcode.com/2022/day/4)
 + **Day 5**: Stack manipulat [()](https://adventofcode.com/2022/day/5)

### 2021 (3/25) 

![](https://geps.dev/progress/12)

 + **Day 1**: Simple counter [(Sonar Sweep)](https://adventofcode.com/2021/day/1)
 + **Day 2**: Simple counter [(Dive !)](https://adventofcode.com/2021/day/2)
 + **Day 3**: Bit manipulation [(Binary Diagnostic)](https://adventofcode.com/2021/day/3)

### 2018 (4/25)

![](https://geps.dev/progress/16)

 + **Day 1**: Simple array manipulation and flag: [(Chronal Calibration)](https://adventofcode.com/2018/day/1)
 + **Day 2**: Simple string manipulation: [(Inventory Management System)](https://adventofcode.com/2018/day/2)
 + **Day 3**: Two dimensional array manipulation: [(No Matter How You Slice It)](https://adventofcode.com/2018/day/3)
 + **Day 5**: String manipulation (memory move): [(Day 5: Alchemical Reduction)](https://adventofcode.com/2018/day/5)

### 2016 (4/25)

![](https://geps.dev/progress/16)

 + **Day 1**: Simple arithmetic: [(No Time for a Taxicab)](https://adventofcode.com/2016/day/1)
 + **Day 2**: Simple coordinate: [(Bathroom Security)](https://adventofcode.com/2016/day/2) 
 + **Day 3**: Simple geometry: [(Squares With Three Sides)](https://adventofcode.com/2016/day/3)
 + **Day 4**: Decrypt and checksum [(Security Through Obscurity)](https://adventofcode.com/2016/day/4) 

### 2015 (19/25)

![](https://geps.dev/progress/76)

 + [**Day 1**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_1): Simple string manipulation and counter [(Not Quite Lisp)](https://adventofcode.com/2015/day/1)
 + [**Day 2**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_2): Arithmetic and comparison statement [(I Was Told There Would Be No Math)](https://adventofcode.com/2015/day/2)
 + [**Day 3**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_3): Set implementation [(Perfectly Spherical Houses in a Vacuum)](https://adventofcode.com/2015/day/3)
 + [**Day 4**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_4): MD5 and brut force [(The Ideal Stocking Stuffer)](https://adventofcode.com/2015/day/4)
 + [**Day 5**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_5): Advanced string manipulation [(Doesn't He Have Intern-Elves For This?)](https://adventofcode.com/2015/day/5)
 + [**Day 6**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_6): Two dimensional array: [(Probably a Fire Hazard)](https://adventofcode.com/2015/day/6)
 + [**Day 7**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_7): Recursively solve and bit manipulation: [(Some Assembly Require)](https://adventofcode.com/2015/day/7)
 + [**Day 8**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_8): Advanced string manipulation (escaped characters): [(Matchsticks)](https://adventofcode.com/2015/day/8)
 + [**Day 9**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_9): Permuation: [(All in a Single Night)](https://adventofcode.com/2015/day/9)
 + [**Day 10**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_10): Smoke the CPU: [(Elves Look Elves Say)](https://adventofcode.com/2015/day/10)
 + [**Day 11**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_11): Advanced string manipulation (password generation) [(Corporate Policy)](https://adventofcode.com/2015/day/11)
 + [**Day 12**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_12): Json (hack with python) [(JSAbacusFramework.io)](https://adventofcode.com/2015/day/12)
 + [**Day 13**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_13): Permutation: [(Knights of the Dinner Table)](https://adventofcode.com/2015/day/13)
 + [**Day 14**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_14): Sequentially computing: [(Reindeer Olympics)](https://adventofcode.com/2015/day/14)
 + [**Day 15**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_15): Addition combination: [(Science for Hungry People)](https://adventofcode.com/2015/day/15)
 + [**Day 16**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_16): Range comparaison [(Aunt Sue)](https://adventofcode.com/2015/day/16)
 + [**Day 17**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_17): Combination [(No Such Thing as Too Much)](https://adventofcode.com/2015/day/17)
 + [**Day 18**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_18): Conway's Game of Life [(Like a GIF For Your Yard)](https://adventofcode.com/2015/day/18)
 + [**Day 23**](https://github.com/lunatikub/adventofcode/tree/master/2015/day_23): CPU instructions emulation [(Opening the Turing Lock)](https://adventofcode.com/2015/day/23)
