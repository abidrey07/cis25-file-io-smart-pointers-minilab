// Problem 3: Broken Smart Pointer Code
// This code has memory management bugs. Fix them using smart pointers.
//
// Instructions:
//   1. Replace raw pointers with appropriate smart pointers (unique_ptr or shared_ptr)
//   2. Remove manual delete calls (smart pointers handle cleanup)
//   3. Ensure no memory leaks occur, even with early returns
//
// When fixed, the program should:
//   - Create and use Student objects without memory leaks
//   - Handle the early return case without leaking memory
//   - Print destruction messages showing proper cleanup

#include <iostream>
#include <string>
#include <vector>
// TODO: Add #include <memory> for smart pointers

class Student {
private:
    std::string name;
    int id;
public:
    Student(const std::string& n, int i) : name(n), id(i) {
        std::cout << "Student created: " << name << std::endl;
    }

    ~Student() {
        std::cout << "Student destroyed: " << name << std::endl;
    }

    std::string getName() const { return name; }
    int getId() const { return id; }

    void print() const {
        std::cout << "  " << name << " (ID: " << id << ")" << std::endl;
    }
};

// BUG 1: This function leaks memory when returning early
void processStudents(bool simulateError) {
    // TODO: Convert these to smart pointers
    Student* alice = new Student("Alice", 1001);
    Student* bob = new Student("Bob", 1002);

    std::cout << "\nProcessing students..." << std::endl;
    alice->print();
    bob->print();

    if (simulateError) {
        std::cout << "Error occurred! Returning early..." << std::endl;
        // BUG: Memory leak! alice and bob are never deleted
        return;
    }

    std::cout << "Processing complete." << std::endl;

    // These only run if we don't return early
    delete alice;
    delete bob;
}

// BUG 2: This function has a double-delete bug
void demonstrateDoubleFree() {
    // TODO: Convert to smart pointer to prevent double-delete
    Student* student = new Student("Charlie", 1003);

    student->print();

    // Simulate passing pointer to two different "owners"
    Student* owner1 = student;
    Student* owner2 = student;

    // BUG: Both owners try to delete - double free!
    delete owner1;
    // delete owner2;  // This would crash! Commented out to prevent crash.

    // With shared_ptr, multiple owners would work correctly
}

// BUG 3: This function uses a pointer after it's deleted
void demonstrateUseAfterFree() {
    // TODO: Convert to smart pointer
    Student* student = new Student("Diana", 1004);

    student->print();

    delete student;

    // BUG: Using pointer after delete - undefined behavior!
    // std::cout << "Name was: " << student->getName() << std::endl;
    // Commented out to prevent crash, but this is the bug to fix
}

int main() {
    std::cout << "=== Test 1: Early return (should leak without fix) ===" << std::endl;
    processStudents(true);

    std::cout << "\n=== Test 2: Normal completion ===" << std::endl;
    processStudents(false);

    std::cout << "\n=== Test 3: Double-free scenario ===" << std::endl;
    demonstrateDoubleFree();

    std::cout << "\n=== Test 4: Use-after-free scenario ===" << std::endl;
    demonstrateUseAfterFree();

    std::cout << "\n=== Program ending ===" << std::endl;
    return 0;
}
