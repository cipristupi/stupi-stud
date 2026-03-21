#!/usr/bin/env python3
"""
===========================================
Custom Log Generator (Python)
===========================================
Usage:
    python3 generate_custom_log.py <number_of_lines>

Description:
    This script generates a custom-formatted log file with random entries.
    The output filename will be suffixed with the current time in ticks.
"""
import random, datetime, time, sys

def current_ticks():
    return int(time.time() * 1000)

users = ["alice", "bob", "carol", "dan", "eve", "mallory", "trent", "peggy"]
apps = ["BillingEngine", "UserAuth", "FileUploader", "ReportGen", "CacheManager", "Notifier", "StreamSync"]
methods = ["Authenticate", "UploadFile", "GeneratePDF", "PurgeCache", "SendAlert", "SyncData", "ValidateToken"]
levels = ["INFO", "ERROR", "WARNING", "PERF"]
err_msgs = [
    "Invalid token", "User not found", "Disk quota exceeded", "Connection timeout",
    "Unauthorized access", "Path does not exist", "Rate limit exceeded"
]
ip_octet = lambda: str(random.randint(1, 254))
paths = ["/data/files/report.pdf", "/var/log/syslog", "/mnt/backup/img.tar.gz", "/etc/config/settings.json"]

def gen_stack(app, method):
    steps = random.choices(["Init", "Process", "Validate", "Save", "Execute", "Retry"], k=random.randint(2, 4))
    return f"{app}->{'->'.join([method] + steps)}"

def gen_line():
    now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    level = random.choice(levels)
    user = random.choice(users)
    app = random.choice(apps)
    method = random.choice(methods)
    ip = f"{ip_octet()}.{ip_octet()}.{ip_octet()}.{ip_octet()}"
    stack = gen_stack(app, method)
    line = f"[{now}] [{level}] [user:{user}] [app:{app}] [method:{method}] [ip:{ip}]"

    if random.random() < 0.2:
        line += f" [path:{random.choice(paths)}]"
    if level == "ERROR" and random.random() < 0.9:
        line += f" [err-msg:{random.choice(err_msgs)}]"
    if level == "PERF":
        line += f" [duration:{random.randint(40, 1200)}ms]"
    if random.random() < 0.5:
        line += f" [thread:{random.randint(1000, 9999)}]"

    line += f" Stack:{stack}"
    return line

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 generate_custom_log.py <number_of_lines>")
        sys.exit(1)
    LINES = int(sys.argv[1])
    filename = f"custom_log_{current_ticks()}.txt"
    with open(filename, "w") as f:
        for _ in range(LINES):
            f.write(gen_line() + "\n")
    print(f"Log written to {filename}")
