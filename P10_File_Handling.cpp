#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student
{
    int rollNo;
    string name;
    string division;
    string address;
};

void addStudent(const string &filename)
{
    ofstream file(filename, ios::app);
    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    Student student;
    cout << "Enter Roll Number: ";
    cin >> student.rollNo;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    file << student.rollNo << " " << student.name << " " << student.division << " " << student.address << endl;
    file.close();
    cout << "Student record added successfully.\n";
}

void deleteStudent(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    int rollNo;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNo;

    ofstream tempFile("temp.txt");
    bool found = false;
    Student student;

    while (file >> student.rollNo)
    {
        file.ignore();
        getline(file, student.name, ' ');
        getline(file, student.division, ' ');
        getline(file, student.address);

        if (student.rollNo != rollNo)
        {
            tempFile << student.rollNo << " " << student.name << " " << student.division << " " << student.address << endl;
        }
        else
        {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (found)
    {
        cout << "Student record deleted successfully.\n";
    }
    else
    {
        cout << "Record not found!\n";
    }
}

void displayStudent(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    int rollNo;
    cout << "Enter Roll Number to display: ";
    cin >> rollNo;

    Student student;
    bool found = false;

    while (file >> student.rollNo)
    {
        file.ignore();
        getline(file, student.name, ' ');
        getline(file, student.division, ' ');
        getline(file, student.address);

        if (student.rollNo == rollNo)
        {
            cout << "\nStudent Details:\n";
            cout << "Roll Number: " << student.rollNo << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Record not found!\n";
    }

    file.close();
}

int main()
{
    string filename = "students.txt";
    int choice;

    do
    {
        cout << "\nStudent Database Management:\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent(filename);
            break;
        case 2:
            deleteStudent(filename);
            break;
        case 3:
            displayStudent(filename);
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}