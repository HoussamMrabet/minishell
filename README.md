# Minishell

Welcome to the Minishell project repository! This project is a simple implementation of a shell, developed in collaboration with [mel-hamd](https://github.com/M-elhamdaoui). We have achieved full points for both mandatory and bonus features.

## Project Overview

Minishell is a simple shell program that emulates basic shell functionalities similar to `bash`. It handles command execution, I/O redirection, environment variables, and more. This project demonstrates a thorough understanding of process management and shell operations.

## Features

### Mandatory Features
- **Prompt Display**: Displays a prompt when waiting for commands.
- **Command Execution**: Launches executables using `PATH` or relative/absolute paths.
- **I/O Redirection**:
  - `<` for input redirection
  - `>` for output redirection
  - `<<` for here documents (delimiter-based input)
  - `>>` for output redirection in append mode
- **Pipes**: Uses `|` to connect the output of one command to the input of another.
- **Environment Variables**: Expands `$` followed by a variable name to its value.
- **Exit Status**: Expands `$?` to the exit status of the last executed command.
- **Signal Handling**:
  - `ctrl-C` to interrupt and display a new prompt
  - `ctrl-D` to exit the shell
  - `ctrl-\` to do nothing
- **Built-ins**:
  - `echo` with `-n` option
  - `cd` for changing directories (relative/absolute paths)
  - `pwd` to print the current working directory
  - `export` to set environment variables
  - `unset` to remove environment variables
  - `env` to list environment variables
  - `exit` to exit the shell

### Bonus Features
- **Logical Operators**: Implements `&&` and `||` with parenthesis for command prioritization.
- **Wildcards**: Supports `*` for wildcard expansion in the current directory.

## Getting Started

### Prerequisites
- C compiler (e.g., `gcc`)
- `readline` library for command-line input

### Installation
1. **Clone the Repository**:
    ```bash
    git clone https://github.com/HoussamMrabet/minishell.git
    cd minishell
    ```

2. **Build the Project**:
    ```bash
    make
    ```

3. **Run Minishell**:
    ```bash
    ./minishell
    ```

### Usage
- **Interactive Mode**: Enter commands at the prompt.
- **Built-ins**: Use `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Redirections and Pipes**: Utilize `<`, `>`, `<<`, `>>`, and `|`.
- **Environment Variables**: Set and use variables with `$`.

## Testing
Create and run test cases to verify functionality. Use provided test programs or your own.

## Contributing
Contributions are welcome! Please submit issues, suggestions, or pull requests. Follow the coding style and guidelines provided.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements
- Thanks to [mel-hamd](https://github.com/M-elhamdaoui) for collaboration.
- The `readline` library for efficient command-line input handling.

For questions or issues, please open an issue on this repository.
