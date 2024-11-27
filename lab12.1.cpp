#include <iostream>
#include <fstream>
using namespace std;

void CreateBIN(char* fname) {
    ofstream fout(fname, ios::binary); // відкриваємо файл для запису
    char ch;
    double number;

    do {
        cout << "Enter a number: ";
        cin >> number;
        fout.write((char*)&number, sizeof(number)); // записуємо число у файл
        cout << "Continue? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

// Функція для виведення вмісту бінарного файлу
void PrintBIN(char* fname) {
    ifstream fin(fname, ios::binary); // відкриваємо файл для читання
    double number;

    cout << "Contents of " << fname << ":\n";
    while (fin.read((char*)&number, sizeof(number))) {
        cout << number << " ";
    }
    cout << endl;
}

// Функція для обробки бінарного файлу
void ProcessBIN(char* fname, char* gname) {
    ifstream fin(fname, ios::binary); // відкриваємо вхідний файл
    ofstream fout(gname, ios::binary); // відкриваємо вихідний файл

    double number;
    double sumNegative = 0, sumPositive = 0;
    int countNegative = 0, countPositive = 0;

    // Підрахунок сум і кількостей
    while (fin.read((char*)&number, sizeof(number))) {
        if (number < 0) {
            sumNegative += number;
            countNegative++;
        }
        else if (number > 0) {
            sumPositive += number;
            countPositive++;
        }
    }

    // Обчислення середнього арифметичного
    double avgNegative = (countNegative > 0) ? (sumNegative / countNegative) : 0;
    double avgPositive = (countPositive > 0) ? (sumPositive / countPositive) : 0;

    // Запис у вихідний файл
    fout.write((char*)&avgNegative, sizeof(avgNegative));
    fout.write((char*)&avgPositive, sizeof(avgPositive));
}

int main() {
    char fname[100]; // ім'я вхідного файлу
    char gname[100]; // ім'я вихідного файлу

    cout << "Enter input file name: ";
    cin >> fname;
    CreateBIN(fname); // створюємо вхідний бінарний файл

    PrintBIN(fname); // виводимо вміст вхідного файлу

    cout << "Enter output file name: ";
    cin >> gname;
    ProcessBIN(fname, gname); // обробляємо файл

    PrintBIN(gname); // виводимо вміст вихідного файлу

    return 0;
}
