#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cstdio>

struct Student
{
    std::string name;
    int rollNo;
    float sgpa;
};

std::string toLowerCase(const std::string &str);
void swap(Student &a, Student &b);

void takeInput(Student list[], int size);
void display(Student list[], int size);
void printDetails(Student name);

void bubbleSort(Student list[], int size);            // Q1. bubble sort
void arrangeAlphabetically(Student list[], int size); // Q2. insertion sort
int partation(Student list[], int low, int high);
void arrangeToFindToppers(Student list[], int low, int high);               // Q3. quick sort
void searchBySgpa(Student list[], float targetSgpa, int size);              // Q4. linear search
void searchByName(Student list[], const std::string &targetName, int size); // Q5. binary search

int main()
{
    const int size = 5;
    Student list[size];

    takeInput(list, size);

    bubbleSort(list, size);            // bubble sort
    arrangeAlphabetically(list, size); // insertion sort

    searchBySgpa(list, 9.1, size);           // linear search
    searchByName(list, "Ali Zaid", size);    // binary search
    arrangeToFindToppers(list, 0, size - 1); // quick sort
    std::cout << "**************** Q3. Sorted list to show first 10 toppers **************** \n";
    display(list, size);

    return 0;
}

void takeInput(Student list[], int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << "Enter Name of student " << i + 1 << ": ";
        std::getline(std::cin, list[i].name);

        std::cout << "Enter Roll Number of student " << i + 1 << ": ";
        std::cin >> list[i].rollNo;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter SGPA of student " << i + 1 << ": ";
        std::cin >> list[i].sgpa;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n";
    }
    std::cout << "\n";
}

void display(Student list[], int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << "Student " << i + 1 << "'s details: \n";
        std::cout << "Name: " << list[i].name << "\n";
        std::cout << "Roll Number: " << list[i].rollNo << "\n";
        std::cout << "SGPA: " << list[i].sgpa << "\n";
        std::cout << "\n";
    }
}

void swap(Student &a, Student &b)
{
    Student temp = a;
    a = b;
    b = temp;
}

std::string toLowerCase(const std::string &str)
{
    std::string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// 🟩 Q1. Sort Student list using Bubble Sort
void bubbleSort(Student list[], int size)
{
    std::string nameTemp;
    int rollNoTemp;
    float sgpaTemp;

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (list[j].rollNo > list[j + 1].rollNo)
            {
                swap(list[j], list[j + 1]);
            }
        }
    }
    std::cout << "**************** Q1. Sorted List using Bubble Sort **************** \n";
    display(list, size);
}

// 🟩 Q2. Sort Student list alphabeticlly using Insertion Sort
void arrangeAlphabetically(Student list[], int size)
{

    for (int i = 1; i < size; i++)
    {
        std::string nameKey = list[i].name;
        int rollNoKey = list[i].rollNo;
        float sgpaKey = list[i].sgpa;

        int j = i - 1;

        while (j >= 0 && toLowerCase(list[j].name) > toLowerCase(nameKey))
        {
            list[j + 1].name = list[j].name;
            list[j + 1].rollNo = list[j].rollNo;
            list[j + 1].sgpa = list[j].sgpa;
            j = j - 1;
        }

        list[j + 1].name = nameKey;
        list[j + 1].rollNo = rollNoKey;
        list[j + 1].sgpa = sgpaKey;
    }

    std::cout << "**************** Q2. Arranged Alphabetically using Insertion Sort **************** \n";
    display(list, size);
}

// 🟩 Q3. Arrange list of students to find out first ten toppers from a class. (Use Quick sort)
int partation(Student list[], int low, int high)
{
    double pivot = list[high].sgpa;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (list[j].sgpa >= pivot)
        {
            i++;
            swap(list[i], list[j]);
        }
    }

    swap(list[i + 1], list[high]);
    return (i + 1);
}

void arrangeToFindToppers(Student list[], int low, int high)
{
    if (low < high)
    {
        int pi = partation(list, low, high);
        arrangeToFindToppers(list, low, pi - 1);
        arrangeToFindToppers(list, pi + 1, high);
    }
}

void printDetails(Student student)
{
    std::cout << '\n';
    std::cout << "Name: " << student.name << '\n';
    std::cout << "Roll No: " << student.rollNo << '\n';
    std::cout << "SGPA: " << student.sgpa;
    std::cout << '\n';
}
// 🟩 Q4. Search students according to SGPA. If more than one student having same SGPA, then print list of all students having same SGPA.
void searchBySgpa(Student list[], float targetSgpa, int size)
{
    printf("**************** Q4. Students scored %.2f SGPA **************** \n", targetSgpa);
    for (int i = 0; i < size; i++)
    {
        if (list[i].sgpa == targetSgpa)
        {
            printDetails(list[i]);
        }
        else if (i == size - 1 && list[i].sgpa != targetSgpa)
        {
            printf("No students scored %.2f SGPA", targetSgpa);
            std::cout << '\n';
        }
    }
}

// 🟩 Q5. Search a perticular strudent according to name using binary search without recursion (all student record of having the presence of search should be displayed)
void searchByName(Student list[], const std::string &targetName, int size)
{
    int low = 0;
    int high = size - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        std::string midNameLower = toLowerCase(list[mid].name);
        std::string targetNameLower = toLowerCase(targetName);

        if (midNameLower == targetNameLower)
        {
            printf("**************** Q5. Searced by name **************** \n");
            printDetails(list[mid]);
            return;
        }
        if (midNameLower < targetNameLower)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    std::cout << "Name not found" << std::endl;
}