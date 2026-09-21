# TaskFlow — Simple Task Manager in C++

A small command-line task manager I built while learning C++ and
backend fundamentals. Tasks are added with a priority, listed, marked
complete, or deleted — and everything is saved to a text file so your
list survives restarts.

## Features

- Add tasks with a priority (1 high, 2 medium, 3 low)
- List tasks sorted by priority (high first)
- Mark tasks complete
- Delete tasks
- Persistent storage in `tasks.txt` (loaded on start, saved on exit)
- Input validation — bad input never crashes the program

## Getting Started

You need a C++ compiler with C++17 support (g++ 8+, clang++ 7+,
or MSVC 19+).

### Build and run

```bash
make        # builds the "taskflow" executable
make run    # builds and runs it
```

Or compile manually:

```bash
g++ -std=c++17 -Wall -Wextra -O2 src/main.cpp src/TaskManager.cpp -o taskflow
./taskflow
```

### Clean up

```bash
make clean
```

## Example session

```
=== TaskFlow — simple task manager (C++) ===

1. Add task
2. List tasks
3. Complete task
4. Delete task
5. Save and quit
> 1
  Task title: Finish C++ assignment
  Priority (1 high, 2 medium, 3 low): 2
  Added task #1.

> 2

  ID  PRI  DONE  TITLE
  --  ---  ----  -----
  1    2    [ ]  Finish C++ assignment

  1 task(s) total.
```

## Project structure

```
src/
  Task.h           # Task struct (data model)
  TaskManager.h    # TaskManager class interface
  TaskManager.cpp  # TaskManager implementation (add/complete/remove/save/load)
  main.cpp         # Command-line menu and user interaction
Makefile           # build automation
```

## What I learned building this

- Designing a class interface in a header file and implementing it separately
- File I/O with `ifstream`/`ofstream` for simple persistence
- Input validation with `std::cin` error states
- Organizing a small multi-file project with a Makefile

## Ideas for the future

- Search/filter tasks by keyword
- Due dates
- Export/import JSON
