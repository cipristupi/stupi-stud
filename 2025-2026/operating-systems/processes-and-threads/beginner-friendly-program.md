# 🔹 1. Process Example (`fork`) — CLEAR BOUNDARIES

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("START: This runs ONCE before fork()\n");

    pid_t pid = fork();  // 🔴 PROCESS SPLIT HAPPENS HERE

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    // =========================================================
    // 🔵 CHILD PROCESS (COPY OF PARENT STARTS EXECUTING HERE)
    // =========================================================
    if (pid == 0) {
        printf("\n--- CHILD PROCESS START ---\n");

        printf("Child: I am a COPY of parent\n");
        printf("Child PID = %d\n", getpid());
        printf("Child Parent PID = %d\n", getppid());

        printf("Child: Doing some work...\n");
        sleep(1);

        printf("--- CHILD PROCESS END ---\n\n");

        _exit(0); // IMPORTANT: child exits safely
    }

    // =========================================================
    // 🟢 PARENT PROCESS (CONTINUES FROM fork() RETURN)
    // =========================================================
    else {
        printf("\n--- PARENT PROCESS START ---\n");

        printf("Parent: I created a child\n");
        printf("Parent PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);

        printf("Parent: Waiting for child to finish...\n");

        wait(NULL); // wait for child

        printf("Parent: Child finished\n");
        printf("--- PARENT PROCESS END ---\n\n");
    }

    printf("END: Both processes reach here separately\n");

    return 0;
}
```

---

## 🧠 What happens step-by-step

```
Before fork:
    1 process

After fork:
    2 processes:
        Parent
        Child (copy of parent memory)
```

Key idea:

* Everything **before fork() runs once**
* Everything **after fork() runs twice (parent + child)**

---

# 🔹 2. Thread Example (`pthread`) — CLEAR BOUNDARIES

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// =========================================================
// 🔵 THREAD FUNCTION (runs in parallel with main thread)
// =========================================================
void *thread_function(void *arg) {
    printf("\n--- THREAD START ---\n");

    int *num = (int *)arg;

    printf("Thread: Received value = %d\n", *num);

    printf("Thread: Doing some work...\n");
    sleep(1);

    printf("Thread: Finished work\n");

    printf("--- THREAD END ---\n\n");

    return NULL;
}

int main() {
    pthread_t thread;

    int value = 42;

    printf("MAIN: Before creating thread\n");

    // 🔴 THREAD CREATION (NEW EXECUTION PATH STARTS)
    pthread_create(&thread, NULL, thread_function, &value);

    // =========================================================
    // 🟢 MAIN THREAD (continues immediately after create)
    // =========================================================
    printf("\n--- MAIN THREAD CONTINUES ---\n");

    printf("Main: Doing work in parallel with thread\n");
    sleep(1);

    printf("Main: Waiting for thread to finish...\n");

    pthread_join(thread, NULL);

    printf("Main: Thread finished\n");
    printf("--- MAIN THREAD END ---\n");

    return 0;
}
```

---

## 🧠 What happens here

```
1 process
   ├── Main thread
   └── New thread (shared memory)
```

Key idea:

* Threads run **in parallel**
* They **share memory**
* Execution order is **not guaranteed**

---

# 🔥 Side-by-side Comparison (important)

| Feature       | fork()             | pthread          |
| ------------- | ------------------ | ---------------- |
| Memory        | ❌ Separate         | ✅ Shared         |
| Execution     | Separate processes | Same process     |
| Speed         | Slower             | Faster           |
| Communication | IPC needed         | Direct variables |

---

# 🔥 CRITICAL VISUAL

## fork()

```
         fork()
           |
     --------------
     |            |
  Parent       Child (copy)
```

## threads

```
   Process
      |
   ---------
   |       |
 Main    Thread
(shared memory)
```

---

# ⚠️ VERY IMPORTANT DIFFERENCE

### fork:

```c
int x = 10;
fork();
x++;
```

➡ Parent and child have **separate copies**

---

### thread:

```c
int x = 10;
pthread_create(...);
x++;
```

➡ Both threads see **same x**

---

# 🚀 If you want next level

I can give you:

* 🔥 Thread + mutex example (with race condition fix)
* 🔥 fork + pipe example (real IPC)
* 🔥 mini shell (like bash)
* 🔥 thread pool implementation

Just tell me 👍
