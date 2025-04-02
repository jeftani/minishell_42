# Minishell

## Introduction
**Minishell** is a custom Unix shell designed to replicate basic functionalities of a real shell, like Bash or Zsh. This project enhances understanding of process control, signal handling, memory management, and command execution in C. The goal is to create a fully interactive and functional shell with built-in commands, environment variable management, and pipeline support.

## Table of Contents
- [Features](#features)
- [Project Requirements](#project-requirements)
- [Functionality](#functionality)
- [Command Execution](#command-execution)
- [Pipes and Redirections](#pipes-and-redirections)
- [Environment Variable Handling](#environment-variable-handling)
- [Signal Handling](#signal-handling)
- [Built-in Commands](#built-in-commands)
- [Compilation](#compilation)
- [Usage](#usage)
- [Testing](#testing)
- [Memory Management](#memory-management)
- [Future Improvements](#future-improvements)
- [License](#license)

## Features
- Interactive command-line interface
- Execution of external commands (`ls`, `grep`, `cat`, etc.)
- Built-in commands (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
- Handling of pipes (`|`) and redirections (`>`, `<`, `>>`, `<<`)
- Environment variable management (`$HOME`, `$PATH`, etc.)
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Proper memory management to avoid leaks
- Error handling for invalid inputs and system calls

## Project Requirements
Minishell adheres to the following specifications:
- **No usage of `system()` or `execvp()`**
- **Handling of PATH resolution manually**
- **No use of external libraries except standard C functions (`malloc`, `free`, `read`, `write`, `fork`, `execve`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `kill`, `getcwd`, `chdir`, `stat`, `lstat`, `fcntl`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs` )**
- **Must be able to handle multiple commands at once using pipes**
- **Must support redirections (`>`, `<`, `>>`, `<<`)**
- **Correctly handle environment variables and export/unset commands**
- **Handle `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` properly**

## Functionality
Minishell operates as follows:
1. Displays a prompt and waits for user input.
2. Parses the command and tokenizes arguments.
3. Handles built-in commands directly.
4. Forks a child process for external commands and executes them using `execve()`.
5. Waits for process completion and updates the exit status.
6. Handles pipes and redirections correctly.

## Command Execution
- If the command is built-in (`cd`, `echo`, etc.), it is executed in the parent process.
- If it is an external command, a child process is created using `fork()`, and `execve()` is called to execute it.
- The shell waits for command completion before displaying a new prompt.
- Environment variables are resolved before execution (`echo $HOME`).

## Pipes and Redirections
- **Pipes (`|`)** allow output of one command to be passed as input to another.
- **Redirections (`>`, `<`, `>>`, `<<`)** are handled by modifying file descriptors using `dup2()`.
- **Multiple pipes and mixed redirections** are supported.

## Environment Variable Handling
- Variables are stored in a linked list or array.
- The `export` command sets new variables or updates existing ones.
- The `unset` command removes environment variables.
- The `env` command displays the current environment variables.

## Signal Handling
Minishell properly handles:
- `Ctrl+C` (SIGINT) – Interrupts a running process but keeps the shell alive.
- `Ctrl+D` (EOF) – Exits the shell when typed at an empty prompt.
- `Ctrl+\` (SIGQUIT) – Kills running processes but does not quit the shell.

## Built-in Commands
Minishell implements the following built-in commands:
- `echo` - Print text to stdout
- `cd` - Change directory
- `pwd` - Print working directory
- `export` - Set environment variables
- `unset` - Remove environment variables
- `env` - Print environment variables
- `exit` - Exit the shell

## Compilation
To compile **minishell**, run:
```sh
make
```
This will generate the `minishell` executable.

To clean object files:
```sh
make clean
```
To remove all compiled files:
```sh
make fclean
```
To recompile everything:
```sh
make re
```

## Usage
Run the shell with:
```sh
./minishell
```
Example session:
```sh
$ echo "Hello, Minishell!"
Hello, Minishell!
$ ls -l | grep minishell
$ cat file.txt > output.txt
$ export MYVAR=42
$ echo $MYVAR
42
$ unset MYVAR
$ cd /tmp && pwd
/tmp
$ exit
```

## Testing
Run various commands to test functionality:
```sh
ls -la | grep minishell
cat file.txt > newfile.txt
export MYVAR=42 && echo $MYVAR
unset MYVAR
cd /tmp && pwd
ls | wc -l
```

## Memory Management
- All dynamically allocated memory is freed before exiting.
- `valgrind` or `asan` can be used to check for memory leaks.
- All system calls are checked to prevent invalid memory access.

## Future Improvements
- Add support for wildcard expansion (`*` and `?`).
- Improve error messages for invalid commands.
- Implement job control (background processes `&`).
- Implement `history` command.

## License
This project is open-source and can be used for educational purposes.

