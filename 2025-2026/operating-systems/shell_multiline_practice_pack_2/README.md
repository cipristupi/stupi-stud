# Shell Script Practice Pack 2

This archive focuses on **multi-line shell scripting** with both **positional arguments** and **named arguments / flags**.

## Included

- `README.md` with 70 problems
- shared sample data in `inputs/`
- selected expected outputs in `outputs/`
- parser starter patterns in `scripts_examples/`

## Suggested practice order

1. positional arguments
2. validation and `usage()`
3. optional flags
4. named arguments
5. repeated named arguments
6. dry-run / verbose
7. subcommands
8. reusable helper functions

## 1. Line counter

**Style:** Positional arguments

Write `linecount.sh` that takes one filename and prints `Lines: N`. Use `inputs/notes.txt`.

Example:
```sh
./linecount.sh inputs/notes.txt
```

Sample expected output:
```text
Lines: 6
```

## 2. Word counter

**Style:** Positional arguments

Write `wordcount.sh` that takes one file and prints the word count. Show a usage message when no argument is provided.

Example:
```sh
./wordcount.sh inputs/sample.txt
```

Sample expected output:
```text
Words: 7
```

## 3. File existence check

**Style:** Positional arguments

Write `exists.sh` that accepts one path and prints whether it is a regular file, directory, or missing.

Example:
```sh
./exists.sh inputs/tree/docs
```

Sample expected output:
```text
Directory exists
```

## 4. Uppercase converter

**Style:** Positional arguments

Write `toupper.sh input output` that converts file content to uppercase.

Example:
```sh
./toupper.sh inputs/notes.txt out.txt
```

Sample expected output:
```text
Creates uppercase output file
```

## 5. Search wrapper

**Style:** Positional arguments

Write `search.sh pattern file` that prints matching lines, with an error if the file is missing.

Example:
```sh
./search.sh ERROR inputs/log.txt
```

Sample expected output:
```text
2025-01-01 ERROR disk full
2025-01-02 ERROR login failed
```

## 6. Count regular files

**Style:** Positional arguments

Write `countfiles.sh dir` that counts regular files recursively.

Example:
```sh
./countfiles.sh inputs/tree
```

Sample expected output:
```text
Files: 5
```

## 7. Sum arguments

**Style:** Positional arguments

Write `sumargs.sh` that sums all numeric positional arguments.

Example:
```sh
./sumargs.sh 10 20 5
```

Sample expected output:
```text
Sum: 35
```

## 8. Maximum argument

**Style:** Positional arguments

Write `maxargs.sh` that prints the largest numeric argument.

Example:
```sh
./maxargs.sh 8 19 2 5
```

Sample expected output:
```text
Max: 19
```

## 9. Extension counter

**Style:** Positional arguments

Write `extcount.sh dir ext` that counts files recursively with the given extension.

Example:
```sh
./extcount.sh inputs/tree txt
```

Sample expected output:
```text
Count: 2
```

## 10. Every nth line

**Style:** Positional arguments

Write `every_nth.sh file n` that prints every nth line.

Example:
```sh
./every_nth.sh inputs/scores.txt 2
```

Sample expected output:
```text
20
40
```

## 11. Reverse lines

**Style:** Positional arguments

Write `reverse_lines.sh file` that prints the lines in reverse order.

Example:
```sh
./reverse_lines.sh inputs/scores.txt
```

Sample expected output:
```text
40
30
20
10
```

## 12. Remove blank lines

**Style:** Positional arguments

Write `clean_blank.sh input output` that removes blank lines.

Example:
```sh
./clean_blank.sh inputs/notes.txt clean.txt
```

Sample expected output:
```text
Creates cleaned output file
```

## 13. CSV column extractor

**Style:** Positional arguments

Write `csvcol.sh file column` that prints the selected CSV column.

Example:
```sh
./csvcol.sh inputs/marks.csv 2
```

Sample expected output:
```text
math
science
math
english
```

## 14. Directory size report

**Style:** Positional arguments

Write `dirsize.sh dir` that prints the size of each immediate subdirectory.

