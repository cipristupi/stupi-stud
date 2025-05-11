# 📘 Log Processing Student Problems (Detailed)

> Based on shell and C programming concepts: `grep`, `sed`, `awk`, `cut`, `sort`, `uniq`, `cat`, `find`, etc., and C concepts: `fork`, `wait`, `exec`, `exit`, `signal`, `kill`, IPC (`pipe`, `FIFO`), POSIX threads (`mutex`, `cond`, `rwlock`, `barrier`).

---

## 🛠️ 1. Only Shell Programming

### 🟢 Easy

1. **Count Log Entries**
   Count how many log lines exist across all log files.
   *Hints:* `cat`, `wc -l`, `find`, `xargs`

2. **Filter ERROR Logs**
   Display only lines marked with `ERROR`.
   *Hints:* `grep 'ERROR'`, file globbing

3. **List Unique Users**
   Extract and show all distinct users from `[user:xyz]` tags.
   *Hints:* `grep`, `cut`, `sort`, `uniq`

4. **Filter by App Name**
   Show logs from a specific app using `[app:AppName]` tag.
   *Hints:* `grep`, pattern matching

5. **Sort Logs Chronologically**
   Sort all logs using their readable timestamp.
   *Hints:* `sort -k`, timestamp field, `cut`

### 🟡 Medium

1. **Log Count per Level per App**
   Group by log level and app, count frequency.
   *Hints:* `awk`, `sort`, `uniq -c`, `cut`

2. **User Logs Sorted by Time**
   Extract logs of a given user, then sort by time.
   *Hints:* `grep`, `sort`, `awk`

3. **Hourly Log Summary**
   Count logs per hour from datetime field.
   *Hints:* `cut`, `uniq -c`, `awk`

4. **Save Failed Logs**
   Save all ERROR and WARNING logs to a new file.
   *Hints:* `grep`, output redirection

5. **Detect Duplicates**
   Find repeated lines and how often they occur.
   *Hints:* `sort`, `uniq -d -c`

### 🔴 Hard

1. **Live Severity Monitor**
   Continuously tail logs and classify by level.
   *Hints:* `tail -f`, `grep`, `tee`

2. **Top Users by Log Count**
   Show users ranked by how many logs they generated.
   *Hints:* `cut`, `sort`, `uniq -c`, `sort -nr`

3. **Merge Sorted Logs**
   Merge and sort logs from multiple files.
   *Hints:* `cat`, `sort`, `uniq`

4. **Alert on Frequent Errors**
   Print an alert if ERROR logs > 10 per minute.
   *Hints:* `grep`, `awk`, `sleep`, timestamp logic

5. **Performance Log Breakdown**
   Filter `[PERF]` logs and analyze processing time.
   *Hints:* `awk`, regex, numerical sort

---

## 🛠️ 2. Only C Programming with Processes

### 🟢 Easy

1. **Fork a Child to Count Logs**
   Parent spawns child to count lines in a file.
   *Hints:* `fork()`, `open()`, `read()`, `wait()`

2. **Filter ERROR Logs via Process**
   Child reads file and outputs only ERROR entries.
   *Hints:* `fork()`, string matching, file I/O

3. **Get Unique Apps in Logs**
   Extract `[app:...]` tags from logs using process.
   *Hints:* `fork()`, `strstr()`, set logic

4. **Sort Logs by Timestamp**
   Child sorts lines based on timestamp string.
   *Hints:* `fork()`, string comparison, `qsort()`

5. **Count Users in Parallel Files**
   Spawn process per file to count user tags.
   *Hints:* `fork()`, loop on files, `wait()`

### 🟡 Medium

1. **App Log Frequency Counter**
   Count log levels per app across multiple files.
   *Hints:* multiple `fork()`, parsing logic

2. **User Logs to File**
   Extract user logs and write to a dedicated file.
   *Hints:* `fork()`, `write()`, file filters

3. **Hourly Summary**
   Parse timestamp and count logs per hour.
   *Hints:* `strptime()`, time struct, `fork()`

4. **Duplicate Line Detection**
   Use C map/hash table to count duplicates.
   *Hints:* hash maps, `fork()`, file parsing

