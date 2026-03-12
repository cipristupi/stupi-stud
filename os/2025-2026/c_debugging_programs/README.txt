# C Debugging Practice Set

This contains 10 intentionally broken `.c` programs for debugging practice.

Design goals for each file:
- uses dynamic memory allocation
- contains multiple functions
- includes at least one allocation inside a function
- intended to contain:
  - 3 compilation errors
  - 3 compiler warnings (typically visible with `gcc -Wall -Wextra`)
  - 2 runtime memory issues to investigate with Valgrind after compilation errors are fixed

Suggested workflow:
1. Compile with:
   gcc -Wall -Wextra -g program_name.c -o program_name
2. Fix compile errors first.
3. Recompile and inspect warnings.
4. Run Valgrind:
   valgrind --leak-check=full --track-origins=yes ./program_name

These programs are intentionally wrong and may contain undefined behavior until fixed.