Example:
```sh
./dirsize.sh inputs/tree
```

Sample expected output:
```text
System-dependent sizes
```

## 15. Count matching lines

**Style:** Positional arguments

Write `countmatch.sh pattern file` that prints how many lines match.

Example:
```sh
./countmatch.sh hello inputs/sample.txt
```

Sample expected output:
```text
Count: 2
```

## 16. Unique words

**Style:** Positional arguments

Write `uniquewords.sh file` that prints the number of unique words.

Example:
```sh
./uniquewords.sh inputs/sample.txt
```

Sample expected output:
```text
Unique words: 5
```

## 17. Rename extension

**Style:** Positional arguments

Write `rename_ext.sh oldext newext` that renames files in the current directory from one extension to another.

Example:
```sh
./rename_ext.sh txt bak
```

Sample expected output:
```text
Renamed files
```

## 18. Long lines

**Style:** Positional arguments

Write `longlines.sh file threshold` that prints lines longer than the threshold.

Example:
```sh
./longlines.sh inputs/notes.txt 15
```

Sample expected output:
```text
Several matching lines
```

## 19. First and last line

**Style:** Positional arguments

Write `firstlast.sh file` that prints the first and last lines.

Example:
```sh
./firstlast.sh inputs/sample.txt
```

Sample expected output:
```text
First: hello world
Last: unix tools
```

## 20. Compare two files

**Style:** Positional arguments

Write `samefile.sh file1 file2` that reports whether contents are identical.

Example:
```sh
./samefile.sh inputs/sample.txt inputs/sample.txt
```

Sample expected output:
```text
Identical
```

## 21. Named copy

**Style:** Named arguments / flags

Write `copy_named.sh --input a --output b` that copies a file.

Example:
```sh
./copy_named.sh --input inputs/sample.txt --output out.txt
```

Sample expected output:
```text
Copied file
```

## 22. Named search

**Style:** Named arguments / flags

Write `search_named.sh --pattern error --file inputs/log.txt --ignore-case`.

Example:
```sh
./search_named.sh --pattern error --file inputs/log.txt --ignore-case
```

Sample expected output:
```text
2 matching lines
```

## 23. Named line counter

**Style:** Named arguments / flags

Write `linecount_named.sh --file inputs/notes.txt`.

Example:
```sh
./linecount_named.sh --file inputs/notes.txt
```

Sample expected output:
```text
Lines: 6
```

## 24. Trim spaces

**Style:** Named arguments / flags

Write `trim.sh --input inputs/spaces.txt --output clean.txt` that trims leading and trailing whitespace.

Example:
```sh
./trim.sh --input inputs/spaces.txt --output clean.txt
```

Sample expected output:
```text
Creates trimmed output file
```

## 25. Replace text

**Style:** Named arguments / flags

Write `replace.sh --file inputs/mixed.txt --from foo --to BAR` and print the transformed result.

Example:
```sh
./replace.sh --file inputs/mixed.txt --from foo --to BAR
```

Sample expected output:
```text
abc123
Room42
UPPER lower
BAR bar baz
```

## 26. Log summary

**Style:** Positional arguments

Write `logsummary.sh logfile` that prints counts of total lines, ERROR, WARNING, INFO.

Example:
```sh
./logsummary.sh inputs/log.txt
```

Sample expected output:
```text
Lines: 5
ERROR: 2
WARNING: 1
INFO: 2
```

## 27. Top N words

**Style:** Positional arguments

Write `topwords.sh file limit` that prints the top frequent words.

Example:
```sh
./topwords.sh inputs/dups.txt 3
```

Sample expected output:
```text
3 apple
2 banana
1 orange
```

## 28. Batch lowercase rename

**Style:** Positional arguments

Write `lower_rename.sh dir` that renames all file names in the directory to lowercase.

Example:
```sh
./lower_rename.sh SOME_DIR
```

Sample expected output:
```text
Renamed files
```

## 29. Backup txt files

**Style:** Positional arguments

Write `backup.sh source_dir backup_dir` that copies `.txt` files preserving names.

