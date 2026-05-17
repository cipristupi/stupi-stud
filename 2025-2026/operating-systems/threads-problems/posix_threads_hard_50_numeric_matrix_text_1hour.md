# Hard POSIX Threads in C — 50 Numeric, Matrix, and Text Problems

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

## Problem 1: Parallel Matrix Multiplication

**Problem description**  
Multiply `A(RxM)` by `B(MxC)`.

**Data input**
```text
R M C T
A
B
```

**Sample input**
```text
2 3 2 2
1 2 3
4 5 6
7 8
9 10
11 12
```

**Correct output**
```text
58 64
139 154
```

**Suggested POSIX concepts**
- POSIX threads, row partitioning

**Tips & tricks**
- Assign output rows to threads. Each output cell has one writer.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 2: Parallel Prefix Sum with Barrier

**Problem description**  
Compute inclusive prefix sum using thread phases.

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
- Barriers, per-chunk sums, POSIX threads

**Tips & tricks**
- Barrier after local prefixes, compute offsets, barrier before applying offsets.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 3: Parallel Matrix Saddle Points

**Problem description**  
Find cells that are minimum in their row and maximum in their column.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
3 3 2
3 1 3
3 2 4
3 1 5
```

**Correct output**
```text
0 1 1
```

**Suggested POSIX concepts**
- Barriers, row mins, column maxes

**Tips & tricks**
- Use three phases: row mins, column maxes, collect matches.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 4: Parallel Iterative Matrix Relaxation

**Problem description**  
Run `K` iterations where each non-border cell becomes average of itself and four neighbors.

**Data input**
```text
R C K T
matrix
```

**Sample input**
```text
3 3 1 2
1 1 1
1 9 1
1 1 1
```

**Correct output**
```text
1 1 1
1 2 1
1 1 1
```

**Suggested POSIX concepts**
- Barriers, double buffering

**Tips & tricks**
- Use `current` and `next`; never update in-place during an iteration.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 5: Parallel Maximum Subarray with Segment Merge

**Problem description**  
Find maximum subarray sum using per-chunk segment summaries.

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
- Threads, segment summaries, deterministic merge

**Tips & tricks**
- Each chunk returns total, best prefix, best suffix, best subarray.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 6: Parallel Longest Increasing Run with Boundary Merge

**Problem description**  
Find longest contiguous strictly increasing run.

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
- Threads, chunk summaries

**Tips & tricks**
- Store prefix length, suffix length, best length, first and last value.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 7: Parallel Top-K Largest

**Problem description**  
Find top `K` largest values.

**Data input**
```text
N K T
a1 ... aN
```

**Sample input**
```text
8 3 2
4 9 1 7 9 3 8 2
```

**Correct output**
```text
9 9 8
```

**Suggested POSIX concepts**
- Threads, local top-K arrays, merge

**Tips & tricks**
- Each thread keeps local sorted top-K. Main merges candidates.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 8: Parallel Inversion Count

**Problem description**  
Count pairs `i<j` with `a[i]>a[j]`.

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
- Threads, pair partitioning

**Tips & tricks**
- Use O(N^2) for 1-hour version. Assign outer-loop ranges.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 9: Parallel Pair Sum Count

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
- Threads, local counters

**Tips & tricks**
- Assign outer index ranges; count all `j>i`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 10: Parallel Anagram Pair Count

**Problem description**  
Count pairs of anagram words.

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
- Threads, signatures, pair counting

**Tips & tricks**
- Precompute 26-count signatures. Compare signatures in pair loops.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 11: Parallel Text Pattern Search with Overlap

**Problem description**  
Find all starting positions of a pattern in a text.

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
- Threads, per-thread result buffers

**Tips & tricks**
- Partition candidate start positions, not raw text chunks.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 12: Parallel K-mer Frequency

**Problem description**  
Count distinct DNA K-mers and print in first-seen order.

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
- Threads, local tables, merge

**Tips & tricks**
- Local tables reduce locking; merge sequentially for deterministic first-seen order.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 13: Parallel Sparse Vector Dot Product

**Problem description**  
Compute dot product of two sparse vectors sorted by index.

**Data input**
```text
N1 N2 T
idx value pairs 1
idx value pairs 2
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
- Threads, binary search, partial sums

**Tips & tricks**
- For each pair in vector 1, binary-search vector 2.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 14: Parallel Matrix 3x3 Convolution

