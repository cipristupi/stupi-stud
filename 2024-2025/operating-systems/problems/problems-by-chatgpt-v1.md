
## 🧩 COMBINATION 1: **Only Shell Programming (Bash, utilities like `grep`, `awk`, `cut`, etc.)**

### ✅ Easy

1. **Count log levels**
   Count how many times each log level (INFO, ERROR, etc.) appears in a log file.

2. **Extract all unique users**
   Print a sorted list of unique users from the log.

3. **Get all ERROR lines**
   Output all lines containing the ERROR log level.

4. **Filter logs by IP range**
   Extract all log lines with IPs starting with `192.168.`.

5. **Display top 5 most frequent methods**
   Use `cut`, `sort`, `uniq` to determine top 5 most used methods.

### 🔶 Medium

1. **Group and count logs per user and app**
   Show how many log entries each (user, app) pair has.

2. **Summarize ERROR logs by app**
   List each app and the number of associated ERROR entries.

3. **Extract all distinct err-msg values**
   Parse and print all unique `[err-msg:...]` values.

4. **Calculate average PERF duration**
   For `[duration:123ms]` lines, extract numbers and compute average.

5. **Show hourly log activity**
   Group log entries by hour and show how many logs occurred in each hour.

### 🔴 Hard

1. **Identify users causing most errors**
   Aggregate and sort users by number of ERROR logs with err-msgs.

2. **Detect possible suspicious activity**
   Print users with logs containing more than 5 ERRORs in less than a minute.

3. **Extract complete stack paths for each app**
   Parse and categorize stack traces per app, saving each to its own file.

4. **Build a histogram of log levels**
   Print a visual histogram (ASCII bars) for log level frequency.

5. **Detect inconsistent app-method pairs**
   List app-method combinations that occurred only once.

---

## 🧩 COMBINATION 2: **Only C Programming with Processes**

### ✅ Easy

1. **Use `fork()` to process file sections in parallel**
   Split the file into N parts, spawn N processes, each counts lines.

2. **Child process filters by level**
   Parent spawns child to output only WARNING lines to a new file.

3. **Use `exec()` to run `grep` on log**
   A C program runs `grep` to extract `[err-msg:` entries.

4. **Count entries using `wait()` after forks**
   Fork 3 children; one counts INFO, one counts ERROR, one counts PERF logs.

5. **Multiple processes extract stack traces**
   Spawn multiple processes, each parsing stacks for a set of apps.

### 🔶 Medium

1. **Each process handles one log level**
   Four children forked, each parses one level and reports counts.

2. **Fork pipeline emulation**
   Use `pipe()` and `fork()` to simulate: grep → cut → sort → uniq.

3. **Process extracts all users using `pipe()`**
   Parent passes lines to child via pipe to extract unique users.

4. **Build log frequency map using `exec()` + `cut|sort|uniq`**
   Use `exec` to run shell pipeline from within C program.

5. **Merge child summaries into one report**
   Children write summaries to separate files; parent merges and formats them.

### 🔴 Hard

1. **Parallel parsing by time chunk**
   Split log into time chunks (e.g. per hour), fork per chunk, aggregate stats.

2. **Create parent-child workflow with signals**
   Child parses logs, parent waits on signal to summarize output.

3. **Use FIFO between processes to pass log lines**
   One process writes matching lines into FIFO, another reads and aggregates.

4. **Spawn process per user for log analysis**
   Fork for each user, process log file for user-specific metrics.

5. **Sort entire log by timestamp using child process**
   Child reads, parses timestamps, and sorts them numerically.

---

## 🧩 COMBINATION 3: **Only C Programming with Threads**

### ✅ Easy

1. **Thread per log level**
   One thread handles INFO, another WARNING, etc.

2. **Parse and count user entries using threads**
   Split file by lines, assign to threads, each counts user references.

3. **Count stack depth using threads**
   Threads parse and count how deep each stack trace goes.

