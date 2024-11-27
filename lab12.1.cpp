#include <iostream>
#include <fstream>
using namespace std;

void CreateBIN(char* fname) {
    ofstream fout(fname, ios::binary); // ��������� ���� ��� ������
    char ch;
    double number;

    do {
        cout << "Enter a number: ";
        cin >> number;
        fout.write((char*)&number, sizeof(number)); // �������� ����� � ����
        cout << "Continue? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

// ������� ��� ��������� ����� �������� �����
void PrintBIN(char* fname) {
    ifstream fin(fname, ios::binary); // ��������� ���� ��� �������
    double number;

    cout << "Contents of " << fname << ":\n";
    while (fin.read((char*)&number, sizeof(number))) {
        cout << number << " ";
    }
    cout << endl;
}

// ������� ��� ������� �������� �����
void ProcessBIN(char* fname, char* gname) {
    ifstream fin(fname, ios::binary); // ��������� ������� ����
    ofstream fout(gname, ios::binary); // ��������� �������� ����

    double number;
    double sumNegative = 0, sumPositive = 0;
    int countNegative = 0, countPositive = 0;

    // ϳ�������� ��� � ���������
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

    // ���������� ���������� �������������
    double avgNegative = (countNegative > 0) ? (sumNegative / countNegative) : 0;
    double avgPositive = (countPositive > 0) ? (sumPositive / countPositive) : 0;

    // ����� � �������� ����
    fout.write((char*)&avgNegative, sizeof(avgNegative));
    fout.write((char*)&avgPositive, sizeof(avgPositive));
}

int main() {
    char fname[100]; // ��'� �������� �����
    char gname[100]; // ��'� ��������� �����

    cout << "Enter input file name: ";
    cin >> fname;
    CreateBIN(fname); // ��������� ������� ������� ����

    PrintBIN(fname); // �������� ���� �������� �����

    cout << "Enter output file name: ";
    cin >> gname;
    ProcessBIN(fname, gname); // ���������� ����

    PrintBIN(gname); // �������� ���� ��������� �����

    return 0;
}
