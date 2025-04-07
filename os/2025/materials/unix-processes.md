Here's an explanation of each of these UNIX processes and their uses:

1. Fork

Fork is a system call that creates a new process by duplicating the current one. When a parent process calls fork(), it creates a new child process that has its own memory space, file descriptors, and program counter. The child process is an exact replica of the parent process.

The system call returns two values:


0 to the child process (to indicate that it's the child)

The process ID (PID) of the child process in the parent process

Example Code:


```c

#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        printf("Hello from child process\n");
    } else if (pid > 0) { // Parent process
        printf("Hello from parent process, child PID: %d\n", pid);
    } else {
        printf("Error creating child process\n");
        exit(1);
    }

    return 0;
}
```

2. Wait

The wait() system call is used by the parent process to wait for the completion of a child process. When a child process terminates, it sends a signal to the parent process indicating its termination.

There are two types of waits:

wait(): Waits for any child process to terminate and returns its PID.
waitpid(pid): Waits for a specific child process with the specified PID.

Example Code:


```c

#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int status;

    // Create a child process using fork()
    pid = fork();

    if (pid == 0) { // Child process
        printf("Hello from child process\n");
        sleep(10); // Simulate some work
        exit(0);
    } else if (pid > 0) { // Parent process
        wait(&status); // Wait for the child to terminate

        printf("Child PID: %d, Exit status: %d\n", pid, WEXITSTATUS(status));
    } else {
        printf("Error creating child process\n");
        exit(1);
    }

    return 0;
}
```

3. Exit

The exit() function is used to terminate a process immediately.


There are two types of exits:


- exit(): Terminates the current process with the specified status code.
- _Exit(): Terminates the current process and does not perform any cleanup actions (not recommended).

Example Code:


```c

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Hello from parent process\n");
    exit(0); // Terminate with status code 0

    return 0;
}
```
4. Signal

Signals are asynchronous messages sent by the operating system to a process. They can be used for various purposes, such as:

- Interrupting a process
- Indicating an error
- Restarting a process

There are two types of signals:


Synchronous: Send by a program to itself (e.g., kill())
Asynchronous: Sent by the operating system to a process (e.g., SIGINT, SIGALRM)

Example Code:

```c
#include <stdio.h>
#include <signal.h>

void sigint_handler(int signal) {
    printf("Received SIGINT\n");
}

int main() {
    signal(SIGINT, sigint_handler); // Register the signal handler

    while (1) {
        printf("Hello from parent process\n");
        sleep(1);
    }

    return 0;
}
```

5. Kill

The kill() system call is used to send a signal to a specific process.

There are two types of kills:

SIGKILL: Forces the termination of the target process
SIGTERM: Terminates the target process after sending a termination request

Example Code:


```c

#include <stdio.h>
#include <signal.h>

void sigint_handler(int signal) {
    printf("Received SIGINT\n");
}

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        while (1) {
            sleep(1);
            kill(getpid(), SIGKILL); // Force termination of the child
        }
    } else if (pid > 0) { // Parent process
        signal(SIGINT, sigint_handler); // Register the signal handler

        printf("Hello from parent process\n");
        sleep(10);
        kill(pid, SIGTERM); // Send a termination request to the child
    } else {
        printf("Error creating child process\n");
        exit(1);
    }

    return 0;
}
```