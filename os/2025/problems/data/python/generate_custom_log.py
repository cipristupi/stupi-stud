# generate_custom_log.py
import random, datetime, time, sys, os

def current_ticks():
    return int(time.time() * 1000)

users = ["alice", "bob", "carol", "dan"]
apps = ["FinanceService", "AuthService", "SearchAPI", "StorageManager"]
methods = ["Login", "ProcessInvoice", "SearchQuery", "WriteFile"]
levels = ["INFO", "ERROR", "WARNING", "PERF"]
ips = ["192.168.1.4", "10.0.0.14", "172.16.3.1", "192.168.5.23"]
err_msgs = ["Invalid password", "File not found", "Timeout occurred", "Permission denied"]

def gen_stack(app, method):
    return f"{app}->{method}->" + random.choice(["Validate", "Execute", "VerifyCredentials", "Save"])

def gen_line():
    level = random.choice(levels)
    user = random.choice(users)
    app = random.choice(apps)
    method = random.choice(methods)
    ip = random.choice(ips)
    now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    line = f"[{now}] [{level}] [app:{app}] [user:{user}] [method:{method}] [ip:{ip}]"
    if level == "ERROR":
        line += f" [err-msg:{random.choice(err_msgs)}]"
    if level == "PERF":
        line += f" Duration: {random.randint(50,300)}ms"
    line += f" Stack: {gen_stack(app, method)}"
    return line

if __name__ == "__main__":
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 100
    filename = f"custom_log_{current_ticks()}.txt"
    with open(filename, "w") as f:
        for _ in range(n):
            f.write(gen_line() + "\n")
    print(f"Log written to {filename}")
