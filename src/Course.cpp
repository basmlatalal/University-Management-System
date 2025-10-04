#include "Course.h"
#include "Student.h"
#include "Professor.h"
#include <iostream>

Course::Course(const std::string& code, const std::string& title, int credits)
    : code(code), title(title), credits(credits) {}

std::string Course::getCode() const { return code; }
std::string Course::getTitle() const { return title; }
int Course::getCredits() const { return credits; }

void Course::addStudent(const std::shared_ptr<Student>& student) {
    // avoid duplicates
    for (auto& w : enrolledStudents) {
        if (auto s = w.lock()) if (s->getId() == student->getId()) return;
    }
    enrolledStudents.push_back(student);
}

void Course::setProfessor(const std::shared_ptr<Professor>& prof) {
    professor = prof;
}

std::shared_ptr<Professor> Course::getProfessor() const {
    return professor.lock();
}

std::vector<std::shared_ptr<Student>> Course::getEnrolledStudents() const {
    std::vector<std::shared_ptr<Student>> out;
    for (auto& w : enrolledStudents) if (auto s = w.lock()) out.push_back(s);
    return out;
}

void Course::displayInfo() const {
    std::cout << "Code: " << code << "\nTitle: " << title << "\nCredits: " << credits << "\nProfessor: ";
    if (auto p = professor.lock()) std::cout << p->getName();
    else std::cout << "None";
    std::cout << "\nStudents: ";
    bool any = false;
    for (auto& w : enrolledStudents) {
        if (auto s = w.lock()) { std::cout << s->getName() << " "; any = true; }
    }
    if (!any) std::cout << "None";
    std::cout << "\n\n";
}
