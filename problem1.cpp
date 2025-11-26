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
using namespace std;

struct Student {
    string name;
    int id;
    double gpa;
};

vector<Student> readStudentsFromFile(const string& filename) {
    vector<Student> students;

    std::ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return students;
    } //validation

    std::string line;
    getline(file,line); // skip first line (header)

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        Student s;

        std::getline(ss, s.name, ',');

        std::getline(ss, field, ',');
        s.id = stoi(field.c_str());

        std::getline(ss, field, ',');
        s.gpa = stof(field.c_str());

        students.push_back(s);
    }

    return students;
}

int main() {
    std::vector<Student> students = readStudentsFromFile("../data/students.csv"); //fixed filename to lead to right directory

    std::cout << "Loaded " << students.size() << " students:" << std::endl;
    for (int i = 0; i < students.size(); i++) {
        std::cout << students[i].name
                  << " (ID: " << students[i].id
                  << ", GPA: " << students[i].gpa << ")" << std::endl;
    }

    return 0;
}
