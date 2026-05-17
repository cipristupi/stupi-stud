# Easy POSIX Threads in C — 50 Numeric, Matrix, and Text Problems

Each problem is designed to be solvable in about **1 hour** in C using POSIX Threads.

The problems focus only on practical data-processing tasks:

- numbers
- arrays
- matrices
- strings/text
- simple logs
- CSV-like/tabular input

No server/framework/cache/database-style exercises are included.

Recommended implementation pattern:

1. Read all input in the main thread.
2. Allocate shared arrays/results before creating threads.
3. Give each thread a small argument struct:
   - `tid`
   - `start`
   - `end`
   - pointers to input/output arrays
   - pointers to mutexes/barriers/condition variables/RW locks when needed
4. Prefer per-thread local results, then reduce in the main thread.
5. Print final output only from the main thread unless ordered thread output is required.



---

## Problem 1: Parallel Sum of Integers

**Problem description**  
Given `N` integers, compute their total sum using `T` threads.

**Data input**
```text
N T
a1 a2 ... aN
```

**Sample input**
```text
8 2
1 2 3 4 5 6 7 8
```

**Correct output**
```text
36
```

**Suggested POSIX concepts**
- POSIX threads, per-thread partial sums, join/reduction

**Tips & tricks**
- Split the array into contiguous chunks. Store each thread's sum in `partial[tid]`, then sum those values in main.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 2: Parallel Count Even Numbers

**Problem description**  
Count how many numbers in an array are even.

**Data input**
```text
N T
a1 a2 ... aN
```

**Sample input**
```text
7 3
1 2 4 5 6 7 8
```

**Correct output**
```text
4
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Do not lock for every number. Use one counter per thread and reduce after joins.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 3: Parallel Count Odd Numbers

**Problem description**  
Count how many numbers in an array are odd.

**Data input**
```text
N T
a1 a2 ... aN
```

**Sample input**
```text
6 2
1 2 3 4 5 6
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Same pattern as even counting. Make the predicate small: `a[i] % 2 != 0`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 4: Parallel Minimum

**Problem description**  
Find the minimum value in an integer array.

**Data input**
```text
N T
a1 a2 ... aN
```

**Sample input**
```text
8 3
5 2 9 -1 7 3 0 4
```

**Correct output**
```text
-1
```

**Suggested POSIX concepts**
- POSIX threads, local minimums

**Tips & tricks**
- Initialize each local minimum with the first element in that thread's range.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 5: Parallel Maximum

**Problem description**  
Find the maximum value in an integer array.

**Data input**
```text
N T
a1 a2 ... aN
```

**Sample input**
```text
8 3
5 2 9 -1 7 3 0 4
```

**Correct output**
```text
9
```

**Suggested POSIX concepts**
- POSIX threads, local maximums

**Tips & tricks**
- Avoid a shared max protected by a mutex inside the loop. Reduce local maximums in main.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 6: Parallel Count Positive Numbers

**Problem description**  
Count positive values in an array.

**Data input**
```text
N T
a1 a2 ... aN
```

**Sample input**
```text
7 2
-3 0 4 5 -1 2 -9
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Positive means `> 0`, not `>= 0`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 7: Parallel Count Negative Numbers

**Problem description**  
Count negative values in an array.

**Data input**
```text
N T
a1 a2 ... aN
```

**Sample input**
```text
7 2
-3 0 4 5 -1 2 -9
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Keep `count_negative[tid]`. No mutex is needed.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 8: Parallel Count Zeroes

**Problem description**  
Count zero values in an array.

**Data input**
```text
N T
a1 a2 ... aN
```

**Sample input**
```text
8 3
0 1 0 2 3 0 4 0
```

