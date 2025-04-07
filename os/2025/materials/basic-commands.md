# Linux Command Examples and Usage

Here's a comprehensive guide to the Linux commands you requested, with examples for each command.

## ls - List directory contents

```bash
# Basic usage
ls

# List all files (including hidden)
ls -a

# List with details
ls -l

# List with human-readable file sizes
ls -lh

# List files sorted by size
ls -lS

# List files sorted by modification time
ls -lt

# List recursively
ls -R

# List directories only
ls -d */
```

## cd - Change directory

```bash
# Go to home directory
cd

# Go up one directory
cd ..

# Go to absolute path
cd /usr/local/bin

# Go to relative path
cd Documents/Projects

# Go to previous directory
cd -

# Go to user's home directory
cd ~

# Go to another user's home directory
cd ~username
```

## mkdir - Make directories

```bash
# Create a directory
mkdir documents

# Create multiple directories
mkdir documents images videos

# Create parent directories if they don't exist
mkdir -p projects/2023/january

# Create directory with specific permissions
mkdir -m 755 secure_folder

# Create directory and show what's being done
mkdir -v new_folder
```

## pwd - Print working directory

```bash
# Print current directory
pwd

# Print physical directory, resolving symlinks
pwd -P

# Print logical directory (with symlinks)
pwd -L
```

## man - Display manual pages

```bash
# View man page for a command
man ls

# Search for manual pages by keyword
man -k search_term

# Display man page from a specific section
man 5 passwd

# Show which sections contain a topic
man -wa ssh

# Display all available sections for a command
man -a printf
```

## head - Output first part of files

```bash
# Show first 10 lines
head file.txt

# Show first 5 lines
head -n 5 file.txt

# Show first 20 bytes
head -c 20 file.txt

# Show first lines of multiple files
head file1.txt file2.txt

# Show all but the last 5 lines
head -n -5 file.txt
```

## tail - Output last part of files

```bash
# Show last 10 lines
tail file.txt

# Show last 5 lines
tail -n 5 file.txt

# Follow file as it grows
tail -f log.txt

# Show all but the first 5 lines
tail -n +5 file.txt

# Follow multiple files
tail -f file1.log file2.log

# Show last 20 bytes
tail -c 20 file.txt
```

## cut - Remove sections from lines of files

```bash
# Cut by character position
cut -c 1-5 file.txt

# Cut by field with tab as delimiter (default)
cut -f 1,3 data.tsv

# Cut by field with custom delimiter
cut -d ',' -f 1,3 data.csv

# Output only delimited fields
cut -s -d ':' -f 1 /etc/passwd

# Complement the selection
cut --complement -c 1-3 file.txt
```

## clear - Clear the terminal screen

```bash
# Clear screen
clear

# Clear screen and scrollback buffer
clear -x

# Alternative method (shortcut)
# Ctrl+L in most terminals
```

## kill - Send a signal to a process

```bash
# Kill a process by PID
kill 1234

# Force kill a process
kill -9 1234

# Kill by process name (using pkill)
pkill firefox

# Send SIGTERM signal
kill -15 1234

# List all available signals
kill -l

# Kill all processes of a specific user
pkill -u username

# Kill all processes in a process group
kill -TERM -12345
```

## echo - Display a line of text

```bash
# Print text
echo "Hello World"

# Print with no newline
echo -n "Hello"

# Print with escape sequences
echo -e "Line 1\nLine 2"

# Expand variables
echo "User: $USER, Home: $HOME"

# Redirect output to a file
echo "Content" > file.txt

# Append to a file
echo "More content" >> file.txt
```

## less - View file content page by page

```bash
# View a file
less file.txt

# Case insensitive search
less -i file.txt

# Show line numbers
less -N file.txt

# Don't wrap long lines
less -S file.txt

# View multiple files
less file1.txt file2.txt

# Start at specific line number
less +100 file.txt

# Start at first occurrence of pattern
less +/pattern file.txt
```

## cp - Copy files and directories

```bash
# Copy a file
cp source.txt destination.txt

# Copy a file to a directory
cp file.txt /path/to/directory/

# Copy multiple files to a directory
cp file1.txt file2.txt directory/

# Copy recursively (directories)
cp -r source_dir/ destination_dir/

# Copy with prompt before overwrite
cp -i source.txt destination.txt

# Copy with original attributes
cp -p source.txt destination.txt

# Copy verbosely (show what's being done)
cp -v source.txt destination.txt
```

## find - Search for files in a directory hierarchy

