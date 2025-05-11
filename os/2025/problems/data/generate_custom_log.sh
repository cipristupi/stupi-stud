#!/bin/bash
# generate_custom_log.sh

users=("alice" "bob" "carol" "dan")
apps=("FinanceService" "AuthService" "SearchAPI" "StorageManager")
methods=("Login" "ProcessInvoice" "SearchQuery" "WriteFile")
levels=("INFO" "ERROR" "WARNING" "PERF")
ips=("192.168.1.4" "10.0.0.14" "172.16.3.1" "192.168.5.23")
err_msgs=("Invalid password" "File not found" "Timeout occurred" "Permission denied")
ticks=$(($(date +%s%N)/1000000))
filename="custom_log_${ticks}.txt"

generate_log() {
    now=$(date "+%Y-%m-%d %H:%M:%S")
    level=${levels[$RANDOM % ${#levels[@]}]}
    user=${users[$RANDOM % ${#users[@]}]}
    app=${apps[$RANDOM % ${#apps[@]}]}
    method=${methods[$RANDOM % ${#methods[@]}]}
    ip=${ips[$RANDOM % ${#ips[@]}]}
    stack="$app->$method->$(shuf -n1 -e Validate Execute VerifyCredentials Save)"

    line="[$now] [$level] [app:$app] [user:$user] [method:$method] [ip:$ip]"
    [[ $level == "ERROR" ]] && line="$line [err-msg:${err_msgs[$RANDOM % ${#err_msgs[@]}]}]"
    [[ $level == "PERF" ]] && line="$line Duration: $((RANDOM % 250 + 50))ms"
    echo "$line Stack: $stack"
}

n=${1:-100}
> "$filename"
for i in $(seq 1 $n); do
    generate_log >> "$filename"
done

echo "Log written to $filename"