**Correct output**
```text
4
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- This is a good first exercise for range splitting.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 9: Parallel Array Copy

**Problem description**  
Copy array `A` into array `B` using `T` threads.

**Data input**
```text
N T
a1 a2 ... aN
```

**Sample input**
```text
5 2
10 20 30 40 50
```

**Correct output**
```text
10 20 30 40 50
```

**Suggested POSIX concepts**
- POSIX threads, independent writes

**Tips & tricks**
- Each thread writes to a distinct slice of `B`. No lock needed.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 10: Parallel Add Constant

**Problem description**  
Add constant `X` to every element of an array.

**Data input**
```text
N T X
a1 a2 ... aN
```

**Sample input**
```text
5 2 10
1 2 3 4 5
```

**Correct output**
```text
11 12 13 14 15
```

**Suggested POSIX concepts**
- POSIX threads, array partitioning

**Tips & tricks**
- In-place update is safe if every index belongs to exactly one thread.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 11: Parallel Multiply by Constant

**Problem description**  
Multiply every element of an array by constant `X`.

**Data input**
```text
N T X
a1 a2 ... aN
```

**Sample input**
```text
5 2 3
1 2 3 4 5
```

**Correct output**
```text
3 6 9 12 15
```

**Suggested POSIX concepts**
- POSIX threads, array partitioning

**Tips & tricks**
- Use `long long` if the values may grow.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 12: Parallel Elementwise Array Addition

**Problem description**  
Compute `C[i] = A[i] + B[i]`.

**Data input**
```text
N T
A values
B values
```

**Sample input**
```text
4 2
1 2 3 4
10 20 30 40
```

**Correct output**
```text
11 22 33 44
```

**Suggested POSIX concepts**
- POSIX threads, independent writes

**Tips & tricks**
- Thread `tid` writes only its assigned indexes in `C`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 13: Parallel Elementwise Array Difference

**Problem description**  
Compute `C[i] = A[i] - B[i]`.

**Data input**
```text
N T
A values
B values
```

**Sample input**
```text
4 2
10 20 30 40
1 2 3 4
```

**Correct output**
```text
9 18 27 36
```

**Suggested POSIX concepts**
- POSIX threads, independent writes

**Tips & tricks**
- Same as addition, just change the operator.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 14: Parallel Elementwise Product

**Problem description**  
Compute `C[i] = A[i] * B[i]`.

**Data input**
```text
N T
A values
B values
```

**Sample input**
```text
4 2
1 2 3 4
5 6 7 8
```

**Correct output**
```text
5 12 21 32
```

**Suggested POSIX concepts**
- POSIX threads, independent writes

**Tips & tricks**
- Use `long long` for multiplication results.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 15: Parallel Count Greater Than X

**Problem description**  
Count how many numbers are greater than `X`.

**Data input**
```text
N T X
a1 ... aN
```

**Sample input**
```text
6 2 5
1 6 7 3 9 5
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Careful: greater than means `> X`, not `>= X`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 16: Parallel Count Less Than X

**Problem description**  
Count how many numbers are less than `X`.

**Data input**
```text
N T X
a1 ... aN
```

**Sample input**
```text
6 2 5
1 6 7 3 9 5
```

**Correct output**
```text
2
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Use the same template as count greater than.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 17: Parallel Replace Negative with Zero

**Problem description**  
Replace all negative values with zero.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
6 2
-1 2 -3 4 0 -5
```

**Correct output**
```text
0 2 0 4 0 0
```

**Suggested POSIX concepts**
- POSIX threads, in-place updates

**Tips & tricks**
- Each thread updates its own array range. No mutex needed.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 18: Parallel Absolute Values

**Problem description**  
Convert all numbers to absolute values.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
5 2
-3 4 -5 0 2
```

**Correct output**
```text
3 4 5 0 2
```

**Suggested POSIX concepts**
- POSIX threads, in-place updates

**Tips & tricks**
- Watch out for `INT_MIN` if using strict production-level code.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 19: Parallel Square Values

**Problem description**  
Replace each number with its square.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
5 2
1 -2 3 -4 5
```

**Correct output**
```text
1 4 9 16 25
```

**Suggested POSIX concepts**
- POSIX threads, in-place updates

**Tips & tricks**
- Use `long long` output if overflow is possible.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 20: Parallel Row Sum Small Matrix

**Problem description**  
Compute row sums of an `R x C` matrix.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
2 3 2
1 2 3
4 5 6
```

**Correct output**
```text
6
15
```

**Suggested POSIX concepts**
- POSIX threads, row partitioning

**Tips & tricks**
- Give whole rows to threads so each result row has one writer.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 21: Parallel Column Sum Small Matrix

**Problem description**  
Compute column sums of an `R x C` matrix.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
2 3 2
1 2 3
4 5 6
```

**Correct output**
```text
5 7 9
```

**Suggested POSIX concepts**
- POSIX threads, column partitioning

**Tips & tricks**
- Easiest: assign columns to threads.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 22: Parallel Matrix Add Constant

**Problem description**  
Add constant `X` to every matrix cell.

**Data input**
```text
R C T X
matrix
```

**Sample input**
```text
2 2 2 5
1 2
3 4
```

**Correct output**
```text
6 7
8 9
```

**Suggested POSIX concepts**
- POSIX threads, flat matrix indexing

**Tips & tricks**
- Flatten `(i,j)` as `i*C+j` to split work easily.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 23: Parallel Count Matrix Zeroes

