# Shell Practice Pack

This archive contains 100 shell problems, shared input files, and expected outputs.

Most problems reuse files under `inputs/`. Expected outputs are under `outputs/`.

For filesystem problems, run commands from the archive root unless the command shown starts with `cd inputs/tree`.

A few outputs are intentionally environment-dependent in real life; here they are fixed to the packaged sample tree.


## Layout

- `inputs/` shared sample inputs

- `inputs/tree/` sample directory tree for `find`, permissions, size, and disk-usage problems

- `inputs/project/` sample source tree for recursive grep problems

- `outputs/pNNN.txt` expected output for problem `NNN`


## Problems

### 1. [Easy] Print the contents of notes.txt.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p001.txt`

- One possible answer:

```sh
cat inputs/notes.txt
```

### 2. [Easy] Count lines in notes.txt.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p002.txt`

- One possible answer:

```sh
wc -l < inputs/notes.txt
```

### 3. [Easy] Count words in notes.txt.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p003.txt`

- One possible answer:

```sh
wc -w < inputs/notes.txt
```

### 4. [Easy] Show first 10 lines of notes.txt.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p004.txt`

- One possible answer:

```sh
head -n 10 inputs/notes.txt
```

### 5. [Easy] Show last 5 lines of notes.txt.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p005.txt`

- One possible answer:

```sh
tail -n 5 inputs/notes.txt
```

### 6. [Easy] Find lines containing error.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p006.txt`

- One possible answer:

```sh
grep 'error' inputs/notes.txt
```

### 7. [Easy] Find lines not containing error.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p007.txt`

- One possible answer:

```sh
grep -v 'error' inputs/notes.txt
```

### 8. [Easy] Search unix ignoring case.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p008.txt`

- One possible answer:

```sh
grep -i 'unix' inputs/notes.txt
```

### 9. [Easy] Print lines starting with #.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p009.txt`

- One possible answer:

```sh
grep '^#' inputs/notes.txt
```

### 10. [Easy] Print lines ending with ;

- Input: `inputs/notes.txt`

- Expected output: `outputs/p010.txt`

- One possible answer:

```sh
grep ';$' inputs/notes.txt
```

### 11. [Easy] Replace foo with bar.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p011.txt`

- One possible answer:

```sh
sed 's/foo/bar/g' inputs/notes.txt
```

### 12. [Easy] Delete blank lines.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p012.txt`

- One possible answer:

```sh
sed '/^$/d' inputs/notes.txt
```

### 13. [Easy] Print only the 3rd line.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p013.txt`

- One possible answer:

```sh
sed -n '3p' inputs/notes.txt
```

### 14. [Easy] Print lines 5 through 12.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p014.txt`

- One possible answer:

```sh
sed -n '5,12p' inputs/notes.txt
```

### 15. [Easy] Extract first column from passwd.txt.

- Input: `inputs/passwd.txt`

- Expected output: `outputs/p015.txt`

- One possible answer:

```sh
cut -d: -f1 inputs/passwd.txt
```

### 16. [Easy] Extract third field from marks.csv.

- Input: `inputs/marks.csv`

- Expected output: `outputs/p016.txt`

- One possible answer:

```sh
cut -d, -f3 inputs/marks.csv
```

### 17. [Easy] Sort names alphabetically.

- Input: `inputs/names.txt`

- Expected output: `outputs/p017.txt`

- One possible answer:

```sh
sort inputs/names.txt
```

### 18. [Easy] Sort numbers numerically.

- Input: `inputs/numbers.txt`

- Expected output: `outputs/p018.txt`

- One possible answer:

```sh
sort -n inputs/numbers.txt
```

### 19. [Easy] Remove duplicate lines from names.txt.

- Input: `inputs/names.txt`

- Expected output: `outputs/p019.txt`

- One possible answer:

```sh
sort inputs/names.txt | uniq
```

### 20. [Easy] Count how many times each line appears in names.txt.

- Input: `inputs/names.txt`

