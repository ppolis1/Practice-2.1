// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

const int maxStud = 40;
const string subjects[] = {
        "Algebra", "Maths", "Programming", "Programming pactice", "Physics", "CS", "Philos", "English"
};


struct Student {
    string fullName;
    string sex;
    unsigned short group{};
    unsigned short listNum{};
    unsigned short grades[8]{};
};


void loadFromFile(Student students[], int& numStudents) //загрузка данных из файла
{
    ifstream in;
    in.open("data.txt");
    while (!in.eof())
    {
        in >> students[numStudents].fullName;
        in >> students[numStudents].sex;
        in >> students[numStudents].group;
        in >> students[numStudents].listNum;
        for (int j = 0; j < 8; ++j) {
            in >> students[numStudents].grades[j];
        }
        numStudents++;
    }
    numStudents--;
    in.close();
}
void saveToFile(Student students[], int& numStudents) // Запись данных в файл
{
    ofstream out;
    out.open("data.txt");
    for (int i = 0; i < numStudents; i++)
    {
        out << students[i].fullName << endl << students[i].sex << endl << students[i].group << endl << students[i].listNum << endl;
        for (int j = 0; j < 8; j++) {
            out << students[i].grades[j];
        }
        out << endl;
    }
    out.close();
}

void addStudents(Student students[], int& numStudents) {

    cout << "Enter the number of students: ";
    cin >> numStudents;

    for (int i = 0; i < numStudents; i++) {
        cout << "Student " << i + 1 << ":\n";

        cout << "Full name: ";
        getline(cin.ignore(), students[i].fullName);


        cout << "Sex (M/W): ";
        cin >> students[i].sex;

        cout << "Group Number: ";
        cin >> students[i].group;

        cout << "List Number: ";
        cin >> students[i].listNum;

        cout << "Grades:\n ";
        for (int j = 0; j < 8; ++j) {
            cout << setw(20) << subjects[j] << ": ";
            cin >> students[i].grades[j];
            if (students[i].grades[j] <= 2) {
                cout << students[i].fullName << "Expelled. Not saved to the DB.\n";
                break;
            }
        }
      
    }
   
   
}



int editStudents(Student students[], int& numStudents) {
    int studentIndex;
    cout << "Enter number of student to edit: ";
    cin >> studentIndex;

    if (studentIndex < 1 || studentIndex > numStudents) {
        cout << "Error!" << endl;
        return 0;
    }

    Student& student = students[studentIndex - 1];


    unsigned short input = 0;
    do {
        cout << "1. " << "Full name: " << student.fullName << endl;
        cout << "2. " << "Sex: " << (student.sex = "M" ? "Male" : "Female") << endl;
        cout << "3. " << "Group: " << student.group << endl;
        cout << "4. " << "List student: " << student.listNum << endl;
        cout << "5. " << "Grades: " << endl;
        for (int i = 0; i < 8; ++i) {
            cout << setw(10) << '|' << setw(8);
            cout << subjects[i] << ": " << student.grades[i] << endl;
        }
        cout << "Enter number of value to update (or 0 to exit):\n";
        cin >> input;
        switch (input) {
        case 0: break;
        case 1: {
            cout << "Full name: ";
            getline(cin.ignore(), student.fullName);
            break;
        }
        case 2: {
            cout << "Sex (M/W): ";
            cin >> student.sex;
            break;
        }
        case 3: {
            cout << "Group: ";
            cin >> student.group;
            break;
        }
        case 4: {
            cout << "List student: ";
            cin >> student.listNum;
            break;
        }
        case 5: {
            cout << "Grades:\n ";
            for (int j = 0; j < 8; ++j) {
                cout << setw(20) << subjects[j] << ": ";
                cin >> student.grades[j];
                if (student.grades[j] <= 2) {
                    cout << student.fullName << "Expelled. Not saved to the DB.\n";
                    break;
                }
            }
        }
        }
    } while (input != 0);
    students[studentIndex - 1] = student;
    return 0;
}



void listStudents(Student students[], int& numStudents) {

    cout << "Information of students:" << endl;
    cout << "\n";

    for (int i = 0; i < numStudents; i++) {
        cout << "Student " << i + 1 << ":" << endl;
        cout << "Full name: " << students[i].fullName << endl;
        cout << "Sex: " << (students[i].sex = "M" ? "Male" : "Female") << endl;
        cout << "Group: " << students[i].group << endl;
        cout << "List number: " << students[i].listNum << endl;
        cout << "Grades: " << endl;
        for (int j = 0; j < 8; ++j) {
            cout << setw(10) << '|' << setw(8);
            cout << subjects[j] << ": " << students[i].grades[j] << endl;
        }
        cout << "\n";
    }
}



void groupStudents(Student students[], int& numStudents, int N) {
    cout << "Students group number " << N << ":" << endl;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].group == N) {
            cout << "Full name: " << students[i].fullName << endl;
            cout << "Sex: " << (students[i].sex = "M" ? "Male" : "Female") << endl;
            cout << "List number: " << students[i].listNum << endl;
            cout << "Grades: " << endl;
            for (int j = 0; j < 8; ++j) {
                cout << setw(10) << '|' << setw(8);
                cout << subjects[j] << ": " << students[i].grades[j] << endl;
            }
            cout << "\n";
        }
    }
}



