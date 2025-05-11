#!/bin/bash
# generate_serilog_log.sh

users=("alice" "bob" "carol" "dan")
apps=("FinanceService" "AuthService" "SearchAPI" "StorageManager")
methods=("Login" "ProcessInvoice" "SearchQuery" "WriteFile")
levels=("Information" "Error" "Warning" "Verbose")
ips=("192.168.1.4" "10.0.0.14" "172.16.3.1" "192.168.5.23")
err_msgs=("Invalid password" "File not found" "Timeout occurred" "Permission denied")
ticks=$(($(date +%s%N)/1000000))
filename="serilog_log_${ticks}.txt"

generate_log() {
    now=$(date "+%Y-%m-%d %H:%M:%S")
    level=${levels[$RANDOM % ${#levels[@]}]}
    user=${users[$RANDOM % ${#users[@]}]}
    app=${apps[$RANDOM % ${#apps[@]}]}
    method=${methods[$RANDOM % ${#methods[@]}]}
    ip=${ips[$RANDOM % ${#ips[@]}]}
    msg=""
    case $level in
        "Information") msg="Operation completed successfully" ;;
        "Error") msg="An error occurred" ;;
        "Warning") msg="Potential issue detected" ;;
        "Verbose") msg="Performance metrics recorded" ;;
    esac
    stack="$app->$method->$(shuf -n1 -e Validate Execute VerifyCredentials Save)"

    log="$now [$level] App:$app User:$user Method:$method IP:$ip Message:'$msg'"
    [[ $level == "Error" ]] && log="$log ErrMsg:'${err_msgs[$RANDOM % ${#err_msgs[@]}]}'"
    log="$log Stack:$stack"
    echo "$log"
}

n=${1:-100}
> "$filename"
for i in $(seq 1 $n); do
    generate_log >> "$filename"
done

echo "Log written to $filename"