Example:
```sh
./backup.sh inputs/tree/docs backup_docs
```

Sample expected output:
```text
Copied files
```

## 30. Recent file finder

**Style:** Positional arguments

Write `recent.sh dir days` that lists files modified in the last N days.

Example:
```sh
./recent.sh inputs/tree 10
```

Sample expected output:
```text
Several paths
```

## 31. Largest file

**Style:** Positional arguments

Write `largest.sh dir` that prints the largest file in the tree.

Example:
```sh
./largest.sh inputs/tree
```

Sample expected output:
```text
One path
```

## 32. Multi-file search

**Style:** Positional arguments

Write `multisearch.sh pattern file1 file2 ...` that prints matches from all files.

Example:
```sh
./multisearch.sh hello inputs/sample.txt inputs/notes.txt
```

Sample expected output:
```text
Matching lines with file names
```

## 33. Total size by extension

**Style:** Positional arguments

Write `totalsize.sh dir ext` that prints the total byte size of matching files.

Example:
```sh
./totalsize.sh inputs/tree txt
```

Sample expected output:
```text
Total bytes
```

## 34. Merge unique

**Style:** Positional arguments

Write `merge_unique.sh out file1 file2 ...` that merges inputs, sorts, removes duplicates.

Example:
```sh
./merge_unique.sh merged.txt inputs/dups.txt inputs/sample.txt
```

Sample expected output:
```text
Created merged file
```

## 35. Average numeric args

**Style:** Positional arguments

Write `avgargs.sh` that averages numeric args and rejects non-numeric ones.

Example:
```sh
./avgargs.sh 10 20 30
```

Sample expected output:
```text
Average: 20
```

## 36. CSV stats

**Style:** Positional arguments

Write `csvstats.sh file.csv` that prints row count, columns in first row, and invalid rows with the wrong field count.

Example:
```sh
./csvstats.sh inputs/marks.csv
```

Sample expected output:
```text
Stats output
```

## 37. Help option

**Style:** Named arguments / flags

Write any script that supports `--help` and prints a usage message with options.

Example:
```sh
./myscript.sh --help
```

Sample expected output:
```text
Usage text
```

## 38. Optional output file

**Style:** Positional arguments

Write `searchsave.sh pattern file [outputfile]` that prints matches and optionally saves them.

Example:
```sh
./searchsave.sh ERROR inputs/log.txt out.txt
```

Sample expected output:
```text
Matches on screen and in file
```

## 39. Recursive TODO scan

**Style:** Positional arguments

Write `todoscan.sh dir` that scans `.c`, `.h`, `.sh` files recursively and prints file names and line numbers with `TODO`.

Example:
```sh
./todoscan.sh inputs/project
```

Sample expected output:
```text
inputs/project/src/main.c:2:TODO
inputs/project/include/util.h:1:TODO
inputs/project/scripts/run.sh:2:TODO
```

## 40. Filter CSV by named args

**Style:** Named arguments / flags

Write `filtercsv.sh --input inputs/marks.csv --column 3 --min 50`.

Example:
```sh
./filtercsv.sh --input inputs/marks.csv --column 3 --min 50
```

Sample expected output:
```text
alice,math,78
bob,science,88
carol,math,91
```

## 41. Count extension with recursive flag

**Style:** Named arguments / flags

Write `count_ext.sh --dir inputs/tree --ext txt --recursive`. Without `--recursive`, only count the top level.

Example:
```sh
./count_ext.sh --dir inputs/tree --ext txt --recursive
```

Sample expected output:
```text
Count: 2
```

## 42. Delete empty files dry-run

**Style:** Named arguments / flags

Write `cleanempty.sh --dir inputs/tree --dry-run`. Without `--dry-run`, actually delete empty files.

Example:
```sh
./cleanempty.sh --dir inputs/tree --dry-run
```

Sample expected output:
```text
List of empty files
```

## 43. File report CSV

**Style:** Positional arguments

Write `filereport.sh dir` that writes CSV rows: path,size,lines,words for each regular file.

