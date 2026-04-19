Absolutely. The key boundary for `fork()` is:

* **Everything in the parent’s memory that exists up to the instant `fork()` returns is what the child starts with as its initial copy**. On Linux this is implemented with **copy-on-write**, so pages are not physically duplicated until one side writes. ([man7.org][1])
* After that boundary, **parent and child are separate processes with separate virtual memory**. Changes to an ordinary variable in one do not change the other. Some kernel-managed things, like inherited file descriptors, still refer to shared underlying kernel objects. ([man7.org][1])
* By contrast, POSIX threads in one process **share global memory and heap**, while each thread has its **own stack**. ([man7.org][2])

Below are all four programs, with **big visible borders** and comments like:

* **“UP TO HERE parent memory is copied”**
* **“FROM HERE parent-only execution”**
* **“FROM HERE child-only execution”**

---

# 1) `fork()` — child gets a copy of the parent’s memory

This program shows:

* a variable before `fork()`
* child changes its copy
* parent changes its own copy
* both started from the same value

```c
/*
    file: fork_memory_copy_demo.c

    Compile:
        gcc -Wall -Wextra -O2 fork_memory_copy_demo.c -o fork_memory_copy_demo

    Run:
        ./fork_memory_copy_demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int x = 10;   // ordinary stack variable in the parent
    int y = 50;   // another ordinary stack variable in the parent

    printf("BEFORE fork(): parent has x=%d, y=%d\n", x, y);
    printf("BEFORE fork(): this code runs only once, in the original parent\n");

    /*
    =====================================================================
    IMPORTANT MEMORY BOUNDARY
    =====================================================================

    UP TO THIS LINE:
        - only ONE process exists: the parent
        - x and y exist only in the parent

    THE NEXT LINE CALLS fork()

    WHAT fork() DOES:
        - creates a child process
        - child starts with a COPY of the parent's memory as it existed
          at the moment fork() happened

    SO:
        child initially gets:
            x = 10
            y = 50

        parent still has:
            x = 10
            y = 50

    After this point:
        parent and child are SEPARATE processes
        parent changes affect only parent memory
        child changes affect only child memory
    =====================================================================
    */
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    /*
    =====================================================================
    FROM HERE ON, TWO PROCESSES EXIST
    =====================================================================
    Both parent and child continue from this point,
    but fork() returns different values in each process:
        - child gets pid == 0
        - parent gets pid > 0
    =====================================================================
    */

    if (pid == 0) {
        /*
        ================================================================
        CHILD-ONLY EXECUTION STARTS HERE
        ================================================================

        CHILD MEMORY EXPLANATION:
            The child is NOT using the same ordinary variable x and y
            as the parent.

            The child received its OWN initial copy of the parent's memory
            as it existed at fork() time.

            So child starts with:
                x = 10
                y = 50

            If child changes x/y now, only the child sees those changes.
        ================================================================
        */

        printf("\n================ CHILD PROCESS ================\n");
        printf("Child: initial copied values -> x=%d, y=%d\n", x, y);

        x = 100;
        y = 500;

        printf("Child: after changing CHILD'S OWN COPY -> x=%d, y=%d\n", x, y);

        /*
            The address may print the same numeric value as in the parent,
            but it is in a different process address space.
            So same-looking address does NOT mean same memory object
            across processes.
        */
        printf("Child: &x=%p, &y=%p\n", (void *)&x, (void *)&y);

        printf("===============================================\n\n");

        _exit(0);
    } else {
        /*
        ================================================================
        PARENT-ONLY EXECUTION STARTS HERE
        ================================================================

        PARENT MEMORY EXPLANATION:
            The parent continues with its OWN original memory.

            Parent still has:
                x = 10
                y = 50

            If parent changes x/y now, only the parent sees those changes.
            The child will NOT be affected.
        ================================================================
        */

        printf("\n================ PARENT PROCESS ===============\n");
        printf("Parent: original values still here -> x=%d, y=%d\n", x, y);

        x = 20;
        y = 60;

        printf("Parent: after changing PARENT'S OWN MEMORY -> x=%d, y=%d\n", x, y);
        printf("Parent: &x=%p, &y=%p\n", (void *)&x, (void *)&y);

        wait(NULL);

        printf("Parent: child is finished\n");
        printf("===============================================\n\n");
    }

    return 0;
}
```

### What to notice

* Both start with `x=10, y=50`.
* Child changes to `100, 500`.
* Parent changes to `20, 60`.
* The changes do not cross over because ordinary process memory is separate after `fork()`. Linux implements this efficiently with copy-on-write. ([man7.org][1])

---

# 2) Threads — same process, shared global memory

This one shows the opposite of `fork()`:

* both threads touch the **same global variable**
* they share memory
* main thread and worker thread both see the same `shared_counter`

