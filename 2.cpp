#include <iostream>
#include <string>

using namespace std;


struct Man {
    string surname;
    string name;
    int age;
    string birthDate; // Формат: DD.MM.YYYY
};

const int MAX_MEN = 100; 

// Прототипи функцій
void inputManInfo(Man& man);
void printMen(const Man men[], int count);
void sortMen(Man men[], int count, bool sortBySurname);
void printBirthdayPeople(const Man men[], int count, int month);
void addMan(Man men[], int& count);
void removeMan(Man men[], int& count);
int searchMan(const Man men[], int count, const string& surname, const string& name);
void editMan(Man men[], int count, int index);

int main() {
    Man men[MAX_MEN];
    int count = 0;    
    char option;

    while (true) {
        cout << "\nOptions:\n"
             << "1. Add person\n"
             << "2. Remove person\n"
             << "3. Print all people (sorted)\n"
             << "4. Print birthday people\n"
             << "5. Search for a person\n"
             << "6. Edit person\n"
             << "7. Exit\n"
             << "Choose an option: ";
        cin >> option;
        cin.ignore();

        switch (option) {
            case '1':
                addMan(men, count);
                break;
            case '2':
                removeMan(men, count);
                break;
            case '3': {
                char sortOption;
                cout << "Sort by surname (s) or name (n)? ";
                cin >> sortOption;
                sortMen(men, count, sortOption == 's');
                printMen(men, count);
                break;
            }
            case '4': {
                int month;
                cout << "Enter month (1-12): ";
                cin >> month;
                printBirthdayPeople(men, count, month);
                break;
            }
            case '5': {
                string surname, name;
                cout << "Enter surname: ";
                getline(cin, surname);
                cout << "Enter name: ";
                getline(cin, name);
                int index = searchMan(men, count, surname, name);
                if (index != -1) {
                    cout << "Found: " << men[index].surname << " " << men[index].name 
                         << ", Age: " << men[index].age << ", Birth Date: " << men[index].birthDate << endl;
                } else {
                    cout << "Person not found.\n";
                }
                break;
            }
            case '6': {
                string surname, name;
                cout << "Enter surname: ";
                getline(cin, surname);
                cout << "Enter name: ";
                getline(cin, name);
                int index = searchMan(men, count, surname, name);
                if (index != -1) {
                    editMan(men, count, index);
                } else {
                    cout << "Person not found.\n";
                }
                break;
            }
            case '7':
                return 0;
            default:
                cout << "Invalid option.\n";
        }
    }
}


void inputManInfo(Man& man) {
    cout << "Enter surname: ";
    getline(cin, man.surname);
    
    cout << "Enter name: ";
    getline(cin, man.name);
    
    cout << "Enter age: ";
    cin >> man.age;
    cin.ignore();
    
    cout << "Enter birth date (DD.MM.YYYY): ";
    getline(cin, man.birthDate);
}


void printMen(const Man men[], int count) {
    cout << "\nList of people:\n";
    for (int i = 0; i < count; ++i) {
        cout << men[i].surname << " " << men[i].name << ", Age: " << men[i].age 
             << ", Birth Date: " << men[i].birthDate << endl;
    }
}


void sortMen(Man men[], int count, bool sortBySurname) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            bool condition = sortBySurname ? men[j].surname > men[j + 1].surname : men[j].name > men[j + 1].name;
            if (condition) {
                swap(men[j], men[j + 1]);
            }
        }
    }
}


void printBirthdayPeople(const Man men[], int count, int month) {
    cout << "\nPeople with birthday in month " << month << ":\n";
    for (int i = 0; i < count; ++i) {
        int birthMonth = stoi(men[i].birthDate.substr(3, 2)); 
        if (birthMonth == month) {
            cout << men[i].surname << " " << men[i].name << " (Birth Date: " << men[i].birthDate << ")\n";
        }
    }
}


void addMan(Man men[], int& count) {
    if (count < MAX_MEN) {
        Man newMan;
        inputManInfo(newMan);
        men[count] = newMan;
        count++; 
    } else {
        cout << "Cannot add more people. Maximum limit reached.\n";
    }
}


void removeMan(Man men[], int& count) {
    string surname, name;
    cout << "Enter surname of the person to remove: ";
    getline(cin, surname);
    cout << "Enter name of the person to remove: ";
    getline(cin, name);

    int index = searchMan(men, count, surname, name);
    if (index != -1) {
        for (int i = index; i < count - 1; ++i) {
            men[i] = men[i + 1]; 
        }
        count--;
        cout << "Person removed.\n";
    } else {
        cout << "Person not found.\n";
    }
}


int searchMan(const Man men[], int count, const string& surname, const string& name) {
    for (int i = 0; i < count; ++i) {
        if (men[i].surname == surname && men[i].name == name) {
            return i; 
        }
    }
    return -1; 
}


void editMan(Man men[], int count, int index) {
    cout << "Editing person: " << men[index].surname << " " << men[index].name << endl;
    inputManInfo(men[index]); 
}
