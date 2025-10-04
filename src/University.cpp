#include "University.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

University::University(const std::string& name) : name(name) {}

void University::addStudent(const std::shared_ptr<Student>& s) {
    if (students.count(s->getId())) {
        std::cout << "Warning: duplicate student id " << s->getId() << " skip.\n";
        return;
    }
    students[s->getId()] = s;
}
void University::addProfessor(const std::shared_ptr<Professor>& p) {
    if (professors.count(p->getId())) {
        std::cout << "Warning: duplicate professor id " << p->getId() << " skip.\n";
        return;
    }
    professors[p->getId()] = p;
}
void University::addCourse(const std::shared_ptr<Course>& c) {
    if (courses.count(c->getCode())) {
        std::cout << "Warning: duplicate course code " << c->getCode() << " skip.\n";
        return;
    }
    courses[c->getCode()] = c;
}

void University::enrollStudentInCourse(int studentId, const std::string& courseCode) {
    auto sIt = students.find(studentId);
    auto cIt = courses.find(courseCode);
    if (sIt == students.end()) { std::cout << "Student " << studentId << " not found.\n"; return; }
    if (cIt == courses.end()) { std::cout << "Course " << courseCode << " not found.\n"; return; }
    sIt->second->addCourse(cIt->second);
    cIt->second->addStudent(sIt->second);
}

void University::assignProfessorToCourse(int professorId, const std::string& courseCode) {
    auto pIt = professors.find(professorId);
    auto cIt = courses.find(courseCode);
    if (pIt == professors.end()) { std::cout << "Professor " << professorId << " not found.\n"; return; }
    if (cIt == courses.end()) { std::cout << "Course " << courseCode << " not found.\n"; return; }
    pIt->second->addCourse(cIt->second);
    cIt->second->setProfessor(pIt->second);
}

void University::displayStudents() const {
    std::cout << "---- Students ----\n";
    for (auto& [id, s] : students) s->displayInfo();
}
void University::displayProfessors() const {
    std::cout << "---- Professors ----\n";
    for (auto& [id, p] : professors) p->displayInfo();
}
void University::displayCourses() const {
    std::cout << "---- Courses ----\n";
    for (auto& [code, c] : courses) c->displayInfo();
}

// ---------------- CSV I/O ----------------
static std::vector<std::string> splitCSVLine(const std::string& line) {
    std::vector<std::string> out;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, ',')) out.push_back(item);
    return out;
}

