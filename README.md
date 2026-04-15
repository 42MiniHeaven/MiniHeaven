_This project has been created as part of the 42 curriculum by azielnic and lwittwer._ 

https://github.com/hamingway2
https://github.com/wittwerl


# Minishell
Minishell is a core project of the 42 curriculum focused on recreating a minimal Bash-like shell. It is implemented in C with basic Unix shell features. The goal of this project is to understand how command-like interpreters work internally.

This project focuses on:

- Parsing and interpreting user input
- Executing commands using system calls
- Managing processes,  file descriptors and redirections
- Handling environment variables
- Implementing built-in shell commands
- Managing signals like Ctrl-C, Ctrl-D and Ctrl-\

By completing Minishell, we gained hands-on experience with low-level programming concepts such as process control, memory management and input parsing.

## Instructions
### Installation

Clone the repository:

	git clone git@github.com:42MiniHeaven/MiniHeaven.git
	cd minishell

### Compilation
Compile the project using:

	make

### Execution
Run the shell with: 
	
	./minishell

### Cleaning

	make clean		# Remove object files
	make fclean		# Remove object files and executable
	make re			# Recompile everything

## Features
- Interactive prompt
- Execution of commands from `PATH`
- Pipes (`|`) and redirections (`<`,`>`,`>>`)
- Environment variable expansion(`$VAR`)
- Built-in commands:
	- `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)

### Usage Example

	> echo Hello
	Hello

	> export TEST=42
	> echo $TEST
	42

## Resources
### Documentation

- GNU Bash Manual
- Linux manual pages (`man`): e.g., `signal`, `fork`, `execve`

### Other information

- Git repositories

### AI Usage

AI tools (such as ChatGPT) were used as a support resource during the project. Specifically:

- To clarify concepts
- To assist with debugging and understanding error messages
- To suggest improvements in code structure and organisation
- To generate ideas for testing and edge cases
- To help write comments in the code

AI was not used to produce complete solutions but rather as a learning aid and debugging assistant.
