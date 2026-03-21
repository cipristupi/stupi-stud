# Shell Scripting Examples Using Common Unix Tools

Here are simple and practical shell scripting examples that use common Unix tools like grep, sed, awk, find, sort, uniq, cut, and cat. These examples are designed for beginners.

## Using grep in Scripts

### 1. Search Log Files for Errors

```bash
#!/bin/bash
# Search for errors in a log file

log_file="/var/log/syslog"  # Change to your log file

echo "Searching for errors in $log_file..."
grep -i "error" "$log_file" | tail -10

echo "Found $(grep -i "error" "$log_file" | wc -l) error messages in total."
```

### 2. Find Users with Bash Shell

```bash
#!/bin/bash
# List all users with bash as their default shell

echo "Users with bash shell:"
grep "/bash" /etc/passwd | cut -d: -f1
```

## Using sed in Scripts

### 3. Replace Text in Multiple Files

```bash
#!/bin/bash
# Replace "old_text" with "new_text" in all .txt files

echo "Replacing 'old_text' with 'new_text' in all .txt files..."

for file in *.txt; do
    if [ -f "$file" ]; then
        echo "Processing $file..."
        sed -i 's/old_text/new_text/g' "$file"
    fi
done

echo "Replacement complete!"
```

### 4. Remove Comments from a Configuration File

```bash
#!/bin/bash
# Create a clean version of a config file without comments

config_file="/etc/ssh/sshd_config"  # Example config file
output_file="clean_config.txt"

echo "Creating clean version of $config_file..."

# Remove comments and empty lines
sed '/^#/d; /^$/d' "$config_file" > "$output_file"

echo "Clean configuration saved to $output_file"
```

## Using awk in Scripts

### 5. Calculate Total Size from ls -l

```bash
#!/bin/bash
# Calculate total file size in current directory

echo "Calculating total file size..."

ls -l | awk '
BEGIN {total=0}
{if (NR>1) total+=$5}
END {printf "Total size: %.2f MB\n", total/(1024*1024)}
'
```

### 6. Process CSV Data

```bash
#!/bin/bash
# Process a CSV file to calculate averages

csv_file="data.csv"  # Should have numeric data in columns

if [ -f "$csv_file" ]; then
    echo "Processing $csv_file..."
    
    # Assuming CSV with header row and numeric 2nd column
    awk -F, '
    NR>1 {sum+=$2; count++}
    END {printf "Average of column 2: %.2f\n", sum/count}
    ' "$csv_file"
else
    echo "File $csv_file not found!"
fi
```

## Using find in Scripts

### 7. Find and Delete Old Files

```bash
#!/bin/bash
# Find and delete files older than 30 days

target_dir="$HOME/Downloads"  # Change to your directory
days=30

echo "Finding files older than $days days in $target_dir..."

# List files first
echo "Would delete these files:"
find "$target_dir" -type f -mtime +$days -exec ls -l {} \;

# Uncomment the next line to actually delete files
# find "$target_dir" -type f -mtime +$days -delete

echo "Done. Remove the # to actually delete files when you're sure."
```

### 8. Find and Process Specific Files

```bash
#!/bin/bash
# Find all JPG files and create a thumbnail directory

source_dir="$HOME/Pictures"
thumb_dir="$HOME/Pictures/thumbnails"

# Create thumbnail directory if it doesn't exist
mkdir -p "$thumb_dir"

echo "Creating thumbnails for JPG files in $source_dir..."

# Find all JPG files and create thumbnails (requires ImageMagick)
find "$source_dir" -name "*.jpg" -type f -exec bash -c '
    filename=$(basename "$1")
    echo "Processing $filename..."
    convert "$1" -resize 200x "$2/$filename"
' bash {} "$thumb_dir" \;

echo "Thumbnails created in $thumb_dir"
```

## Using sort, uniq, and cut in Scripts

### 9. Analyze Web Server Logs

```bash
#!/bin/bash
# Analyze Apache access logs to find top IP addresses

log_file="/var/log/apache2/access.log"  # Change to your log file

if [ -f "$log_file" ]; then
    echo "Top 5 IP addresses accessing the server:"
    
    # Extract IP address (first field), sort, count, and show top 5
    cut -d' ' -f1 "$log_file" | sort | uniq -c | sort -nr | head -5
else
    echo "Log file not found!"
fi
```

### 10. Find Duplicate Files by Size

```bash
#!/bin/bash
# Find potentially duplicate files based on size

target_dir="$HOME/Documents"  # Change to your directory

echo "Finding potential duplicate files in $target_dir..."

# Find files, extract size and name, sort by size, and group
find "$target_dir" -type f -exec du -b {} \; | sort -n | cut -f1,2 | awk '
{
    size=$1;
    name=$2;
    if (lastsize == size) {
        printf "Potential duplicate: %s (%d bytes)\n", name, size;
        if (first_match) {
            printf "                   %s (%d bytes)\n", lastname, lastsize;
            first_match = 0;
        }
    } else {
        first_match = 1;
    }
    lastname = name;
    lastsize = size;
}'
```

## Using cat and Other Tools Together

### 11. Combine and Process Text Files

