#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// Struct for student data
struct Student {
    string name;
    int id;
    double* testScores; // Dynamically allocated array for test scores
    double average;
    char grade;
};

// Function prototypes
Student* getData(ifstream& file, int& studentCnt, int& testsCnt);
void calcAverage(Student* students, int studentCnt, int testsCnt);
char getLetterGrade(double average);
void displayResults(Student* students, int studentCnt);
void freeMemory(Student* students, int studentCnt);

int main() {
    ifstream file("grades.txt"); // Open input file
    if (!file) {
        cerr << "Error: Could not open file!" << endl;
        return 1;
    }

    int studentCnt, testsCnt;
    Student* students = getData(file, studentCnt, testsCnt); // Read data dynamically
    file.close(); // Close file after reading

    calcAverage(students, studentCnt, testsCnt); // Calculate averages and grades
    displayResults(students, studentCnt); // Display results

    freeMemory(students, studentCnt); // Free dynamically allocated memory

    return 0;
}

// Function to read student data from the file dynamically
Student* getData(ifstream& file, int& studentCnt, int& testsCnt) {
    file >> studentCnt >> testsCnt; // Read number of students and tests

    Student* students = new Student[studentCnt]; // Allocate array for students

    for (int i = 0; i < studentCnt; i++) {
        file >> students[i].name >> students[i].id;

        students[i].testScores = new double[testsCnt]; // Allocate array for test scores

        for (int j = 0; j < testsCnt; j++) {
            file >> students[i].testScores[j]; // Read test scores
        }
    }
    return students;
}

// Function to calculate the average and assign grades
void calcAverage(Student* students, int studentCnt, int testsCnt) {
    for (int i = 0; i < studentCnt; i++) {
        double sum = 0;
        for (int j = 0; j < testsCnt; j++) {
            sum += students[i].testScores[j];
        }
        students[i].average = sum / testsCnt;
        students[i].grade = getLetterGrade(students[i].average);
    }
}

// Function to assign a letter grade based on the average score
char getLetterGrade(double average) {
    if (average >= 90) return 'A';
    if (average >= 80) return 'B';
    if (average >= 70) return 'C';
    if (average >= 60) return 'D';
    return 'F';
}

// Function to display results
void displayResults(Student* students, int studentCnt) {
    cout << fixed << setprecision(2);
    cout << left << setw(10) << "Student" << setw(8) << "ID" 
         << setw(8) << "Score" << setw(6) << "Grade" << endl;
    cout << "---------------------------------" << endl;

    for (int i = 0; i < studentCnt; i++) {
        cout << left << setw(10) << students[i].name 
             << setw(8) << students[i].id 
             << setw(8) << students[i].average 
             << setw(6) << students[i].grade << endl;
    }
}

// Function to free dynamically allocated memory
void freeMemory(Student* students, int studentCnt) {
    for (int i = 0; i < studentCnt; i++) {
        delete[] students[i].testScores; // Free test score arrays
    }
    delete[] students; // Free student array
}

   




    

