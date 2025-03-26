# Distributed Calculator using Inter-Process Communication in C

This project is a modular, Linux-based distributed calculator system developed in C for the Operating Systems course. It demonstrates fundamental operating system concepts including:

- Process creation (`fork`)
- Program execution (`exec`)
- Inter-process communication (named pipes/FIFOs)
- Synchronization and error handling
- Result persistence with a dedicated saver process

### 🛠️ Architecture

- `calculator.c`: Main controller that handles user input and manages child processes
- `addition.c`, `subtraction.c`, `multiplication.c`, `division.c`: Perform respective operations independently
- `saver.c`: Stores results into `results.txt`
- Communication: Named pipes (`mkfifo`)
- Automation: `Makefile` provided for easy compilation

### 📁 Example Workflow
1. User selects an operation
2. `calculator.c` forks a child and execs the respective operation process
3. Inputs are sent via pipes
4. Results are returned and saved by `saver.c`


