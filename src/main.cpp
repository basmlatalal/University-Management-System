#include <iostream>
#include <memory>
#include <string>
#include <limits>
#include "University.h"

static void pause() { std::cout << "Press Enter to continue..."; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }

int main() {
    University uni("Cairo University");
    const std::string dataFolder = "./data";

    // attempt to load existing data (graceful)
    uni.loadDataFromCSV(dataFolder);

    while (true) {
        std::cout << "\n--- University Management Menu ---\n"
                  << "1) Add Student\n"
                  << "2) Add Professor\n"
                  << "3) Add Course\n"
                  << "4) Enroll Student in Course\n"
                  << "5) Assign Professor to Course\n"
                  << "6) List Students\n"
                  << "7) List Professors\n"
                  << "8) List Courses\n"
                  << "9) Load CSV from disk\n"
                  << "10) Save CSV to disk\n"
                  << "0) Exit\n"
                  << "Choose option: ";

        int choice;
        if (!(std::cin >> choice)) { std::cin.clear(); std::cin.ignore(10000, '\n'); continue; }
        std::cin.ignore(10000, '\n');

        if (choice == 0) {
            std::cout << "Save before exit? (y/n): ";
            char c; std::cin >> c; std::cin.ignore(10000, '\n');
            if (c == 'y' || c == 'Y') uni.saveDataToCSV(dataFolder);
            break;
        }
        if (choice == 1) {
            int id; std::string name; std::string yearS; Student::Address addr;
            std::cout << "Student ID: "; std::cin >> id; std::cin.ignore();
            std::cout << "Name: "; std::getline(std::cin, name);
            std::cout << "Year (Freshman/Sophomore/Junior/Senior) *case sensitive*: "; std::getline(std::cin, yearS);
            std::cout << "City: "; std::getline(std::cin, addr.city);
            std::cout << "Street: "; std::getline(std::cin, addr.street);
            Student::Year y = Student::stringToYear(yearS);
            uni.addStudent(std::make_shared<Student>(id, name, y, addr));
            std::cout << "Student added.\n";
            pause();
            continue;
        }
        if (choice == 2) {
            int id; std::string name, dept; Professor::Address addr;
            std::cout << "Professor ID: "; std::cin >> id; std::cin.ignore();
            std::cout << "Name: "; std::getline(std::cin, name);
            std::cout << "Department: "; std::getline(std::cin, dept);
            std::cout << "City: "; std::getline(std::cin, addr.city);
            std::cout << "Street: "; std::getline(std::cin, addr.street);
            uni.addProfessor(std::make_shared<Professor>(id, name, dept, addr));
            std::cout << "Professor added.\n";
            pause();
            continue;
        }
        if (choice == 3) {
            std::string code, title; int credits;
            std::cout << "Course code: "; std::getline(std::cin, code);
            if (code.empty()) { std::getline(std::cin, code); } // fallback
            std::cout << "Title: "; std::getline(std::cin, title);
            std::cout << "Credits: "; std::cin >> credits; std::cin.ignore();
            uni.addCourse(std::make_shared<Course>(code, title, credits));
            std::cout << "Course added.\n";
            pause();
            continue;
        }
        if (choice == 4) {
            int sid; std::string code;
            std::cout << "Student ID: "; std::cin >> sid; std::cin.ignore();
            std::cout << "Course code: "; std::getline(std::cin, code);
            uni.enrollStudentInCourse(sid, code);
            pause();
            continue;
        }
        if (choice == 5) {
            int pid; std::string code;
            std::cout << "Professor ID: "; std::cin >> pid; std::cin.ignore();
            std::cout << "Course code: "; std::getline(std::cin, code);
            uni.assignProfessorToCourse(pid, code);
            pause();
            continue;
        }
        if (choice == 6) { uni.displayStudents(); pause(); continue; }
        if (choice == 7) { uni.displayProfessors(); pause(); continue; }
        if (choice == 8) { uni.displayCourses(); pause(); continue; }
        if (choice == 9) { uni.loadDataFromCSV(dataFolder); pause(); continue; }
        if (choice == 10) { uni.saveDataToCSV(dataFolder); pause(); continue; }

        std::cout << "Invalid option\n";
    }

    std::cout << "Goodbye!\n";
    return 0;
}
