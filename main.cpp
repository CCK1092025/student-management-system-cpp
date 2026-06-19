/*#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

class Student {
public:
    string name;
    int id;
    double gpa;

    Student(string n, int i, double g) : name(n), id(i), gpa(g) {} // Use initialization list
};

vector<Student> students;

// Helper function to safely clear input stream on error
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// =============================
// 功能：新增学生
// =============================
void addStudent() {
    string name;
    int id;
    double gpa;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover newline
    cout << "Enter full name: ";
    getline(cin, name);

    cout << "Enter ID: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Enter an integer for ID: ";
        clearInputBuffer();
    }

    cout << "Enter GPA: ";
    while (!(cin >> gpa)) {
        cout << "Invalid input. Enter a number for GPA: ";
        clearInputBuffer();
    }

    students.push_back(Student(name, id, gpa));
    cout << "Student added ✅\n";
}

// =============================
// 功能：显示所有学生
// =============================
void displayStudents() {
    if (students.empty()) {
        cout << "No students found.\n";
        return;
    }

    for (const auto &s : students) { // Use const auto& to prevent modifications/copying
        cout << "Name: " << s.name 
             << " | ID: " << s.id 
             << " | GPA: " << s.gpa << endl;
    }
}

// =============================
// 功能：搜索学生
// =============================
void searchStudent() {
    int id;
    cout << "Enter ID to search: ";
    if (!(cin >> id)) {
        cout << "Invalid ID.\n";
        clearInputBuffer();
        return;
    }

    for (const auto &s : students) {
        if (s.id == id) {
            cout << "Found: " << s.name << " | GPA: " << s.gpa << endl;
            return;
        }
    }
    cout << "Student not found.\n";
}

// =============================
// 功能：更新学生
// =============================
void updateStudent() {
    int id;
    cout << "Enter ID to update: ";
    if (!(cin >> id)) {
        cout << "Invalid ID.\n";
        clearInputBuffer();
        return;
    }

    for (auto &s : students) {
        if (s.id == id) {
            cout << "Enter new GPA: ";
            while (!(cin >> s.gpa)) {
                cout << "Invalid GPA. Try again: ";
                clearInputBuffer();
            }
            cout << "Updated ✅\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

// =============================
// 功能：删除学生
// =============================
void deleteStudent() {
    int id;
    cout << "Enter ID to delete: ";
    if (!(cin >> id)) {
        cout << "Invalid ID.\n";
        clearInputBuffer();
        return;
    }

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            students.erase(it);
            cout << "Deleted ✅\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

// =============================
// 功能：排序 (Optimized reference passing)
// =============================
void sortByGPA() {
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        return a.gpa > b.gpa; 
    });
    cout << "Sorted by GPA ✅\n";
}

// =============================
// 功能：存文件 (CSV-style format using commas)
// =============================
void saveToFile() {
    ofstream file("students.txt");
    if (!file) {
        cout << "Error opening file for writing!\n";
        return;
    }

    for (const auto &s : students) {
        file << s.name << "," << s.id << "," << s.gpa << "\n";
    }

    file.close();
    cout << "Saved to file ✅\n";
}

// =============================
// 功能：读文件 (Robust comma-separated parsing)
// =============================
void loadFromFile() {
    ifstream file("students.txt");
    if (!file) {
        cout << "No existing save file found.\n";
        return;
    }

    students.clear();
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        size_t firstComma = line.find(',');
        size_t secondComma = line.find(',', firstComma + 1);

        if (firstComma == string::npos || secondComma == string::npos) continue;

        string name = line.substr(0, firstComma);
        int id = stoi(line.substr(firstComma + 1, secondComma - firstComma - 1));
        double gpa = stod(line.substr(secondComma + 1));

        students.push_back(Student(name, id, gpa));
    }

    file.close();
    cout << "Loaded from file ✅\n";
}

// =============================
// 主程序
// =============================
int main() {
    int choice;

    while (true) {
        cout << "\n==== Student System ====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort by GPA\n";
        cout << "7. Save to File\n";
        cout << "8. Load from File\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        
        if (!(cin >> choice)) {
            cout << "Please enter a valid number.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: sortByGPA(); break;
            case 7: saveToFile(); break;
            case 8: loadFromFile(); break;
            case 0: return 0;
            default: cout << "Invalid choice\n";
        }
    }
}