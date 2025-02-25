/*This program will read how many students and tests are in the file, and then dynamically allocate
the space and assign the data to a struct for the students. It then gets the Avg and letter grade 
for each student and then will display it in a table format. */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std; 

struct student {
  string name;
  int idNum;
  double avg;
  char grade;
  int* tests;


};
/*This function reads data from a file to determine how many students and tests there are and 
dynamically allocates the memory needed and assigns each student and test results to a struct*/
student* getData(ifstream& file, int&, int&);
//This function recieves the student and test scores to calculate an avg for each student
void calcAverage(student students[], int, int);
//This function recieves the student and average to convert it into a letter grade. 
void getLetterGrade(student students[], int);
//This function displays the student name, avg grade, and letter grade in a table. 
void displayData(student students[], int, int);

int main() { 
  ifstream file("grades.txt");
  if (!file) {
      cerr << "File could not be opened!" << endl;
      return 1; // Exit if file can't be opened
  }

  int studentCnt, testCnt;
  
  student* students = getData(file, studentCnt, testCnt);
  calcAverage(students, studentCnt, testCnt);
  getLetterGrade(students, studentCnt);
  displayData(students, studentCnt, testCnt);

  // Free dynamically allocated memory
  for(int i = 0; i < studentCnt; i++) {
      delete[] students[i].tests;
  }
  delete[] students;
  
return 0;
}

student* getData(ifstream& file, int& studentCnt, int& testCnt){
  
  file >> studentCnt >> testCnt; // Read the number of students and tests
  student* students = new student[studentCnt]; // dynamically allocates memory for num of students
  
  for (int i = 0; i < studentCnt; i++){
    students[i].tests = new int [testCnt]; //dynamically allocates memory for number of tests
    file >> students[i].name >> students[i].idNum;
    for (int j = 0; j < testCnt; j++){
      file >> students[i].tests[j];
    }
  }
  return students;
}
void calcAverage(student students[], int studentCnt, int testCnt){
  for (int i = 0; i < studentCnt; i++) {
    double sum = 0; 
    for (int j = 0; j < testCnt; j++){
        sum += students[i].tests[j];
      }
      students[i].avg = sum / testCnt;
    }
}
void getLetterGrade(student students[], int studentCnt){
   for (int i = 0; i < studentCnt; i++) {
          if (students[i].avg >= 91) {
              students[i].grade = 'A';
          } else if (students[i].avg >= 81) {
              students[i].grade = 'B';
          } else if (students[i].avg >= 71) {
              students[i].grade = 'C';
          } else if (students[i].avg >= 61) {
              students[i].grade = 'D';
          } else {
              students[i].grade = 'F';
          }
      }
  
}
void displayData(student students[], int studentCnt, int testCnt){
cout << "-----------------------------------------------" << endl;
    cout << setw(12) << left << "Name" 
         << setw(6) << "ID" 
         << setw(10) << "Average" 
         << setw(7) << "Grade" << endl;
    cout << "-----------------------------------------------" << endl;
    for (int i = 0; i < studentCnt; i++) {
        cout << setw(12) << left << students[i].name 
             << setw(6) << students[i].idNum << "\t";
        cout << setw(10) << students[i].avg 
             << setw(7) << students[i].grade << endl;
    }
}