void topStudents(Student students[], int& numStudents, int size) {
    const int count = 5;

    struct Rating {
        int index;
        float average;
    } topStud[count]; 
     
    for (int i = 0; i < count; i++) {
        topStud[i].index = -1;
        topStud[i].average = 0;
    }
    for (int i = 0; i < size; i++) {
        float sum = 0;
        for (int j = 0; j < 8; j++) {
            sum += students[i].grades[j];
        }
        float average = sum / 8;


        for (int j = 0; j < count; j++) {
            if (topStud[j].index == -1 || average > topStud[j].average) {
                for (int k = count - 1; k > j; k--) {
                    topStud[k] = topStud[k - 1];
                }
                topStud[j].index = i;
                topStud[j].average = average;
                break;
            }
        }
    }

    cout << "Top students:" << endl;
    for (int i = 0; i < count; i++) {
        if (topStud[i].index == -1) {
            break;
        }
        int index = topStud[i].index;
        cout << "Student " << index + 1 << ": " << students[index].fullName << ", rating: " << topStud[i].average
            << endl;
    }
}



void numberByGender(Student students[], int& numStudents) {

    int numMale = 0, numFemale = 0;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].sex == "M") {
            ++numMale;
        }
        else {
            ++numFemale;
        }
    }
    cout << "\n";
    cout << "Number of Male Students: " << numMale << endl;
    cout << "Number of Female Students: " << numFemale << endl;
}



void scholarshipStudents(Student students[], int& numStudents) {
    
    //cout << "Students not receiving scholarship:" << "\n";
    bool grad3 = false, grad4 = false, grad5 = false;
    for (int i = 0; i < numStudents; i++) {
        int minGrade = 5;
        for (int j = 0; j < 8; j++) {
            minGrade = min(minGrade, students[i].grades[j]);
        }
        if (minGrade == 3) {
            cout << "The student doesnt receive a scholarship:" << endl;
            cout << "Full name: " << students[i].fullName << endl;
            cout << "Sex: " << (students[i].sex = "M" ? "Male" : "Female") << endl;
            cout << "List number: " << students[i].listNum << endl;
            cout << "Grades: " << endl;
            for (int j = 0; j < 8; ++j) {
                cout << setw(10) << '|' << setw(8);
                cout << subjects[j] << ": " << students[i].grades[j] << endl;
            }
            cout << "\n";
        }
        else if (minGrade == 4) {
            cout << "The student stadies only on 'good' and 'excellent': " << endl;
            cout << "Full name: " << students[i].fullName << endl;
            cout << "Sex: " << (students[i].sex = "M" ? "Male" : "Female") << endl;
            cout << "List number: " << students[i].listNum << endl;
            cout << "Grades: " << endl;
            for (int j = 0; j < 8; ++j) {
                cout << setw(10) << '|' << setw(8);
                cout << subjects[j] << ": " << students[i].grades[j] << endl;
            }
            cout << "\n";
        }
        else {
            cout << "The student stadies only on 'excellent':" << endl;
            cout << "Full name: " << students[i].fullName << endl;
            cout << "Sex: " << (students[i].sex = "M" ? "Male" : "Female") << endl;
            cout << "List number: " << students[i].listNum << endl;
            cout << "Grades: " << endl;
            for (int j = 0; j < 8; ++j) {
                cout << setw(10) << '|' << setw(8);
                cout << subjects[j] << ": " << students[i].grades[j] << endl;
            }
            cout << "\n";

        }

    }
    

 
    cout << "\n";
}




void studentsByListNum(Student students[], int& numStudents, int k) {
    cout << "Students with List Number " << k << ":" << endl;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].listNum == k) {
            cout << "List number: " << students[i].listNum << endl;
            cout << "Full name: " << students[i].fullName << endl;
            cout << "Sex: " << (students[i].sex = "M" ? "Male" : "Female") << endl;
            cout << "Grades: " << endl;
            for (int j = 0; j < 8; ++j) {
                cout << setw(10) << '|' << setw(8);
                cout << subjects[j] << ": " << students[i].grades[j] << endl;
              
            }
            cout << "\n";
        }
    }
}



int main() {
    int num;
    Student students[maxStud];
    loadFromFile(students, num);
    

    cout << "Enter 'c' to get list of commands\n";
    while (true) {

        char number;
        cout << "  Commands:\n ";
        cin.sync();
        cin >> number;

        if (number == '0') break;

        switch (number) {

        case '1': {
            addStudents(students, num);
            break;
        }
        case '2': {
            editStudents(students, num);
            break;
        }
        case '3': {
            listStudents(students, num);
            break;
        }
        case '4': {
            int N;
            cout << "Enter group: ";
            cin >> N;
            groupStudents(students, num, N);
            break;
        }
        case '5': {
            int size;
            cout << "Enter number of top: ";
            cin >> size;
            topStudents(students, num, size);
            break;
        }
        case '6': {
            numberByGender(students, num); // 6
            break;
        }
        case '7': {
            scholarshipStudents(students, num); // 7
            break;
        }
        case '8': {
            int input;
            cout << "Enter List Number to Search: ";
            cin >> input;
            studentsByListNum(students, num, input); // 8
            break;
        }
        case 'c': {
            cout << "Choose an action:\n";
            cout << "1 - Add new student.\n";
            cout << "2 - Making changes to an existing record.\n";
            cout << "3 - Print all students.\n";
            cout << "4 - Filter students by group number.\n";
            cout << "5 - Sort students by grade point average.\n";
            cout << "6 - Count amount of men/women.\n";
            cout << "7 - Group students by scholarship.\n";
            cout << "8 - Filter students by index.\n";
            cout << ">>>...\n";
            break;
        }
        default:
            cout << "Error" << "\n";  
        }
        saveToFile(students, num);
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