```bash
#!/bin/bash
# Combine text files, remove duplicates, and sort

output_file="combined.txt"

echo "Combining all .txt files, removing duplicates, and sorting..."

# Combine all .txt files, sort, and remove duplicates
cat *.txt | sort | uniq > "$output_file"

echo "Result saved to $output_file with $(wc -l < "$output_file") lines."
```

### 12. Create a System Info Report

```bash
#!/bin/bash
# Create a system information report

report_file="system_report.txt"

echo "Creating system report in $report_file..."

# Start with a clean file
cat > "$report_file" << EOF
System Report
Date: $(date)
Hostname: $(hostname)
===========================================

EOF

# Add CPU info
echo "CPU Information:" >> "$report_file"
grep "model name" /proc/cpuinfo | head -1 | sed 's/model name\s*: //' >> "$report_file"
echo "" >> "$report_file"

# Add memory info
echo "Memory Information:" >> "$report_file"
free -h | grep -v + >> "$report_file"
echo "" >> "$report_file"

# Add disk info
echo "Disk Usage:" >> "$report_file"
df -h | grep -v tmpfs >> "$report_file"
echo "" >> "$report_file"

# Add top processes
echo "Top 5 Processes by CPU Usage:" >> "$report_file"
ps aux | sort -rk 3,3 | head -6 >> "$report_file"
echo "" >> "$report_file"

echo "Report created at $report_file"
```

## Combined Tool Scripts

### 13. Log File Analyzer

```bash
#!/bin/bash
# Analyze a log file for errors and warnings

log_file="/var/log/syslog"  # Change to your log file
report_file="log_analysis.txt"

echo "Analyzing $log_file..."

# Create report header
cat > "$report_file" << EOF
Log Analysis Report
File: $log_file
Date: $(date)
===========================================

EOF

# Count and list errors
error_count=$(grep -i "error" "$log_file" | wc -l)
echo "Total Errors: $error_count" >> "$report_file"
echo "" >> "$report_file"

echo "Most Common Errors:" >> "$report_file"
grep -i "error" "$log_file" | awk '{$1=$2=$3=$4=""; print $0}' | sed 's/^[ \t]*//' | sort | uniq -c | sort -nr | head -5 >> "$report_file"
echo "" >> "$report_file"

# Count and list warnings
warning_count=$(grep -i "warning" "$log_file" | wc -l)
echo "Total Warnings: $warning_count" >> "$report_file"
echo "" >> "$report_file"

echo "Most Common Warnings:" >> "$report_file"
grep -i "warning" "$log_file" | awk '{$1=$2=$3=$4=""; print $0}' | sed 's/^[ \t]*//' | sort | uniq -c | sort -nr | head -5 >> "$report_file"
echo "" >> "$report_file"

# Time distribution analysis
echo "Error Distribution by Hour:" >> "$report_file"
grep -i "error" "$log_file" | cut -c12-13 | sort | uniq -c | sort -n -k2 >> "$report_file"

echo "Analysis complete! Check $report_file for results."
```

### 14. File Organization Script

```bash
#!/bin/bash
# Organize files in a directory by extension

source_dir="$HOME/Downloads"  # Change to your directory

echo "Organizing files in $source_dir by extension..."

# Find unique file extensions
extensions=$(find "$source_dir" -type f -name "*.*" | sed 's/.*\.//' | sort | uniq)

# Create directories and move files
for ext in $extensions; do
    # Skip if extension is empty
    if [ -z "$ext" ]; then
        continue
    fi
    
    # Create directory if it doesn't exist
    mkdir -p "$source_dir/$ext"
    
    echo "Moving .$ext files..."
    find "$source_dir" -maxdepth 1 -type f -name "*.$ext" -exec mv {} "$source_dir/$ext/" \;
done

echo "Organization complete!"
```

### 15. Database Query Results Processor

```bash
#!/bin/bash
# Process database query results (simulated with CSV)

data_file="database_export.csv"  # Your CSV file with database data

if [ ! -f "$data_file" ]; then
    echo "Data file not found!"
    exit 1
fi

echo "Processing database data from $data_file..."

# Summary statistics - assuming CSV with header row and numeric columns
echo "Summary Statistics:"
awk -F, '
BEGIN {lines=0; sum=0;}
NR>1 {
    lines++;
    sum+=$3;  # Assuming the 3rd column has numeric values
}
END {
    printf "Total records: %d\n", lines;
    printf "Average value: %.2f\n", sum/lines;
}' "$data_file"

# Find top values
echo -e "\nTop 5 entries by value:"
sort -t, -k3,3nr "$data_file" | head -6

# Count entries by category (assuming 2nd column is category)
echo -e "\nEntries by category:"
cut -d, -f2 "$data_file" | tail -n +2 | sort | uniq -c | sort -nr

echo "Processing complete!"
```

## Tips for Working with Unix Tools in Scripts

1. **Test commands in terminal first** before adding them to scripts
2. **Use echo statements** to debug your script
3. **Add comments** to explain complex commands
4. **Use '-v' or '--verbose'** options when available to see what's happening
5. **Redirect errors** to separate files with `2> error.log`
6. **Use variables** for frequently used values like filenames or directories
7. **Check if files exist** before processing them
8. **Use quotes around variables** to handle spaces in filenames
9. **Create backup copies** before modifying important files

These examples show how powerful shell scripting can be when you combine different Unix tools. Start with the simpler scripts and gradually work your way up to the more complex ones!