**Problem description**  
Apply 3x3 kernel, border output cells remain zero.

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
- Threads, separate input/output matrices

**Tips & tricks**
- Only compute inner cells. Do not overwrite input.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 15: Parallel Median of Each Row

**Problem description**  
Compute median for each row of a matrix; columns count is odd.

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
- Threads, row partitioning, qsort

**Tips & tricks**
- Copy row to temporary buffer, sort, take middle.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 16: Parallel Row Normalization

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
- Threads, row partitioning

**Tips & tricks**
- Assign full rows to threads to avoid synchronization.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 17: Parallel Matrix Symmetry Check

**Problem description**  
Check if matrix is symmetric.

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
- Threads, local boolean flags

**Tips & tricks**
- Only check upper triangle. Main combines flags.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 18: Parallel Equal Row Detector

**Problem description**  
Count equal row pairs.

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
- Threads, pair comparisons

**Tips & tricks**
- Use O(R^2*C), partition outer row index.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 19: Parallel Unique Count After Sorting

**Problem description**  
Count distinct numbers in an array.

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
- qsort, threads, boundary counting

**Tips & tricks**
- Sort first, then count unique boundaries in parallel.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 20: Parallel Range Sum Queries

**Problem description**  
Answer many range sum queries.

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
- Prefix sums, threads

**Tips & tricks**
- Build prefix once, then each query is O(1). Parallelize queries.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 21: Parallel Range Minimum Queries Simple

**Problem description**  
Answer range minimum queries using direct scanning.

**Data input**
```text
N Q T
a1 ... aN
queries
```

**Sample input**
```text
5 3 2
5 2 8 1 4
0 2
1 3
3 4
```

**Correct output**
```text
2
1
1
```

**Suggested POSIX concepts**
- Threads, query partitioning

**Tips & tricks**
- For 1 hour, scan each query range. Do not build sparse table.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 22: Parallel Range Even Count Queries

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
- Prefix counts, threads

**Tips & tricks**
- Prefix array stores number of evens up to each index.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 23: Parallel Token Length Histogram

**Problem description**  
Compute word-length histogram with bucket `L+`.

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
- Threads, tokenization, local histograms

**Tips & tricks**
- Tokenize first, then parallelize over token lengths.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 24: Parallel Log Severity and Longest Message

**Problem description**  
Count log severities and find longest message length.

**Data input**
```text
N T
lines
```

**Sample input**
```text
4 2
INFO start
ERROR failure happened
WARN slow
INFO ok
```

**Correct output**
```text
INFO=2
WARN=1
ERROR=1
longest=22
```

**Suggested POSIX concepts**
- Threads, local counters, local max

**Tips & tricks**
- Read full lines. Severity is prefix before first space.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 25: Parallel Character Frequency with Mutex Buckets

**Problem description**  
Count ASCII character frequencies using bucket mutexes.

**Data input**
```text
T
text line
```

**Sample input**
```text
3
abca!
```

**Correct output**
```text
!:1
a:2
b:1
c:1
```

**Suggested POSIX concepts**
- Mutexes, bucket locking

**Tips & tricks**
- For learning mutexes, lock only the bucket for the character. For speed, use local histograms.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 26: Parallel Bounded Min-Max Queue over Array Chunks

**Problem description**  
Threads process chunks and update a shared global min/max safely.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
8 3
5 -2 7 9 0 3 -8 4
```

**Correct output**
```text
min=-8 max=9
```

**Suggested POSIX concepts**
- Mutex, local min/max

**Tips & tricks**
- Compute local min/max first, then lock once to update global values.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 27: Parallel Ordered Thread Output

**Problem description**  
Each thread computes a chunk sum, but outputs must appear in thread id order.

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
thread 0: 3
thread 1: 7
thread 2: 11
```

**Suggested POSIX concepts**
- Condition variables, mutex

**Tips & tricks**
- Use `next_to_print`. Threads wait until `tid == next_to_print`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 28: Parallel Producer-Consumer Sum of Numbers

**Problem description**  
Producer thread reads numbers into a bounded buffer; consumer threads sum them.

**Data input**
```text
N C T
a1 ... aN
```

**Sample input**
```text
6 2 2
1 2 3 4 5 6
```

**Correct output**
```text
21
```

**Suggested POSIX concepts**
- Condition variables, mutex, bounded buffer

