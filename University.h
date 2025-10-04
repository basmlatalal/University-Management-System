#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <string>
#include <map>
#include <memory>

#include "Student.h"
#include "Professor.h"
#include "Course.h"

class University {
public:
    University(const std::string& name);

    // containers
    std::map<int, std::shared_ptr<Student>> students;
    std::map<int, std::shared_ptr<Professor>> professors;
    std::map<std::string, std::shared_ptr<Course>> courses;

    // operations
    void addStudent(const std::shared_ptr<Student>& s);
    void addProfessor(const std::shared_ptr<Professor>& p);
    void addCourse(const std::shared_ptr<Course>& c);

    void enrollStudentInCourse(int studentId, const std::string& courseCode);
    void assignProfessorToCourse(int professorId, const std::string& courseCode);

    void displayStudents() const;
    void displayProfessors() const;
    void displayCourses() const;

    // CSV I/O (folder path)
    void loadDataFromCSV(const std::string& folder);
    void saveDataToCSV(const std::string& folder) const;

private:
    std::string name;
};

#endif // UNIVERSITY_H
