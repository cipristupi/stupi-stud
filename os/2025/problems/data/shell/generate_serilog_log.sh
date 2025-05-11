#!/bin/bash

# ================================
# Serilog-Like Log Generator (Bash)
# ================================
# Usage:
#   chmod +x generate_serilog.sh
#   ./generate_serilog.sh <number_of_lines>
#
# Description:
#   This script generates a Serilog-like formatted log file (non-JSON) with random entries.
#   The output filename will be suffixed with the current date and time in ticks.

# Check if the number of lines is provided as argument
if [ -z "$1" ]; then
  echo "Usage: $0 <number_of_lines>"
  exit 1
fi

# Arrays of possible log components
users=("alice" "bob" "carol" "dan" "eve" "mallory" "trent" "peggy")
apps=("BillingEngine" "UserAuth" "FileUploader" "ReportGen" "CacheManager" "Notifier" "StreamSync")
methods=("Authenticate" "UploadFile" "GeneratePDF" "PurgeCache" "SendAlert" "SyncData" "ValidateToken")
levels=("Information" "Error" "Warning" "Verbose")
err_msgs=("Invalid token" "User not found" "Disk quota exceeded" "Connection timeout" "Unauthorized access" "Path does not exist" "Rate limit exceeded")
messages=("User login successful" "PDF report generated" "Cache cleared" "File uploaded" "System alert sent" "Sync completed" "Request throttled")
paths=("/tmp/file1.txt" "/data/img.jpg" "/etc/init.d/boot" "/opt/log/archive.zip")

# Get current time in milliseconds for unique filename
ticks=$(($(date +%s%N)/1000000))
filename="serilog_log_${ticks}.txt"
n=$1  # Number of lines to generate

# Function to generate random stack trace
generate_stack() {
    local app=$1
    local method=$2
    local parts=("Init" "Dispatch" "Finalize" "Verify" "Transform" "Collect")
    local path=""
    for i in $(seq 1 $((RANDOM % 3 + 2))); do
        path+="->${parts[$RANDOM % ${#parts[@]}]}"
    done
    echo "$app->$method$path"
}

# Function to generate a random log entry
generate_log() {
    now=$(date "+%Y-%m-%d %H:%M:%S")
    level=${levels[$RANDOM % ${#levels[@]}]}
    user=${users[$RANDOM % ${#users[@]}]}
    app=${apps[$RANDOM % ${#apps[@]}]}
    method=${methods[$RANDOM % ${#methods[@]}]}
    ip="$((RANDOM%255+1)).$((RANDOM%255+1)).$((RANDOM%255+1)).$((RANDOM%255+1))"
    msg="${messages[$RANDOM % ${#messages[@]}]}"
    stack=$(generate_stack "$app" "$method")

    log="$now [$level] App:$app User:$user Method:$method IP:$ip Message:'$msg'"

    # Add error message for "Error" level logs
    if [[ "$level" == "Error" ]] && (( RANDOM % 10 < 8 )); then
        log+=" ErrMsg:'${err_msgs[$RANDOM % ${#err_msgs[@]}]}'"
    fi

    # Add path field randomly
    if (( RANDOM % 4 == 0 )); then
        log+=" Path:'${paths[$RANDOM % ${#paths[@]}]}'"
    fi

    # Add thread information randomly
    if (( RANDOM % 3 == 0 )); then
        log+=" Thread:$((RANDOM % 9000 + 1000))"
    fi

    # Append the generated stack trace
    log+=" Stack:$stack"
    
    echo "$log"
}

# Empty the log file if it exists
> "$filename"

# Generate the requested number of log entries with progress indicator
for i in $(seq 1 $n); do
    generate_log >> "$filename"
    
    # Display progress as the number of lines generated
    if (( i % 100 == 0 )); then
        echo "Generated $i/$n lines..."
    fi
done

# Final progress message
echo "✅ Log written to $filename ($n lines)"
