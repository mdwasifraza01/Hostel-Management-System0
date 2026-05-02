# Hostel Management System (C++)

A CLI-based Hostel Management System built in C++ using core Data Structures.

## Description
Efficiently manages student records and room allocation using optimized data structures. Automates hostel processes and improves record management efficiency.

## Technologies Used
- **Language:** C++
- **Data Structures:** Arrays, Linked List, Queue

## Data Structure Usage
| Structure | Used For |
|-----------|----------|
| Linked List | Student records (insert, delete, traverse, search) |
| Array | Room status tracking (O(1) access by room index) |
| Queue (FIFO) | Waiting list when no rooms are available |

## Features
- Add new student with auto room allotment
- Display all students (linked list traversal)
- Search student by ID
- Remove student and auto-allot freed room to next in queue
- View room status (all 20 rooms)
- View waiting queue
- Manual room allotment from queue

## How to Run

### Compile
```bash
g++ hostel_management.cpp -o hostel
```

### Run
```bash
./hostel        # Linux / Mac
hostel.exe      # Windows
```

## Sample Output
```
========================================================
      HOSTEL MANAGEMENT SYSTEM  (C++)
========================================================
  [1] Add Student
  [2] Display All Students
  [3] Search Student
  [4] Remove Student
  [5] Room Status
  [6] View Waiting Queue
  [7] Allot Room (from queue)
  [0] Exit
```

## Author
(Your Name) — [GitHub Profile](https://github.com/yourusername)
