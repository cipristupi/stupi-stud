Below is a practical guide you can use for almost all the POSIX Threads problems in C.

# Generic Tips & Tricks for Solving POSIX Threads Problems in C

## 1. Start with the sequential solution first

Before adding threads, write the logic as if it runs on one thread.

Example:

```c
long long sum = 0;

for (int i = 0; i < n; i++) {
    sum += a[i];
}
```

Then ask:

> Which loop can be split between threads?

Most problems can be parallelized by splitting one main loop:

```c
for (int i = start; i < end; i++) {
    // thread work here
}
```

Do not start with mutexes and condition variables immediately. First identify:

* what data each thread reads
* what data each thread writes
* what data is shared
* what final result must be combined

---

# 2. How to split work between threads

The most common split is by contiguous ranges.

```c
int start = tid * n / num_threads;
int end   = (tid + 1) * n / num_threads;
```

This works even when `n` is not divisible by the number of threads.

Example with `N = 10`, `T = 3`:

```text
thread 0: indexes 0..2
thread 1: indexes 3..5
thread 2: indexes 6..9
```

In C:

```c
typedef struct {
    int tid;
    int start;
    int end;
    int *a;
    long long *partial;
} ThreadArgs;
```

Worker:

```c
void *worker_sum(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;

    long long local_sum = 0;

    for (int i = args->start; i < args->end; i++) {
        local_sum += args->a[i];
    }

    args->partial[args->tid] = local_sum;

    return NULL;
}
```

Main reduction:

```c
long long total = 0;

for (int t = 0; t < num_threads; t++) {
    total += partial[t];
}
```

This is the safest pattern.

---

# 3. Prefer local results instead of locking inside loops

Bad pattern:

```c
pthread_mutex_lock(&mutex);
global_sum += a[i];
pthread_mutex_unlock(&mutex);
```

Doing this inside a loop creates heavy lock contention.

Better pattern:

```c
long long local_sum = 0;

for (int i = start; i < end; i++) {
    local_sum += a[i];
}

partial[tid] = local_sum;
```

Then the main thread combines results after `pthread_join`.

Use this pattern for:

* sum
* count
* min/max
* histogram
* frequency count
* dot product
* number classification
* text statistics
* matrix statistics

---

# 4. When you do not need a mutex

You do **not** need a mutex when each thread writes to a different memory location.

Safe:

```c
out[i] = a[i] + b[i];
```

as long as each index `i` belongs to exactly one thread.

Examples that usually need no mutex:

* array addition
* matrix addition
* matrix transpose
* matrix-vector multiplication
* row sums
* column sums, if columns are split
* replacing characters in separate string ranges
* computing one result per row
* computing one result per query

Rule:

> Multiple threads may read the same data safely.
> Multiple threads may write safely only if they write to different locations.

---

# 5. When you need a mutex

Use a mutex when several threads may modify the same shared variable.

Example:

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long long global_count = 0;
```

Worker:

```c
pthread_mutex_lock(&mutex);
global_count += local_count;
pthread_mutex_unlock(&mutex);
```

Use mutexes for:

* updating a shared counter
* updating a shared min/max
* writing to a shared dynamic result list
* protecting a shared queue/buffer
* protecting shared flags
* protecting shared indexes

But avoid this:

```c
for (...) {
    pthread_mutex_lock(&mutex);
    shared++;
    pthread_mutex_unlock(&mutex);
}
```

Prefer:

```c
local++;
// later:
pthread_mutex_lock(&mutex);
shared += local;
pthread_mutex_unlock(&mutex);
```

---

# 6. How to avoid deadlocks

A deadlock usually happens when threads wait forever for locks or conditions.

## Deadlock rule 1: Always unlock what you lock

Bad:

```c
pthread_mutex_lock(&mutex);

if (error) {
    return NULL; // BUG: mutex never unlocked
}

pthread_mutex_unlock(&mutex);
```

Better:

```c
pthread_mutex_lock(&mutex);

if (error) {
    pthread_mutex_unlock(&mutex);
    return NULL;
}

pthread_mutex_unlock(&mutex);
```

## Deadlock rule 2: Always lock mutexes in the same order

Bad:

```c
// Thread A
lock(A);
lock(B);

// Thread B
lock(B);
lock(A);
```

This can deadlock.

Better:

```c
// Everyone locks in the same order
lock(A);
lock(B);
unlock(B);
unlock(A);
```

## Deadlock rule 3: Keep critical sections small

Bad:

```c
pthread_mutex_lock(&mutex);

for (int i = 0; i < n; i++) {
    expensive_work();
}