5. **Filter by IP**
   Extract logs from specific IP ranges.
   *Hints:* `strstr()`, regex, `fork()`

### 🔴 Hard

1. **Multi-Process Summary Tool**
   Fork N children, each analyzes a different file.
   *Hints:* `fork()`, `waitpid()`, aggregate results

2. **Log Analyzer with Signals**
   Terminate process on too many errors using `SIGINT`.
   *Hints:* `signal()`, error threshold, `kill()`

3. **Parent Aggregator Process**
   Children send back data for parent to combine.
   *Hints:* `fork()`, shared memory or temporary files

4. **Fork-Tree Log Monitor**
   Recursive fork for log tree parsing.
   *Hints:* multiple `fork()`, pipe trees

5. **Failover Log Handling**
   Restart process if crash occurs during parsing.
   *Hints:* `fork()`, `wait()`, `WIFEXITED`

---

## 🛠️ 3. Only C with Processes + Communication

### 🟢 Easy

1. **Pipe to Count Logs**
   Child counts lines, sends count via pipe.
   *Hints:* `pipe()`, `fork()`, `read()`, `write()`

2. **Child Sends Errors to Parent**
   Filtered ERROR logs sent through pipe.
   *Hints:* `pipe()`, `strstr()`, string buffer

3. **Send User Count to Parent**
   Count unique users, send count via pipe.
   *Hints:* `pipe()`, set logic

4. **Child Sends Sorted Logs**
   Child sorts and returns logs.
   *Hints:* `pipe()`, `qsort()`, buffer read/write

5. **Parent Receives Log Sizes**
   Each child returns size of log files.
   *Hints:* `stat()`, `pipe()`, `fork()`

### 🟡 Medium

1. **Multiple Children Summary**
   Children process log levels and report back.
   *Hints:* `pipe()`, struct passing

2. **App-Specific Filter & Return**
   Child filters logs by app, parent saves output.
   *Hints:* pipe communication, string filters

3. **Hourly Count Return**
   Return hourly breakdown via structured buffer.
   *Hints:* time parsing, data struct

4. **Child Detects Duplicates**
   Returns duplicate count to parent.
   *Hints:* line hashing, pipe

5. **Log Alerts via Pipe**
   Signal parent if too many errors detected.
   *Hints:* error counter, signal via pipe

### 🔴 Hard

1. **Dynamic Log Parsing Chain**
   Pipe output of one child to another.
   *Hints:* `pipe()`, chaining pipes

2. **Fork & Combine Logs by Tags**
   Parallel parsing by tag, return summaries.
   *Hints:* `pipe()`, string parsing, sync

3. **Live Communication with Parent**
   Use `select()` to receive log snippets.
   *Hints:* non-blocking pipe, monitoring

4. **Child Alerts with Signals & Data**
   Send signal + pipe message on error bursts.
   *Hints:* `signal()`, `write()`, `alarm()`

5. **Multiple Streams Aggregator**
   Handle pipes from many children simultaneously.
   *Hints:* `poll()`, multiple `pipe()`

---

## 🛠️ 4. Only C Programming with Threads

### 🟢 Easy

1. **Thread per Log Chunk**
   Divide log file, process in separate threads.
   *Hints:* `pthread_create()`, `fseek()`, thread fn

2. **Thread Filters Errors**
   One thread reads, one filters, another displays.
   *Hints:* `pthread`, filters, shared buffer

3. **User Count via Threads**
   Count users using multiple threads and merge.
   *Hints:* atomic counter, mutex

4. **App-specific Logs**
   Each thread parses one app's logs.
   *Hints:* thread parameters

5. **Log Level Counter**
   Threads count log levels separately.
   *Hints:* `pthread`, shared struct, mutex

### 🟡 Medium

1. **Parallel Hourly Parser**
   Each thread handles an hour block of data.
   *Hints:* timestamp filter, mutex

2. **Threaded File Merger**
   Combine files and resolve duplicate timestamps.
   *Hints:* sorted merge, barrier

3. **Thread Log Summary Writer**
   Worker threads parse logs, main thread writes summary.
   *Hints:* condition variable, shared queue

4. **Threaded Duplicate Finder**
   Detect duplicate lines across segments.
   *Hints:* hash table + mutex

