#include "Professor.h"
#include "Course.h"
#include <iostream>

Professor::Professor(int id, const std::string& name, const std::string& department, const Address& addr)
    : id(id), name(name), department(department), address(addr) {}

int Professor::getId() const { return id; }
std::string Professor::getName() const { return name; }
std::string Professor::getDepartment() const { return department; }
Professor::Address Professor::getAddress() const { return address; }

void Professor::setName(const std::string& n) { name = n; }
void Professor::setDepartment(const std::string& d) { department = d; }
void Professor::setAddress(const Address& a) { address = a; }

void Professor::addCourse(const std::shared_ptr<Course>& course) {
    for (auto& c : assignedCourses) if (c->getCode() == course->getCode()) return;
    assignedCourses.push_back(course);
}

const std::vector<std::shared_ptr<Course>>& Professor::getCourses() const { return assignedCourses; }

void Professor::displayInfo() const {
    std::cout << "ID: " << id << "\nName: " << name << "\nDepartment: " << department
              << "\nAddress: " << address.city << ", " << address.street << "\nCourses: ";
    if (assignedCourses.empty()) std::cout << "None";
    else for (auto& c : assignedCourses) std::cout << c->getCode() << "(" << c->getTitle() << ") ";
    std::cout << "\n\n";
}
