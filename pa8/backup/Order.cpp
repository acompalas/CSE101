/*
----------------------------------------
Class: CSE101
Project: pa8
Name: Anderson Compalas
CRUZID: acompala
Filename: Order.cpp
----------------------------------------
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Dictionary.h"

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

    Dictionary dict;
    string line;
    int size = 0;

    //Read Lines from file and insert them into dictionary
    while (getline(fin, line)) {
        dict.setValue(line, size + 1);
        size++;
    }

    //Print inOrderString
    fout << dict << endl;   

    //Print preOrderString
    fout << dict.pre_string() << endl; 

    // close files
    fin.close();
    fout.close();

    return 0;
}