```bash
# Find files by name
find /path -name "*.txt"

# Find directories
find /path -type d

# Find files by permission
find /path -perm 644

# Find files modified in the last 7 days
find /path -mtime -7

# Find files larger than 10MB
find /path -size +10M

# Find and execute command on each file
find /path -name "*.log" -exec rm {} \;

# Find empty files
find /path -type f -empty

# Find and delete files older than 30 days
find /path -mtime +30 -delete
```

## zip - Package and compress files

```bash
# Create a zip archive
zip archive.zip file1 file2

# Add files to existing archive
zip -u archive.zip newfile.txt

# Create a zip archive from a directory
zip -r archive.zip directory/

# Create a password-protected zip
zip -e archive.zip file1 file2

# Set compression level (0-9)
zip -9 archive.zip file1 file2

# Exclude specific files
zip -r archive.zip directory/ -x "*.git*"

# Create a split zip archive (1GB parts)
zip -r -s 1g archive.zip directory/
```

## unzip - Extract zip archives

```bash
# Extract entire archive
unzip archive.zip

# List contents without extracting
unzip -l archive.zip

# Extract to specific directory
unzip archive.zip -d /target/directory/

# Extract specific files
unzip archive.zip "*.txt"

# Extract quietly (suppress output)
unzip -q archive.zip

# Test archive integrity
unzip -t archive.zip

# Update existing files only if newer
unzip -u archive.zip
```

## tar - Archive files

```bash
# Create a tar archive
tar -cf archive.tar file1 file2

# Create a gzipped tar archive
tar -czf archive.tar.gz directory/

# Extract a tar archive
tar -xf archive.tar

# Extract a gzipped tar archive
tar -xzf archive.tar.gz

# List archive contents
tar -tf archive.tar

# Extract specific files
tar -xf archive.tar file1 file2

# Append files to archive
tar -rf archive.tar newfile.txt

# Create bzip2 compressed archive
tar -cjf archive.tar.bz2 directory/
```

## gzip - Compress files

```bash
# Compress a file (replaces original)
gzip file.txt

# Compress with specific compression level
gzip -9 file.txt

# Compress keeping original file
gzip -c file.txt > file.txt.gz

# Compress multiple files
gzip file1.txt file2.txt

# Compress all files in a directory
gzip -r directory/

# Show compression information
gzip -l file.txt.gz

# Test compressed file integrity
gzip -t file.txt.gz
```

## gunzip - Decompress files

```bash
# Decompress a file
gunzip file.txt.gz

# Decompress keeping compressed file
gunzip -c file.txt.gz > file.txt

# Decompress multiple files
gunzip file1.txt.gz file2.txt.gz

# Test compressed file integrity
gunzip -t file.txt.gz

# Decompress verbosely
gunzip -v file.txt.gz

# Force decompression even if file exists
gunzip -f file.txt.gz
```

## write - Send a message to another user

```bash
# Send a message to a specific user
write username

# Send a message to a specific terminal
write username pts/1

# Send a message to all users (as root)
wall "System rebooting in 10 minutes"

# Send a message from a file
write username < message.txt

# End a message with Ctrl+D
```

## who - Show who is logged in

```bash
# Display users currently logged in
who

# Show login time
who -b

# Show run level
who -r

# Show process ID
who -p

# Show dead processes
who -d

# Display all information
who -a

# Show current user
who am i
```

## finger - User information lookup

```bash
# Get information about a user
finger username

# Get information about current user
finger

# Get information about all users
finger -s

# Get information from a remote system
finger user@host

# Get information without project file
finger -p username

# Get information without .plan file
finger -l username
```

## ping - Send ICMP ECHO_REQUEST to network hosts

```bash
# Basic ping
ping google.com

# Specify number of packets
ping -c 5 8.8.8.8

# Ping with specific interval
ping -i 2 google.com

# Set packet size
ping -s 1500 google.com

# Flood ping (as root)
ping -f google.com

# Ping with timeout
ping -W 2 google.com

# Audible ping
ping -a google.com
```

## cat - Concatenate and display files

```bash
# Display file content
cat file.txt

# Display multiple files
cat file1.txt file2.txt

# Display with line numbers
cat -n file.txt

# Display with non-printing characters
cat -v file.txt

# Squeeze multiple blank lines
cat -s file.txt

# Display end of lines
cat -E file.txt

# Create a file with content
cat > newfile.txt << EOF
This is line 1
This is line 2
EOF
```

## sort - Sort lines of text files

```bash
# Simple sort
sort file.txt

# Sort numerically
sort -n numbers.txt

# Sort in reverse
sort -r file.txt

# Sort by specific field (tab-delimited)
sort -k 2 data.tsv

# Sort by specific field with custom delimiter
sort -t ',' -k 3 data.csv

# Sort and remove duplicates
sort -u file.txt

# Sort ignoring case
sort -f file.txt

# Sort months (not alphabetically)
sort -M month_list.txt
```

