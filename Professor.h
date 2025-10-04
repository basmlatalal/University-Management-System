#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <vector>
#include <memory>

class Course;

class Professor {
public:
    struct Address {
        std::string city;
        std::string street;
    };

    Professor(int id, const std::string& name, const std::string& department, const Address& addr);

    int getId() const;
    std::string getName() const;
    std::string getDepartment() const;
    Address getAddress() const;

    void setName(const std::string& n);
    void setDepartment(const std::string& d);
    void setAddress(const Address& a);

    void addCourse(const std::shared_ptr<Course>& course);
    const std::vector<std::shared_ptr<Course>>& getCourses() const;

    void displayInfo() const;

private:
    int id;
    std::string name;
    std::string department;
    Address address;
    std::vector<std::shared_ptr<Course>> assignedCourses;
};

#endif // PROFESSOR_H
