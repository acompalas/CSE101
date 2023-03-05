/*
-----------------------------------------------------------------------------
Class: CSE101
Project: pa6
Name: Anderson Compalas
CRUZID: 1793470
Cruz Email: acompala
Filename: BigIntegerTest.cpp
------------------------------------------------------------------------------
*/

//-----------------------------------------------------------------------------
//  BigIntegerClient.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>
#include "BigInteger.h"
#include "List.h"

using namespace std;

int main(){

   string s1 = "9128734667000004389234563456345619187236478";
   //string s2 = "-330293847502398475";
   string s3 = "9876545439000000000000000200000000000006543654365346534";
   //string s4 = "9876545439000000000000000100000000000006543654365346534";
   //string s5 = "98765454390000000000000000000000000000065436543";
   //string s6 = "9876545439000000000000000000000000000006543";
   string test =  "187236478";
   string test2 = "365346534";
   long x = 187236478;
   long y = 365346534;
   long k =  x * y;
   string dos = "2";

   //BigInteger N;
   BigInteger scalar1 = BigInteger(test);
   BigInteger scalar2 = BigInteger(test2);
   BigInteger two = (dos);
   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s3);
   BigInteger cA = A;
   BigInteger nA = A;
   nA.negate();
   BigInteger C = A+B;
   BigInteger D = B+A;
   BigInteger E = A-A;
   BigInteger F = B-A;
   BigInteger G = A*B;
   BigInteger H = B*A;
   BigInteger I = C*E;
   BigInteger mult = scalar2 * scalar1;

   cout << endl;

   cout << "A = " << A << endl;
   cout << "-A = " << nA << endl;
   cout << "B = " << B << endl;
   cout << "mult = " << mult << endl;
   cout << "long k = " << k << endl;

   cout << endl;
   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

   cout << "C = " << C << endl;
   cout << "D = " << D << endl;
   cout << "E = " << E << endl;
   cout << "F = " << F << endl;
   cout << "G = " << G << endl;
   cout << "H = " << H << endl;
   cout << "I = " << I << endl;
   
   string f = "9876545438990871265333000195610765436550198035178110056";
   BigInteger mF = BigInteger(f);
   //mF.printList();
   cout << endl;

   string ps1 = "355797";
   string ps2 = "149082";

   BigInteger p1 = BigInteger(ps1);
   BigInteger p2 = BigInteger(ps2);
   BigInteger padd = p1 + p2;

   cout << "padd = " << padd << endl;
   cout << endl;

   BigInteger psub = p1 - p2;
   cout << "psub = " << psub << endl;
   cout << endl;

   string str1 = A.to_string();
   string str2 = "9128734667000004389234563456345619187236478";
   int result = strcmp(str1.c_str(), str2.c_str());
   
   cout << "(A == model A) = ";
   if( result == 0){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
   }

   cout << "(cA == copy A) = " << ((A==cA)?"True":"False") << endl;
   str1 = B.to_string();
   str2 = "9876545439000000000000000200000000000006543654365346534";
   result = strcmp(str1.c_str(), str2.c_str());

   str1 = nA.to_string();
   str2 = "-9128734667000004389234563456345619187236478";
   result = strcmp(str1.c_str(), str2.c_str());
   
   cout << "(nA == negative A) = ";
   if( result == 0 && nA.sign() == -1){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
      if(nA.sign() != 1){
         cout << "Sign error:";
         cout << "nA.sign() = " << nA.sign() << endl;
      }
   }
   
   cout << "(B == model B) = ";
   if( result == 0 && B.sign() == 1){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
   }

   str1 = C.to_string();
   str2 = "9876545439009128734667000204389234563462889273552583012";
   result = strcmp(str1.c_str(), str2.c_str());

   cout << "(C == model C) = ";
   if(result == 0 && C.sign() == 1){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
      if(C.sign() != 1){
         cout << "Sign error:";
         cout << "C.sign() = " << C.sign() << endl;
      }
   }

   str1 = D.to_string();
   str2 = "9876545439009128734667000204389234563462889273552583012";
   result = strcmp(str1.c_str(), str2.c_str());

   cout << "(D == model D) = ";
   if( result == 0 && D.sign() == 1){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
      if(D.sign() != 1){
         cout << "Sign error:";
         cout << "D.sign() = " << D.sign() << endl;
      }
   }
   cout << "(C==D) = " << ((C==D)?"True":"False") << endl;
   
   str1 = E.to_string();
   str2 = "0";
   result = strcmp(str1.c_str(), str2.c_str());

   cout << "(E == model E) = ";
   if( result == 0 && E.sign() == 0){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
      if(E.sign() != 0){
         cout << "Sign error:";
         cout << "E.sign() = " << E.sign() << endl;
      }
   }

   str1 = F.to_string();
   str2 = "9876545438990871265333000195610765436550198035178110056";
   result = strcmp(str1.c_str(), str2.c_str());

   cout << "(F == model F) = ";
   if( result == 0){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
   }

   str1 = G.to_string();
   str2 = "90160362739200077163474610231673334191391936936690338086239565536986604508155969004351356275667252";
   result = strcmp(str1.c_str(), str2.c_str());

   cout << "(G == model G) = ";
   if( result == 0){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
   }

   str1 = H.to_string();
   str2 = "90160362739200077163474610231673334191391936936690338086239565536986604508155969004351356275667252";
   result = strcmp(str1.c_str(), str2.c_str());

   cout << "(H == model H) = ";
   if( result == 0){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
   }

   cout << "(G==H) = " << ((G==H)?"True":"False") << endl;

   str1 = I.to_string();
   str2 = "0";
   result = strcmp(str1.c_str(), str2.c_str());

   cout << "(I == model I) = ";
   if( result == 0 && I.sign() == 0){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
      if(I.sign() != 0){
         cout << "Sign error:";
         cout << "I.sign() = " << I.sign() << endl;
      }
   }
   
   cout << endl;
   cout << "Assign functions" << endl;
   A += B;
   B -= C;
   C *= D;
   BigInteger Big = A*B*C*D*F*G*H;
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << "Big = " << Big << endl;
   
   cout << endl;

   str1 = A.to_string();
   str2 = "9876545439009128734667000204389234563462889273552583012";
   result = strcmp(str1.c_str(), str2.c_str());
   
   cout << "(A == model A) = ";
   if( result == 0 || A.sign() != 1){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
      if(A.sign() != 1){
         cout << "Sign error:";
         cout << "A.sign() = " << A.sign() << endl;
      }
   }

   str1 = B.to_string();
   str2 = "-9128734667000004389234563456345619187236478";
   result = strcmp(str1.c_str(), str2.c_str());
   
   cout << "(B == model B) = ";
   if( result == 0 && B.sign() == -1){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
      if(B.sign() != -1){
         cout << "Sign error:";
         cout << "B.sign() = " << B.sign() << endl;
      }
   }

   str1 = C.to_string();
   str2 = "97546149808812023446478487438741745308273629383177772500393093795831048940893389587964125538699008537150992144";
   result = strcmp(str1.c_str(), str2.c_str());
   
   cout << "(C == model C) = ";
   if( result == 0){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
      if(C.sign() != 0){
         cout << "Sign error:";
         cout << "C.sign() = " << C.sign() << endl;
      }
   }

   str1 = Big.to_string();
   str2 = "-6973763505900742737377809725497711067673393438190517155201841548145850668519116060678354794423551800641769814109924900105193364647725353661077374966624919005377027228048733559312591777369207681813901673984563442940611523403779498331383100652687907083994840696203218939396997398237072904395356864183944192776430773708931634969633508486213545101734004934049624392639565334544556411486115514261806244008121210454747968819475674445648370854714914066227362555481137574228074941273926042561552459426095789255070996692992";
   result = strcmp(str1.c_str(), str2.c_str());
   
   cout << "(Big == model Big) = ";
   if( result == 0 && Big.sign() == -1){
      cout << "True" << endl;
   }else{
      cout << "False" << endl;
      if(Big.sign() != -1){
         cout << "Sign error:";
         cout << "Big.sign() = " << Big.sign() << endl;
      }
   }
   
   cout << endl;

   // test exceptions
   try{
      BigInteger J = BigInteger("");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << " 1  continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("+");
      //cout << J << endl;
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << " 2 continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("12329837492387492837492$4982379487293847");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << " 3  continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("5298374902837409+82734098729287349827398");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << " 4 continuing without interruption" << endl;
   }

   cout << endl;

   

   return EXIT_SUCCESS;
}