void University::loadDataFromCSV(const std::string& folder) {
    // create folder if not exists? no, just try to open files; errors reported gracefully
    std::ifstream f;
    std::string path;

    // Students
    path = folder + "/students.csv";
    f.open(path);
    if (f.is_open()) {
        std::string line;
        // optional header detection: if first line contains non-numeric id skip header
        while (std::getline(f, line)) {
            if (line.empty()) continue;
            auto parts = splitCSVLine(line);
            if (parts.size() < 5) continue;
            // handle header detection: if first token is "id" skip
            if (parts[0] == "id" || parts[0] == "name") continue;
            int id = std::stoi(parts[0]);
            std::string name = parts[1];
            Student::Year y = Student::stringToYear(parts[2]);
            Student::Address addr{parts[3], parts[4]};
            if (!students.count(id)) addStudent(std::make_shared<Student>(id, name, y, addr));
        }
        f.close();
    } else {
        std::cout << "students.csv not found at " << path << " (will create on save)\n";
    }

    // Professors
    path = folder + "/professors.csv";
    f.open(path);
    if (f.is_open()) {
        std::string line;
        while (std::getline(f, line)) {
            if (line.empty()) continue;
            auto parts = splitCSVLine(line);
            if (parts.size() < 5) continue;
            if (parts[0] == "id" || parts[0] == "name") continue;
            int id = std::stoi(parts[0]);
            std::string name = parts[1];
            std::string dept = parts[2];
            Professor::Address addr{parts[3], parts[4]};
            if (!professors.count(id)) addProfessor(std::make_shared<Professor>(id, name, dept, addr));
        }
        f.close();
    } else {
        std::cout << "professors.csv not found at " << path << "\n";
    }

    // Courses
    path = folder + "/courses.csv";
    f.open(path);
    if (f.is_open()) {
        std::string line;
        while (std::getline(f, line)) {
            if (line.empty()) continue;
            auto parts = splitCSVLine(line);
            if (parts.size() < 3) continue;
            if (parts[0] == "code" || parts[0] == "title") continue;
            std::string code = parts[0];
            std::string title = parts[1];
            int credits = std::stoi(parts[2]);
            if (!courses.count(code)) addCourse(std::make_shared<Course>(code, title, credits));
        }
        f.close();
    } else {
        std::cout << "courses.csv not found at " << path << "\n";
    }

    // Enrollments
    path = folder + "/enrollments.csv";
    f.open(path);
    if (f.is_open()) {
        std::string line;
        while (std::getline(f, line)) {
            if (line.empty()) continue;
            auto parts = splitCSVLine(line);
            if (parts.size() < 2) continue;
            if (parts[0] == "studentId") continue;
            int sid = std::stoi(parts[0]);
            std::string code = parts[1];
            if (students.count(sid) && courses.count(code)) {
                // enroll bi-directionally
                students[sid]->addCourse(courses[code]);
                courses[code]->addStudent(students[sid]);
            }
        }
        f.close();
    } else {
        std::cout << "enrollments.csv not found at " << path << "\n";
    }

    // Assignments
    path = folder + "/assignments.csv";
    f.open(path);
    if (f.is_open()) {
        std::string line;
        while (std::getline(f, line)) {
            if (line.empty()) continue;
            auto parts = splitCSVLine(line);
            if (parts.size() < 2) continue;
            if (parts[0] == "professorId") continue;
            int pid = std::stoi(parts[0]);
            std::string code = parts[1];
            if (professors.count(pid) && courses.count(code)) {
                professors[pid]->addCourse(courses[code]);
                courses[code]->setProfessor(professors[pid]);
            }
        }
        f.close();
    } else {
        std::cout << "assignments.csv not found at " << path << "\n";
    }

    std::cout << "CSV load complete (folder: " << folder << ")\n";
}

void University::saveDataToCSV(const std::string& folder) const {
    // ensure directory exists
    std::filesystem::create_directories(folder);

    // Students
    {
        std::ofstream s(folder + "/students.csv");
        s << "id,name,year,city,street\n";
        for (auto& [id, st] : students) {
            auto addr = st->getAddress();
            s << st->getId() << "," << st->getName() << "," << Student::yearToString(st->getYear())
              << "," << addr.city << "," << addr.street << "\n";
        }
    }

    // Professors
    {
        std::ofstream p(folder + "/professors.csv");
        p << "id,name,department,city,street\n";
        for (auto& [id, pr] : professors) {
            auto addr = pr->getAddress();
            p << pr->getId() << "," << pr->getName() << "," << pr->getDepartment()
              << "," << addr.city << "," << addr.street << "\n";
        }
    }

    // Courses
    {
        std::ofstream c(folder + "/courses.csv");
        c << "code,title,credits\n";
        for (auto& [code, co] : courses) {
            c << co->getCode() << "," << co->getTitle() << "," << co->getCredits() << "\n";
        }
    }

    // Enrollments
    {
        std::ofstream e(folder + "/enrollments.csv");
        e << "studentId,courseCode\n";
        for (auto& [sid, st] : students) {
            for (auto& co : st->getCourses()) e << sid << "," << co->getCode() << "\n";
        }
    }

    // Assignments
    {
        std::ofstream a(folder + "/assignments.csv");
        a << "professorId,courseCode\n";
        for (auto& [pid, pr] : professors) {
            for (auto& co : pr->getCourses()) a << pid << "," << co->getCode() << "\n";
        }
    }

    std::cout << "CSV save complete (folder: " << folder << ")\n";
}