**Problem description**  
Count zero cells in a matrix.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
2 3 2
0 1 0
2 0 3
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Treat the matrix as a flat array.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 24: Parallel Matrix Main Diagonal Sum

**Problem description**  
Compute the main diagonal sum of an `N x N` matrix.

**Data input**
```text
N T
matrix
```

**Sample input**
```text
3 2
1 2 3
4 5 6
7 8 9
```

**Correct output**
```text
15
```

**Suggested POSIX concepts**
- POSIX threads, diagonal partitioning

**Tips & tricks**
- There are only `N` diagonal elements. Partition indexes `0..N-1`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 25: Parallel Matrix Secondary Diagonal Sum

**Problem description**  
Compute the secondary diagonal sum of an `N x N` matrix.

**Data input**
```text
N T
matrix
```

**Sample input**
```text
3 2
1 2 3
4 5 6
7 8 9
```

**Correct output**
```text
15
```

**Suggested POSIX concepts**
- POSIX threads, diagonal partitioning

**Tips & tricks**
- Secondary diagonal cell for row `i` is column `N-1-i`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 26: Parallel Count Letter A

**Problem description**  
Count occurrences of letter `a` in a text line.

**Data input**
```text
T
text line
```

**Sample input**
```text
2
banana
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, string partitioning

**Tips & tricks**
- Process character ranges. Count lowercase `a` only unless you choose to extend it.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 27: Parallel Count Spaces

**Problem description**  
Count spaces in a text line.

**Data input**
```text
T
text line
```

**Sample input**
```text
3
hello parallel world
```

**Correct output**
```text
2
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Use `text[i] == ' '`. Keep local counts.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 28: Parallel Count Digits

**Problem description**  
Count digit characters in a text line.

**Data input**
```text
T
text line
```

**Sample input**
```text
2
abc123x9
```

**Correct output**
```text
4
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Use `isdigit((unsigned char)c)` from `<ctype.h>`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 29: Parallel Count Uppercase

**Problem description**  
Count uppercase letters in a text line.

**Data input**
```text
T
text line
```

**Sample input**
```text
2
AbC deF
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Use `isupper((unsigned char)c)`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 30: Parallel Count Lowercase

**Problem description**  
Count lowercase letters in a text line.

**Data input**
```text
T
text line
```

**Sample input**
```text
2
AbC deF
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Use `islower((unsigned char)c)`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 31: Parallel String Copy

**Problem description**  
Copy a string into another buffer using threads.

**Data input**
```text
T
text line
```

**Sample input**
```text
3
parallel copy
```

**Correct output**
```text
parallel copy
```

**Suggested POSIX concepts**
- POSIX threads, independent writes

**Tips & tricks**
- Allocate output length `strlen(text)+1`. Set the null terminator once in main.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 32: Parallel Replace Spaces with Underscores

**Problem description**  
Replace every space with `_`.

**Data input**
```text
T
text line
```

**Sample input**
```text
2
hello parallel world
```

**Correct output**
```text
hello_parallel_world
```

**Suggested POSIX concepts**
- POSIX threads, in-place string update

**Tips & tricks**
- Each thread updates its own character range.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 33: Parallel Count Vowels Basic

**Problem description**  
Count lowercase vowels in a text line.

**Data input**
```text
T
text line
```

**Sample input**
```text
2
hello world
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Check `a,e,i,o,u`. Decide whether to include uppercase; this version says lowercase only.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 34: Parallel First Half and Second Half Sums

**Problem description**  
Compute the sum of the first half and second half of an array using two threads.

**Data input**
```text
N
a1 ... aN
```

**Sample input**
```text
6
1 2 3 4 5 6
```

**Correct output**
```text
first=6
second=15
```

**Suggested POSIX concepts**
- POSIX threads, fixed two-thread split

**Tips & tricks**
- This is a simple exercise in passing different ranges to different threads.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 35: Parallel Sum of Squares

**Problem description**  
Compute the sum of squares of array values.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
4 2
1 2 3 4
```

**Correct output**
```text
30
```

**Suggested POSIX concepts**
- POSIX threads, partial sums

**Tips & tricks**
- Use `long long` for the partial sums.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 36: Parallel Count Multiples of K

**Problem description**  
Count numbers divisible by `K`.

**Data input**
```text
N T K
a1 ... aN
```

**Sample input**
```text
6 2 3
3 4 6 7 9 10
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Assume `K != 0`. Check `a[i] % K == 0`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 37: Parallel Index of First Negative

**Problem description**  
Find the smallest index containing a negative number.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
6 3
4 5 6 -1 2 -3
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local index search

**Tips & tricks**
- Each thread finds its local first negative. Main takes the minimum index.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 38: Parallel Index of Last Zero

