# Medium POSIX Threads in C — 50 Numeric, Matrix, and Text Problems

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

## Problem 1: Parallel Histogram 0-9

**Problem description**  
Given digits in range `0..9`, compute the frequency of each digit.

**Data input**
```text
N T
d1 d2 ... dN
```

**Sample input**
```text
12 3
0 1 2 2 3 4 4 4 9 9 0 1
```

**Correct output**
```text
0:2
1:2
2:2
3:1
4:3
5:0
6:0
7:0
8:0
9:2
```

**Suggested POSIX concepts**
- POSIX threads, local histograms, reduction

**Tips & tricks**
- Use `local[tid][10]`, then merge in main. This avoids mutex contention.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 2: Parallel Letter Frequency

**Problem description**  
Count frequency of lowercase letters `a-z` in a text line.

**Data input**
```text
T
text line
```

**Sample input**
```text
3
hello parallel
```

**Correct output**
```text
a:2
e:2
h:1
l:4
o:1
p:1
r:1
```

**Suggested POSIX concepts**
- POSIX threads, local histograms

**Tips & tricks**
- Print only letters with nonzero counts. Ignore spaces.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 3: Parallel Word Count

**Problem description**  
Count words separated by spaces in one text line.

**Data input**
```text
T
text line
```

**Sample input**
```text
3
POSIX threads are useful
```

**Correct output**
```text
4
```

**Suggested POSIX concepts**
- POSIX threads, boundary handling

**Tips & tricks**
- Count a word start when current char is non-space and previous char is space or index is 0.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 4: Parallel Average and Count Above

**Problem description**  
Compute average and count values greater than the average.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
6 3
1 2 3 4 5 6
```

**Correct output**
```text
average=3.500000
count=3
```

**Suggested POSIX concepts**
- POSIX threads, barrier or two-phase computation

**Tips & tricks**
- Phase 1 computes sum. Phase 2 counts values above average.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 5: Parallel Dot Product

**Problem description**  
Compute dot product of two integer arrays.

**Data input**
```text
N T
A
B
```

**Sample input**
```text
5 2
1 2 3 4 5
10 20 30 40 50
```

**Correct output**
```text
550
```

**Suggested POSIX concepts**
- POSIX threads, partial sums

**Tips & tricks**
- Use `long long partial[T]`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 6: Parallel Matrix Addition

**Problem description**  
Add two matrices.

**Data input**
```text
R C T
A
B
```

**Sample input**
```text
2 3 2
1 2 3
4 5 6
10 20 30
40 50 60
```

**Correct output**
```text
11 22 33
44 55 66
```

**Suggested POSIX concepts**
- POSIX threads, flat partitioning

**Tips & tricks**
- Flatten `R*C` cells and split indexes.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 7: Parallel Matrix Transpose

**Problem description**  
Transpose an `R x C` matrix.

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
1 4
2 5
3 6
```

**Suggested POSIX concepts**
- POSIX threads, independent output writes

**Tips & tricks**
- Write `out[j][i] = in[i][j]`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 8: Parallel Matrix Border Sum

**Problem description**  
Compute sum of border cells.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
3 4 2
1 2 3 4
5 6 7 8
9 10 11 12
```

**Correct output**
```text
65
```

**Suggested POSIX concepts**
- POSIX threads, flat scan

**Tips & tricks**
- A cell is border if row/column is first or last.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 9: Parallel Matrix Trace Batch

**Problem description**  
Given `K` square matrices, compute the trace of each.

**Data input**
```text
K N T
matrices
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
5
13
```

**Suggested POSIX concepts**
- POSIX threads, partition by matrix

**Tips & tricks**
- Assign matrix indexes to threads; each trace has one writer.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 10: Parallel Prime Counter

**Problem description**  
Count prime numbers in an array.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
8 2
2 3 4 5 6 7 8 9
```

**Correct output**
```text
4
```

**Suggested POSIX concepts**
- POSIX threads, local counters

**Tips & tricks**
- Trial division up to `sqrt(n)` is enough.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 11: Parallel GCD Pair Sum

**Problem description**  
Compute sum of `gcd(A[i], B[i])`.

