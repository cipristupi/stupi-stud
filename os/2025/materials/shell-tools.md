# Unix Shell Tools Guide

Here's a comprehensive overview of essential Unix command-line tools:

## grep - Global Regular Expression Print

`grep` searches text or files for patterns matching a given regular expression.

**Basic usage:**
```bash
grep [options] pattern [file...]
```

**Common options:**
- `-i`: Case-insensitive search
- `-v`: Invert match (show non-matching lines)
- `-r`: Recursive search through directories
- `-n`: Show line numbers
- `-l`: Show only filenames of matching files

**Examples:**
```bash
grep "error" logfile.txt               # Find lines containing "error"
grep -i "warning" *.log                # Find "warning" case-insensitive in all .log files
grep -r "TODO" --include="*.py" .      # Find "TODO" in all Python files in current directory
```

## sed - Stream Editor

`sed` is used for parsing and transforming text.

**Basic usage:**
```bash
sed [options] 'command' [file...]
```

**Common commands:**
- `s/pattern/replacement/`: Substitute text
- `d`: Delete lines
- `p`: Print lines (usually with -n option)

**Examples:**
```bash
sed 's/old/new/' file.txt              # Replace first occurrence of "old" with "new"
sed 's/old/new/g' file.txt             # Replace all occurrences of "old" with "new"
sed -i 's/error/ERROR/g' file.txt      # Edit file in-place
sed '5d' file.txt                      # Delete line 5
sed '/pattern/d' file.txt              # Delete lines matching pattern
```

## awk - Aho, Weinberger, and Kernighan

`awk` is a powerful text processing tool designed for data extraction and reporting.

**Basic usage:**
```bash
awk [options] 'pattern {action}' [file...]
```

**Key concepts:**
- Fields: `$1`, `$2`, etc. (default delimiter is whitespace)
- `$0`: The entire line
- `NR`: Current line number
- `NF`: Number of fields in current line

**Examples:**
```bash
awk '{print $1, $3}' file.txt          # Print first and third columns
awk -F, '{print $2}' data.csv          # Print second column of CSV file
awk '$3 > 100 {print $0}' data.txt     # Print lines where third field > 100
awk 'NR > 10 {print $0}' file.txt      # Print lines after line 10
```

## find - Search for Files

`find` searches for files in a directory hierarchy.

**Basic usage:**
```bash
find [path] [options] [expression]
```

**Common options:**
- `-name pattern`: Match filename
- `-type f|d`: Find files (f) or directories (d)
- `-mtime n`: Files modified n days ago
- `-size n[cwbkMG]`: Files of size n

**Examples:**
```bash
find . -name "*.txt"                    # Find all .txt files in current directory
find /home -type d -name "logs"         # Find directories named "logs" under /home
find . -mtime -7 -type f                # Files modified in the last 7 days
find . -size +10M                       # Files larger than 10MB
```

## sort - Sort Lines of Text

`sort` sorts lines of text files.

**Basic usage:**
```bash
sort [options] [file...]
```

**Common options:**
- `-n`: Numeric sort
- `-r`: Reverse order
- `-k n`: Sort by n-th field
- `-u`: Remove duplicates (unique)

**Examples:**
```bash
sort file.txt                           # Sort lines alphabetically
sort -n numbers.txt                     # Sort numerically
sort -k2 -n data.txt                    # Sort by second field numerically
sort -r file.txt                        # Sort in reverse order
```

## uniq - Report or Filter Repeated Lines

`uniq` filters adjacent duplicate lines.

**Basic usage:**
```bash
uniq [options] [input [output]]
```

**Common options:**
- `-c`: Count occurrences
- `-d`: Only print duplicate lines
- `-u`: Only print unique lines

**Examples:**
```bash
sort file.txt | uniq                    # Remove adjacent duplicate lines (sort first!)
sort file.txt | uniq -c                 # Count unique lines
sort file.txt | uniq -d                 # Show only duplicate lines
```

## cut - Remove Sections from Lines

`cut` extracts portions of lines from files.

**Basic usage:**
```bash
cut [options] [file...]
```

**Common options:**
- `-d delimiter`: Set field delimiter
- `-f n`: Select fields
- `-c n`: Select characters

**Examples:**
```bash
cut -d',' -f1,3 data.csv               # Extract fields 1 and 3 from CSV
cut -c1-10 file.txt                    # Extract first 10 characters of each line
cut -d':' -f1 /etc/passwd              # Extract usernames from passwd file
```

## cat - Concatenate Files

`cat` concatenates and displays files.

**Basic usage:**
```bash
cat [options] [file...]
```

**Common options:**
- `-n`: Number output lines
- `-s`: Suppress repeated empty lines
- `-A`: Show all (display non-printing characters)

**Examples:**
```bash
cat file.txt                            # Display file contents
cat file1.txt file2.txt > combined.txt  # Combine files
cat -n file.txt                         # Display with line numbers
```

## Common Pipelines and Combinations

Unix tools excel when combined together:

```bash
# Count occurrences of a pattern
grep "error" logfile.txt | wc -l

# Extract and sort the third column
awk '{print $3}' data.txt | sort -n

# Find the 5 most common words in a file
cat file.txt | tr -s ' ' '\n' | sort | uniq -c | sort -nr | head -5

# Find large files modified in the last week
find . -type f -mtime -7 -size +10M -exec ls -lh {} \;

# Replace text in multiple files
find . -name "*.html" -exec sed -i 's/old/new/g' {} \;

# Extract usernames who logged in today
grep "$(date +%b' '%d)" /var/log/auth.log | grep "session opened" | awk '{print $11}' | sort | uniq
```

These tools form the foundation of Unix text processing and are essential for system administration, data analysis, and automation tasks.