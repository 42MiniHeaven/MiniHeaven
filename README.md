# MiniHeaven
is a custom Unix-like shell written in C that mimics the basic behavior of the Bash shell.  
It was developed as a learning project to understand how shells work under the hood: parsing input, managing processes, handling redirections, pipes, built-ins, and environment variables.

---

## 📖 Overview

Minishell implements a simplified command-line interpreter that:

❌- Reads user input from a prompt
❌- Parses commands and arguments
❌- Executes external programs
❌- Supports input/output redirection (`<`, `>`, `<<`, `>>`)
❌- Supports pipes (`|`)
❌- Handles a set of built-in commands
❌- Manages environment variables and expansion
❌- Handles signals (Ctrl-C, Ctrl-D, etc.)  

---

## 🛠️ Features

❌✔ Execute external commands using `PATH`  
❌✔ Built-in commands:
❌- `cd`, `echo`, `pwd`
❌- `export`, `unset`
❌- `env`, `exit`  
❌✔ Input/Output redirection  
❌✔ Pipes  
❌✔ Environment variable expansion (`$VAR`, `$?`)  
❌✔ Signal handling similar to Bash :contentReference[oaicite:2]{index=2}

*(List more features if your implementation supports them — e.g., quoting, heredoc, etc.)*
