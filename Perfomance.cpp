#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

class Student {
private:
    string name;
    double ability; // Probability of solving equation correctly

public:
    Student(const string& _name, double _ability) : name(_name), ability(_ability) {}

    double getAbility() const {
        return ability;
    }

    const string& getName() const {
        return name;
    }
};

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

class Teacher {
private:
    vector<Student> students;
    vector<Task> tasks;

public:

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    int solveTask(const Task& task, const Student& student) const {
        double ability = student.getAbility();
        if (ability == 0) {
            // Bad student
            return 0;
        }
        else if (ability == 0.55) {
            // Average student
            double chance = static_cast<double>(rand()) / RAND_MAX;
            if (chance <= ability) {
                return 1;
            }
        }
        else {
            // Good student;
            return 1; 
        }
        return 0;
    }

   void checkTasks() {

    for (const Task& task : tasks) {
        cout << "Checking task with coefficients: " << task.getA() << " " << task.getB() << " " << task.getC() << endl;

        for (const Student& student : students) {
            int solvedTasks = solveTask(task, student);
            cout << "Student: " << student.getName();
            if (solvedTasks > 0) {
                // Output roots
                double D = task.getB() * task.getB() - 4 * task.getA() * task.getC();
                if (D < 0) {
                    cout << ", No  roots" << endl;
                } else if (D == 0) {
                    double root = -task.getB() / (2 * task.getA());
                    cout << ", Root: " << root << endl;
                } else {
                    double root1 = (-task.getB() + sqrt(D)) / (2 * task.getA());
                    double root2 = (-task.getB() - sqrt(D)) / (2 * task.getA());
                    cout << ", Roots: " << root1 << ", " << root2 << endl;
                }

            } else {
                cout << ", Root: 0" << endl;
            }
        }
    }
}


    void printPerformance() const {
        // Output performance table
        cout << "Performance Table:" << endl;

        for (const Student& student : students) {
            cout << "Student: " << student.getName();
            int solvedTasks = 0;
            for (const Task& task : tasks) {
                solvedTasks += solveTask(task, student);
            }
            cout << ", Number of solved tasks: " << static_cast<int>(solvedTasks) << endl;
        }
    }
};

int main() {
    srand(time(0));

    Teacher teacher;

    // Load students from students.txt
    ifstream studentFile("students.txt");

    string studentName;
    double ability;
    while (studentFile >> studentName >> ability) {
        teacher.addStudent(Student(studentName, ability));
    }
    studentFile.close();

    // Load tasks from equations.txt
    ifstream taskFile("equations.txt");

    double a, b, c;
    while (taskFile >> a >> b >> c) {
        teacher.addTask(Task(a, b, c));
    }
    taskFile.close();

    teacher.checkTasks();
    teacher.printPerformance();

    return 0;
}