- Expected output: `outputs/p020.txt`

- One possible answer:

```sh
sort inputs/names.txt | uniq -c | awk '{print $1, $2}'
```

### 21. [Easy] Print only unique lines from names.txt after sorting.

- Input: `inputs/names.txt`

- Expected output: `outputs/p021.txt`

- One possible answer:

```sh
sort inputs/names.txt | uniq -u
```

### 22. [Easy] Print only duplicated lines from names.txt after sorting.

- Input: `inputs/names.txt`

- Expected output: `outputs/p022.txt`

- One possible answer:

```sh
sort inputs/names.txt | uniq -d
```

### 23. [Easy] Merge file1.txt and file2.txt.

- Input: `inputs/file1.txt, inputs/file2.txt`

- Expected output: `outputs/p023.txt`

- One possible answer:

```sh
cat inputs/file1.txt inputs/file2.txt
```

### 24. [Easy] Display file1.txt with line numbers.

- Input: `inputs/file1.txt`

- Expected output: `outputs/p024.txt`

- One possible answer:

```sh
nl inputs/file1.txt
```

### 25. [Easy] Find all .txt files in inputs/tree.

- Input: `inputs/tree/`

- Expected output: `outputs/p025.txt`

- One possible answer:

```sh
cd inputs/tree && find . -maxdepth 1 -type f -name '*.txt'
```

### 26. [Easy] Find all directories in inputs/tree.

- Input: `inputs/tree/`

- Expected output: `outputs/p026.txt`

- One possible answer:

```sh
cd inputs/tree && find . -maxdepth 1 -type d
```

### 27. [Easy] Find all empty files in inputs/tree recursively.

- Input: `inputs/tree/`

- Expected output: `outputs/p027.txt`

- One possible answer:

```sh
cd inputs/tree && find . -type f -empty
```

### 28. [Easy] Find all files larger than 10 MB in inputs/tree.

- Input: `inputs/tree/`

- Expected output: `outputs/p028.txt`

- One possible answer:

```sh
cd inputs/tree && find . -type f -size +10M
```

### 29. [Easy] Convert notes.txt to uppercase.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p029.txt`

- One possible answer:

```sh
tr '[:lower:]' '[:upper:]' < inputs/notes.txt
```

### 30. [Easy] Convert notes.txt to lowercase.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p030.txt`

- One possible answer:

```sh
tr '[:upper:]' '[:lower:]' < inputs/notes.txt
```

### 31. [Easy] Remove all digits from data.txt.

- Input: `inputs/data.txt`

- Expected output: `outputs/p031.txt`

- One possible answer:

```sh
tr -d '0-9' < inputs/data.txt
```

### 32. [Easy] Print longest line length in notes.txt.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p032.txt`

- One possible answer:

```sh
awk '{ if (length > max) max = length } END { print max }' inputs/notes.txt
```

### 33. [Easy] Count how many lines in notes.txt contain the substring the.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p033.txt`

- One possible answer:

```sh
grep -c 'the' inputs/notes.txt
```

### 34. [Easy] Print the number of characters in each line of notes.txt.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p034.txt`

- One possible answer:

```sh
awk '{ print length }' inputs/notes.txt
```

### 35. [Easy] Show the file names in inputs/tree sorted by size.

- Input: `inputs/tree/`

- Expected output: `outputs/p035.txt`

- One possible answer:

```sh
cd inputs/tree && find . -maxdepth 1 -type f -printf '%s %f\n' | sort -n
```

### 36. [Medium] Print lines where exact word ERROR appears.

- Input: `inputs/log.txt`

- Expected output: `outputs/p036.txt`

- One possible answer:

```sh
grep -w 'ERROR' inputs/log.txt
```

### 37. [Medium] Print lines where error appears ignoring case.

- Input: `inputs/log.txt`

- Expected output: `outputs/p037.txt`

- One possible answer:

```sh
grep -i 'error' inputs/log.txt
```

### 38. [Medium] Print usernames from passwd.txt.