Example:
```sh
./filereport.sh inputs/tree
```

Sample expected output:
```text
CSV report
```

## 44. Extract range

**Style:** Named arguments / flags

Write `range.sh --file inputs/notes.txt --start 2 --end 4`.

Example:
```sh
./range.sh --file inputs/notes.txt --start 2 --end 4
```

Sample expected output:
```text
this is shell scripting
TODO: clean this file
```

## 45. Bash users parser

**Style:** Positional arguments

Write `shellusers.sh inputs/passwd.txt` that prints only users with `/bin/bash`.

Example:
```sh
./shellusers.sh inputs/passwd.txt
```

Sample expected output:
```text
root
bob
```

## 46. Short and long options

**Style:** Named arguments / flags

Write `searchflex.sh` supporting both `-p error -f file` and `--pattern error --file file`.

Example:
```sh
./searchflex.sh -p ERROR -f inputs/log.txt
```

Sample expected output:
```text
2025-01-01 ERROR disk full
2025-01-02 ERROR login failed
```

## 47. Required and optional args

**Style:** Named arguments / flags

Write `report.sh --input data.txt --output out.txt [--verbose]`. With `--verbose`, print progress messages.

Example:
```sh
./report.sh --input inputs/sample.txt --output out.txt --verbose
```

Sample expected output:
```text
Saved report with progress
```

## 48. Repeated named args

**Style:** Named arguments / flags

Write `multifilegrep.sh --pattern hello --file inputs/sample.txt --file inputs/notes.txt`.

Example:
```sh
./multifilegrep.sh --pattern hello --file inputs/sample.txt --file inputs/notes.txt
```

Sample expected output:
```text
Matches from both files
```

## 49. Support --exclude

**Style:** Named arguments / flags

Write `findlogs.sh --dir inputs/tree --exclude archive --ext log`. Skip directories with the excluded name.

Example:
```sh
./findlogs.sh --dir inputs/tree --exclude archive --ext log
```

Sample expected output:
```text
inputs/tree/logs/app.log
inputs/tree/logs/empty.log
```

## 50. Order-independent named args

**Style:** Named arguments / flags

Write `replace_named.sh` where `--file`, `--from`, and `--to` may appear in any order.

Example:
```sh
./replace_named.sh --to BAR --file inputs/mixed.txt --from foo
```

Sample expected output:
```text
Same transformed output
```

## 51. Full text stats

**Style:** Named arguments / flags

Write `textstats.sh --input inputs/sample.txt` that prints lines, words, chars, unique words, top 5 words, longest line, average words per line.

Example:
```sh
./textstats.sh --input inputs/sample.txt
```

Sample expected output:
```text
Summary report
```

## 52. Directory audit

**Style:** Named arguments / flags

Write `audit.sh --dir inputs/tree` printing totals, empties, 5 largest files, 5 newest files.

Example:
```sh
./audit.sh --dir inputs/tree
```

Sample expected output:
```text
Audit summary
```

## 53. Date-filter log

**Style:** Named arguments / flags

Write `logfilter.sh --input inputs/log.txt --from 2025-01-01 --to 2025-01-01` to print only logs in the date range.

Example:
```sh
./logfilter.sh --input inputs/log.txt --from 2025-01-01 --to 2025-01-01
```

Sample expected output:
```text
2025-01-01 INFO start
2025-01-01 WARNING low memory
2025-01-01 ERROR disk full
```

## 54. CSV deduplicator

**Style:** Named arguments / flags

Write `dedupcsv.sh --input inputs/data.csv --key 1 --output cleaned.csv` keeping first occurrence by key.

Example:
```sh
./dedupcsv.sh --input inputs/data.csv --key 1 --output cleaned.csv
```

Sample expected output:
```text
Creates deduped CSV
```

## 55. Dedup keep latest

**Style:** Named arguments / flags

Write `dedup_latest.sh --input inputs/data.csv --id-col 1 --date-col 3` keeping the latest date per ID.

Example:
```sh
./dedup_latest.sh --input inputs/data.csv --id-col 1 --date-col 3
```

