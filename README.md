```
╔════════════════════════════════════════════════════════════════╗
║                    SIMPLE SHELL (hsh)                          ║
║              A Unix Shell Implementation in C                  ║
╚════════════════════════════════════════════════════════════════╝
```

## Overview

This project implements a simple UNIX shell in C. The shell reads commands from the user, parses them, and executes them. It supports both interactive and non-interactive modes, providing a minimal but functional implementation of a Unix shell.

## Resources

### Recommended Reading
- Unix shell fundamentals
- Thompson shell history
- Ken Thompson biography
- Shell implementation concepts

### Man Pages
```bash
man sh          # Standard shell manual
sh              # Run the shell directly
```

## Learning Objectives

Upon completion, you should understand:

**Historical Context**
- Who designed and implemented the original Unix operating system
- Who wrote the first version of the UNIX shell
- Who invented the B programming language (predecessor to C)
- Who is Ken Thompson

**Core Concepts**
- How a shell works
- Process identifiers (pid) and parent process identifiers (ppid)
- Environment variable manipulation
- Difference between functions and system calls
- Process creation and management

**Technical Skills**
- The three prototypes of `main`
- How shells use PATH to locate programs
- The `execve` system call for program execution
- Process suspension with `waitpid`/`wait`
- EOF (end-of-file) handling

## Compilation

Compile the shell using:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($) /bin/pwd
/home/user/simple_shell
($) exit
$
```

### Non-Interactive Mode

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c

$ cat commands.txt | ./hsh
/bin/ls
/bin/pwd
```

## Requirements

### General
- **Editors**: vi, vim, emacs
- **Compiler**: gcc (Ubuntu 20.04 LTS)
- **Flags**: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- **Styling**: Betty style guide compliance
- **Memory**: No memory leaks allowed
- **Functions per file**: Maximum 5
- **Header guards**: Required for all header files

### Code Standards
- All files must end with a newline
- README.md is mandatory at project root
- Use system calls only when necessary
- Output must match `/bin/sh` behavior exactly

## Allowed Functions & System Calls

```
String Functions:          Process Management:
├── strlen()              ├── fork()
├── strcpy()              ├── execve()
├── strcat()              ├── exit() / _exit()
├── strtok()              ├── wait() / waitpid()
└── ...all from string.h  └── wait3() / wait4()

File Operations:           Memory Management:
├── open()                ├── malloc()
├── close()               └── free()
├── read()
├── write()               I/O Functions:
├── access()              ├── printf()
└── stat()                ├── fprintf()
                          └── getline()

Directory Operations:      Other:
├── opendir()             ├── getpid()
├── readdir()             ├── chdir()
├── closedir()            ├── isatty()
└── getcwd()              └── signal()
```

## Error Handling

Error output must match `/bin/sh` format:

```bash
$ echo "invalid_cmd" | ./hsh
./hsh: 1: invalid_cmd: not found
```

The program name in errors reflects `argv[0]`:
```bash
$ echo "test" | ./././hsh
./././hsh: 1: test: not found
```

## Project Structure

```
.
├── hsh              # Compiled shell executable
├── main.c           # Entry point
├── shell.c          # Core shell implementation
├── helpers.c        # Utility functions
├── builtins.c       # Built-in command handlers
└── README.md        # This file
```

## Features Implemented

- [x] Interactive prompt and command execution
- [x] Non-interactive mode (piped input)
- [x] PATH-based command lookup
- [x] Process forking and execution
- [x] Error handling and reporting
- [x] Environment variable support
- [x] Memory management
- [x] Signal handling

## Testing

The shell should pass all test cases in both modes:

```bash
# Interactive testing
$ ./hsh
($) ls -la
($) pwd
($) exit

# Non-interactive testing
$ echo "ls -la" | ./hsh
$ cat test_file | ./hsh
```

## Betty Style Compliance

Code is checked with:
```bash
betty-style.pl *.c *.h
betty-doc.pl *.c *.h
```

## Notes

- This implementation prioritizes correctness and code quality
- Each file contains no more than 5 functions
- All header files are include-guarded
- System calls are used only when necessary
- The checker will verify compliance with all requirements

---
AUTHORS:
C. Silva & D. Rossi

```
╔══════════════════════════════════════════════════════╗
║  "The Unix philosophy: Do one thing and do it well"  ║
║                   -  Ken Thompson                    ║
╚══════════════════════════════════════════════════════╝
```