- Input: `inputs/passwd.txt`

- Expected output: `outputs/p038.txt`

- One possible answer:

```sh
awk -F: '{print $1}' inputs/passwd.txt
```

### 39. [Medium] Print usernames and shells from passwd.txt.

- Input: `inputs/passwd.txt`

- Expected output: `outputs/p039.txt`

- One possible answer:

```sh
awk -F: '{print $1, $7}' inputs/passwd.txt
```

### 40. [Medium] Count how many users use /bin/bash.

- Input: `inputs/passwd.txt`

- Expected output: `outputs/p040.txt`

- One possible answer:

```sh
awk -F: '$7=="/bin/bash"{c++} END{print c+0}' inputs/passwd.txt
```

### 41. [Medium] Print the 2nd and 4th columns from spacecols.txt.

- Input: `inputs/spacecols.txt`

- Expected output: `outputs/p041.txt`

- One possible answer:

```sh
awk '{print $2, $4}' inputs/spacecols.txt
```

### 42. [Medium] Replace multiple spaces with a single space in the first two lines of data.txt.

- Input: `inputs/data.txt`

- Expected output: `outputs/p042.txt`

- One possible answer:

```sh
head -n 4 inputs/data.txt | tail -n 2 | tr -s ' '
```

### 43. [Medium] Remove leading spaces from data.txt.

- Input: `inputs/data.txt`

- Expected output: `outputs/p043.txt`

- One possible answer:

```sh
sed 's/^[[:space:]]*//' inputs/data.txt
```

### 44. [Medium] Remove trailing spaces from data.txt.

- Input: `inputs/data.txt`

- Expected output: `outputs/p044.txt`

- One possible answer:

```sh
sed 's/[[:space:]]*$//' inputs/data.txt
```

### 45. [Medium] Remove leading and trailing spaces from data.txt.

- Input: `inputs/data.txt`

- Expected output: `outputs/p045.txt`

- One possible answer:

```sh
sed 's/^[[:space:]]*//; s/[[:space:]]*$//' inputs/data.txt
```

### 46. [Medium] Print lines longer than 80 characters.

- Input: `inputs/longlines.txt`

- Expected output: `outputs/p046.txt`

- One possible answer:

```sh
awk 'length > 80' inputs/longlines.txt
```

### 47. [Medium] Print only blank lines from notes.txt.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p047.txt`

- One possible answer:

```sh
grep '^$' inputs/notes.txt
```

### 48. [Medium] Print only non-blank lines from notes.txt.

- Input: `inputs/notes.txt`

- Expected output: `outputs/p048.txt`

- One possible answer:

```sh
grep -v '^$' inputs/notes.txt
```

### 49. [Medium] Count how many .sh files exist recursively under inputs/.

- Input: `inputs/`

- Expected output: `outputs/p049.txt`

- One possible answer:

```sh
find inputs -type f -name '*.sh' | wc -l
```

### 50. [Medium] Find all .log files in inputs/tree modified in the last 3 days.

- Input: `inputs/tree/`

- Expected output: `outputs/p050.txt`

- One possible answer:

```sh
cd inputs/tree && find . -type f -name '*.log' -mtime -3
```

### 51. [Medium] Find the .tmp files that would be deleted in inputs/tree.

- Input: `inputs/tree/`

- Expected output: `outputs/p051.txt`

- One possible answer:

```sh
cd inputs/tree && find . -type f -name '*.tmp'
```

### 52. [Medium] Find all files owned by the current user in inputs/tree.

- Input: `inputs/tree/`

- Expected output: `outputs/p052.txt`

- One possible answer:

```sh
cd inputs/tree && find . -type f -user "$(whoami)"
```

### 53. [Medium] Find regular files with permission 644 in inputs/tree.

- Input: `inputs/tree/`

- Expected output: `outputs/p053.txt`

- One possible answer:

```sh
cd inputs/tree && find . -type f -perm 644
```

### 54. [Medium] From marks.csv, print rows where the 3rd field > 50.