Sample expected output:
```text
1,Alice,2025-02-01
2,Bob,2025-01-03
```

## 56. Batch replace in many files

**Style:** Named arguments / flags

Write `batch_replace.sh --from TODO --to DONE --ext c --dir inputs/project` to update matching files.

Example:
```sh
./batch_replace.sh --from TODO --to DONE --ext c --dir inputs/project
```

Sample expected output:
```text
Modified files
```

## 57. Config-file driven scan

**Style:** Named arguments / flags

Write a script that reads config lines like `DIR=inputs/tree`, `EXT=log`, `PATTERN=ERROR` and prints match counts per file.

Example:
```sh
./configscan.sh config.env
```

Sample expected output:
```text
Count per file
```

## 58. Subcommands

**Style:** Named arguments / flags

Write one script `tool.sh` supporting subcommands like `count`, `search`, `topwords`.

Example:
```sh
./tool.sh count --file inputs/sample.txt
```

Sample expected output:
```text
Count output
```

## 59. Archive logs report

**Style:** Named arguments / flags

Write `archive_logs.sh --dir inputs/tree/logs --output report.txt` that summarizes `.log` files and creates a tar archive.

Example:
```sh
./archive_logs.sh --dir inputs/tree/logs --output report.txt
```

Sample expected output:
```text
Report file and tar archive
```

## 60. Robust parser

**Style:** Named arguments / flags

Write one script supporting `--input`, `--output`, `--pattern`, `--ignore-case`, `--dry-run`, `--verbose`, `--help`, rejecting unknown flags.

Example:
```sh
Various tests
```

Sample expected output:
```text
Validated behavior
```

## 61. Reusable parse_args()

**Style:** Named arguments / flags

Write a script with a `parse_args()` function and demonstrate storing parsed values in variables.

Example:
```sh
Any test
```

Sample expected output:
```text
Parsed options
```

## 62. Reusable usage()

**Style:** Named arguments / flags

Write a script where every usage error calls `usage()` and exits with code 1.

Example:
```sh
Bad-argument test
```

Sample expected output:
```text
Usage on bad args
```

## 63. Exit codes

**Style:** Positional arguments

Write a script using exit code 0 for success, 1 for usage error, 2 for missing file, 3 for invalid content.

Example:
```sh
Different test cases
```

Sample expected output:
```text
Correct status codes
```

## 64. Logging helpers

**Style:** Named arguments / flags

Write a script with `log_info` and `log_error` helpers; `log_info` only prints with `--verbose`.

Example:
```sh
Any file task
```

Sample expected output:
```text
Visible logging
```

## 65. Confirmation prompt

**Style:** Named arguments / flags

Write a script that asks `Delete 12 files? [y/N]` before deleting files.

Example:
```sh
Use temp dir
```

Sample expected output:
```text
Prompted delete
```

## 66. Support --yes

**Style:** Named arguments / flags

Extend the previous script so `--yes` skips the prompt.

Example:
```sh
Use temp dir
```

Sample expected output:
```text
No prompt
```

## 67. Temporary file with trap

**Style:** Positional arguments

Write a script that uses a temporary file and removes it with `trap` on exit.

Example:
```sh
Any transform task
```

Sample expected output:
```text
Temp file cleaned
```

## 68. Handle SIGINT

**Style:** Positional arguments

Write a script that traps Ctrl+C and prints `Interrupted. Cleaning up...`.

Example:
```sh
Manual test
```

Sample expected output:
```text
Cleanup message
```

## 69. Multiple formats

**Style:** Named arguments / flags

Write `report.sh --format text|csv|json` producing the same stats in different formats.

Example:
```sh
./report.sh --format json --input inputs/sample.txt
```

Sample expected output:
```text
Different format outputs
```

## 70. Split library and main

**Style:** Positional arguments

Create `lib.sh` with helper functions and `main.sh` that sources it to solve a text-processing task.

Example:
```sh
./main.sh inputs/sample.txt
```

Sample expected output:
```text
Modular result
```