**Data input**
```text
N T
A
B
```

**Sample input**
```text
4 2
12 18 7 20
8 24 14 30
```

**Correct output**
```text
27
```

**Suggested POSIX concepts**
- POSIX threads, partial sums, Euclidean algorithm

**Tips & tricks**
- Keep GCD iterative and use local sums.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 12: Parallel Prefix Sum by Chunks

**Problem description**  
Compute inclusive prefix sums.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
8 4
1 2 3 4 5 6 7 8
```

**Correct output**
```text
1 3 6 10 15 21 28 36
```

**Suggested POSIX concepts**
- POSIX threads, barriers, chunk totals

**Tips & tricks**
- Compute local prefix and chunk sums, compute offsets, then add offsets.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 13: Parallel Moving Average

**Problem description**  
Compute moving average with window size `W`.

**Data input**
```text
N W T
a1 ... aN
```

**Sample input**
```text
5 3 2
1 2 3 4 5
```

**Correct output**
```text
2.000000 3.000000 4.000000
```

**Suggested POSIX concepts**
- POSIX threads, prefix sums

**Tips & tricks**
- Build prefix sum first, parallelize output window indexes.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 14: Parallel Hamming Distance

**Problem description**  
Compute Hamming distance between equal-length strings.

**Data input**
```text
T
s1
s2
```

**Sample input**
```text
3
karolin
kathrin
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local mismatch counts

**Tips & tricks**
- Partition string indexes.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 15: Parallel Palindrome Check

**Problem description**  
Check if a cleaned string is a palindrome ignoring spaces and case.

**Data input**
```text
T
text line
```

**Sample input**
```text
3
Never odd or even
```

**Correct output**
```text
PALINDROME
```

**Suggested POSIX concepts**
- POSIX threads, local flags

**Tips & tricks**
- Clean the string sequentially first. Then check mirrored positions in parallel.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 16: Parallel Target Word Count

**Problem description**  
Count occurrences of a target word in a list of words.

**Data input**
```text
N T
target
words
```

**Sample input**
```text
8 3
cat
dog cat bird cat cat fish dog cat
```

**Correct output**
```text
4
```

**Suggested POSIX concepts**
- POSIX threads, string comparison

**Tips & tricks**
- Read words into an array. Use `strcmp`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 17: Parallel Longest Word Length

**Problem description**  
Find the length of the longest word in text.

**Data input**
```text
T
text line
```

**Sample input**
```text
3
parallel synchronization mutex
```

**Correct output**
```text
15
```

**Suggested POSIX concepts**
- POSIX threads, token lengths

**Tips & tricks**
- Simpler: tokenize into word lengths first, then parallelize max.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 18: Parallel CSV Column Sum

**Problem description**  
Compute sum of selected column in an integer table.

**Data input**
```text
R C T target_col
rows
```

**Sample input**
```text
3 4 2 2
1 2 3 4
5 6 7 8
9 10 11 12
```

**Correct output**
```text
21
```

**Suggested POSIX concepts**
- POSIX threads, row partitioning

**Tips & tricks**
- Target column is 0-based.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 19: Parallel Log Severity Counter

**Problem description**  
Count lines starting with `INFO`, `WARN`, and `ERROR`.

**Data input**
```text
N T
lines
```

**Sample input**
```text
5 2
INFO started
WARN slow
ERROR failed
INFO done
ERROR timeout
```

**Correct output**
```text
INFO=2
WARN=1
ERROR=2
```

**Suggested POSIX concepts**
- POSIX threads, per-thread counters

**Tips & tricks**
- Read all lines first. Use `strncmp`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 20: Parallel Character Class Counter

**Problem description**  
Count uppercase, lowercase, digits, spaces, and other characters.

**Data input**
```text
T
text line
```

**Sample input**
```text
3
Abc 123!
```

**Correct output**
```text
uppercase=1
lowercase=2
digits=3
spaces=1
other=1
```

**Suggested POSIX concepts**
- POSIX threads, local class counters

**Tips & tricks**
- Use `<ctype.h>` and cast to `unsigned char`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 21: Parallel Matrix Symmetry Check