## wc - Print line, word, and byte counts

```bash
# Count lines, words, and bytes
wc file.txt

# Count lines only
wc -l file.txt

# Count words only
wc -w file.txt

# Count characters only
wc -m file.txt

# Count bytes only
wc -c file.txt

# Count lines for multiple files
wc -l file1.txt file2.txt

# Count all files in a directory
wc -l *
```

## rm - Remove files or directories

```bash
# Remove a file
rm file.txt

# Remove multiple files
rm file1.txt file2.txt

# Remove interactively (with prompt)
rm -i file.txt

# Force remove
rm -f file.txt

# Remove directory and contents
rm -r directory/

# Force remove directory and contents
rm -rf directory/

# Remove files matching pattern
rm *.tmp
```

## chmod - Change file mode bits

```bash
# Give full permissions to owner
chmod 700 file.txt

# Give read/write to owner, read to group/others
chmod 644 file.txt

# Give execute permission to owner
chmod +x script.sh

# Add write permission for group
chmod g+w file.txt

# Remove execute permission for others
chmod o-x file.txt

# Change permissions recursively
chmod -R 755 directory/

# Make file read-only for everyone
chmod a=r file.txt
```

## passwd - Change user password

```bash
# Change your own password
passwd

# Change another user's password (as root)
passwd username

# Delete a user's password (as root)
passwd -d username

# Set account expiration info
passwd -e username

# Lock a user account
passwd -l username

# Unlock a user account
passwd -u username

# Get password status
passwd -S username
```

## ps - Report process status

```bash
# Show current user's processes
ps

# Show all processes
ps -e

# Show full format listing
ps -ef

# Show process hierarchy
ps -H

# Show processes with BSD syntax
ps aux

# Show processes for specific user
ps -u username

# Show processes with specific PID
ps -p 1234

# Show processes with threads
ps -eLf
```

## fg - Bring job to foreground

```bash
# Bring most recent background job to foreground
fg

# Bring specific job to foreground by job number
fg %1

# Bring job to foreground by job name
fg %name

# Bring job to foreground by process ID
fg %pid
```

## bg - Put job in background

```bash
# Continue most recent stopped job in background
bg

# Continue specific job in background by job number
bg %1

# Continue job in background by job name
bg %name

# Continue job in background by process ID
bg %pid
```

## file - Determine file type

```bash
# Check file type
file filename

# Check multiple files
file file1 file2 file3

# Don't follow symlinks
file -P filename

# Show mime type
file --mime-type filename

# Show mime type and encoding
file --mime filename

# Read files from a list
file -f filelist.txt
```

## w - Show who is logged on and what they are doing

```bash
# Show logged in users and their activity
w

# Show without header
w -h

# Show only user information
w -s

# Show specific user
w username

# Display IP addresses instead of hostnames
w -i

# Don't truncate long usernames
w -f
```

## mv - Move (rename) files

```bash
# Rename a file
mv oldname.txt newname.txt

# Move a file to a directory
mv file.txt /target/directory/

# Move multiple files to a directory
mv file1.txt file2.txt directory/

# Move with prompt before overwrite
mv -i source.txt target.txt

# Don't overwrite existing destination
mv -n source.txt target.txt

# Update only when source is newer
mv -u source.txt target.txt

# Move verbosely
mv -v source.txt target.txt
```

## df - Report file system disk space usage

```bash
# Show all filesystems
df

# Show human readable sizes
df -h

# Show filesystem type
df -T

# Show info for specific filesystem
df -h /dev/sda1

# Show inode information
df -i

# Show used and available inodes in percentage
df -iP

# Show stats in 1K blocks
df -k
```

## du - Estimate file space usage

```bash
# Show disk usage of directory
du /path/to/directory

# Show human readable sizes
du -h /home/user

# Show total for directory
du -s /var/log

# Show total for each subdirectory
du -h --max-depth=1 /

# Show apparent size rather than disk usage
du -h --apparent-size file.txt

# Show files as well as directories
du -a /path/to/directory

# Exclude files matching pattern
du --exclude="*.log" /var/log
```

## comm - Compare two sorted files line by line

```bash
# Compare two sorted files
comm file1.txt file2.txt

# Show only lines unique to first file
comm -23 file1.txt file2.txt

# Show only lines unique to second file
comm -13 file1.txt file2.txt

# Show only lines common to both files
comm -12 file1.txt file2.txt

# Ignore case differences when comparing
comm <(sort -f file1.txt) <(sort -f file2.txt)

# Compare sorted output of two commands
comm <(ls dir1 | sort) <(ls dir2 | sort)
```

