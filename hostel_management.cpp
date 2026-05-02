/*
 * ============================================================
 *  HOSTEL MANAGEMENT SYSTEM
 *  Language  : C++
 *  Data Structures: Arrays, Linked List, Queue
 *  Description: Efficiently manages student records and room
 *               allocation using optimized data structures.
 *  Author    : (Your Name)
 *  GitHub    : (Your GitHub Link)
 * ============================================================
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// ─────────────────────────────────────────
//  CONSTANTS
// ─────────────────────────────────────────
const int MAX_ROOMS = 20;

// ─────────────────────────────────────────
//  STUDENT NODE  (Linked List)
// ─────────────────────────────────────────
struct Student {
    int    id;
    string name;
    string course;
    int    year;
    int    roomNumber;   // 0 = not allotted yet
    Student* next;

    Student(int i, string n, string c, int y)
        : id(i), name(n), course(c), year(y), roomNumber(0), next(nullptr) {}
};

// ─────────────────────────────────────────
//  QUEUE NODE  (Waiting list)
// ─────────────────────────────────────────
struct QueueNode {
    int studentId;
    QueueNode* next;
    QueueNode(int id) : studentId(id), next(nullptr) {}
};

// ─────────────────────────────────────────
//  WAITING QUEUE  (FIFO)
// ─────────────────────────────────────────
class WaitingQueue {
    QueueNode* front;
    QueueNode* rear;
    int size;
public:
    WaitingQueue() : front(nullptr), rear(nullptr), size(0) {}

    void enqueue(int studentId) {
        QueueNode* node = new QueueNode(studentId);
        if (!rear) { front = rear = node; }
        else        { rear->next = node; rear = node; }
        size++;
    }

    int dequeue() {
        if (!front) return -1;
        int id = front->studentId;
        QueueNode* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        size--;
        return id;
    }

    bool isEmpty()  { return front == nullptr; }
    int  getSize()  { return size; }

    void display() {
        if (isEmpty()) {
            cout << "  Queue is empty.\n";
            return;
        }
        QueueNode* cur = front;
        int pos = 1;
        while (cur) {
            cout << "  [" << pos++ << "] Student ID: " << cur->studentId << "\n";
            cur = cur->next;
        }
    }
};

// ─────────────────────────────────────────
//  HOSTEL SYSTEM
// ─────────────────────────────────────────
class HostelManagement {
    // Linked List of students
    Student*     head;
    int          nextId;

    // Array of rooms: true = occupied, false = available
    bool         rooms[MAX_ROOMS + 1];   // index 1..MAX_ROOMS

    // Waiting queue
    WaitingQueue waitQueue;

public:
    HostelManagement() : head(nullptr), nextId(1) {
        for (int i = 0; i <= MAX_ROOMS; i++) rooms[i] = false;
    }

    // ── helpers ──────────────────────────
    void clearInput() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void printLine(char ch = '-', int len = 56) {
        cout << string(len, ch) << "\n";
    }

    void printHeader(const string& title) {
        cout << "\n";
        printLine('=');
        cout << "  " << title << "\n";
        printLine('=');
    }

    // Find first free room (returns 0 if none)
    int findFreeRoom() {
        for (int i = 1; i <= MAX_ROOMS; i++)
            if (!rooms[i]) return i;
        return 0;
    }

    // Find student by id in linked list
    Student* findStudent(int id) {
        Student* cur = head;
        while (cur) {
            if (cur->id == id) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    // Insert at tail of linked list
    void insertStudent(Student* s) {
        if (!head) { head = s; return; }
        Student* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = s;
    }

    // ── 1. ADD STUDENT ───────────────────
    void addStudent() {
        printHeader("ADD NEW STUDENT");

        string name, course;
        int year;

        clearInput();
        cout << "  Enter Name   : "; getline(cin, name);
        cout << "  Enter Course : "; getline(cin, course);
        cout << "  Enter Year   : "; cin >> year;

        Student* s = new Student(nextId++, name, course, year);
        insertStudent(s);

        int room = findFreeRoom();
        if (room != 0) {
            s->roomNumber = room;
            rooms[room] = true;
            cout << "\n  Student added successfully!\n";
            cout << "  ID     : " << s->id << "\n";
            cout << "  Room   : " << room << "\n";
        } else {
            waitQueue.enqueue(s->id);
            cout << "\n  No rooms available. Student ID " << s->id
                 << " added to waiting queue (pos " << waitQueue.getSize() << ").\n";
        }
        printLine();
    }

    // ── 2. DISPLAY ALL STUDENTS ──────────
    void displayAll() {
        printHeader("ALL STUDENT RECORDS  [Linked List Traversal]");

        if (!head) { cout << "  No records found.\n"; return; }

        cout << left
             << setw(6)  << "ID"
             << setw(20) << "Name"
             << setw(16) << "Course"
             << setw(6)  << "Yr"
             << setw(8)  << "Room" << "\n";
        printLine();

        Student* cur = head;
        while (cur) {
            string roomStr = (cur->roomNumber == 0) ? "Queue" : to_string(cur->roomNumber);
            cout << left
                 << setw(6)  << cur->id
                 << setw(20) << cur->name
                 << setw(16) << cur->course
                 << setw(6)  << cur->year
                 << setw(8)  << roomStr;
            if (cur->next) cout << " -> ";
            cout << "\n";
            cur = cur->next;
        }
        printLine();
    }

    // ── 3. SEARCH STUDENT ────────────────
    void searchStudent() {
        printHeader("SEARCH STUDENT");
        int id;
        cout << "  Enter Student ID: "; cin >> id;

        Student* s = findStudent(id);
        if (!s) {
            cout << "  Student ID " << id << " not found.\n";
        } else {
            printLine();
            cout << "  ID     : " << s->id     << "\n";
            cout << "  Name   : " << s->name   << "\n";
            cout << "  Course : " << s->course << "\n";
            cout << "  Year   : " << s->year   << "\n";
            cout << "  Room   : " << (s->roomNumber == 0 ? "Waiting" : to_string(s->roomNumber)) << "\n";
            printLine();
        }
    }

    // ── 4. REMOVE STUDENT ────────────────
    void removeStudent() {
        printHeader("REMOVE STUDENT");
        int id;
        cout << "  Enter Student ID to remove: "; cin >> id;

        if (!head) { cout << "  No records exist.\n"; return; }

        Student* prev = nullptr;
        Student* cur  = head;

        while (cur && cur->id != id) { prev = cur; cur = cur->next; }

        if (!cur) { cout << "  Student ID " << id << " not found.\n"; return; }

        // Free room
        if (cur->roomNumber != 0) {
            rooms[cur->roomNumber] = false;
            cout << "  Room " << cur->roomNumber << " is now available.\n";

            // Allot freed room to next in queue
            if (!waitQueue.isEmpty()) {
                int qId  = waitQueue.dequeue();
                Student* qs = findStudent(qId);
                if (qs) {
                    qs->roomNumber       = cur->roomNumber;
                    rooms[cur->roomNumber] = true;
                    cout << "  Room " << cur->roomNumber
                         << " auto-allotted to waiting student ID " << qId << ".\n";
                }
            }
        }

        // Unlink node
        if (prev) prev->next = cur->next;
        else      head       = cur->next;

        cout << "  Student \"" << cur->name << "\" removed.\n";
        delete cur;
        printLine();
    }

    // ── 5. ROOM STATUS ───────────────────
    void roomStatus() {
        printHeader("ROOM STATUS  [Array]");

        int occ = 0, avail = 0;
        cout << left << setw(8) << "Room" << setw(14) << "Status" << "Index\n";
        printLine();
        for (int i = 1; i <= MAX_ROOMS; i++) {
            cout << left << setw(8) << i
                 << setw(14) << (rooms[i] ? "Occupied" : "Available")
                 << "[" << i << "]\n";
            rooms[i] ? occ++ : avail++;
        }
        printLine();
        cout << "  Occupied : " << occ   << "  |  "
             << "Available: " << avail  << "  |  "
             << "Total: "     << MAX_ROOMS << "\n";
        printLine();
    }

    // ── 6. WAITING QUEUE ─────────────────
    void showQueue() {
        printHeader("WAITING QUEUE  [FIFO]");
        waitQueue.display();
        cout << "  Queue size: " << waitQueue.getSize() << "\n";
        printLine();
    }

    // ── 7. ALLOT ROOM MANUALLY ───────────
    void allotRoom() {
        printHeader("ALLOT ROOM");
        if (waitQueue.isEmpty()) {
            cout << "  No students in waiting queue.\n";
            return;
        }
        int room = findFreeRoom();
        if (room == 0) {
            cout << "  No rooms available right now.\n";
            return;
        }
        int id = waitQueue.dequeue();
        Student* s = findStudent(id);
        if (s) {
            s->roomNumber = room;
            rooms[room]   = true;
            cout << "  Room " << room << " allotted to "
                 << s->name << " (ID: " << id << ").\n";
        }
        printLine();
    }

    // ── MAIN MENU ────────────────────────
    void run() {
        int choice;
        do {
            cout << "\n";
            printLine('=');
            cout << "      HOSTEL MANAGEMENT SYSTEM  (C++)\n";
            printLine('=');
            cout << "  [1] Add Student\n";
            cout << "  [2] Display All Students\n";
            cout << "  [3] Search Student\n";
            cout << "  [4] Remove Student\n";
            cout << "  [5] Room Status\n";
            cout << "  [6] View Waiting Queue\n";
            cout << "  [7] Allot Room (from queue)\n";
            cout << "  [0] Exit\n";
            printLine();
            cout << "  Enter choice: "; cin >> choice;

            switch (choice) {
                case 1: addStudent();    break;
                case 2: displayAll();   break;
                case 3: searchStudent(); break;
                case 4: removeStudent(); break;
                case 5: roomStatus();   break;
                case 6: showQueue();    break;
                case 7: allotRoom();    break;
                case 0: cout << "\n  Exiting... Goodbye!\n\n"; break;
                default: cout << "  Invalid choice. Try again.\n";
            }
        } while (choice != 0);
    }

    // Destructor - free linked list
    ~HostelManagement() {
        Student* cur = head;
        while (cur) {
            Student* temp = cur;
            cur = cur->next;
            delete temp;
        }
    }
};

// ─────────────────────────────────────────
//  ENTRY POINT
// ─────────────────────────────────────────
int main() {
    HostelManagement hms;
    hms.run();
    return 0;
}
