#include "Student.h"
#include "Course.h"
#include <iostream>

Student::Student(int id, const std::string& name, Year year, const Address& addr)
    : id(id), name(name), year(year), address(addr) {}

int Student::getId() const { return id; }
std::string Student::getName() const { return name; }
Student::Year Student::getYear() const { return year; }
Student::Address Student::getAddress() const { return address; }
void Student::setName(const std::string& n) { name = n; }
void Student::setYear(Year y) { year = y; }
void Student::setAddress(const Address& a) { address = a; }

void Student::addCourse(const std::shared_ptr<Course>& course) {
    // avoid duplicates
    for (auto& c : enrolledCourses) if (c->getCode() == course->getCode()) return;
    enrolledCourses.push_back(course);
}

const std::vector<std::shared_ptr<Course>>& Student::getCourses() const {
    return enrolledCourses;
}

void Student::displayInfo() const {
    std::cout << "ID: " << id << "\nName: " << name
              << "\nYear: " << yearToString(year)
              << "\nAddress: " << address.city << ", " << address.street << "\nCourses: ";
    if (enrolledCourses.empty()) std::cout << "None";
    else {
        for (auto& c : enrolledCourses) std::cout << c->getCode() << "(" << c->getTitle() << ") ";
    }
    std::cout << "\n\n";
}

std::string Student::yearToString(Year y) {
    switch (y) {
        case Year::Freshman: return "Freshman";
        case Year::Sophomore: return "Sophomore";
        case Year::Junior: return "Junior";
        case Year::Senior: return "Senior";
    }
    return "Unknown";
}

Student::Year Student::stringToYear(const std::string& s) {
    if (s == "Freshman") return Year::Freshman;
    if (s == "Sophomore") return Year::Sophomore;
    if (s == "Junior") return Year::Junior;
    if (s == "Senior") return Year::Senior;
    return Year::Freshman;
}
