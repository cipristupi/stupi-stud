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

ticks=$(($(date +%s%N)/1000000))  # Get current time in milliseconds for unique filename
filename="custom_log_${ticks}.txt"
n=$1  # Number of lines to generate

# Generate stack trace
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

# Generate a random log entry
generate_log() {
    now=$(date "+%Y-%m-%d %H:%M:%S")
    level=${levels[$RANDOM % ${#levels[@]}]}
    user=${users[$RANDOM % ${#users[@]}]}
    app=${apps[$RANDOM % ${#apps[@]}]}
    method=${methods[$RANDOM % ${#methods[@]}]}
    ip="$((RANDOM%255+1)).$((RANDOM%255+1)).$((RANDOM%255+1)).$((RANDOM%255+1))"
    stack=$(generate_stack "$app" "$method")
    line="[$now] [$level] [user:$user] [app:$app] [method:$method] [ip:$ip]"

    # Add optional path field randomly
    if (( RANDOM % 5 == 0 )); then
        line+=" [path:${paths[$RANDOM % ${#paths[@]}]}]"
    fi

    # Add error message for errors
    if [[ "$level" == "ERROR" ]] && (( RANDOM % 10 < 9 )); then
        line+=" [err-msg:${err_msgs[$RANDOM % ${#err_msgs[@]}]}]"
    fi

    # Add performance duration for "PERF" level logs
    if [[ "$level" == "PERF" ]]; then
        line+=" [duration:$((RANDOM % 1200 + 30))ms]"
    fi

    # Add thread information
    if (( RANDOM % 2 == 0 )); then
        line+=" [thread:$((RANDOM % 9000 + 1000))]"
    fi

    # Append the generated stack trace
    echo "$line Stack:$stack"
}

# Empty the log file if it exists
> "$filename"

# Generate the requested number of log entries with progress indicator
for i in $(seq 1 $n); do
    generate_log >> "$filename"
    
    # Display progress every 100 lines
    if (( i % 100 == 0 )); then
        echo "Generated $i/$n lines..."
    fi
done

# Final progress message
echo "✅ Log written to $filename ($n lines)"
