#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Struct to hold student data
struct Student {
    string name;
    int id;
    double* testScores;
    double average;
    char grade;
};

// Function prototypes
Student* getData(ifstream& file, int& studentCnt, int& testsCnt);
void calcAverage(Student students[], int studentCnt, int testsCnt);
char getLetterGrade(double avg);
void printReport(const Student students[], int studentCnt);
void freeMemory(Student* students, int studentCnt);

int main() {
    ifstream file("grades.txt"); // File should contain student data
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int studentCnt, testsCnt;
    Student* students = getData(file, studentCnt, testsCnt);
    file.close();

    calcAverage(students, studentCnt, testsCnt);
    printReport(students, studentCnt);

    freeMemory(students, studentCnt);

    return 0;
}

// Function to read student data from file
Student* getData(ifstream& file, int& studentCnt, int& testsCnt) {
    file >> studentCnt >> testsCnt; // Read number of students and tests

    Student* students = new Student[studentCnt];

    for (int i = 0; i < studentCnt; i++) {
        file >> students[i].name >> students[i].id;
        students[i].testScores = new double[testsCnt];

        for (int j = 0; j < testsCnt; j++) {
            file >> students[i].testScores[j];
        }
    }
    return students;
}

// Function to calculate average score and assign letter grades
void calcAverage(Student students[], int studentCnt, int testsCnt) {
    for (int i = 0; i < studentCnt; i++) {
        double total = 0;
        for (int j = 0; j < testsCnt; j++) {
            total += students[i].testScores[j];
        }
        students[i].average = total / testsCnt;
        students[i].grade = getLetterGrade(students[i].average);
    }
}

// Function to determine letter grade
char getLetterGrade(double avg) {
    if (avg >= 90) return 'A';
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    if (avg >= 60) return 'D';
    return 'F';
}

// Function to print formatted report
void printReport(const Student students[], int studentCnt) {
    cout << left << setw(12) << "Student" << setw(6) << "ID" 
         << setw(8) << "Score" << "Grade" << endl;
    cout << "----------------------------------" << endl;

    for (int i = 0; i < studentCnt; i++) {
        cout << left << setw(12) << students[i].name 
             << setw(6) << students[i].id 
             << setw(8) << fixed << setprecision(1) << students[i].average 
             << students[i].grade << endl;
    }
}

// Function to deallocate memory
void freeMemory(Student* students, int studentCnt) {
    for (int i = 0; i < studentCnt; i++) {
        delete[] students[i].testScores; // Free each student's test scores array
    }
    delete[] students; // Free main student array
}
