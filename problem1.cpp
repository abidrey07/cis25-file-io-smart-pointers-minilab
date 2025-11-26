// Problem 1: Broken File Reading
// This code attempts to read student records from a CSV file, but has several bugs.
// Fix all the issues so the program correctly reads and displays the data.
//
// Expected output when fixed (using data/students.csv):
//   Loaded 3 students:
//   Alice Johnson (ID: 1001, GPA: 3.8)
//   Bob Smith (ID: 1002, GPA: 3.5)
//   Carol White (ID: 1003, GPA: 3.9)

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdexcept>

struct Student {
    std::string name;
    int id;
    double gpa;
};

std::vector<Student> readStudentsFromFile(std::string filename) {
    std::vector<Student> students;

    std::ifstream file(filename);

    // BUG 1: No error handling for file open failure
    // Should check if file opened and throw an exception if not
    // The caller should use try/catch to handle gracefully

    std::string line;

    // BUG 2: Should skip the header row, but doesn't

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        Student s;

        // BUG 3: Using wrong delimiter (space instead of comma)
        // This causes names to be truncated at the first space
        std::getline(ss, s.name, ' ');

        std::getline(ss, field, ',');
        s.id = atoi(field.c_str());

        std::getline(ss, field, ',');
        s.gpa = atof(field.c_str());

        students.push_back(s);
    }

    return students;
}

int main() {
    // BUG 1 (continued): No try/catch block to handle file errors gracefully
    // Should wrap in try/catch and exit with error message if exception thrown

    std::vector<Student> students = readStudentsFromFile("data/students.csv");

    std::cout << "Loaded " << students.size() << " students:" << std::endl;
    for (int i = 0; i < students.size(); i++) {
        std::cout << students[i].name
                  << " (ID: " << students[i].id
                  << ", GPA: " << students[i].gpa << ")" << std::endl;
    }

    return 0;
}