**Problem description**  
Check whether an `N x N` matrix is symmetric.

**Data input**
```text
N T
matrix
```

**Sample input**
```text
3 2
1 2 3
2 5 6
3 6 9
```

**Correct output**
```text
SYMMETRIC
```

**Suggested POSIX concepts**
- POSIX threads, local flags

**Tips & tricks**
- Only check cells above the main diagonal.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 22: Parallel Matrix Threshold Count

**Problem description**  
Count matrix values greater than `X`.

**Data input**
```text
R C T X
matrix
```

**Sample input**
```text
3 3 2 5
1 6 7
2 5 8
9 0 4
```

**Correct output**
```text
4
```

**Suggested POSIX concepts**
- POSIX threads, flat matrix scan

**Tips & tricks**
- Use local counts.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 23: Parallel Row Maximums

**Problem description**  
Compute maximum value of each matrix row.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
3 3 2
1 5 2
9 3 4
0 8 7
```

**Correct output**
```text
5
9
8
```

**Suggested POSIX concepts**
- POSIX threads, row partitioning

**Tips & tricks**
- Each row result has one writer.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 24: Parallel Column Maximums

**Problem description**  
Compute maximum value of each matrix column.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
3 3 2
1 5 2
9 3 4
0 8 7
```

**Correct output**
```text
9 8 7
```

**Suggested POSIX concepts**
- POSIX threads, column partitioning

**Tips & tricks**
- Assign columns to threads for simpler writes.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 25: Parallel Normalize Vector

**Problem description**  
Normalize a vector by Euclidean norm.

**Data input**
```text
N T
v1 ... vN
```

**Sample input**
```text
3 2
3 4 0
```

**Correct output**
```text
0.600000 0.800000 0.000000
```

**Suggested POSIX concepts**
- POSIX threads, barrier, partial sums

**Tips & tricks**
- Compute sum of squares, compute norm, then divide.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 26: Parallel Top Two Distinct

**Problem description**  
Find largest and second largest distinct values.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
9 3
5 9 1 9 7 3 7 2 4
```

**Correct output**
```text
9 7
```

**Suggested POSIX concepts**
- POSIX threads, local top-two, reduction

**Tips & tricks**
- Each thread tracks two distinct values.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 27: Parallel Pair Sum Count

**Problem description**  
Count pairs whose sum equals `X`.

**Data input**
```text
N T X
a1 ... aN
```

**Sample input**
```text
6 3 10
1 9 5 5 3 7
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, pair partitioning

**Tips & tricks**
- Use `O(N^2)` and assign outer-loop ranges.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 28: Parallel Inversion Count

**Problem description**  
Count inversions `i<j` and `a[i]>a[j]`.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
5 2
2 4 1 3 5
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, local pair counts

**Tips & tricks**
- Use `long long` for result.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 29: Parallel DNA GC Content

**Problem description**  
Compute GC percentage of a DNA string.

**Data input**
```text
T
DNA_string
```

**Sample input**
```text
4
ACGTGGCA
```

**Correct output**
```text
62.500000
```

**Suggested POSIX concepts**
- POSIX threads, local counts

**Tips & tricks**
- Count `G` and `C`, divide by total length.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 30: Parallel Text Pattern Positions

**Problem description**  
Find all starting positions of a pattern in text.

**Data input**
```text
T
pattern
text
```

**Sample input**
```text
3
aba
ababa aba
```

**Correct output**
```text
0 2 6
```

**Suggested POSIX concepts**
- POSIX threads, candidate range partitioning

**Tips & tricks**
- Test every candidate start position; merge results in order.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 31: Parallel Replace Character

**Problem description**  
Replace all occurrences of one character with another and count replacements.

**Data input**
```text
T
A B
text
```

**Sample input**
```text
2
a x
banana
```

**Correct output**
```text
3
bxnxnx
```

**Suggested POSIX concepts**
- POSIX threads, string partitioning

**Tips & tricks**
- Each thread writes to a different output range.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 32: Parallel Matrix Row Normalization