5. **Threaded Log Alert Monitor**
   Raise flag if too many ERRORs in time window.
   *Hints:* time checks, mutex counter

---

## 🛠️ 5. C Programming with Processes and Threads

### 🟢 Easy

1. **Spawn Process and Thread**
   Parent process forks, and each child spawns a thread to process a portion of the log file.
   *Hints:* `fork()`, `pthread_create()`, divide file by byte range or lines

2. **Parallel App Log Filtering**
   Each child process filters logs by a specific app and uses a thread for each log level.
   *Hints:* process per app, thread per level, `pipe()` for collection

3. **Count Logs in Parallel**
   Each process/thread pair counts total logs in a file.
   *Hints:* fork N children, each with a counting thread, aggregate with `wait()`

4. **Sort and Print Logs by Time**
   Each child process has a thread to sort its file segment and return sorted data.
   *Hints:* `qsort()`, thread-safe buffer

5. **Log Summary per Segment**
   Threads parse ranges within file for ERROR/INFO counts and write summary.
   *Hints:* `pthread`, shared struct, mutex

### 🟡 Medium

1. **Dynamic Work Queue for Threads in Children**
   Processes generate tasks (log lines) and distribute to threads.
   *Hints:* task queue, mutex, thread pool

2. **Multi-threaded Children Send Stats**
   Each child has threads analyze logs and return to parent.
   *Hints:* `pipe()`, `pthread`, structured output

3. **Parallel Duplicate Detection**
   Each thread checks for duplication in a segment; processes resolve overlap.
   *Hints:* thread hash table, cross-process coordination

4. **Segmented File Analyzer**
   Divide log file into N parts, fork processes with threads to parse each.
   *Hints:* file segmentation, `fseek()`, thread pooling

5. **App/Level/Time Summary**
   Multi-process/thread setup that summarizes logs by app, level, and hour.
   *Hints:* parsing pipeline, time group logic, mutex

### 🔴 Hard

1. **Real-Time Log Monitor with Recovery**
   Use watchdog process to restart child if threads crash during monitoring.
   *Hints:* `pthread`, `signal()`, `waitpid()`, health flag

2. **Process-Thread Hierarchy with Aggregation**
   Top-level process forks workers, each spawning threads for level parsing.
   *Hints:* tree design, file partitioning, pipe return

3. **Concurrent Alerting System**
   Threads monitor error rates; processes communicate status and escalate alerts.
   *Hints:* rate limiting, mutexes, inter-process flags

4. **Shared Memory Ring Buffer**
   Threads push data into a ring buffer, shared across processes.
   *Hints:* `shm_open()`, `mmap()`, mutex in shared region

5. **Crash-Resilient Log Analyzer**
   Fault-tolerant thread/process design with fallback and retry.
   *Hints:* `setjmp()`, recovery logic, process restart on failure

---

## 🛠️ 6. C Programming with Processes, Threads, and Shell Scripting (C is Main Controller)

### 🟢 Easy

1. **C Calls Shell Script to Count Logs**
   C spawns shell to run `wc -l` and collects output.
   *Hints:* `popen()`, `execvp()`, `fgets()`

2. **Shell Extracts Logs, Threads Parse**
   Shell script filters logs, C threads parse output.
   *Hints:* `system()`, `fopen()`, multithread parsing

3. **Shell Lists Files, C Loads with Threads**
   C calls shell to find logs, threads load and parse.
   *Hints:* `find`, `pthread`, thread-safe buffer

4. **Shell Error Extractor + C Summary**
   Shell filters ERROR logs to temp file; C processes lines.
   *Hints:* `system()`, file I/O, log summary

5. **C Invokes grep for Filtering**
   `grep` via shell extracts lines, thread parses.
   *Hints:* `exec()`, temporary files or `popen()`

### 🟡 Medium

1. **C Master – Shell Scanner – Threaded Parser**
   Shell finds files and filters, C threads analyze level frequency.
   *Hints:* `popen()`, `pthread`, mutex for results

2. **Shell Scripts Log Rotator**
   Shell rotates logs; C waits, then forks thread workers.
   *Hints:* `stat()`, log aging, `pthread`

