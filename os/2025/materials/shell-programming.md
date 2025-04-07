# Shell Scripting Examples for Beginners

Here are some simple and practical shell scripting examples to help you get started:

## 1. Hello World Script

```bash
#!/bin/bash
# This is a comment
echo "Hello World!"
```

Save this as `hello.sh`, then make it executable and run it:
```bash
chmod +x hello.sh
./hello.sh
```

## 2. Variables and User Input

```bash
#!/bin/bash
# Define a variable
name="World"
echo "Hello $name!"

# Get user input
echo "What's your name?"
read user_name
echo "Hello $user_name, nice to meet you!"
```

## 3. Simple Backup Script

```bash
#!/bin/bash
# Backup important files to a directory

# Variables
backup_dir="$HOME/backup"
date_stamp=$(date +%Y-%m-%d)

# Create backup directory if it doesn't exist
mkdir -p "$backup_dir/$date_stamp"

# Copy important files
cp -v ~/.bashrc "$backup_dir/$date_stamp/"
cp -v ~/.bash_history "$backup_dir/$date_stamp/"

echo "Backup completed to $backup_dir/$date_stamp"
```

## 4. If-Else Conditions

```bash
#!/bin/bash
# Check if a file exists

file_path="/etc/hosts"

if [ -f "$file_path" ]; then
    echo "The file $file_path exists!"
    echo "Here are the first 3 lines:"
    head -n 3 "$file_path"
else
    echo "The file $file_path does not exist."
fi
```

## 5. For Loop to Process Files

```bash
#!/bin/bash
# Print the size of all text files in current directory

echo "Checking size of all .txt files:"

for file in *.txt; do
    if [ -f "$file" ]; then
        size=$(du -h "$file" | cut -f1)
        echo "$file - $size"
    fi
done
```

## 6. Simple Menu Script

```bash
#!/bin/bash
# A simple menu

echo "Select an option:"
echo "1) Show date"
echo "2) List files"
echo "3) Check disk space"
echo "4) Exit"

read -p "Enter choice [1-4]: " choice

case $choice in
    1)
        date
        ;;
    2)
        ls -la
        ;;
    3)
        df -h
        ;;
    4)
        echo "Goodbye!"
        exit 0
        ;;
    *)
        echo "Invalid option!"
        ;;
esac
```

## 7. Count Files in Directories

```bash
#!/bin/bash
# Count files in each subdirectory

for dir in */; do
    if [ -d "$dir" ]; then
        count=$(find "$dir" -type f | wc -l)
        echo "$dir has $count files"
    fi
done
```

## 8. While Loop with Counter

```bash
#!/bin/bash
# Count from 1 to 5

counter=1
while [ $counter -le 5 ]; do
    echo "Count: $counter"
    counter=$((counter + 1))
    sleep 1  # Wait for 1 second
done
echo "Counting complete!"
```

## 9. Process Log Files

```bash
#!/bin/bash
# Find ERROR messages in a log file

log_file="/var/log/syslog"  # Adjust path as needed

if [ -f "$log_file" ]; then
    echo "Searching for errors in $log_file..."
    grep -i "error" "$log_file" | tail -5
else
    echo "Log file not found!"
fi
```

## 10. Script with Parameters

```bash
#!/bin/bash
# Use command line parameters

echo "Script name: $0"
echo "First parameter: $1"
echo "Second parameter: $2"
echo "All parameters: $@"
echo "Number of parameters: $#"

# Example usage: ./script.sh hello world
```

## Tips for Beginners:

1. Always start your script with `#!/bin/bash` (called a shebang)
2. Make your scripts executable with `chmod +x script.sh`
3. Use comments to explain what your script does
4. Test commands in the terminal before adding them to scripts
5. Indent your code for better readability
6. Use echo statements to debug your script
7. Always quote your variables like `"$variable"` to handle spaces properly

These simple examples should help you get started with shell scripting. Try modifying them to suit your needs and gradually build more complex scripts as you become comfortable!