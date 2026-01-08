# Simple Shell (hsh) - Logic Flowchart

## Main Flow Diagram

```
┌─────────────────────────────────────────┐
│   START: main()                         │
│   - Check if interactive (isatty)       │
│   - Initialize variables                │
└────────────────┬────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────┐
│   DISPLAY PROMPT (if interactive)       │
│   Print: "($) "                         │
└────────────────┬────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────┐
│   READ INPUT: getline()                 │
│   - EOF detected?                       │
│     ├─ YES → Print newline & BREAK      │
│     └─ NO → Continue                    │
└────────────────┬────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────┐
│   VALIDATE INPUT                        │
│   - Strip newline character             │
│   - Empty line?                         │
│     ├─ YES → Skip to next iteration     │
│     └─ NO → Continue                    │
└────────────────┬────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────┐
│   PARSE COMMAND: split_line()           │
│   - Tokenize by spaces & tabs           │
│   - Build argv array                    │
│   - NULL-terminate array                │
└────────────────┬────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────┐
│   CHECK: Is args[0] == "exit"?          │
│   ├─ YES → Free memory & BREAK loop     │
│   └─ NO → Continue                      │
└────────────────┬────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────┐
│   CHECK BUILT-INS: handle_builtin()     │
│   ├─ "env" → Execute builtin_env()      │
│   └─ Other → Return -1 (not built-in)   │
└────────────────┬────────────────────────┘
                 │
        ┌────────┴────────┐
        │                 │
        ▼                 ▼
   ┌─────────┐      ┌──────────────────┐
   │Built-in │      │Not Built-in      │
   │Executed │      │Execute via fork  │
   │Return   │      │& execve()        │
   │status   │      │                  │
   └────┬────┘      └────────┬─────────┘
        │                    │
        └────────┬───────────┘
                 │
                 ▼
┌─────────────────────────────────────────┐
│   CLEANUP: Free memory                  │
│   - Free args array                     │
│   - Free each token                     │
│   - Increment line number               │
└────────────────┬────────────────────────┘
                 │
                 ▼
              [LOOP BACK TO PROMPT]

```

---

## Detailed Sub-Process: execute_cmd()

When a command is NOT a built-in, this function handles execution:

```
┌──────────────────────────────────┐
│  RECEIVE: argv[], argv0, line_num│
└────────────┬─────────────────────┘
             │
             ▼
┌──────────────────────────────────┐
│  DETERMINE PATH TYPE             │
│  - Contains '/'?                 │
│    ├─ YES → Full path provided   │
│    └─ NO → Search in PATH env    │
└────────────┬─────────────────────┘
             │
    ┌────────┴─────────┐
    │                  │
    ▼                  ▼
[Full Path]      [search_path()]
   │                   │
   │              ┌────┴──────┐
   │              │            │
   └──────────────┼────────────┘
                  │
                  ▼
        ┌──────────────────────┐
        │ CHECK: File exists   │
        │ & is executable      │
        │ (access X_OK)        │
        └──────────┬───────────┘
                   │
          ┌────────┴────────┐
          │                 │
          ▼                 ▼
      [EXISTS]         [NOT FOUND]
          │                 │
          │         ┌───────┴────────┐
          │         │ Print error:   │
          │         │ "not found"    │
          │         │ Return 127     │
          │         │ Free memory    │
          │         └────────┬───────┘
          │                  │
          ▼                  │
    ┌──────────────┐         │
    │  FORK()      │         │
    │  PID = -1?   │         │
    │  ├─ Error    │         │
    │  │ Return 1  │         │
    │  └─ Continue │         │
    └──────┬───────┘         │
           │                 │
    ┌──────┴────────┐        │
    │               │        │
    ▼               ▼        │
[CHILD]      [PARENT]        │
 PID=0        wait()          │
    │           │            │
    │     ┌─────┴──────┐     │
    │     │            │     │
    ▼     │            │     │
 execve() │     [Exit Status] │
 (or      │            │     │
  error)  ▼            │     │
    │   Return         │     │
    │   status         │     │
    │                  │     │
    └─────────────┬────┴─────┘
                  │
                  ▼
         [RETURN TO MAIN LOOP]
```

---

## Sub-Process: search_path()

Finds a command in the PATH environment variable:

```
┌────────────────────────────┐
│ INPUT: cmd (e.g., "ls")    │
└────────────┬───────────────┘
             │
             ▼
┌────────────────────────────┐
│ GET PATH env variable      │
│ (using _getenv())          │
│ PATH not set?              │
│ ├─ YES → Return NULL       │
│ └─ NO → Continue           │
└────────────┬───────────────┘
             │
             ▼
┌────────────────────────────┐
│ SPLIT PATH by ":"          │
│ - Allocate copy of PATH    │
│ - Use strtok()             │
│ - Get first directory      │
└────────────┬───────────────┘
             │
             ▼
        [LOOP THROUGH DIRS]
             │
             ▼
┌────────────────────────────┐
│ FOR EACH DIRECTORY:        │
│ - Build full path:         │
│   dir/cmd                  │
│ - Check if executable      │
│   (access X_OK)            │
└────────────┬───────────────┘
             │
    ┌────────┴────────┐
    │                 │
    ▼                 ▼
[FOUND]           [NOT FOUND]
    │                 │
    │           Get next dir
    │                 │
    │         ┌───────┘
    │         ▼
    │      [More dirs?]
    │         │
    │    ┌────┴────┐
    │    │         │
    │    │ YES     NO
    │    │         │
    │    ▼         ▼
    │ [CONTINUE] [RETURN NULL]
    │            Free copy
    │
    ▼
[ALLOCATE & RETURN]
 Full path string
 Free copy
```

---

## Sub-Process: split_line()

Tokenizes input into command arguments:

```
┌──────────────────────────┐
│ INPUT: "ls -la /tmp"     │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│ ALLOCATE tokens array    │
│ (initial size: 64)       │
│ ALLOCATE copy of line    │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│ TOKENIZE by " " & "\t"   │
│ (strtok)                 │
│ Get first token          │
└────────────┬─────────────┘
             │
             ▼
        [LOOP EACH TOKEN]
             │
             ▼
┌──────────────────────────┐
│ ALLOCATE memory for      │
│ token & add to array     │
│ Position++               │
│ Check buffer size        │
│ ├─ Need realloc?         │
│ │ YES → Double size      │
│ └─ NO → Continue         │
└────────────┬─────────────┘
             │
             ▼
      [Get next token]
             │
    ┌────────┴────────┐
    │                 │
    ▼                 ▼
[TOKEN EXISTS]    [NO MORE]
    │               │
    │          ┌────┴─────────┐
    │          │              │
    │          ▼              ▼
    │      [NULL TERMINATE]   │
    │      [FREE COPY]        │
    └─────────┬───────────────┘
              │
              ▼
    [RETURN argv ARRAY]
```

---

## Built-in Commands: handle_builtin()

```
┌──────────────────────────┐
│ INPUT: argv[], argv0,    │
│ line_num                 │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│ CHECK argv[0]:           │
│ ├─ "exit"? → handled     │
│ │           in main()    │
│ ├─ "env"? → Print env    │
│ │           Return 0     │
│ └─ Other? → Return -1    │
│            (not built-in)│
└──────────────┬───────────┘
               │
               ▼
    [RETURN status OR -1]
```

---

## Memory Management Flow

```
ALLOCATION PATH:
main() calls split_line()
    ├─ Allocates tokens array
    ├─ Allocates copy of line
    └─ Allocates each token

CLEANUP PATH (in main loop):
    ├─ Free each token: args[i]
    ├─ Free args array
    └─ Continue to next iteration

Final cleanup on exit:
    └─ Free line buffer
```

---

## Error Handling

| Scenario | Action | Return |
|----------|--------|--------|
| Command not found | Print error to stderr | 127 |
| fork() fails | Print "fork" error | 1 |
| execve() fails | Print error & exit(127) | - |
| PATH not set | Return NULL from search_path() | - |
| malloc() fails | Print "malloc" error, return NULL | - |
| EOF reached | Clean up and exit | 0 |

---

## Key Functions Summary

| Function | Purpose | Returns |
|----------|---------|---------|
| `main()` | Shell loop, reads input | exit status |
| `split_line()` | Tokenizes input | argv array |
| `handle_builtin()` | Checks for built-ins | status or -1 |
| `execute_cmd()` | Forks & executes command | exit status |
| `search_path()` | Finds cmd in PATH | full path or NULL |
| `_getenv()` | Gets environment variable | value or NULL |
| `builtin_env()` | Prints environment | 0 |
| `_add_token()` | Adds token to array | tokens array or NULL |