- Input: `inputs/marks.csv`

- Expected output: `outputs/p054.txt`

- One possible answer:

```sh
awk -F, '$3 > 50' inputs/marks.csv
```

### 55. [Medium] From marks.csv, print rows where the 2nd field is math.

- Input: `inputs/marks.csv`

- Expected output: `outputs/p055.txt`

- One possible answer:

```sh
awk -F, '$2=="math"' inputs/marks.csv
```

### 56. [Medium] Sum all numbers in the first column of numbers_col1.txt.

- Input: `inputs/numbers_col1.txt`

- Expected output: `outputs/p056.txt`

- One possible answer:

```sh
awk '{sum += $1} END {print sum}' inputs/numbers_col1.txt
```

### 57. [Medium] Compute the average of scores.txt.

- Input: `inputs/scores.txt`

- Expected output: `outputs/p057.txt`

- One possible answer:

```sh
awk '{sum+=$1; n++} END{if(n) print sum/n}' inputs/scores.txt
```

### 58. [Medium] Find the maximum number in scores.txt.

- Input: `inputs/scores.txt`

- Expected output: `outputs/p058.txt`

- One possible answer:

```sh
awk 'NR==1 || $1>max {max=$1} END{print max}' inputs/scores.txt
```

### 59. [Medium] Find the minimum number in scores.txt.

- Input: `inputs/scores.txt`

- Expected output: `outputs/p059.txt`

- One possible answer:

```sh
awk 'NR==1 || $1<min {min=$1} END{print min}' inputs/scores.txt
```

### 60. [Medium] Print the line numbers of all TODO matches in inputs/project.

- Input: `inputs/project/`

- Expected output: `outputs/p060.txt`

- One possible answer:

```sh
grep -rn 'TODO' inputs/project
```

### 61. [Medium] Search recursively for main( in all .c files under inputs/project.

- Input: `inputs/project/`

- Expected output: `outputs/p061.txt`

- One possible answer:

```sh
find inputs/project -type f -name '*.c' -exec grep -H 'main(' {} +
```

### 62. [Medium] Print the 5 most frequent words in file.txt.

- Input: `inputs/file.txt`

- Expected output: `outputs/p062.txt`

- One possible answer:

```sh
tr -cs '[:alnum:]' '\n' < inputs/file.txt | tr '[:upper:]' '[:lower:]' | sort | uniq -c | sort -nr | head -n 5
```

### 63. [Medium] Count how many unique words are in file.txt.

- Input: `inputs/file.txt`

- Expected output: `outputs/p063.txt`

- One possible answer:

```sh
tr -cs '[:alnum:]' '\n' < inputs/file.txt | tr '[:upper:]' '[:lower:]' | sort -u | wc -l
```

### 64. [Medium] Print all duplicate words in file.txt.

- Input: `inputs/file.txt`

- Expected output: `outputs/p064.txt`

- One possible answer:

```sh
tr -cs '[:alnum:]' '\n' < inputs/file.txt | tr '[:upper:]' '[:lower:]' | sort | uniq -d
```

### 65. [Medium] Join f1.txt and f2.txt on the first column.

- Input: `inputs/f1.txt, inputs/f2.txt`

- Expected output: `outputs/p065.txt`

- One possible answer:

```sh
join inputs/f1.txt inputs/f2.txt
```

### 66. [Medium] Print lines common to file1.txt and file2.txt.

- Input: `inputs/file1.txt, inputs/file2.txt`

- Expected output: `outputs/p066.txt`

- One possible answer:

```sh
comm -12 <(sort inputs/file1.txt) <(sort inputs/file2.txt)
```

### 67. [Medium] Print lines present in file1.txt but not in file2.txt.

- Input: `inputs/file1.txt, inputs/file2.txt`

- Expected output: `outputs/p067.txt`

- One possible answer:

```sh
comm -23 <(sort inputs/file1.txt) <(sort inputs/file2.txt)
```

### 68. [Medium] Compare two sorted files and print lines unique to either file.

