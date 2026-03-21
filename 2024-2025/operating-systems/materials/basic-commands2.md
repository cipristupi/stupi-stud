# 🐧 Linux Command Reference

## 📁 File and Directory Management

| Command      | Description                         | Example                              |
|--------------|-------------------------------------|--------------------------------------|
| `ls`         | List directory contents             | `ls -l`, `ls -a`                     |
| `cd`         | Change directory                    | `cd /home/user/Documents`           |
| `mkdir`      | Create new directory                | `mkdir new_folder`                  |
| `pwd`        | Print working directory             | `pwd`                                |
| `cp`         | Copy files/directories              | `cp file1.txt file2.txt`, `cp -r dir1 dir2` |
| `mv`         | Move/rename files or directories    | `mv old.txt new.txt`, `mv file.txt /path/` |
| `rm`         | Remove files/directories            | `rm file.txt`, `rm -r folder/`      |

## 📄 File Content Viewing and Manipulation

| Command      | Description                         | Example                              |
|--------------|-------------------------------------|--------------------------------------|
| `cat`        | Concatenate and display files       | `cat file.txt`                       |
| `less`       | View file one page at a time        | `less bigfile.txt`                   |
| `head`       | Show first lines of a file          | `head file.txt`, `head -n 5 file.txt`|
| `tail`       | Show last lines of a file           | `tail -f log.txt`                    |
| `cut`        | Remove sections from each line      | `cut -d ':' -f 1 /etc/passwd`        |
| `sort`       | Sort lines of a file                | `sort names.txt`                     |
| `wc`         | Word, line, byte count              | `wc -l file.txt`, `wc -w file.txt`   |
| `diff`       | Compare two files line-by-line      | `diff file1.txt file2.txt`           |
| `comm`       | Compare two sorted files            | `comm file1.txt file2.txt`           |

## 🗂️ Compression & Archiving

| Command      | Description                         | Example                              |
|--------------|-------------------------------------|--------------------------------------|
| `zip`        | Compress into .zip format           | `zip archive.zip file.txt`           |
| `unzip`      | Extract .zip file                   | `unzip archive.zip`                  |
| `tar`        | Archive multiple files              | `tar -cvf archive.tar folder/`, `tar -xvf archive.tar` |
| `gzip`       | Compress a single file              | `gzip file.txt`                      |
| `gunzip`     | Decompress .gz file                 | `gunzip file.txt.gz`                 |

## 🛠️ System Info & Process Management

| Command      | Description                         | Example                              |
|--------------|-------------------------------------|--------------------------------------|
| `ps`         | Show running processes              | `ps aux`                             |
| `kill`       | Terminate process by PID            | `kill 1234`                          |
| `fg`         | Resume process in foreground        | `fg %1`                              |
| `bg`         | Resume process in background        | `bg %1`                              |
| `df`         | Disk space usage                    | `df -h`                              |
| `du`         | Directory space usage               | `du -sh *`                           |

## 🔐 Permissions and Security

| Command      | Description                         | Example                              |
|--------------|-------------------------------------|--------------------------------------|
| `chmod`      | Change file permissions             | `chmod 755 file.sh`                  |
| `passwd`     | Change user password                | `passwd`                             |

## 💬 Communication and User Info

| Command      | Description                         | Example                              |
|--------------|-------------------------------------|--------------------------------------|
| `write`      | Send message to another user        | `write user1`                        |
| `who`        | Show who is logged in               | `who`                                |
| `w`          | Show user activity                  | `w`                                  |
| `finger`     | User info                           | `finger user1`                       |
| `mesg`       | Allow/block messages                | `mesg n`, `mesg y`                   |

## 🌐 Networking

| Command      | Description                         | Example                              |
|--------------|-------------------------------------|--------------------------------------|
| `ping`       | Test network connectivity           | `ping google.com`                    |
| `ssh`        | Secure shell remote login           | `ssh user@host.com`                  |
| `scp`        | Secure file transfer                | `scp file.txt user@host:/path/`      |

## 📧 Email Clients (Terminal-based)

| Command      | Description                         | Example                              |
|--------------|-------------------------------------|--------------------------------------|
| `pine`       | Terminal email client (deprecated)  | `pine`                               |
| `mutt`       | Terminal email client               | `mutt`                               |
| `alpine`     | Updated version of pine             | `alpine`                             |

## 🧹 Miscellaneous

| Command      | Description                         | Example                              |
|--------------|-------------------------------------|--------------------------------------|
| `echo`       | Display message or variable         | `echo "Hello"`, `echo $HOME`         |
| `clear`      | Clear terminal screen               | `clear`                              |
| `date`       | Show current date/time              | `date`                               |
| `cal`        | Show calendar                       | `cal`, `cal 2025`                    |
| `nohup`      | Run command immune to hangups       | `nohup ./script.sh &`                |
| `file`       | Identify file type                  | `file image.png`                     |
| `man`        | Show manual for command             | `man ls`                             |
| `whatis`     | One-line command description        | `whatis tar`                         |
| `apropos`    | Search command by keyword           | `apropos network`                    |
