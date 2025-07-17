#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
    int roll;
    string name;
    float marks;
    char grade;

public:
    // Constructor
    Student(int r = 0, string n = "", float m = 0.0f) {
        roll = r;
        name = n;
        marks = m;
        calculateGrade();
    }

    // Take input
    void input() {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks (0–100): ";
        cin >> marks;
        calculateGrade();
    }

    // Calculate grade
    void calculateGrade() {
        if (marks >= 90)
            grade = 'A';
        else if (marks >= 75)
            grade = 'B';
        else if (marks >= 60)
            grade = 'C';
        else if (marks >= 40)
            grade = 'D';
        else
            grade = 'F';
    }

    // Display student
    void display() {
        cout << "Roll: " << roll << "\nName: " << name << "\nMarks: " << marks << "\nGrade: " << grade << "\n--------------------\n";
    }

    // Save to file
    void saveToFile() {
        ofstream fout("students.txt", ios::app);
        fout << roll << "|" << name << "|" << marks << "\n";
        fout.close();
    }

    // Get roll for search/delete
    int getRoll() {
        return roll;
    }

    // Static: Display all students
    static void displayAll() {
        ifstream fin("students.txt");
        string line;

        if (!fin) {
            cout << "No records found.\n";
            return;
        }

        cout << "\n--- Student Records ---\n";
        while (getline(fin, line)) {
            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);

            int r = stoi(line.substr(0, p1));
            string n = line.substr(p1 + 1, p2 - p1 - 1);
            float m = stof(line.substr(p2 + 1));

            Student s(r, n, m);
            s.display();
        }

        fin.close();
    }

    // Static: Search by roll number
    static void searchStudent(int rsearch) {
        ifstream fin("students.txt");
        string line;
        bool found = false;

        while (getline(fin, line)) {
            size_t p1 = line.find('|');
            int r = stoi(line.substr(0, p1));
            if (r == rsearch) {
                size_t p2 = line.find('|', p1 + 1);
                string n = line.substr(p1 + 1, p2 - p1 - 1);
                float m = stof(line.substr(p2 + 1));

                Student s(r, n, m);
                cout << "\nStudent Found:\n";
                s.display();
                found = true;
                break;
            }
        }

        if (!found)
            cout << "Student not found.\n";

        fin.close();
    }

    // Static: Delete by roll number
    static void deleteStudent(int rdelete) {
        ifstream fin("students.txt");
        ofstream temp("temp.txt");

        string line;
        bool found = false;

        while (getline(fin, line)) {
            size_t p1 = line.find('|');
            int r = stoi(line.substr(0, p1));
            if (r != rdelete) {
                temp << line << "\n";
            }
            else {
                found = true;
            }
        }

        fin.close();
        temp.close();
        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found)
            cout << "Student deleted.\n";
        else
            cout << "Student not found.\n";
    }
};

int main() {
    int choice;

    do {
        cout << "\n===== Student Report Card Menu =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search by Roll Number\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Student s;
            s.input();
            s.saveToFile();
            break;
        }
        case 2:
            Student::displayAll();
            break;
        case 3: {
            int roll;
            cout << "Enter Roll Number to Search: ";
            cin >> roll;
            Student::searchStudent(roll);
            break;
        }
        case 4: {
            int roll;
            cout << "Enter Roll Number to Delete: ";
            cin >> roll;
            Student::deleteStudent(roll);
            break;
        }
        case 5:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