- Input: `inputs/file1.txt, inputs/file2.txt`

- Expected output: `outputs/p068.txt`

- One possible answer:

```sh
comm -3 <(sort inputs/file1.txt) <(sort inputs/file2.txt) | sed 's/^\t//'
```

### 69. [Medium] Print the top 10 largest files in inputs/tree.

- Input: `inputs/tree/`

- Expected output: `outputs/p069.txt`

- One possible answer:

```sh
cd inputs/tree && find . -type f -printf '%s %p\n' | sort -nr | head -n 10
```

### 70. [Medium] Print the number of files in each immediate subdirectory of inputs/tree.

- Input: `inputs/tree/`

- Expected output: `outputs/p070.txt`

- One possible answer:

```sh
cd inputs/tree && for d in */; do printf '%s %s\n' "$d" "$(find "$d" -type f | wc -l)"; done
```

### 71. [Medium] Rename all .txt files to .bak in inputs/tree (show resulting top-level names).

- Input: `inputs/tree/`

- Expected output: `outputs/p071.txt`

- One possible answer:

```sh
for f in inputs/tree/*.txt; do echo "${f##*/}"; done | sed 's/\.txt$/.bak/'
```

### 72. [Medium] Print every 3rd line from numbers.txt.

- Input: `inputs/numbers.txt plus an extra 9-line sample in the README explanation`

- Expected output: `outputs/p072.txt`

- One possible answer:

```sh
seq 1 9 | awk 'NR % 3 == 0'
```

### 73. [Medium] Print odd-numbered lines from file1.txt.

- Input: `inputs/file1.txt`

- Expected output: `outputs/p073.txt`

- One possible answer:

```sh
awk 'NR % 2 == 1' inputs/file1.txt
```

### 74. [Medium] Print even-numbered lines from file1.txt.

- Input: `inputs/file1.txt`

- Expected output: `outputs/p074.txt`

- One possible answer:

```sh
awk 'NR % 2 == 0' inputs/file1.txt
```

### 75. [Medium] Swap the first two columns in spacecols.txt.

- Input: `inputs/spacecols.txt`

- Expected output: `outputs/p075.txt`

- One possible answer:

```sh
awk '{tmp=$1; $1=$2; $2=tmp; print}' inputs/spacecols.txt
```

### 76. [Hard] From Apache access.log, print the IP address that appears most often.

- Input: `inputs/access.log`

- Expected output: `outputs/p076.txt`

- One possible answer:

```sh
awk '{print $1}' inputs/access.log | sort | uniq -c | sort -nr | head -n 1 | awk '{print $2}'
```

### 77. [Hard] From Apache access.log, count requests per IP address.

- Input: `inputs/access.log`

- Expected output: `outputs/p077.txt`

- One possible answer:

```sh
awk '{print $1}' inputs/access.log | sort | uniq -c | sort -nr
```

### 78. [Hard] From Apache access.log, print only requests with status code 404.

- Input: `inputs/access.log`

- Expected output: `outputs/p078.txt`

- One possible answer:

```sh
awk '$9 == 404' inputs/access.log
```

### 79. [Hard] From Apache access.log, count how many requests were made on each day.

- Input: `inputs/access.log`

- Expected output: `outputs/p079.txt`

- One possible answer:

```sh
awk '{gsub(/\[/,"",$4); split($4,a,":"); print a[1]}' inputs/access.log | sort | uniq -c
```

### 80. [Hard] From sys.log, print the top 10 most common error messages.

- Input: `inputs/sys.log`

- Expected output: `outputs/p080.txt`

- One possible answer:

```sh
grep '^ERROR:' inputs/sys.log | sort | uniq -c | sort -nr | head -n 10
```

### 81. [Hard] Print CSV rows where a field contains commas inside quotes.

- Input: `inputs/data.csv`

- Expected output: `outputs/p081.txt`

- One possible answer:

```sh
grep '".*,' inputs/data.csv
```