4. **Thread-safe count of ERRORs**
   Use mutex to increment shared counter for ERROR logs.

5. **Extract paths concurrently**
   Threads extract `[path:...]` fields into a shared list.

### 🔶 Medium

1. **Thread pool for chunked log processing**
   Divide file into chunks, assign to fixed thread pool, aggregate results.

2. **Threaded average duration of PERF logs**
   Each thread parses part of file and computes average, combined at end.

3. **RW lock for shared error message map**
   Threads read/write to a shared map of err-msgs with RW lock.

4. **Multithreaded hourly activity histogram**
   Use mutex per hour-bin to build histogram safely.

5. **Threads detect duplicate stacks**
   Identify repeated stack traces in different threads safely.

### 🔴 Hard

1. **Multithreaded parser with work-stealing**
   Threads fetch unprocessed lines, parse dynamically.

2. **Use condition variable to alert when error count crosses threshold**
   One thread monitors, others parse logs; monitor signals when errors spike.

3. **Multithreaded log merger and sorter**
   Threads parse and produce sorted outputs, merged using barrier sync.

4. **Thread-safe log summary report**
   Each thread produces partial report, final merge under mutex.

5. **Detect bursts of logs in sliding time window**
   Each thread slides window over time range and checks burst rate.

---

## 🧩 COMBINATION 4: **C with Processes and Threads**

### ✅ Easy

1. **One process, multiple threads**
   Each thread parses log section; parent process coordinates summary.

2. **Processes split work, each has thread pool**
   Each forked process handles a time range using threads.

3. **Thread-safe logging per process**
   Each process logs parsed output with its threads, using file locking.

4. **Concurrent IP counting per app**
   Fork per app, threads per region/IP to count usage.

5. **Threaded method frequency in each process**
   Fork per method category; each spawns threads to analyze usage.

### 🔶 Medium

1. **Process/thread matrix for logs per hour**
   Fork per hour group, use threads to analyze within group.

2. **Concurrent histogram build with process+thread teams**
   Process handles segment, thread builds histogram of levels.

3. **Process manages files, threads parse**
   One process opens and maps file chunks, threads parse in parallel.

4. **Analyze logs per user: process per user, threads per feature**
   App-specific, user-specific threads gather usage metrics.

5. **Shared memory across processes, threads fill it**
   Use shared memory for metrics; threads fill values in child processes.

### 🔴 Hard

1. **POSIX threads and shared memory for real-time analysis**
   Threads write stats to shared memory; master process reads in real time.

2. **Fork-join with barrier to summarize stacks**
   Threads parse stacks, barrier sync, process combines into report.

3. **Build a full log analyzer CLI tool (grep-like)**
   Multithreaded grep replacement with forked search modules.

4. **Multi-process perf parser with thread-based aggregation**
   Process-level division of PERF entries, threads compute per segment.

5. **Log anomaly detection using hybrid approach**
   Threads extract behavior, process aggregates for anomaly scoring.

---

## 🧩 COMBINATION 5: **Processes + Threads + Shell Scripting**

### ✅ Easy

1. **Script calls compiled C parser with threads**
   Shell script runs threaded C tool that filters logs by app.

2. **Script forks log segment processors**
   Fork C programs per log file, each uses threads.

3. **Shell grep → C thread counter**
   Script filters logs, C program (with threads) processes output.

4. **Parallel sort via `sort` and threaded parser**
   Shell does sorting, passes to threaded C analyzer.

5. **Batch process logs with cron, C handles threading**
   Cron invokes shell script that runs C parser per log file.

### 🔶 Medium

1. **Shell extracts per-app logs, passes to C thread analyzer**
   Use `grep` in shell to split logs, C threads summarize.

2. **Hybrid: shell filters by error, C counts users via threads**
   Combine shell and C to split/filter/analyze.

3. **Shell filters logs per hour, C+threads handle each file**
   Shell creates temp files per hour, C reads each in threads.

