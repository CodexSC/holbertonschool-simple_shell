╔════════════════════════════════════════════════════════════════╗
║                    SIMPLE SHELL (hsh)                          ║
║              A Unix Shell Implementation in C                  ║
╚════════════════════════════════════════════════════════════════╝

## Overview

This project implements a simple UNIX shell in C. The shell reads commands from standard input, parses them into tokens, and executes them using system calls. It supports both interactive and non-interactive modes and closely follows the behavior of `/bin/sh` for basic command execution and error handling.

The goal of this project is to understand how a shell works internally, including process creation, environment handling, and command execution.

---

## Resources

### Recommended Reading

* UNIX shell fundamentals
* Thompson shell history
* Ken Thompson biography
* Shell implementation concepts

### Man Pages

```bash
man sh
man execve
man fork
man wait
```

---

## Learning Objectives

### Historical Context

* Who designed and implemented the original UNIX operating system
* Who wrote the first version of the UNIX shell
* Who invented the B programming language (predecessor to C)
* Who is Ken Thompson

### Core Concepts

* How a shell works internally
* Process identifiers (PID / PPID)
* Environment variables and PATH resolution
* Difference between system calls and library functions
* Parent/child process relationship

### Technical Skills

* The three prototypes of `main`
* Using PATH to locate executables
* Executing programs with `execve`
* Process synchronization with `wait` / `waitpid`
* Handling EOF (Ctrl+D)

---

## Compilation

Compile the shell using:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---

## Usage

### Interactive Mode

```bash
$ ./hsh
($) ls
($) pwd
($) exit
```

### Non-Interactive Mode

```bash
$ echo "/bin/ls" | ./hsh
$ cat commands.txt | ./hsh
```

---

## Shell Execution Flow

```text
User Input
   ↓
getline()
   ↓
split_line()
   ↓
handle_builtin()
   ↓ (if not builtin)
execute_cmd()
   ↓
fork()
   ↓
execve()
   ↓
wait()
```

### Description

1. The shell reads a full line from standard input using `getline`
2. The line is split into tokens (command and arguments)
3. Built-in commands are executed directly in the parent process
4. External commands are searched in the PATH
5. A child process is created using `fork`
6. The command is executed using `execve`
7. The parent process waits for the child to terminate

---

## Built-in Commands

The following built-in commands are supported:

* `env` : prints the current environment variables
* `exit` : exits the shell

Built-ins are executed without creating a new process.

---

## Error Handling

The shell strictly follows `/bin/sh` error formatting.

### Command Not Found

```bash
./hsh: 1: invalid_cmd: not found
```

* `./hsh` → shell name (`argv[0]`)
* `1` → line number
* `invalid_cmd` → command entered
* Exit status: `127`

### Fork Failure

If `fork()` fails:

* An error message is printed using `perror`
* The shell continues running safely

### Exec Failure

If `execve()` fails in the child process:

* An error message is printed
* The child exits with status `127`

---

## Exit Status Handling

* Built-in commands return their own status code
* External commands return the child process exit status
* The shell exits using the status of the last executed command

---

## Environment Handling

* Environment variables are accessed using the global `environ`
* The `PATH` variable is parsed to locate executables
* Commands containing `/` are treated as absolute or relative paths

---

## Memory Management

This shell is designed to avoid memory leaks:

* All allocated tokens are freed after each command
* Memory allocated during PATH search is released after execution
* The input buffer allocated by `getline` is freed before exiting
* No dangling pointers or double frees are present

---

## Signal Handling

* The shell handles EOF (Ctrl+D) gracefully
* In interactive mode, the shell exits cleanly on EOF
* Child processes handle execution signals independently

*(Advanced signal handling such as SIGINT is intentionally minimal.)*

---

## Limitations

This shell does **not** support:

* Pipes (`|`)
* Redirections (`>`, `<`, `>>`)
* Command chaining (`;`, `&&`, `||`)
* Variable expansion (`$VAR`)
* Aliases or job control

These features are intentionally excluded to keep the implementation simple and focused.

---

## Requirements

### General

* Editors: vi, vim, emacs
* Compiler: gcc (Ubuntu 20.04 LTS)
* Flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`
* Betty style guide compliance
* No memory leaks allowed
* Maximum 5 functions per file

### Code Standards

* All files end with a newline
* Header files are include-guarded
* Only allowed functions are used
* Output matches `/bin/sh` behavior

---

## Allowed Functions & System Calls

```
strlen   strcpy   strtok   fork   execve   wait   exit
malloc   free     access   open   read     write
isatty   stat     getenv   getline
```

---

## Authors

C. Silva & D. Rossi

```
╔══════════════════════════════════════════════════════╗
║  "The Unix philosophy: Do one thing and do it well"  ║
║                   - Ken Thompson                    ║
╚══════════════════════════════════════════════════════╝
```
