This project has been created as part of the 42 curriculum by <andriamr>[, <nyrakoto>[, ]]

## minishell

## Description

**Minishell** is a simplified implementation of a UNIX shell, created as part of the 42 school curriculum. This project aims to recreate the basic features of a command interpreter, similar to bash, in C with the use of limited functions.

### Project goals

- Understand the internal workings of a UNIX shell
- Master processes and signal handling on Linux
- Implement a robust command line parser
- Handle redirections and pipes
- Recreate built-in commands
- Understand multitasking at the process level

### Overview

Minishell provides a command line interface that allows the user to execute programs, manage environment variables, use file redirections, and chain commands with pipes. It similar of bash behavior for the implemented features.

---

## Features

### Built-in commands (Builtins)

- **`echo`**: Prints arguments with `-n` option (no trailing newline)
- **`cd`**: Changes the current directory (relative and absolute paths)
- **`pwd`**: Prints the current working directory
- **`export`**: Sets environment variables
- **`unset`**: Unsets environment variables
- **`env`**: Displays environment variables
- **`exit`**: Exits the shell with an optional return code

### Advanced features

- **Quote handling**: Single quotes `'` and double quotes `"`
- **Variable expansion**: `$VAR` and `$?` (return code)
- **Redirections**:
  - `<`: Input redirection
  - `>`: Output redirection (truncate)
  - `>>`: Output redirection (append)
  - `<<`: Here-document
- **Pipes**: Chaining commands with `|`
- **Signal handling**:
  - `Ctrl-C`: Displays a new prompt
  - `Ctrl-D`: Exits the shell
  - `Ctrl-\`: Ignored
- **Command history**: Navigation with up/down arrows
- **Error handling**: Appropriate error messages and return codes

---

## Instructions

### Requirements

- **Operating system**: Linux
- **Compiler**: GCC, CC or CLANG with C99 or higher support
- **Libraries**:
  - `readline` (GNU Readline Library)
  - `ncurses`

### Compilation

To compile the project, simply use the provided Makefile:

```bash
make
```

This will generate the `minishell` executable at the root of the project.

### Cleaning

```bash
# Remove object files
make clean

# Remove object files and the executable
make fclean

# Fully recompile the project
make re
```

### Execution

To run minishell:

```bash
./minishell
```

You will then see the prompt:

```
minishell$
```

### Usage examples

```bash
# Simple command
minishell$ echo "Hello World"
Hello World

# Variable expansion
minishell$ export NAME=andriamr
minishell$ echo "Hello $NAME"
Hello andriamr

# Return code
minishell$ ls /nonexistent
ls: cannot access '/nonexistent': No such file or directory
minishell$ echo $?
2

# Pipes
minishell$ ls -l | grep minishell | wc -l
1

# Redirections
minishell$ echo "Test" > output.txt
minishell$ cat < output.txt
Test
minishell$ echo "Line 2" >> output.txt
minishell$ cat output.txt
Test
Line 2

# Here-document
minishell$ cat << EOF
> Hello
> World
> EOF
Hello
World

# Chained commands
minishell$ echo "First" | cat -e | cat -e
First$

# Change directory
minishell$ cd /tmp
minishell$ pwd
/tmp
minishell$ cd -
minishell$ pwd
/home/user

# Exit the shell
minishell$ exit 42
```

## Resources

### Official documentation

- Peer to peer learning
- [Linux Man Pages] - On UNIX terminal
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/) - Complete documentation of the bash shell
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) - POSIX standard for shells
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) - Documentation for the readline library
 ...

---

## Use of AI
- To better understand the approach and design of the project instead of starting randomly
- To test robustness
- To better understand the use of authorized functions and their differences
- In the context of this project, AI was used as an assistance tool for project design to make it more achievable
- Structuring and formatting of the documentation
- Suggestions of usage examples


### Parts developed without AI

- **Global project architecture**: Design of data structures and modular organization
- **Parser implementation**: Tokenization, quote handling, variable expansion
- **Business logic of builtins**: Implementation of `cd`, `echo`, `export`, `unset`, etc.
- **Process management**: Fork, exec, pipes, redirections
- **Signal management**: SIGINT, SIGQUIT handlers for different contexts
- **Memory management**: Allocation/freeing and prevention of memory leaks

---

## Project structure

```
minishell/
├── Makefile              # Build file
├── README.md             # This file
├── include/
│   └── minishell.h       # Main header with structures and prototypes
├── LIBFT/                # Libft library (utility functions)
│   ├── ft_*.c
│   ├── libft.h
│   └── Makefile
└── src/
    ├── builtins/         # Built-in commands
    │   ├── cd.c
    │   ├── echo.c
    │   ├── env.c
    │   ├── exit.c
    │   ├── export.c
    │   ├── pwd.c
    │   ├── unset.c
    │   └── check_builtins.c
    ├── execution/        # Command execution
    │   ├── main.c
    │   ├── cmd_line.c
    │   ├── execution.c
    │   ├── pipe.c
    │   ├── pipeline.c
    │   ├── pipeline_utils.c
    │   ├── redirection.c
    │   └── signal.c
    └── parsing/          # Input analysis and processing
        ├── tokenisation.c
        ├── split_token.c
        ├── ft_expander.c
        ├── expander_utils.c
        ├── ft_quote.c
        ├── checker_pipe.c
        ├── split_by_pipe.c
        ├── add_cmd.c
        ├── put_cmd.c
        ├── list_pars.c
        ├── pars_utils.c
        ├── token_utils.c
        ├── split_utils.c
        ├── struct_init.c
        ├── ft_list_str.c
        └── ft_exit.c
```

---

## Technical choices

### Modular architecture

The project is organized into two main modules:

1. **Parsing**: Lexical and syntactic analysis of the command line
2. **Execution**: Management of processes, pipes and redirections, builtins

This separation facilitates maintenance and allows for better testability.

### Memory management

- Systematic use of `valgrind` to detect leaks
- Dedicated free functions for each structure
- Strict handling of allocations during variable expansion

### Parsing

- Separation by pipe
- Two-pass tokenization: separator detection then extraction
- Quote handling by maintaining a state (`in_quote`, `in_dquote`)
- Variable expansion during parsing for double quotes

---

## Acknowledgements

- The 42 school team
- The teaching staff of 42 Antananarivo
- The 42 community for the shared resources

---

*Project completed in January 2026 - 42 Antananarivo*
