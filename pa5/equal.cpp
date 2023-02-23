#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool checkFilesEqual(string file1, string file2) {
    ifstream fin1(file1);
    ifstream fin2(file2);
    string line1, line2;

    while (getline(fin1, line1) && getline(fin2, line2)) {
        if (line1 != line2) {
            fin1.close();
            fin2.close();
            return false;
        }
    }

    if (getline(fin1, line1) || getline(fin2, line2)) {
        fin1.close();
        fin2.close();
        return false;
    }

    fin1.close();
    fin2.close();
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./program file1.txt file2.txt" << endl;
        return 1;
    }

    if (checkFilesEqual(argv[1], argv[2])) {
        cout << "Files are equal" << endl;
        return 0;
    }
    else {
        cout << "Files are not equal" << endl;
        return 1;
    }
}