```c
/*
    file: thread_shared_memory_demo.c

    Compile:
        gcc -Wall -Wextra -O2 -pthread thread_shared_memory_demo.c -o thread_shared_memory_demo

    Run:
        ./thread_shared_memory_demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
    GLOBAL VARIABLE:
    All threads in this process share this variable.
*/
int shared_counter = 0;

void *worker_thread(void *arg) {
    (void)arg;

    /*
    ================================================================
    WORKER THREAD EXECUTION STARTS HERE
    ================================================================

    THREAD MEMORY EXPLANATION:
        This thread is in the SAME process as main().
        That means global variables and heap memory are SHARED.

        So shared_counter below is the SAME variable seen by main().
    ================================================================
    */

    printf("\n---------------- WORKER THREAD ----------------\n");
    printf("Worker: initial shared_counter = %d\n", shared_counter);

    shared_counter += 10;

    printf("Worker: after update shared_counter = %d\n", shared_counter);
    printf("------------------------------------------------\n\n");

    return NULL;
}

int main(void) {
    pthread_t tid;

    printf("Main: before creating thread, shared_counter = %d\n", shared_counter);

    /*
    =====================================================================
    THREAD CREATION BOUNDARY
    =====================================================================

    UP TO THIS LINE:
        - only main thread exists

    NEXT LINE:
        - creates a second thread in the SAME process

    IMPORTANT DIFFERENCE FROM fork():
        - NO separate process is created
        - NO separate copy of ordinary process memory is created
        - threads SHARE global memory and heap
        - each thread has its own stack
    =====================================================================
    */
    if (pthread_create(&tid, NULL, worker_thread, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    /*
    ================================================================
    MAIN THREAD CONTINUES HERE
    ================================================================

    This is still the original main thread.
    It runs in parallel with worker_thread().
    Both threads share shared_counter.
    ================================================================
    */
    printf("---------------- MAIN THREAD ------------------\n");
    shared_counter += 5;
    printf("Main: after own update shared_counter = %d\n", shared_counter);

    pthread_join(tid, NULL);

    printf("Main: after join, final shared_counter = %d\n", shared_counter);
    printf("------------------------------------------------\n");

    return 0;
}
```

### What to notice

Threads share global memory and heap, but each thread has its own stack. That is the fundamental reason races are possible in threaded programs. ([man7.org][2])

---

# 3) Threads — race condition, then fixed with a mutex

This gives you both versions:

* broken version
* fixed version

---

## 3A) Broken: race condition

```c
/*
    file: thread_race_demo.c

    Compile:
        gcc -Wall -Wextra -O2 -pthread thread_race_demo.c -o thread_race_demo

    Run:
        ./thread_race_demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long counter = 0;   // shared by all threads

void *incrementer(void *arg) {
    (void)arg;

    /*
    ================================================================
    THREAD-ONLY CODE
    ================================================================
    This thread and the other thread both access the SAME counter.
    There is NO protection here.
    So this program has a race condition.
    ================================================================
    */
    for (long i = 0; i < 1000000; i++) {
        counter++;   // NOT SAFE: read-modify-write on shared variable
    }

    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    /*
    =====================================================================
    THREAD CREATION BOUNDARY
    =====================================================================
    After these calls, multiple threads run in the SAME process and share
    the SAME global variable "counter".
    =====================================================================
    */
    pthread_create(&t1, NULL, incrementer, NULL);
    pthread_create(&t2, NULL, incrementer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Expected around 2000000, got counter = %ld\n", counter);
    return 0;
}
```

---

## 3B) Fixed: mutex protects shared memory

```c
/*
    file: thread_mutex_demo.c

    Compile:
        gcc -Wall -Wextra -O2 -pthread thread_mutex_demo.c -o thread_mutex_demo

    Run:
        ./thread_mutex_demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long counter = 0;   // shared by all threads
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *incrementer(void *arg) {
    (void)arg;

    /*
    ================================================================
    THREAD-ONLY CODE
    ================================================================
    Same shared counter as before, BUT now each update is protected
    by a mutex.
    ================================================================
    */
    for (long i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    /*
    =====================================================================
    THREAD CREATION BOUNDARY
    =====================================================================
    Same process, same shared memory, but now access is synchronized.
    =====================================================================
    */
    pthread_create(&t1, NULL, incrementer, NULL);
    pthread_create(&t2, NULL, incrementer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter = %ld\n", counter);

    pthread_mutex_destroy(&lock);
    return 0;
}
```

---

# 4) `fork()` + shared memory with `mmap()` — parent and child really do share

This is the “exception demo.” Normally after `fork()` parent and child have separate ordinary memory. But if you explicitly create **shared memory**, then both can see the same value.