## diff - Compare files line by line

```bash
# Compare two files
diff file1.txt file2.txt

# Compare directories
diff -r dir1/ dir2/

# Ignore whitespace
diff -w file1.txt file2.txt

# Show side by side comparison
diff -y file1.txt file2.txt

# Generate unified format patch
diff -u file1.txt file2.txt

# Brief report of differences
diff -q file1.txt file2.txt

# Ignore case differences
diff -i file1.txt file2.txt
```

## mesg - Control write access to your terminal

```bash
# Display current status
mesg

# Allow write messages to your terminal
mesg y

# Disallow write messages to your terminal
mesg n
```

## date - Display or set date and time

```bash
# Display current date and time
date

# Display date in specific format
date "+%Y-%m-%d %H:%M:%S"

# Display UTC time
date -u

# Set system date (as root)
date -s "2023-04-01 12:00:00"

# Display time for specific timezone
TZ='America/New_York' date

# Display date as seconds since epoch
date +%s

# Convert seconds since epoch to date
date -d @1609459200
```

## cal - Display a calendar

```bash
# Display current month
cal

# Display specific month and year
cal 4 2023

# Display entire year
cal 2023

# Start weeks on Monday
cal -m

# Display 3 months (previous, current, next)
cal -3

# Display Julian dates (day of year)
cal -j

# Display Monday as first day of week
cal -m
```

## nohup - Run a command immune to hangups

```bash
# Run command that continues after logout
nohup command &

# Run with custom output file 
nohup command > output.log 2>&1 &

# Run multiple commands
nohup bash -c "command1 && command2" &

# Check if process is still running
ps aux | grep process_name

# View nohup output
cat nohup.out

# Run with specific priority
nohup nice -n 10 command &
```

## ssh - Secure Shell client

```bash
# Connect to remote server
ssh user@hostname

# Connect with specific port
ssh -p 2222 user@hostname

# Connect with specific identity file
ssh -i ~/.ssh/id_rsa user@hostname

# Run command on remote server
ssh user@hostname "ls -la"

# Forward local port to remote server
ssh -L 8080:localhost:80 user@hostname

# Forward remote port to local machine
ssh -R 8080:localhost:80 user@hostname

# SSH with X11 forwarding
ssh -X user@hostname
```

## scp - Secure copy

```bash
# Copy local file to remote server
scp file.txt user@hostname:/remote/directory/

# Copy remote file to local machine
scp user@hostname:/remote/file.txt local/directory/

# Copy directory recursively
scp -r local/directory/ user@hostname:/remote/directory/

# Copy with specific port
scp -P 2222 file.txt user@hostname:/remote/directory/

# Copy preserving file attributes
scp -p file.txt user@hostname:/remote/directory/

# Copy with compression
scp -C file.txt user@hostname:/remote/directory/

# Copy with specific identity file
scp -i ~/.ssh/id_rsa file.txt user@hostname:/remote/directory/
```

## Pine/Mutt/Alpine - Email clients

```bash
# Start alpine mail client
alpine

# Start alpine with specific config file
alpine -p config_file

# Start mutt email client
mutt

# Open mutt to compose email to specific address
mutt user@example.com

# Open mutt with subject
mutt -s "Email Subject" user@example.com

# Open mutt with attachment
mutt -a attachment.pdf user@example.com

# Pine with specific folder
pine -f INBOX.Drafts

# Mutt with specific mailbox
mutt -f ~/Mail/archive
```

## mesg n - Disable write access to your terminal

```bash
# Disallow messages to your terminal
mesg n

# Verify status after change
mesg

# Re-enable messages
mesg y

# Check current status
ls -l $(tty)

# Temporarily disable for specific operation
(mesg n; command; mesg y)
```

## whatis - Display one-line manual page descriptions

```bash
# Get brief description of a command
whatis ls

# Search for multiple commands
whatis cp mv rm

# Match all database entries
whatis -w "*ls*"

# Match commands exactly
whatis -e ls

# Rebuild whatis database
sudo makewhatis

# Search in specific section
whatis -s 1 printf
```

## apropos - Search the manual page names and descriptions

```bash
# Find commands related to a keyword
apropos password

# Search with case sensitivity
apropos -s password

# Match all words
apropos -a user password

# Match exact phrase
apropos "file system"

# Show section numbers
apropos -s password

# Search specific manual section
apropos -s 8 network

# Search with regex
apropos -r "^find.*file"
```