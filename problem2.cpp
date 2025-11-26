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
#include <memory>


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
   //converted to smart ptrs
    std::unique_ptr<Student> alice(new Student("Alice", 1001));
    std::unique_ptr<Student> bob(new Student("Bob", 1002));

    std::cout << "\nProcessing students..." << std::endl;
    alice->print();
    bob->print();

    if (simulateError) {
        std::cout << "Error occurred! Returning early..." << std::endl;
        //smart ptrs automatically delete
        return;
    }

    std::cout << "Processing complete." << std::endl;
}

// BUG 2: This function has a double-delete bug
void demonstrateDoubleFree() {
    // converted to smart pointer to prevent double-delete
    std::shared_ptr<Student> student(new Student("Charlie", 1003));

    // Simulated passing pointer to two different "owners"
    std::shared_ptr<Student> owner1 = student;
    std::shared_ptr<Student> owner2 = owner1 = student;
    // Student* owner1 = student;
    // Student* owner2 = student;
    student->print();
    owner1->print();
    owner2->print();
    // With shared_ptr, multiple owners would work correctly
}

// BUG 3: This function uses a pointer after it's deleted
void demonstrateUseAfterFree() {
    //convert to smart ptr
    std::unique_ptr<Student> student(new Student("Diana", 1004));

    student->print();
    std::cout << "Name was: " << student->getName() << std::endl;
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
