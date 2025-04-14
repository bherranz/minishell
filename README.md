# Minishell 🐚

Minishell is a minimalist shell implementation in C that replicates basic Bash behavior. This project was developed as part of the 42 programming school to deepen understanding of process management, signals, and system interaction.

## Table of Contents
1. [Features](#-features)
2. [Installation & Usage](#-installation--usage)
3. [Project Structure](#-project-structure)
4. [Usage Example](#-usage-example)
5. [Dependencies](#-dependencies)
6. [Authors](#-authors)

## 📌 Features

- Interactive prompt with command history.
- Execution of system commands (via PATH or absolute/relative paths).
- Implementation of redirection operators (`<`, `>`, `>>`, `<<`).
- Support for pipelines (`|`).
- Environment variable expansion (`$VAR` and `$?`).
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`).
- Built-in command implementation:
  - `echo` (with `-n`)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## 🚀 Installation & Usage

```bash
# Clone the repository
git clone https://github.com/bherranz/minishell.git
cd minishell

# Compile the project
make

# Run minishell
./minishell
```

## 📂 Project Structure

```
minishell/
├── src/        # Source code
├── inc/        # Header files
├── libft/      # External library used
├── Makefile    # Build script
└── README.md   # Project documentation
```

## 📷 Usage Example

```bash
$> echo "Hello, world"
Hello, world
$> ls -l | grep minishell
-rwxr-xr-x  1 user  group  12345 Mar 10 20:00 minishell
$> export VAR=42
$> echo $VAR
42
$> exit
```

## 🛠 Dependencies

Minishell uses the following external functions:
- `readline`, `add_history`, `rl_clear_history` (input handling)
- `execve`, `fork`, `pipe`, `dup2` (process management and command execution)
- `signal`, `sigaction` (signal handling)

## 👨‍💻 Authors

Developed by [miparis](https://github.com/miparis) and [bherranz](https://github.com/bherranz).
