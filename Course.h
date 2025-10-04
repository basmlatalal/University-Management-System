#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <memory>

class Student;
class Professor;

class Course {
private:
    std::string code;
    std::string title;
    int credits;

    // use weak_ptr inside Course to avoid circular shared_ptr cycles
    std::vector<std::weak_ptr<Student>> enrolledStudents;
    std::weak_ptr<Professor> professor; // assigned professor (weak)

public:
    Course(const std::string& code, const std::string& title, int credits);

    std::string getCode() const;
    std::string getTitle() const;
    int getCredits() const;

    void addStudent(const std::shared_ptr<Student>& student); // stores weak_ptr
    void setProfessor(const std::shared_ptr<Professor>& prof); // stores weak_ptr
    std::shared_ptr<Professor> getProfessor() const;

    std::vector<std::shared_ptr<Student>> getEnrolledStudents() const; // return shared_ptr list

    void displayInfo() const;
};

#endif // COURSE_H