pthread_mutex_unlock(&mutex);
```

Better:

```c
expensive_work_without_lock();

pthread_mutex_lock(&mutex);
update_shared_result();
pthread_mutex_unlock(&mutex);
```

## Deadlock rule 4: Never wait on a condition without a loop

Bad:

```c
if (count == 0) {
    pthread_cond_wait(&not_empty, &mutex);
}
```

Good:

```c
while (count == 0) {
    pthread_cond_wait(&not_empty, &mutex);
}
```

Always use `while`, not `if`.

---

# 7. Condition variables: producer-consumer pattern

Condition variables are used when a thread must wait until some condition becomes true.

Typical example: bounded buffer.

Shared state:

```c
pthread_mutex_t mutex;
pthread_cond_t not_empty;
pthread_cond_t not_full;

int buffer[CAP];
int count = 0;
int head = 0;
int tail = 0;
int done = 0;
```

Producer:

```c
pthread_mutex_lock(&mutex);

while (count == CAP) {
    pthread_cond_wait(&not_full, &mutex);
}

buffer[tail] = value;
tail = (tail + 1) % CAP;
count++;

pthread_cond_signal(&not_empty);
pthread_mutex_unlock(&mutex);
```

Consumer:

```c
pthread_mutex_lock(&mutex);

while (count == 0 && !done) {
    pthread_cond_wait(&not_empty, &mutex);
}

