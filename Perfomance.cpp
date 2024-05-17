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
using std::pair;
using std::make_pair;
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

    virtual pair<int, vector<double>> solveTask(const Task& task) const {
        return make_pair(0, vector<double>());
    }
};

class Good : public Student {
public:
    Good(const string& _name, double _ability) : Student(_name, _ability) {}

    pair<int, vector<double>> solveTask(const Task& task) const override {
        double D = task.getB() * task.getB() - 4 * task.getA() * task.getC();
        vector<double> roots;
        if (D < 0) {
            return make_pair(0, roots);
        }
        else if (D == 0) {
            double root = -task.getB() / (2 * task.getA());
            roots.push_back(root);
            return make_pair(1, roots);
        }
        else {
            double root1 = (-task.getB() + sqrt(D)) / (2 * task.getA());
            double root2 = (-task.getB() - sqrt(D)) / (2 * task.getA());
            roots.push_back(root1);
            roots.push_back(root2);
            return make_pair(2, roots);
        }
    }
};

class Average : public Student {
public:
    Average(const string& _name, double _ability) : Student(_name, _ability) {}
    pair<int, vector<double>> solveTask(const Task& task) const override {
        double chance = static_cast<double>(rand()) / RAND_MAX;
        double ability = getAbility();
        if (chance <= ability) {
            Good solve(getName(), ability);
            return solve.solveTask(task);
        }
        else {
            return make_pair(0, vector<double>());
        }
    }
};

class Bad : public Student {
public:
    Bad(const string& _name, double _ability) : Student(_name, _ability) {}

    pair<int, vector<double>> solveTask(const Task& task) const override {
        return make_pair(1, vector<double>(1, 0.0));
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
                pair<int, vector<double>> solution = student->solveTask(task);
                cout << student->getName() << ", Roots: ";
                if (solution.first == 0) {
                    cout << "No roots" << endl;
                }
                else if (solution.first == 1) {
                    cout << solution.second[0] << endl;
                }
                else if (solution.first == 2) {
                    cout << solution.second[0] << ", " << solution.second[1] << endl;
                }
            }
        }
    }
    void printProgress() const {
        cout << "Progress:" << endl;
        for (const Student* student : students) {
            cout << student->getName();
            int solvedTasks = 0;
            for (const Task& task : tasks) {
                pair<int, vector<double>> solution = student->solveTask(task);
                Good* solver = new Good("", 1);
                pair<int, vector<double>> accurate = solver->solveTask(task);
                if (solution == accurate) {
                    solvedTasks++;
                }
                delete solver;
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