```c
/*
    file: fork_shared_mmap_demo.c

    Compile:
        gcc -Wall -Wextra -O2 fork_shared_mmap_demo.c -o fork_shared_mmap_demo

    Run:
        ./fork_shared_mmap_demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

int main(void) {
    /*
        This integer will live in SHARED MEMORY, not ordinary stack memory.
        Because of that, parent and child will both see updates to it.
    */
    int *shared_value = mmap(NULL,
                             sizeof(*shared_value),
                             PROT_READ | PROT_WRITE,
                             MAP_SHARED | MAP_ANONYMOUS,
                             -1,
                             0);

    if (shared_value == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    *shared_value = 10;

    int ordinary_value = 10;  // ordinary stack variable, NOT shared

    printf("BEFORE fork(): shared_value=%d, ordinary_value=%d\n",
           *shared_value, ordinary_value);

    /*
    =====================================================================
    MEMORY BOUNDARY FOR fork()
    =====================================================================

    UP TO THIS LINE:
        - parent has:
            * shared_value in a shared mmap region
            * ordinary_value in ordinary parent stack memory

    AT fork():
        - child gets access to the SAME shared mmap region
        - child also gets its OWN COPY of ordinary parent memory

    SO AFTER fork():
        shared_value     -> genuinely shared between parent and child
        ordinary_value   -> copied, then separate in each process
    =====================================================================
    */
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        munmap(shared_value, sizeof(*shared_value));
        return 1;
    }

    if (pid == 0) {
        /*
        ================================================================
        CHILD-ONLY EXECUTION
        ================================================================
        Child can change:
            - shared_value: parent WILL see it
            - ordinary_value: parent will NOT see it
        ================================================================
        */
        printf("\n*************** CHILD PROCESS *****************\n");
        printf("Child: initial shared_value=%d, ordinary_value=%d\n",
               *shared_value, ordinary_value);

        *shared_value = 999;
        ordinary_value = 111;

        printf("Child: after changes shared_value=%d, ordinary_value=%d\n",
               *shared_value, ordinary_value);
        printf("***********************************************\n\n");

        munmap(shared_value, sizeof(*shared_value));
        _exit(0);
    } else {
        /*
        ================================================================
        PARENT-ONLY EXECUTION
        ================================================================
        Parent waits, then reads values:
            - shared_value should reflect child's update
            - ordinary_value should stay parent's own version
        ================================================================
        */
        wait(NULL);

        printf("\n*************** PARENT PROCESS ****************\n");
        printf("Parent: after child finished shared_value=%d, ordinary_value=%d\n",
               *shared_value, ordinary_value);
        printf("***********************************************\n\n");

        munmap(shared_value, sizeof(*shared_value));
    }

    return 0;
}
```

### What to notice

* `shared_value` becomes `999` in the parent too.
* `ordinary_value` stays unchanged in the parent.
* That is the cleanest contrast between:

  * **ordinary post-fork copied memory**
  * **intentionally shared memory**

---

# Quick visual memory diagrams

## A) Normal `fork()`

Before `fork()`:

```text
ONE PROCESS
parent memory:
    x = 10
    y = 50
```

At `fork()`:

```text
CHILD STARTS WITH A COPY OF PARENT MEMORY AS IT EXISTS HERE
```

After `fork()`:

```text
PARENT PROCESS                 CHILD PROCESS
x = 10 -> can become 20        x = 10 -> can become 100
y = 50 -> can become 60        y = 50 -> can become 500
```

---

## B) Threads

```text
ONE PROCESS
    ├── main thread
    └── worker thread

Shared:
    globals
    heap

Separate per thread:
    stack
    registers
```

---

## C) `fork()` + shared `mmap`

```text
PARENT PROCESS                 CHILD PROCESS
ordinary_value = separate      ordinary_value = separate

shared_value ---- same shared mapping ---- shared_value
```

---

# The exact boundary comment you asked for

Use this template in any `fork()` program:

```c
/*
=====================================================================
UP TO THIS LINE:
    parent memory exists only in the parent

THE NEXT LINE CALLS fork()

AT THE MOMENT fork() HAPPENS:
    the child starts with a copy of the parent's ordinary memory
    as it exists right here

FROM AFTER fork():
    parent and child are separate processes
    parent changes affect only parent memory
    child changes affect only child memory

EXCEPTION:
    explicitly shared memory (for example mmap with MAP_SHARED)
    can be seen by both processes
=====================================================================
*/
pid_t pid = fork();
```

And then immediately after:

```c
/*
=====================================================================
FROM HERE:
    two processes now exist

    if (pid == 0)  -> child-only path
    if (pid > 0)   -> parent-only path
=====================================================================
*/
```

---

# One more important note

Even though parent and child ordinary memory are separate after `fork()`, inherited file descriptors still refer to shared underlying kernel open-file descriptions, so offsets and some flags can still affect both sides. That is why memory isolation and kernel-resource sharing are different ideas. ([man7.org][3])

[1]: https://man7.org/linux/man-pages/man2/fork.2.html?utm_source=chatgpt.com "fork(2) - Linux manual page"
[2]: https://man7.org/linux/man-pages/man7/pthreads.7.html?utm_source=chatgpt.com "pthreads(7) - Linux manual page"
[3]: https://man7.org/linux/man-pages/man2/open.2.html?utm_source=chatgpt.com "open(2) - Linux manual page"
