# Mini-Lab: File I/O and Smart Pointers

**CIS-25: Data Structures**
**November 26, 2025**

## Overview

In this lab, you'll fix three C++ programs that have bugs related to file I/O and memory management. Each problem demonstrates common mistakes that cause real issues in C++ code.

**Collaboration:** Work in groups of up to 4. Submit one zipped copy of the repository per group. Include all group members' names as a comment on the Canvas submission or in a text file in the repo.

## The Problems

1. `problem1.cpp` — **Broken File Reading**: Code that fails to correctly read a CSV file.
2. `problem2.cpp` — **Broken Smart Pointers**: Code with memory leaks that should use smart pointers.
3. `problem3.cpp` — **Implement RAII**: Implement a wrapper class that automatically manages a resource.

## Setup

1. Download the starter code from Canvas (or clone the repository)
2. Open the folder in CLion (File > Open, select the folder containing `CMakeLists.txt`)
3. Build the project (Build > Build Project)

## Your Task

For each problem:

1. **Read the code** and the comments describing the bugs
2. **Fix the bugs** — make the code work correctly
3. **Test your fix** — run the program and verify correct output
4. **Document your changes** in your submission

## Problem Details

### Problem 1: Broken File Reading

The code reads student records from `data/students.csv` but has three bugs:

1. No error handling for file open failure — should check if file opened successfully, throw an exception if not, and use `try/catch` in the caller to exit gracefully with an error message
2. Doesn't skip the header row
3. Uses wrong delimiter (space instead of comma)

**Expected output when fixed:**
```
Loaded 3 students:
Alice Johnson (ID: 1001, GPA: 3.8)
Bob Smith (ID: 1002, GPA: 3.5)
Carol White (ID: 1003, GPA: 3.9)
```

### Problem 2: Broken Smart Pointers

The code has memory management bugs that should be fixed with smart pointers:

1. Memory leak on early return (fix with `unique_ptr`)
2. Double-delete scenario (would crash without smart pointers)
3. Use-after-free scenario (undefined behavior)

**Your task:**
- Add `#include <memory>`
- Replace raw pointers with `std::unique_ptr` or `std::shared_ptr`
- Remove manual `delete` calls
- Verify destructor messages show proper cleanup

### Problem 3: Implement RAII

The code has a `DatabaseConnection` class that requires manual `connect()` and `disconnect()` calls. When functions return early, the connection is left open.

**Your task:** Implement a `ConnectionGuard` class that:
- Takes a `DatabaseConnection*` in its constructor
- Calls `connect()` in the constructor
- Calls `disconnect()` in the destructor

Then modify the functions to use `ConnectionGuard` instead of manual connect/disconnect.

**Test:** All "Connection still open?" checks should print "No (correct)".

## Deliverables

Submit a zipped copy of your completed repository containing all your fixed code. Include group members' names as a comment on the Canvas submission or in a `README.txt` file in the repo.

## Grading Rubric (15 points)

- **Problem 1** (5 points): All file reading bugs fixed, correct output
- **Problem 2** (5 points): Smart pointers used correctly, no memory leaks
- **Problem 3** (5 points): RAII wrapper implemented, connections auto-close

## Tips

- Read the lecture notes section on File I/O for CSV parsing examples
- Read the lecture notes section on Smart Pointers for `unique_ptr` and `shared_ptr` examples
- The RAII section shows how to build a wrapper class
- Test incrementally — fix one bug at a time and verify it works