**Tips & tricks**
- Keep buffer small. Use `not_empty` and `not_full`. Send stop signals after producer finishes.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 29: Parallel Producer-Consumer Word Length Sum

**Problem description**  
Producer inserts words into a bounded buffer; consumers sum word lengths.

**Data input**
```text
N C T
words
```

**Sample input**
```text
5 2 2
one three seven two four
```

**Correct output**
```text
22
```

**Suggested POSIX concepts**
- Condition variables, mutex

**Tips & tricks**
- Use a done flag and broadcast when producer finishes.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 30: Parallel Readers Count Word Occurrences with RW Lock

**Problem description**  
Multiple reader threads count target word while one writer thread replaces one word before counting starts.

**Data input**
```text
N T
target
old new
words
```

**Sample input**
```text
6 2
cat
dog cat dog bird dog cat
dog cat
```

**Correct output**
```text
4
```

**Suggested POSIX concepts**
- RW lock

**Tips & tricks**
- Apply writer update with write lock. Readers count with read lock.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 31: Parallel Read-Mostly Array Sum with RW Lock

**Problem description**  
Support point updates and sum queries over an array.

**Data input**
```text
N Q T
array
operations
```

**Sample input**
```text
5 4 3
1 2 3 4 5
S 0 4
U 2 10
S 1 3
S 2 2
```

**Correct output**
```text
15
16
10
```

**Suggested POSIX concepts**
- RW lock, optional query partitioning

**Tips & tricks**
- Use read lock for sums and write lock for updates.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 32: Parallel Barrier-Based Two-Pass Standardization

**Problem description**  
Given values, compute z-scores `(x-mean)/stddev`.

**Data input**
```text
N T
values
```

**Sample input**
```text
3 2
1 2 3
```

**Correct output**
```text
-1.224745 0.000000 1.224745
```

**Suggested POSIX concepts**
- Barriers, partial sums

**Tips & tricks**
- Phase 1 mean, phase 2 variance, phase 3 output.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 33: Parallel Matrix Column Normalization

**Problem description**  
Normalize each column by its column sum.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
2 3 2
1 2 3
4 8 9
```

**Correct output**
```text
0.200000 0.200000 0.250000
0.800000 0.800000 0.750000
```

**Suggested POSIX concepts**
- Threads, column sums, barrier

**Tips & tricks**
- Compute column sums first, then divide cells.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 34: Parallel Matrix Threshold Binarization

**Problem description**  
Convert matrix to 1 if value >= threshold else 0, then count ones.

**Data input**
```text
R C T X
matrix
```

**Sample input**
```text
2 3 2 5
1 5 7
3 9 2
```

**Correct output**
```text
0 1 1
0 1 0
ones=3
```

**Suggested POSIX concepts**
- Threads, independent writes, local count

**Tips & tricks**
- Each thread writes output cells and local count.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 35: Parallel Matrix Diagonal Difference Batch

**Problem description**  
For each of `K` square matrices, compute diagonal difference.

**Data input**
```text
K N T
matrices
```

**Sample input**
```text
1 3 2
11 2 4
4 5 6
10 8 -12
```

**Correct output**
```text
15
```

**Suggested POSIX concepts**
- Threads, per-matrix outputs

**Tips & tricks**
- Parallelize by matrix or by diagonal index.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 36: Parallel Divisibility Matrix

**Problem description**  
Build matrix `M[i][j]=1` if `A[i]` divisible by `B[j]`.

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
- Threads, flat output partitioning

**Tips & tricks**
- Assume no divisor is zero.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 37: Parallel Polynomial Batch Evaluation

**Problem description**  
Evaluate polynomial at many `x` values.

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
- Threads, Horner method

**Tips & tricks**
- Each thread handles a range of x-values.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 38: Parallel Numerical Integration

**Problem description**  
Approximate integral of `x*x` using midpoint rectangles.

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
- Threads, partial floating sums

**Tips & tricks**
- Output with `%.6f`; accept tolerance.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 39: Parallel Monte Carlo Pi

**Problem description**  
Estimate Pi using deterministic per-thread seeds.

**Data input**
```text
N T
```

**Sample input**
```text
100000 4
```

**Correct output**
```text
approximately 3.14
```

**Suggested POSIX concepts**
- Threads, rand_r, local counts

**Tips & tricks**
- Use `rand_r(&seed)` with seed based on `tid`.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 40: Parallel Sliding Window Maximum Simple

**Problem description**  
Compute max for every window of size `W` using direct scanning.

**Data input**
```text
N W T
a1 ... aN
```

**Sample input**
```text
6 3 2
1 3 2 5 4 6
```

**Correct output**
```text
3 5 5 6
```

**Suggested POSIX concepts**
- Threads, output index partitioning

**Tips & tricks**
- For 1 hour, O(N*W) is fine.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 41: Parallel Sliding Window Sum

**Problem description**  
Compute sum for every window of size `W`.

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
6 9 12
```