**Problem description**  
Normalize each row by its row sum.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
2 3 2
1 1 2
2 3 5
```

**Correct output**
```text
0.250000 0.250000 0.500000
0.200000 0.300000 0.500000
```

**Suggested POSIX concepts**
- POSIX threads, row partitioning

**Tips & tricks**
- Give complete rows to threads.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 33: Parallel Median of Rows

**Problem description**  
Compute median of each row. `C` is odd.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
3 5 2
5 1 3 2 4
9 7 8 6 5
10 20 30 40 50
```

**Correct output**
```text
3
7
30
```

**Suggested POSIX concepts**
- POSIX threads, row sorting

**Tips & tricks**
- Copy each row before sorting if original must be preserved.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 34: Parallel Unique Count After Sort

**Problem description**  
Count distinct integers.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
8 2
1 2 2 3 4 4 4 5
```

**Correct output**
```text
5
```

**Suggested POSIX concepts**
- POSIX threads, sorted scan

**Tips & tricks**
- Sort sequentially with `qsort`, then parallelize unique-boundary counting.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 35: Parallel Token Length Histogram

**Problem description**  
Compute histogram of word lengths from `1` to `L`, plus `L+`.

**Data input**
```text
T L
text line
```

**Sample input**
```text
3 5
a bb ccc dddd eeeee ffffff
```

**Correct output**
```text
1:1
2:1
3:1
4:1
5:1
5+:1
```

**Suggested POSIX concepts**
- POSIX threads, tokenization, local histograms

**Tips & tricks**
- Tokenize into lengths first; parallelize counting.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 36: Parallel Anagram Pair Count

**Problem description**  
Count pairs of words that are anagrams.

**Data input**
```text
N T
words
```

**Sample input**
```text
5 2
listen
silent
enlist
cat
tac
```

**Correct output**
```text
4
```

**Suggested POSIX concepts**
- POSIX threads, pair partitioning

**Tips & tricks**
- Precompute 26-letter signatures.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 37: Parallel Sparse Vector Dot

**Problem description**  
Compute dot product of sparse vectors sorted by index.

**Data input**
```text
N1 N2 T
pairs1
pairs2
```

**Sample input**
```text
3 4 2
0 5
3 7
8 2
1 10
3 4
8 6
9 1
```

**Correct output**
```text
40
```

**Suggested POSIX concepts**
- POSIX threads, binary search, partial sums

**Tips & tricks**
- For each first-vector index, binary-search the second vector.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 38: Parallel Polynomial Evaluation

**Problem description**  
Evaluate polynomial at multiple `x` values.

**Data input**
```text
D M T
coefficients
x values
```

**Sample input**
```text
2 3 2
1 2 3
0 1 2
```

**Correct output**
```text
1 6 17
```

**Suggested POSIX concepts**
- POSIX threads, Horner method

**Tips & tricks**
- Coefficients are `c0..cD`. Polynomial is `1+2x+3x^2`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 39: Parallel Matrix Diagonal Difference

**Problem description**  
Compute absolute difference between main and secondary diagonal sums.

**Data input**
```text
N T
matrix
```

**Sample input**
```text
3 2
11 2 4
4 5 6
10 8 -12
```

**Correct output**
```text
15
```

**Suggested POSIX concepts**
- POSIX threads, diagonal partitioning

**Tips & tricks**
- Compute two local sums per thread.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 40: Parallel Equal Row Pair Count

**Problem description**  
Count pairs of equal rows in a matrix.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
4 3 2
1 2 3
4 5 6
1 2 3
1 2 3
```

**Correct output**
```text
3
```

**Suggested POSIX concepts**
- POSIX threads, pair comparison

**Tips & tricks**
- Assign outer row ranges to threads.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 41: Parallel Longest Increasing Run

**Problem description**  
Find the longest contiguous strictly increasing run.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
9 3
1 2 3 2 3 4 5 1 2
```

**Correct output**
```text
4
```

**Suggested POSIX concepts**
- POSIX threads, chunk summaries

**Tips & tricks**
- Each chunk reports best, prefix, suffix, first, last; merge summaries.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 42: Parallel Maximum Subarray Sum

**Problem description**  
Find maximum subarray sum.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
8 2
-2 -3 4 -1 -2 1 5 -3
```

