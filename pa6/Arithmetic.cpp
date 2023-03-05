/*
----------------------------------------
Class: CSE101
Project: pa6
Name: Anderson Compalas
CRUZID: 1793470
Cruz Email: acompala
Filename: Arithmetic.cpp
----------------------------------------
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "BigInteger.h"
#include "List.h"

using namespace std;

int main(int argc, char *argv[]) {
    // check if input and output file names are provided
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    // open input file
    ifstream fin(argv[1]);
    if (!fin.is_open()) {
        cout << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    // open output file
    ofstream fout(argv[2]);
    if (!fout.is_open()) {
        cout << "Error opening output file: " << argv[2] << endl;
        return 1;
    }

    // read input file line by line and write to output file
    string line, line1, line2;

    getline(fin, line1);
    getline(fin, line); // skip empty line
    getline(fin, line2);

    string s3 = "3";
    string s2 = "2";
    string s9 = "9";
    string s16 = "16";

    BigInteger A = BigInteger(line1);
    BigInteger B = BigInteger(line2);
    BigInteger three = BigInteger(s3);
    BigInteger two = BigInteger(s2);
    BigInteger nine = BigInteger(s9);
    BigInteger sixteen = BigInteger(s16);
    BigInteger A_3 = three * A;
    BigInteger B_2 = two * B;
    BigInteger A_94 = nine * A * A * A * A;
    BigInteger B_165 = sixteen * B * B * B * B * B;
    /*
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "A - B = " << A - B << endl << endl;
    cout << "A_3 = " << A_3 << endl;
    cout << "B_2 = " << B_2 << endl;
    cout << "A_3 - B_2 = " << A_3 - B_2 << endl;
    */

    fout << A << endl << endl;
    fout << B << endl << endl;
    fout << A + B << endl << endl;
    fout << A - B << endl << endl;
    fout << A - A << endl << endl;
    fout << A_3 - B_2 << endl << endl;
    fout << A * B << endl << endl;
    fout << A * A << endl << endl;
    fout << B * B << endl << endl;
    fout << A_94 + B_165 << endl;




    // close files
    fin.close();
    fout.close();

    return 0;
}