**Suggested POSIX concepts**
- Prefix sums, threads

**Tips & tricks**
- Use prefix sums and parallelize output windows.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 42: Parallel Matrix Local Maxima

**Problem description**  
Find cells greater than their up/down/left/right neighbors.

**Data input**
```text
R C T
matrix
```

**Sample input**
```text
3 3 2
1 2 1
2 9 2
1 2 1
```

**Correct output**
```text
1 1 9
```

**Suggested POSIX concepts**
- Threads, result buffers

**Tips & tricks**
- Ignore border cells for simplicity.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 43: Parallel Text Line Statistics

**Problem description**  
Given lines, compute min/max/average length and count empty lines.

**Data input**
```text
N T
lines
```

**Sample input**
```text
4 2
abc
hello

parallel
```

**Correct output**
```text
min=0
max=8
avg=4.000000
empty=1
```

**Suggested POSIX concepts**
- Threads, local stats

**Tips & tricks**
- Read lines carefully with `fgets`; preserve empty line.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 44: Parallel Repeated Word Detector

**Problem description**  
Print words appearing more than once, in order of first repeated detection.

**Data input**
```text
N T
words
```

**Sample input**
```text
8 2
apple pear apple plum pear pear kiwi apple
```

**Correct output**
```text
apple
pear
```

**Suggested POSIX concepts**
- Mutex or local maps, deterministic final scan

**Tips & tricks**
- Count frequencies, then scan original order in main.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 45: Parallel Sortedness Check

**Problem description**  
Check whether array is non-decreasing.

**Data input**
```text
N T
a1 ... aN
```

**Sample input**
```text
6 2
1 2 2 3 5 8
```

**Correct output**
```text
SORTED
```

**Suggested POSIX concepts**
- Threads, boundary checks

**Tips & tricks**
- Each thread checks internal range; also check boundary between chunks.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 46: Parallel Merge Two Sorted Arrays

**Problem description**  
Merge two sorted arrays into one sorted array.

**Data input**
```text
N M T
A
B
```

**Sample input**
```text
4 3 2
1 3 5 7
2 4 6
```

**Correct output**
```text
1 2 3 4 5 6 7
```

**Suggested POSIX concepts**
- Threads, binary search partitioning

**Tips & tricks**
- For 1 hour, each output index can binary-search how many values come from A.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 47: Parallel Matrix Vector Multiplication

**Problem description**  
Compute `y = A*x`.

**Data input**
```text
R C T
matrix
vector
```

**Sample input**
```text
2 3 2
1 2 3
4 5 6
10 20 30
```

**Correct output**
```text
140
320
```

**Suggested POSIX concepts**
- Threads, row partitioning

**Tips & tricks**
- Each output row has one writer.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 48: Parallel Text Checksum Per Line

**Problem description**  
Compute ASCII checksum for each line.

**Data input**
```text
N T
lines
```

**Sample input**
```text
3 2
ABC
hi
!
```

**Correct output**
```text
198
209
33
```

**Suggested POSIX concepts**
- Threads, line partitioning

**Tips & tricks**
- One checksum output per line. No lock needed.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 49: Parallel Run-Length Count

**Problem description**  
Count contiguous runs of identical characters in a string.

**Data input**
```text
T
text
```

**Sample input**
```text
3
aaabbcaaa
```

**Correct output**
```text
4
```

**Suggested POSIX concepts**
- Threads, chunk summaries

**Tips & tricks**
- Each chunk reports internal runs plus first/last char; merge boundaries.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.

---

## Problem 50: Parallel Matrix Spiral Sum Layers

**Problem description**  
Compute sum of each matrix layer/ring.

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
40
5
```

**Suggested POSIX concepts**
- Threads, layer partitioning

**Tips & tricks**
- Layer 0 border sum is 40, layer 1 center is 5.
- Keep output deterministic: collect results in arrays and print from the main thread.
- Start with correct sequential logic, then parallelize the loop.