**Correct output**
```text
7
```

**Suggested POSIX concepts**
- POSIX threads, segment summaries

**Tips & tricks**
- Each chunk computes total, best prefix, best suffix, best subarray.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 43: Parallel 3x3 Matrix Convolution

**Problem description**  
Apply a 3x3 kernel, border output cells remain zero.

**Data input**
```text
R C T
matrix
kernel
```

**Sample input**
```text
3 3 2
1 2 3
4 5 6
7 8 9
0 0 0
0 1 0
0 0 0
```

**Correct output**
```text
0 0 0
0 5 0
0 0 0
```

**Suggested POSIX concepts**
- POSIX threads, read-only input, output matrix

**Tips & tricks**
- Do not overwrite input during convolution.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 44: Parallel K-mer Frequency Basic

**Problem description**  
Count distinct DNA K-mers in first-seen order.

**Data input**
```text
T K
DNA_string
```

**Sample input**
```text
3 2
ACGTAC
```

**Correct output**
```text
AC:2
CG:1
GT:1
TA:1
```

**Suggested POSIX concepts**
- POSIX threads, local tables or mutex table

**Tips & tricks**
- For 1 hour, use simple arrays of strings instead of a hash table.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 45: Parallel Range Sum Queries

**Problem description**  
Answer `Q` range sum queries using a prefix sum.

**Data input**
```text
N Q T
a1 ... aN
queries
```

**Sample input**
```text
5 3 2
1 2 3 4 5
0 2
1 3
2 4
```

**Correct output**
```text
6
9
12
```

**Suggested POSIX concepts**
- POSIX threads, prefix array, query partitioning

**Tips & tricks**
- Build prefix sequentially, answer queries in parallel.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 46: Parallel Range Even Queries

**Problem description**  
Answer queries asking how many even numbers are in `[L,R]`.

**Data input**
```text
N Q T
a1 ... aN
queries
```

**Sample input**
```text
6 3 2
1 2 4 5 6 8
0 2
1 4
3 5
```

**Correct output**
```text
2
3
2
```

**Suggested POSIX concepts**
- POSIX threads, prefix count, query partitioning

**Tips & tricks**
- Build prefix of even counts.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 47: Parallel Number Classification

**Problem description**  
Classify numbers as negative, zero, even positive, odd positive.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
8 2
-3 0 2 5 -1 8 7 0
```

**Correct output**
```text
negative=2
zero=2
even_positive=2
odd_positive=2
```

**Suggested POSIX concepts**
- POSIX threads, local category counters

**Tips & tricks**
- Use `counts[tid][4]`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 48: Parallel Divisibility Matrix

**Problem description**  
Build binary matrix where `A[i]` is divisible by `B[j]`.

**Data input**
```text
N M T
A
B
```

**Sample input**
```text
3 4 2
6 10 15
2 3 5 7
```

**Correct output**
```text
1 1 0 0
1 0 1 0
0 1 1 0
```

**Suggested POSIX concepts**
- POSIX threads, flat output cells

**Tips & tricks**
- Convert flat output index to `(i,j)`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 49: Parallel Numerical Integration

**Problem description**  
Approximate integral of `f(x)=x*x` on `[A,B]` with rectangles.

**Data input**
```text
A B N T
```

**Sample input**
```text
0 1 100000 4
```

**Correct output**
```text
approximately 0.333333
```

**Suggested POSIX concepts**
- POSIX threads, floating partial sums

**Tips & tricks**
- Use midpoint rule and compare with tolerance.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.


---

## Problem 50: Parallel Distance from Origin

**Problem description**  
Given `N` 2D points `(x, y)`, compute the squared distance `x*x + y*y` for every point.

**Data input**
```text
N T
x1 y1
x2 y2
...
xN yN
```

**Sample input**
```text
4 2
0 0
1 2
3 4
-2 5
```

**Correct output**
```text
0
5
25
29
```

**Suggested POSIX concepts**
- POSIX threads, independent output writes

**Tips & tricks**
- Each thread processes a range of points and writes to `dist[i]`.
- Use squared distance to avoid floating-point `sqrt`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.
