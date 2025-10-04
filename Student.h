#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <memory>

class Course;

class Student {
public:
    enum class Year { Freshman, Sophomore, Junior, Senior };

    struct Address {
        std::string city;
        std::string street;
    };

    Student(int id, const std::string& name, Year year, const Address& addr);

    // getters / setters
    int getId() const;
    std::string getName() const;
    Year getYear() const;
    Address getAddress() const;
    void setName(const std::string& n);
    void setYear(Year y);
    void setAddress(const Address& a);

    // courses (student "owns" shared_ptrs to Course entries)
    void addCourse(const std::shared_ptr<Course>& course);
    const std::vector<std::shared_ptr<Course>>& getCourses() const;

    // display
    void displayInfo() const;

    // helpers
    static std::string yearToString(Year y);
    static Year stringToYear(const std::string& s);

private:
    int id;
    std::string name;
    Year year;
    Address address;
    std::vector<std::shared_ptr<Course>> enrolledCourses;
};

#endif // STUDENT_H
