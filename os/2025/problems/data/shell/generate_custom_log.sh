#!/bin/bash
# ================================
# Custom-Like Log Generator (Bash)
# ================================
# Usage:
#   chmod +x generate_custom_log.sh
#   ./generate_custom_log.sh <number_of_lines>
#
# Description:
#   This script generates a Custom-like formatted log file (non-JSON) with random entries.
#   The output filename will be suffixed with the current date and time in ticks.

# Check if number of lines is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <number_of_lines>"
  exit 1
fi

users=("alice" "bob" "carol" "dan" "eve" "mallory" "trent" "peggy")
apps=("BillingEngine" "UserAuth" "FileUploader" "ReportGen" "CacheManager" "Notifier" "StreamSync")
methods=("Authenticate" "UploadFile" "GeneratePDF" "PurgeCache" "SendAlert" "SyncData" "ValidateToken")
levels=("INFO" "ERROR" "WARNING" "PERF")
err_msgs=("Invalid token" "User not found" "Disk quota exceeded" "Connection timeout" "Unauthorized access" "Path does not exist" "Rate limit exceeded")
paths=("/data/files/report.pdf" "/var/log/syslog" "/mnt/backup/img.tar.gz" "/etc/config/settings.json")

ticks=$(($(date +%s%N)/1000000))
filename="custom_log_${ticks}.txt"
n=$1

generate_stack() {
    local app=$1
    local method=$2
    local steps=("Init" "Process" "Validate" "Save" "Execute" "Retry")
    local chain=""
    for i in $(seq 1 $((RANDOM % 3 + 2))); do
        chain+="->${steps[$RANDOM % ${#steps[@]}]}"
    done
    echo "$app->$method$chain"
}

generate_log() {
    now=$(date "+%Y-%m-%d %H:%M:%S")
    level=${levels[$RANDOM % ${#levels[@]}]}
    user=${users[$RANDOM % ${#users[@]}]}
    app=${apps[$RANDOM % ${#apps[@]}]}
    method=${methods[$RANDOM % ${#methods[@]}]}
    ip="$((RANDOM%255+1)).$((RANDOM%255+1)).$((RANDOM%255+1)).$((RANDOM%255+1))"
    stack=$(generate_stack "$app" "$method")
    line="[$now] [$level] [user:$user] [app:$app] [method:$method] [ip:$ip]"

    if (( RANDOM % 5 == 0 )); then
        line+=" [path:${paths[$RANDOM % ${#paths[@]}]}]"
    fi
    if [[ "$level" == "ERROR" ]] && (( RANDOM % 10 < 9 )); then
        line+=" [err-msg:${err_msgs[$RANDOM % ${#err_msgs[@]}]}]"
    fi
    if [[ "$level" == "PERF" ]]; then
        line+=" [duration:$((RANDOM % 1200 + 30))ms]"
    fi
    if (( RANDOM % 2 == 0 )); then
        line+=" [thread:$((RANDOM % 9000 + 1000))]"
    fi
    echo "$line Stack:$stack"
}

> "$filename"
for i in $(seq 1 $n); do
    generate_log >> "$filename"
done

echo "Log written to $filename"