**Problem description**  
Find the largest index containing zero.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
7 2
0 1 0 2 3 0 4
```

**Correct output**
```text
5
```

**Suggested POSIX concepts**
- POSIX threads, local index search

**Tips & tricks**
- Each thread finds its local last zero. Main takes the maximum index.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 39: Parallel Boolean All Positive

**Problem description**  
Check whether all numbers are positive.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
5 2
1 2 3 4 5
```

**Correct output**
```text
YES
```

**Suggested POSIX concepts**
- POSIX threads, local boolean flags

**Tips & tricks**
- Each thread sets `ok[tid]=0` if it finds a non-positive number.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 40: Parallel Boolean Any Negative

**Problem description**  
Check whether any number is negative.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
5 2
1 2 -3 4 5
```

**Correct output**
```text
YES
```

**Suggested POSIX concepts**
- POSIX threads, local boolean flags

**Tips & tricks**
- Avoid shared early-stop at first. Local flags are simpler.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 41: Parallel Clamp Values

**Problem description**  
Clamp all values to interval `[L, R]`.

**Data input**
```text
N T L R
a1 ... aN
```

**Sample input**
```text
6 2 0 10
-5 3 20 7 0 11
```

**Correct output**
```text
0 3 10 7 0 10
```

**Suggested POSIX concepts**
- POSIX threads, in-place updates

**Tips & tricks**
- For each value: if below `L`, set to `L`; if above `R`, set to `R`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 42: Parallel Count Characters Equal to Target

**Problem description**  
Count occurrences of a target character.

**Data input**
```text
T
target
text line
```

**Sample input**
```text
3
x
axbxxc
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Read the target as a char. Then read the full text line.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 43: Parallel Reverse Array by Chunks

**Problem description**  
Create a reversed copy of an array.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
5 2
1 2 3 4 5
```

**Correct output**
```text
5 4 3 2 1
```

**Suggested POSIX concepts**
- POSIX threads, independent output writes

**Tips & tricks**
- For index `i`, output index is `N-1-i`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 44: Parallel Matrix Copy

**Problem description**  
Copy an `R x C` matrix.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
2 2 2
1 2
3 4
```

**Correct output**
```text
1 2
3 4
```

**Suggested POSIX concepts**
- POSIX threads, flat partitioning

**Tips & tricks**
- Flatten matrix memory and copy ranges.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 45: Parallel Matrix Elementwise Product

**Problem description**  
Compute elementwise product of two matrices.

**Data input**
```text
R C T
A
B
```

**Sample input**
```text
2 2 2
1 2
3 4
5 6
7 8
```

**Correct output**
```text
5 12
21 32
```

**Suggested POSIX concepts**
- POSIX threads, independent writes

**Tips & tricks**
- Same as array elementwise product, but print as matrix.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 46: Parallel Count Lines Longer Than L

**Problem description**  
Given `N` text lines, count how many have length greater than `L`.

**Data input**
```text
N T L
lines
```

**Sample input**
```text
4 2 3
hi
hello
abcd
x
```

**Correct output**
```text
2
```

**Suggested POSIX concepts**
- POSIX threads, line length array

**Tips & tricks**
- Read lines first, compute lengths, then parallelize counting.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 47: Parallel Sum Each Pair

**Problem description**  
Given two arrays, compute the sum of each pair as output.

**Data input**
```text
N T
A
B
```

**Sample input**
```text
3 2
1 2 3
4 5 6
```

**Correct output**
```text
5 7 9
```

**Suggested POSIX concepts**
- POSIX threads, independent output writes

**Tips & tricks**
- This is a clean template for thread argument structs.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 48: Parallel Count ASCII Punctuation

**Problem description**  
Count punctuation characters in a text line.

**Data input**
```text
T
text line
```

**Sample input**
```text
2
Hello, world!
```

**Correct output**
```text
2
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Use `ispunct((unsigned char)c)`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 49: Parallel Simple Checksum

**Problem description**  
Compute checksum: sum of all character ASCII codes.

**Data input**
```text
T
text line
```

**Sample input**
```text
2
ABC
```

**Correct output**
```text
198
```

**Suggested POSIX concepts**
- POSIX threads, partial sums

**Tips & tricks**
- Characters `A+B+C` are `65+66+67=198`. Use `unsigned char`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 50: Parallel Count Matrix Values in Range

**Problem description**  
Count matrix values between `L` and `R`, inclusive.

**Data input**
```text
Rows Cols T L R
matrix
```

**Sample input**
```text
2 3 2 3 6
1 3 5
6 7 2
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Flatten the matrix and test `L <= value <= R`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.