### 82. [Hard] Print the 10 most frequent words across all .txt files in inputs/tree.

- Input: `inputs/tree/`

- Expected output: `outputs/p082.txt`

- One possible answer:

```sh
find inputs/tree -type f -name '*.txt' -exec cat {} + | tr -cs '[:alnum:]' '\n' | tr '[:upper:]' '[:lower:]' | sort | uniq -c | sort -nr | head -n 10
```

### 83. [Hard] Recursively search source files and print function names that contain test.

- Input: `inputs/project/`

- Expected output: `outputs/p083.txt`

- One possible answer:

```sh
grep -RhoE '[A-Za-z_][A-Za-z0-9_]*test[A-Za-z0-9_]*[[:space:]]*\(' inputs/project --include='*.c' --include='*.h' | sed 's/[[:space:]]*(//' | sort -u
```

### 84. [Hard] Find duplicate files by name in inputs/tree.

- Input: `inputs/tree/`

- Expected output: `outputs/p084.txt`

- One possible answer:

```sh
find inputs/tree -type f -printf '%f\n' | sort | uniq -d
```

### 85. [Hard] Find duplicate files by content checksum in inputs/tree.

- Input: `inputs/tree/`

- Expected output: `outputs/p085.txt`

- One possible answer:

```sh
find inputs/tree -type f -exec md5sum {} + | sort
```

### 86. [Hard] Print all files larger than 1 MB along with sizes, sorted descending.

- Input: `inputs/tree/`

- Expected output: `outputs/p086.txt`

- One possible answer:

```sh
cd inputs/tree && find . -type f -size +1M -printf '%s %p\n' | sort -nr
```

### 87. [Hard] Find all shell scripts under inputs/ that do not have execute permission.

- Input: `inputs/`

- Expected output: `outputs/p087.txt`

- One possible answer:

```sh
find inputs -type f -name '*.sh' ! -perm /111
```

### 88. [Hard] Print directories in inputs/tree containing more than 100 immediate files.

- Input: `inputs/tree/`

- Expected output: `outputs/p088.txt`

- One possible answer:

```sh
cd inputs/tree && find . -type d | while read -r d; do c=$(find "$d" -maxdepth 1 -type f | wc -l); [ "$c" -gt 100 ] && echo "$d $c"; done
```

### 89. [Hard] From ps.txt, print the process consuming the most memory.

- Input: `inputs/ps.txt`

- Expected output: `outputs/p089.txt`

- One possible answer:

```sh
awk 'NR>1 {print $11, $4}' inputs/ps.txt | sort -k2,2nr | head -n 1
```

### 90. [Hard] From ps.txt, print the top 5 CPU-consuming processes.

- Input: `inputs/ps.txt`

- Expected output: `outputs/p090.txt`

- One possible answer:

```sh
awk 'NR>1 {print $3, $11}' inputs/ps.txt | sort -nr | head -n 5
```

### 91. [Hard] Print the total disk usage of each immediate subdirectory in inputs/tree sorted by size.

- Input: `inputs/tree/`

- Expected output: `outputs/p091.txt`

- One possible answer:

```sh
cd inputs/tree && du -sh ./*/ 2>/dev/null | sort -h
```

### 92. [Hard] Given log timestamps, print gaps where no OK message appeared for more than 5 minutes.

- Input: `inputs/log.txt`

- Expected output: `outputs/p092.txt`

- One possible answer:

```sh
awk '...see explanation below...' inputs/log.txt
```

Example `awk` body used for problem 92:

```sh
awk '
$3=="OK" {
  cmd = "date -d \"" $1 " " $2 "\" +%s"
  cmd | getline t
  close(cmd)
  if (prev && t - prev > 300)
    print prevs, "->", $1, $2
  prev = t
  prevs = $1 " " $2
}' inputs/log.txt
```

### 93. [Hard] Merge a.csv and b.csv on ID and print unmatched rows.

- Input: `inputs/a.csv, inputs/b.csv`

- Expected output: `outputs/p093.txt`

