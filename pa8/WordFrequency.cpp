/*
----------------------------------------
Class: CSE101
Project: pa8
Name: Anderson Compalas
CRUZID: acompala
----------------------------------------
*/


//-----------------------------------------------------------------------------
// WordFrequency.cpp
// Illustrates file input-output commands and text processing using the
// string functions find_first_of(), find_first_not_of() and substr().
// 
// compile:
//
//      g++ -std=c++17 -Wall -o FileIO FileIO.cpp
//
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include <stdexcept>
#include <cctype>
#include "Dictionary.h"

using namespace std;

#define MAX_LEN 300

string toLowerCase(string str) {
    for (auto& c : str) {
        c = tolower(c);
    }
    return str;
}

int main(int argc, char * argv[]){

   int line_count;
   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string tokenBuffer;
   string token;
   //string delim = " "; 
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   // read each line of input file, then count and insert tokens into dictionary
   Dictionary dict;
   line_count = 0;
   while( getline(in, line) )  {
      line_count++;
      len = line.length();
      
      // get tokens in this line
      
      tokenBuffer = "";

      // get first token
      //beginning of the word
      begin = min(line.find_first_not_of(delim, 0), len);
      //end of the word
      end   = min(line.find_first_of(delim, begin), len);
      //token is our individual word
      token = line.substr(begin, end-begin);
      //cout << "outside loop" << token << endl;
      while( token!="" ){  // we have a token
         // update token buffer
         tokenBuffer += "   "+token+"\n";
         

         token = toLowerCase(token);
         if(!dict.contains(token)){
            //cout << token << endl;
            dict.setValue(token, 1);
         }else{
            dict.getValue(token)++;
         }
         // get next token
         //beginning of the word
         begin = min(line.find_first_not_of(delim, end+1), len);
         //end of the word
         end   = min(line.find_first_of(delim, begin), len);
         //token is our individual word
         token = line.substr(begin, end-begin);
         
         
      }
   }

   //Print inOrderString
   out << dict << endl;

   //out << dict.pre_string() << endl; 

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}