3. **C + Shell Sync Parsing**
   Shell processes time ranges, C threads parse outputs and sync results.
   *Hints:* file partitioning, time parsing

4. **Log Processor via Bash Script CLI**
   Shell provides arguments; C reads and dispatches threads.
   *Hints:* `argv`, `popen()`, file filters

5. **Hybrid Duplicate Analyzer**
   Shell prepares segments; C runs thread per chunk for duplicates.
   *Hints:* string hashing, `grep`, `uniq`, `pthread`

### 🔴 Hard

1. **Multi-Stage Pipeline: Shell → C Process → Threads**
   Shell filters, C process aggregates, threads parse each metric.
   *Hints:* `exec()`, parsing, file pipe

2. **Interactive Log Control**
   Shell manages inputs to C; C forks threads and updates status in terminal.
   *Hints:* `read()`, shell UI loop, thread-safe display

3. **C Threads Monitor, Shell Reports**
   Threads write status files, shell scripts poll and report to terminal.
   *Hints:* watchdog shell loop, `sleep`, log flags

4. **Shell Log Merging, C Thread Aggregator**
   Shell merges logs, threads compute app/user/hour stats.
   *Hints:* structured parsing, level grouping

5. **C-Shell Real-Time Analyzer**
   Shell streams logs via FIFO; C reads and threads analyze on the fly.
   *Hints:* `mkfifo()`, `read()`, thread-safe queue

---

## 🛠️ 7. C with Processes, Threads, and Parent-Child Communication

### 🟢 Easy

1. **Child with Threads Parses Logs**
   Child spawns threads, then returns summary to parent.
   *Hints:* `pthread`, `pipe()`, structured data write

2. **Pipe Communication to Parent**
   Threads write stats to pipe; parent reads all results.
   *Hints:* `pthread`, `write()`, `read()`, aggregation

3. **Threaded File Handlers in Child**
   Each thread reads a file, and child sends merged result.
   *Hints:* buffer logic, `pipe()`, `pthread`

4. **Hourly Breakdown via Threads**
   Threads parse by hour; child sends stats to parent.
   *Hints:* time parsing, buffer aggregation

5. **Duplicate Detector Communicator**
   Detects duplicates; threads tally and child reports.
   *Hints:* thread-safe hash, pipe summary

### 🟡 Medium

1. **Children with Thread Pools**
   Children spawn thread pool to parse logs concurrently.
   *Hints:* reusable thread queue, `pipe()`, result structs

2. **Parent Aggregator**
   Threads in child parse by app; parent combines results.
   *Hints:* inter-process summary, tagged pipe data

3. **Threaded Parser Sends Alerts**
   Threads detect errors and signal parent process.
   *Hints:* `signal()`, alert condition

4. **Parallel Histogram Generator**
   Threads create histograms (levels/times); child returns summary.
   *Hints:* time grouping, mutex, pipe

5. **App-Specific Threaded Analyzers**
   Each thread handles one app’s logs; results piped.
   *Hints:* buffer management, `fork()`, filtering

---

## 🛠️ 8. C as Main Controller with Shell + Processes + Threads

> **Already covered above in Section 6**

---

## 🛠️ 9. C as Controller + Shell + Threads + Process Communication

> **Combines all above + IPC (pipe/FIFO/shared memory)**

### 🔴 Hard Only

1. **Shell Finds Logs → FIFO Streams to C → Threads Parse**
   Shell uses `find`, writes to FIFO; C reads, threads parse.
   *Hints:* `mkfifo()`, `pthread`, FIFO reader

2. **Real-Time Log Pipeline with Alerts**
   Shell `tail -f` → pipe → C → threaded alert system.
   *Hints:* live pipe reader, alert threads

3. **Shared Memory Summary Writer**
   Threads write to shared memory; another process reads.
   *Hints:* `shm_open()`, `mmap()`, mutex

4. **Parent Monitors, Shell Reacts**
   Threads write status files; shell scripts send user alerts.
   *Hints:* C status output, `bash` checker loop

5. **Full Hybrid Monitoring Stack**
   Shell rotates logs, C processes with threads, communication via pipe and shared mem.
   *Hints:* all tools: `pipe()`, `fork()`, `pthread`, `exec()`, `shm_open()`

---