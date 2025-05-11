#!/usr/bin/env python3
"""
===========================================
Custom Log Generator (Python)
===========================================
Usage:
    python3 generate_serilog_log.py <number_of_lines>

Description:
    This script generates a serilog-formatted log file with random entries.
    The output filename will be suffixed with the current time in ticks.
"""
import random, datetime, time, sys

def current_ticks():
    return int(time.time() * 1000)

users = ["alice", "bob", "carol", "dan", "eve", "mallory", "trent", "peggy"]
apps = ["BillingEngine", "UserAuth", "FileUploader", "ReportGen", "CacheManager", "Notifier", "StreamSync"]
methods = ["Authenticate", "UploadFile", "GeneratePDF", "PurgeCache", "SendAlert", "SyncData", "ValidateToken"]
levels = ["Information", "Error", "Warning", "Verbose"]
err_msgs = [
    "Invalid token", "User not found", "Disk quota exceeded", "Connection timeout",
    "Unauthorized access", "Path does not exist", "Rate limit exceeded"
]
messages = [
    "User login successful", "PDF report generated", "Cache cleared",
    "File uploaded", "System alert sent", "Sync completed", "Request throttled"
]

def gen_stack(app, method):
    call_chain = ["Init", "Process", "Dispatch", "Finalize"]
    return f"{app}->{method}->" + "->".join(random.sample(call_chain, random.randint(2, 4)))

def gen_log():
    now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    level = random.choice(levels)
    user = random.choice(users)
    app = random.choice(apps)
    method = random.choice(methods)
    ip = ".".join(str(random.randint(1, 254)) for _ in range(4))
    msg = random.choice(messages)
    stack = gen_stack(app, method)

    log = f"{now} [{level}] App:{app} User:{user} Method:{method} IP:{ip} Message:'{msg}'"
    if level == "Error":
        if random.random() < 0.8:
            log += f" ErrMsg:'{random.choice(err_msgs)}'"
    if random.random() < 0.4:
        log += f" Path:'{random.choice(['/tmp/file1.txt', '/data/img.jpg', '/etc/init.d/boot'])}'"
    if random.random() < 0.3:
        log += f" Thread:{random.randint(1000, 9999)}"
    log += f" Stack:{stack}"
    return log

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 generate_custom_log.py <number_of_lines>")
        sys.exit(1)
    LINES = int(sys.argv[1])
    filename = f"serilog_log_{current_ticks()}.txt"
    with open(filename, "w") as f:
        for _ in range(LINES):
            f.write(gen_log() + "\n")
    print(f"Log written to {filename}")
