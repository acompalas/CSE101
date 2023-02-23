/*
----------------------------------------
Class: CSE101
Project: pa5
Name: Anderson Compalas
CRUZID: 1793470
Cruz Email: acompala
Filename: Shuffle.cpp
----------------------------------------
*/

#include<iostream>
#include<fstream>
#include<string> 
#include<stdexcept>
#include <iomanip>
#include "List.h"

using namespace std;

//Declarations
void shuffle(List& D);

int main(int argc, char * argv[]){

   if (argc < 2) {
         std::cout << "Usage: " << argv[0] << " output_file\n";
         return 1;
      }

   int max_size = stoi(argv[1]);
   //std::ofstream outfile(argv[2]);
   /*
   if (!outfile.is_open()) {
      std::cerr << "Error: Could not open file " << argv[1] << "\n";
      return 1;
   }
   */

   cout << "deck size" << "       " << "shuffle count" << endl;
   cout << "------------------------------" << endl;
   //outfile << "deck size" << "       " << "shuffle count" << endl;
   //outfile << "------------------------------" << endl;
   for (int n = 1; n <= max_size; n++) {
      List D;
      for (int i = 0; i < n; i++) {
         D.insertBefore(i);
      }
      List original = D;
      //cout << "original: " << original << endl;
      int count = 1;
      shuffle(D);
      //cout << "shuffled: " << D << endl;
      //cout << endl;
      //cout << "isEqual() = " << (D==original?"true":"false") << endl;
      while (!D.equals(original)) {
         shuffle(D);
         //cout << "shuffled: " << D << endl;
         count++;
      }
      //cout << "isEqual() = " << (D==original?"true":"false") << endl;
      //cout << endl;
      cout << " " << left <<  setw(16) << n << count << endl;
      //outfile << " " << left <<  setw(16) << n << count << endl;
      //cout << setprecision(2);
      //outfile << " " << left << n << setw(16) << right << count << endl;
      
   }

   //outfile.close();

   return(EXIT_SUCCESS);
}


//Global functions

void shuffle(List& D){
   List left, right;
   int n = D.length();
   int half = n/2;
   D.moveFront();
   //Build left list
   for(int i = 0; i < half; i++){
      left.insertBefore(D.moveNext());
   }
   //cout << "left: " << left << endl;
   //Build right list
   for(int j = half; j < n; j++){
      right.insertBefore(D.moveNext());
   }
   //cout << "right: " << right << endl;
   D.clear();
   left.moveFront();
   right.moveFront();
   while( left.position() < left.length() && right.position() < right.length()){
      D.insertBefore(right.moveNext());
      D.insertBefore(left.moveNext());
   }
   while(right.position() < right.length()){
      D.insertBefore(right.moveNext());
   }
   while(left.position() < left.length()){
      D.insertBefore(left.moveNext());
   }

   return;
}

