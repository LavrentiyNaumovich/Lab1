#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>

using std::vector;
using std::cout;
using std::string;
using std::ifstream;
using std::endl;

class Task {
private:
    double a, b, c;

public:
    Task(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

    double getA() const {
        return a;
    }

    double getB() const {
        return b;
    }

    double getC() const {
        return c;
    }
};

class Student {
private:
    string name;
    double ability;

public:
    Student(const string& _name, double _ability) : name(_name), ability(_ability) {}

    double getAbility() const {
        return ability;
    }

    const string& getName() const {
        return name;
    }

    virtual int solveTask(const Task& task) const {
        return 0; 
    }
};

class Good : public Student {
public:
    Good(const string& _name, double _ability) : Student(_name, _ability) {}

    int solveTask(const Task& task) const override {
        return 1; 
    }
};

class Average : public Student {
public:
    Average(const string& _name, double _ability) : Student(_name, _ability) {}

   
    int solveTask(const Task& task) const override {
        double chance = static_cast<double>(rand()) / RAND_MAX;
        double ability = getAbility();
        if (chance <= ability) {
            return 1; 
        }
        return 0; 
    }
};

class Bad : public Student {
public:
    Bad(const string& _name, double _ability) : Student(_name, _ability) {}

    
    int solveTask(const Task& task) const override {
        return 0; 
    }
};

class Teacher {
private:
    vector<Student*> students; 
    vector<Task> tasks;

public:
    void addStudent(Student* student) {
        students.push_back(student);
    }

    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void checkTasks() {
        for (const Task& task : tasks) {
            cout << "Checking task with coefficients: " << task.getA() << " " << task.getB() << " " << task.getC() << endl;
            for (const Student* student : students) { 
                int solvedTasks = student->solveTask(task);
                cout << "Student: " << student->getName();
                if (solvedTasks > 0) {
                    double D = task.getB() * task.getB() - 4 * task.getA() * task.getC();
                    if (D < 0) {
                        cout << ", No  roots" << endl;
                    }
                    else if (D == 0) {
                        double root = -task.getB() / (2 * task.getA());
                        cout << ", Root: " << root << endl;
                    }
                    else {
                        double root1 = (-task.getB() + sqrt(D)) / (2 * task.getA());
                        double root2 = (-task.getB() - sqrt(D)) / (2 * task.getA());
                        cout << ", Roots: " << root1 << ", " << root2 << endl;
                    }
                }
                else {
                    cout << ", Root: 0" << endl;
                }
            }
        }
    }

    void printProgress() const {
        cout << "Progress:" << endl;
        for (const Student* student : students) { 
            cout << "Student: " << student->getName();
            int solvedTasks = 0;
            for (const Task& task : tasks) {
                solvedTasks += student->solveTask(task); 
            }
            cout << ", Number of solved tasks: " << solvedTasks << endl;
        }
    }

   
    ~Teacher() {
        for (Student* student : students) {
            delete student; 
        }
    }
};

void loadStudents(const string& filename, Teacher& teacher) {
    ifstream studentFile(filename);
    string studentName;
    double ability;
    while (studentFile >> studentName >> ability) {
        if (ability == 0)
            teacher.addStudent(new Bad(studentName, ability));
        else if (ability == 0.55)
            teacher.addStudent(new Average(studentName, ability));
        else
            teacher.addStudent(new Good(studentName, ability));
    }
    studentFile.close();
}

void loadTasks(const string& filename, Teacher& teacher) {
    ifstream taskFile(filename);
    double a, b, c;
    while (taskFile >> a >> b >> c) {
        teacher.addTask(Task(a, b, c));
    }
    taskFile.close();
}

int main() {
    srand(time(0));

    Teacher teacher;


    loadStudents("students.txt", teacher);
    loadTasks("equations.txt", teacher);

    teacher.checkTasks();
    teacher.printProgress();

    return 0;
}
