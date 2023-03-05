/*
-----------------------------------------------------------------------------
Class: CSE101
Project: pa6
Name: Anderson Compalas
CRUZID: 1793470
Cruz Email: acompala
Filename: ListTest.cpp
------------------------------------------------------------------------------
*/


//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------


#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

   int i, n=10;
   List A, B, C, D;

   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertAfter(11-i);
      C.insertBefore(i);
      D.insertBefore(11-i);
   }

   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   A.moveBack();
   B.moveBack();
   C.moveFront();
   D.moveFront();

   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

   cout << endl << "B: ";
   for(i=1; i<=7; i++){
      cout << B.movePrev() << " ";
   }
   cout << endl << "B.position() = " << B.position() << endl;
   
   cout << endl << "C: ";
   for(i=1; i<=7; i++){
      cout << C.moveNext() << " ";
   }
   cout << endl << "C.position() = " << C.position() << endl;

   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==D is " << (C==D?"true":"false") << endl;
   cout << "D==A is " << (D==A?"true":"false") << endl;
   cout << endl;

   cout << B.findNext(5) << endl;
   cout << B << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findPrev(2) << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl; 
   cout << B.findNext(20) << endl; 
   cout << B.position() << endl;
   cout << B.findPrev(20) << endl;
   cout << B.position() << endl;
   cout << endl;

   for( i=10; i>=1; i--){
      A.insertAfter(i);
      A.movePrev();
   }
   cout << "A = " << A << endl;
   for( i=1; i<=15; i++){
      A.moveNext();
   }
   cout << A.position() << endl;
   cout << "A before: " << A.peekPrev() << endl;
   cout << "A after: " << A.peekNext() << endl;
   cout << endl;
   cout << "Called cleanup(): " << endl;
   A.cleanup();
   cout << "A = " << A << endl;
   cout << "Correct position: 10" << endl;
   cout << "Actual position: " << A.position() << endl;
   cout << "A before: " << A.peekPrev() << endl;
   cout << "A.length()" << A.length() << endl;
   if(A.peekPrev() != A.back()){
      cout << "A after: " << A.peekNext() << endl;
   }
   cout << endl;

   List E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;
   cout << "A = " << A << endl;
   cout << "E = " << E << endl;

   cout << endl;

   List F = A.concat(B);
   cout << "F = " << F << endl;
   cout << "length: " << F.length() << endl;
   cout << "front: " << F.front() << endl;
   cout << "back: " << F.back() << endl;
   cout << "position: " << F.position() << endl;
   for( i=1; i<=7; i++){
      cout << "peekNext: " << F.peekNext() << endl;
      F.insertBefore(-i);
      cout << F.moveNext() << endl; 
   }
   cout << "F = " << F << endl;

   cout << endl;
   cout << "Cleanup_position: " << endl;
   cout << endl;
   List G;
   G.insertBefore(1);
   G.insertBefore(2);
   G.insertBefore(2);
   G.insertBefore(1);
   G.insertBefore(2);
   G.insertBefore(3);
   G.insertBefore(1);
   G.findPrev(3);
   cout << "G: " << G << endl;
   cout << "Called findPrev(3): " << G.peekNext() << endl;
   cout << "G position before movePrev(): " << G.position() << endl;
   cout << "G before: " << G.peekPrev() << endl;
   cout << "G after: " << G.peekNext() << endl;
   cout << endl;
   G.movePrev();
   cout << "G: " << G << endl;
   cout << "Called movePrev() " << endl;
   cout << "G before: " << G.peekPrev() << endl;
   cout << "G after: " << G.peekNext() << endl;
   cout << "G position before cleanup(): " << G.position() << endl;
   G.cleanup();
   cout << endl;
   cout << "Called cleanup() " << endl;
   cout << "G cleaned: " << G << endl;
   cout << "G position: " << G.position() << endl;
   cout << "G before: " << G.peekPrev() << endl;
   cout << "G after: " << G.peekNext() << endl;

   cout << endl;
   cout << "FindPrev_value: " << endl;
   cout << endl;
   List H;
   H.insertBefore(34);
   H.insertBefore(77);
   H.insertBefore(77);
   H.insertBefore(1);
   H.insertBefore(34);
   H.insertBefore(1);
   H.insertBefore(55);
   H.insertBefore(77);
   cout << "H: " << H << endl;


   H.moveBack();
   cout << "H.position() before cleanup(): " << H.position() << endl;
   cout << endl;
   H.cleanup();
   H.findPrev(1);
   cout << "H cleaned: " << H << endl;
   cout << "H.position(): " << H.position() << endl;

   cout << endl;
   cout << "test exceptions: " << endl;
   cout << "A = " << A << endl;
   A.moveFront();
   cout << "A.position(): " << A.position() << endl;
   try{
      A.peekPrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.movePrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setBefore(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseBefore();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.moveBack();
   try{
      A.peekNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.moveNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setAfter(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseAfter();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.clear();
   try{
      A.front();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.back();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;


   return( EXIT_SUCCESS );
}