- One possible answer:

```sh
join -t, -v1 <(sort -t, -k1,1 inputs/a.csv) <(sort -t, -k1,1 inputs/b.csv); join -t, -v2 <(sort -t, -k1,1 inputs/a.csv) <(sort -t, -k1,1 inputs/b.csv)
```

### 94. [Hard] Validate that every line in data.csv has exactly 5 comma-separated fields.

- Input: `inputs/data.csv`

- Expected output: `outputs/p094.txt`

- One possible answer:

```sh
awk -F, 'NF != 5 {print NR ":" $0}' inputs/data.csv
```

### 95. [Hard] Print lines in code.txt where the number of ( and ) is not equal.

- Input: `inputs/code.txt`

- Expected output: `outputs/p095.txt`

- One possible answer:

```sh
awk '{ open=gsub(/\(/,"&"); close=gsub(/\)/,"&"); if (open != close) print }' inputs/code.txt
```

### 96. [Hard] Remove duplicate CSV records from dedupe.csv based on first field, keeping the first occurrence.

- Input: `inputs/dedupe.csv`

- Expected output: `outputs/p096.txt`

- One possible answer:

```sh
awk -F, '!seen[$1]++' inputs/dedupe.csv
```

### 97. [Hard] Remove duplicate records from dates.csv based on first field, keeping the latest occurrence by date.

- Input: `inputs/dates.csv`

- Expected output: `outputs/p097.txt`

- One possible answer:

```sh
awk -F, '!($1 in best) || $3 > date[$1] { best[$1]=$0; date[$1]=$3 } END { for (id in best) print best[id] }' inputs/dates.csv | sort -t, -k1,1n
```

### 98. [Hard] Build a shell script that takes a directory and prints total files, total directories, largest file, and most recently modified file.

- Input: `inputs/tree/`

- Expected output: `outputs/p098.txt`

- One possible answer:

```sh
see README script block
```

Reference script:

```sh
#!/bin/sh

dir=${1:-.}

echo "Total files: $(find "$dir" -type f | wc -l)"
echo "Total directories: $(find "$dir" -type d | wc -l)"

echo "Largest file:"
find "$dir" -type f -printf '%s %p\n' | sort -nr | head -n 1

echo "Most recently modified file:"
find "$dir" -type f -printf '%T@ %p\n' | sort -nr | head -n 1 | cut -d' ' -f2-
```

### 99. [Hard] Build a shell script that scans .log files and creates a summary report.

- Input: `inputs/tree/*.log`

- Expected output: `outputs/p099.txt`

- One possible answer:

```sh
see README script block
```

Reference script:

```sh
#!/bin/sh

for f in "$@"/*.log ./*.log; do
  [ -f "$f" ] || continue
  lines=$(wc -l < "$f")
  err=$(grep -c 'ERROR' "$f")
  warn=$(grep -c 'WARNING' "$f")
  info=$(grep -c 'INFO' "$f")
  echo "$f,$lines,$err,$warn,$info"
done
```

### 100. [Hard] Build a shell script that accepts a text file and prints line, word, unique-word, frequency, longest-line, and average-word stats.

- Input: `inputs/sample.txt`

- Expected output: `outputs/p100.txt`

- One possible answer:

```sh
see README script block
```

Reference script:

```sh
#!/bin/sh

file=$1

echo "Total lines: $(wc -l < "$file")"
echo "Total words: $(wc -w < "$file")"

echo "Unique words: $(tr -cs '[:alnum:]' '\n' < "$file" | tr '[:upper:]' '[:lower:]' | sort -u | wc -l)"

echo "Most frequent word:"
tr -cs '[:alnum:]' '\n' < "$file" | tr '[:upper:]' '[:lower:]' | sort | uniq -c | sort -nr | head -n 1

echo "Longest line length: $(awk '{if(length>max) max=length} END{print max}' "$file")"

echo "Average words per line: $(awk '{sum += NF; n++} END{if(n) print sum/n; else print 0}' "$file")"
```