if (count == 0 && done) {
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int value = buffer[head];
head = (head + 1) % CAP;
count--;

pthread_cond_signal(&not_full);
pthread_mutex_unlock(&mutex);
```

Important:

```c
pthread_cond_wait(&cond, &mutex);
```

automatically:

1. unlocks the mutex
2. waits
3. re-locks the mutex before returning

So the mutex must be locked before calling `pthread_cond_wait`.

---

# 8. Barriers: multi-phase problems

Use barriers when all threads must finish phase 1 before any thread starts phase 2.

Example problems:

* prefix sum
* vector normalization
* matrix relaxation
* row/column preprocessing
* iterative algorithms

Initialize:

```c
pthread_barrier_t barrier;
pthread_barrier_init(&barrier, NULL, num_threads);
```

Worker:

```c
// Phase 1
compute_partial_sum();

pthread_barrier_wait(&barrier);

// Phase 2
use_global_result();

pthread_barrier_wait(&barrier);

// Phase 3
write_output();
```

Destroy:

```c
pthread_barrier_destroy(&barrier);
```

Common mistake:

> All threads must reach the same barrier.

This is dangerous:

```c
if (tid == 0) {
    pthread_barrier_wait(&barrier);
}
```

Only one thread waits, so it will wait forever.

Correct:

```c
pthread_barrier_wait(&barrier);
```

called by every thread.

---

# 9. Read-write locks

Use RW locks when:

* many threads read shared data
* few threads update shared data

Initialize:

```c
pthread_rwlock_t rwlock;
pthread_rwlock_init(&rwlock, NULL);
```

Reader:

```c
pthread_rwlock_rdlock(&rwlock);

// read shared array safely

pthread_rwlock_unlock(&rwlock);
```

Writer:

```c
pthread_rwlock_wrlock(&rwlock);

// modify shared array safely

pthread_rwlock_unlock(&rwlock);
```

Destroy:

```c
pthread_rwlock_destroy(&rwlock);
```

Use RW locks for problems like:

* range sum queries with updates
* shared array reads and occasional writes
* shared word table reads and updates
* read-mostly matrix/vector problems

Do not use RW locks if all threads are only reading immutable input. Plain reads are already safe.

---

# 10. Safe memory allocation with threads

## Allocate before creating threads

Good:

```c
int *a = malloc(n * sizeof(int));
pthread_t *threads = malloc(t * sizeof(pthread_t));
ThreadArgs *args = malloc(t * sizeof(ThreadArgs));
long long *partial = calloc(t, sizeof(long long));
```

Then create threads.

Avoid allocating important shared arrays inside worker threads unless necessary.

## Check allocation results

```c
if (!a || !threads || !args || !partial) {
    fprintf(stderr, "Memory allocation failed\n");
    free(a);
    free(threads);
    free(args);
    free(partial);
    exit(1);
}
```

## Do not pass address of loop variable

Bad:

```c
for (int i = 0; i < t; i++) {
    pthread_create(&threads[i], NULL, worker, &i);
}
```

All threads may see the same changing `i`.

Good:

```c
for (int i = 0; i < t; i++) {
    args[i].tid = i;
    pthread_create(&threads[i], NULL, worker, &args[i]);
}
```

---

# 11. Safe memory deallocation

Only free memory after all threads are done.

Correct order:

```c
for (int i = 0; i < t; i++) {
    pthread_join(threads[i], NULL);
}

free(a);
free(partial);
free(args);
free(threads);
```

Bad:

```c
pthread_create(...);

free(args); // BUG: thread may still use args
```

Rule:

> If a thread uses memory, do not free it until after `pthread_join`.

---

# 12. Thread argument struct pattern

This pattern works for almost all problems.

```c
typedef struct {
    int tid;
    int num_threads;

    int start;
    int end;

    int n;
    int *a;

    long long *partial;

    pthread_mutex_t *mutex;
    pthread_barrier_t *barrier;
} ThreadArgs;
```

Main:

```c
pthread_t *threads = malloc(T * sizeof(pthread_t));
ThreadArgs *args = malloc(T * sizeof(ThreadArgs));

for (int tid = 0; tid < T; tid++) {
    args[tid].tid = tid;
    args[tid].num_threads = T;
    args[tid].start = tid * N / T;
    args[tid].end = (tid + 1) * N / T;
    args[tid].n = N;
    args[tid].a = a;
    args[tid].partial = partial;
    args[tid].mutex = &mutex;
    args[tid].barrier = &barrier;

    pthread_create(&threads[tid], NULL, worker, &args[tid]);
}
```

---

# 13. Correctness checklist

Before saying the solution is done, check these:

## Work splitting

Ask:

```text
Does every element get processed?
Does any element get processed twice?
What happens when N is not divisible by T?
What happens when T > N?
```

The range formula:

```c
start = tid * n / T;
end = (tid + 1) * n / T;
```

handles most of this safely.

## Shared data

Ask:

```text
Is this variable read-only?
Is this variable written by only one thread?
Is this variable written by multiple threads?
```

If multiple threads write to the same variable, use:

* per-thread local result, or
* mutex, or
* RW lock, depending on the problem

## Output order

Threads run in unpredictable order.

Bad:

```c
printf("thread result: %d\n", result);
```

from many threads, if order matters.

Better:

```c
results[tid] = value;
```

Then main prints after joins.

## Floating-point results

Parallel floating-point reduction may produce tiny differences due to order of addition.

For problems with floating-point output:

```c
printf("%.6f\n", value);
```

Use tolerance when testing.

---

# 14. Common bug: race condition

Race condition example:

```c
global_count++;
```

This is not safe with multiple threads.

It looks like one operation, but internally it is:

```text
read global_count
add 1
write global_count
```

Two threads can overwrite each other.

Fix 1: mutex

```c
pthread_mutex_lock(&mutex);
global_count++;
pthread_mutex_unlock(&mutex);
```

Fix 2: local counters, preferred

```c
local_count++;
partial[tid] = local_count;
```

---

# 15. Common bug: wrong lifetime of local variables

Bad:

```c
void create_threads() {
    ThreadArgs args[10];

    for (...) {
        pthread_create(..., &args[i]);
    }

    return; // BUG: args disappears while threads may still use it
}
```

Good:

```c
ThreadArgs *args = malloc(T * sizeof(ThreadArgs));
```

or make sure you join before leaving the function.

---

# 16. Common bug: printing from threads

This can produce messy output:

```c
printf("%d ", value);
```

from many threads.

Even if `printf` itself is internally protected, the logical order is not guaranteed.

Better:

```c
output[i] = value;
```

After joins:

```c
for (int i = 0; i < n; i++) {
    printf("%d ", output[i]);
}
```

Use condition variables only if the exercise explicitly asks for ordered threaded output.

---

# 17. Matrix splitting strategies

## Split by rows

Best for:

* row sums
* matrix-vector multiplication
* matrix multiplication
* row normalization
* median per row

```c
int row_start = tid * rows / T;
int row_end = (tid + 1) * rows / T;
```

## Split by columns

Best for:

* column sums
* column maximums
* column normalization

```c
int col_start = tid * cols / T;
int col_end = (tid + 1) * cols / T;
```

## Split by flat cells

Best for:

* matrix addition
* matrix transpose
* threshold counting
* elementwise operations

```c
int total = rows * cols;
int start = tid * total / T;
int end = (tid + 1) * total / T;

for (int idx = start; idx < end; idx++) {
    int i = idx / cols;
    int j = idx % cols;
}
```

---

# 18. Text splitting strategies

Text is trickier because words may cross boundaries.

## Character-based problems

Easy to split directly:

* count vowels
* count digits
* count uppercase
* checksum
* replace characters
* Hamming distance

Use:

```c
start = tid * len / T;
end = (tid + 1) * len / T;
```

## Word-based problems

Be careful with boundary words.

For word count, count word starts:

```c
if (text[i] != ' ' && (i == 0 || text[i - 1] == ' ')) {
    count++;
}
```

This works even if a word crosses a thread boundary.

For more complex word tasks, simpler approach:

1. tokenize words sequentially
2. store them in an array
3. parallelize over word indexes

That is usually better for 1-hour problems.

---

# 19. Histograms and frequency counts

Best safe pattern:

```c
int **local_hist = calloc(T, sizeof(int *));
for (int t = 0; t < T; t++) {
    local_hist[t] = calloc(K, sizeof(int));
}
```

Worker:

```c
local_hist[tid][value]++;
```

Main merge:

```c
for (int k = 0; k < K; k++) {
    int total = 0;

    for (int t = 0; t < T; t++) {
        total += local_hist[t][k];
    }

    hist[k] = total;
}
```

This is usually better than:

```c
pthread_mutex_lock(&bucket_mutex[value]);
hist[value]++;
pthread_mutex_unlock(&bucket_mutex[value]);
```

Bucket mutexes are useful for learning, but local histograms are simpler and faster.

---

# 20. Barriers vs join/restart

For two-phase problems, you have two options.

## Option A: join and start new threads

Phase 1:

```c
create threads
join threads
```

Compute global result in main.

Phase 2:

```c
create threads again
join threads
```

This is simple but slower.

## Option B: barrier inside worker

```c
phase_1();

pthread_barrier_wait(&barrier);

phase_2();

pthread_barrier_wait(&barrier);

phase_3();
```

This is better when the same threads do several phases.

Use barriers for hard problems. Use join/restart for simpler medium problems if you want easier code.

---

# 21. How to debug threaded C programs

Compile with warnings and debug info:

```bash
gcc -Wall -Wextra -O0 -g -pthread main.c -o main
```

Use ThreadSanitizer if available:

```bash
gcc -Wall -Wextra -O1 -g -fsanitize=thread -pthread main.c -o main
```

Use AddressSanitizer for memory bugs:

```bash
gcc -Wall -Wextra -O1 -g -fsanitize=address -pthread main.c -o main
```

Add debug prints with thread IDs:

```c
fprintf(stderr, "[T%d] start=%d end=%d\n", tid, start, end);
```

But remove them before final output if the judge expects exact output.

---

# 22. A reusable template

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int tid;
    int start;
    int end;
    int *a;
    long long *partial;
} ThreadArgs;

void *worker(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;

    long long local = 0;

    for (int i = args->start; i < args->end; i++) {
        local += args->a[i];
    }

    args->partial[args->tid] = local;

    return NULL;
}

int main(void) {
    int n, T;

    scanf("%d %d", &n, &T);

    int *a = malloc(n * sizeof(int));
    pthread_t *threads = malloc(T * sizeof(pthread_t));
    ThreadArgs *args = malloc(T * sizeof(ThreadArgs));
    long long *partial = calloc(T, sizeof(long long));

    if (!a || !threads || !args || !partial) {
        fprintf(stderr, "Memory allocation failed\n");
        free(a);
        free(threads);
        free(args);
        free(partial);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int tid = 0; tid < T; tid++) {
        args[tid].tid = tid;
        args[tid].start = tid * n / T;
        args[tid].end = (tid + 1) * n / T;
        args[tid].a = a;
        args[tid].partial = partial;

        if (pthread_create(&threads[tid], NULL, worker, &args[tid]) != 0) {
            fprintf(stderr, "Failed to create thread %d\n", tid);
            free(a);
            free(threads);
            free(args);
            free(partial);
            return 1;
        }
    }

    for (int tid = 0; tid < T; tid++) {
        pthread_join(threads[tid], NULL);
    }

    long long total = 0;

    for (int tid = 0; tid < T; tid++) {
        total += partial[tid];
    }

    printf("%lld\n", total);

    free(a);
    free(threads);
    free(args);
    free(partial);

    return 0;
}
```

---

# 23. Final mental model

For most problems, think like this:

```text
Input data is shared and read-only.
Each thread gets a slice.
Each thread computes local result.
Main thread combines local results.
Only use mutexes when shared writes are unavoidable.
Only use condition variables when threads must wait for data/state.
Only use barriers when all threads must finish one phase before another begins.
Only use RW locks when many readers and few writers access the same structure.
Free memory only after all threads have joined.
```

That mindset will solve most POSIX Threads exercises safely and cleanly.
