#include <iostream>
#include <string>

using namespace std;


struct Student {
    string surname;
    string group;
    int grades[5];
};


void inputStudentInfo(Student& student) {
    cout << "Enter surname: ";
    getline(cin, student.surname);
    
    cout << "Enter group: ";
    getline(cin, student.group);
    
    cout << "Enter 5 grades (0-100): ";
    for (int& grade : student.grades) {
        cin >> grade;
    }
    cin.ignore();
}


void printStudents(const Student* students, int size) {
    cout << "\nHonor students:\n";
    for (int i = 0; i < size; ++i) {
        int excellentCount = 0, failingCount = 0;
        for (int grade : students[i].grades) {
            if (grade >= 90) excellentCount++;
            if (grade <= 3) failingCount++;
        }
        if (excellentCount > 3) {
            cout << students[i].surname << " (Group: " << students[i].group << ")\n";
        }
        if (failingCount > 2) {
            cout << "Failing: " << students[i].surname << " (Group: " << students[i].group << ")\n";
        }
    }
}

int main() {
    int studentCount = 0;
    int maxStudents = 2; 
    Student* students = new Student[maxStudents];

    while (true) {
        if (studentCount == maxStudents) {
            maxStudents *= 2;
            Student* temp = new Student[maxStudents];
            for (int i = 0; i < studentCount; ++i) {
                temp[i] = students[i];
            }
            delete[] students;
            students = temp;
        }

        inputStudentInfo(students[studentCount]);
        studentCount++;

        char addMore;
        cout << "Do you want to add another student? (y/n): ";
        cin >> addMore;
        cin.ignore(); 
        if (addMore != 'y' && addMore != 'Y') break; 
    }

    printStudents(students, studentCount);

    delete[] students; 
    return 0;
}