4. **FIFO from shell → threaded C**
   Shell writes log lines into FIFO, C threads read and process.

5. **Shell script monitors file, spawns threaded C on change**
   Use `inotify` or polling to trigger threaded analysis.

### 🔴 Hard

1. **Full pipeline: shell filters → processes forked → threads parse**
   Shell filters log → processes fork → threads count stack depths.

2. **Script coordinates process/thread jobs and logs summaries**
   Runs multiple C programs with forks and threads; collects summaries.

3. **Live log monitoring with tail, C threaded analyzer**
   Shell tails file and pipes to threaded C program.

4. **MapReduce-style analysis via shell, forked C threads**
   Shell splits logs, C programs act as mappers and reducers.

5. **Shell script manages job queue for C parsers with threads**
   Script assigns log files to forked/exec’d threaded programs using queue.

> 🧠 **C is the main controller**, using:

* `fork()`, `exec*()`, threads, pipes, signals
* And **invokes shell commands/scripts** as subprocesses

## ✅ Easy

1. **C program counts log lines via `wc -l` shell command**

   * C executes `wc -l log.txt` using `execvp()` or `popen()`
   * Displays total line count to stdout

2. **C forks and uses shell `grep` to extract ERROR lines**

   * C forks a process, uses `execlp("grep", ...)` to filter `[ERROR]` lines
   * Outputs to `errors.txt`

3. **C spawns a thread to run `system("sort log.txt")`**

   * Demonstrates thread and shell interaction
   * Thread handles logging the sorted output

4. **Threaded C program calls `cut` to extract user fields**

   * Each thread spawns a shell command like `cut -d' ' -f...` for users

5. **Use C to invoke shell `uniq` to get unique log levels**

   * C launches `cut`, `sort`, `uniq` pipeline using shell commands

---

## 🔶 Medium

1. **C uses threads to process segments of the log, shell script parses each**

   * C splits file into chunks
   * For each chunk, a thread runs a shell script that:

     * Greps `[user:...]`
     * Counts and returns total via `popen()`

2. **C forks multiple processes and passes data to shell via pipe**

   * Each process reads log lines and writes to a pipe
   * A shell command (e.g. `awk`, `sort`, `uniq`) is called with redirected stdin

3. **Threaded C app runs `grep` pipelines via `popen()`**

   * Threads each extract different log levels
   * Use `popen("grep INFO log.txt", "r")` etc.

4. **C analyzes log and calls shell `mv` to archive parts**

   * After finding too many `[ERROR]`, C calls `system("mv log.txt logs/archive/")`

5. **C program orchestrates parallel shell `grep` for apps**

   * C threads each call a `grep "app:AppName"` and aggregate results

---

## 🔴 Hard

1. **C program forks processes, each launching shell pipelines for analysis**

   * Each child handles a log level (`ERROR`, `INFO`, etc.)
   * Each child runs: `grep LEVEL | cut | sort | uniq` via `system()` or `popen()`
   * Parent waits for all children, aggregates total counts

2. **C multithreaded log parser runs shell compression after analysis**

   * After threads finish parsing logs, C runs `gzip` or `tar` using `execvp()` to compress output logs

3. **C creates FIFO, shell script reads from it, processes logs in real time**

   * C writes `[PERF]` logs to named pipe
   * Shell script reads from pipe and uses `awk` or `grep` to analyze durations
   * Demonstrates inter-process communication

4. **C processes log chunks, launches shell script to process each**

   * Thread per chunk, each thread writes to a temp file
   * C `fork()`s to run a shell script (`parse_chunk.sh`) on each file
   * Shell script returns summary; C aggregates

5. **Build hybrid log analyzer:**

   * C uses `fork()` to spawn log workers
   * Each worker thread spawns shell processes to:

     * Filter logs by timestamp
     * Extract and count `[err-msg:...]`
   * Results written to shared memory or files, then merged by parent

---