/*
----------------------------------------
Class: CSE101
Project: pa6
Name: Anderson Compalas
CRUZID: 1793470
Cruz Email: acompala
Filename: BigInteger.h
----------------------------------------
*/

//-----------------------------------------------------------------------------
// BigInteger.cpp
// Implemented functions for the BigInteger ADT
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include "List.h"
#include "BigInteger.h"

using namespace std;

// Constants -------------------------------------------------

const long base = 1000000000; //10^9
const int power = 9;

// Function Prototypes ----------------------------------------

//void printList(List &L);

//negateList()
//Changes the sign of each integer in List L. Used by sub()/
void negateList(List& L);

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn);
// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L);
// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p);
// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m);

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(string s) {
    digits = List();
    string str = s;
    signum = 1;
    int p = power;
    int n; 

    if(s.empty()){
        //cout << "x1: " << endl;
        throw invalid_argument("BigInteger: Constructor: empty string");
    }

    if (s[0] == '-') {
        signum = -1;
        str = s.substr(1);
    }
    if (s[0] == '+') {
        signum = 1;
        str = s.substr(1);
    }

    n = str.size();
    if(str.empty() && s.empty() == false){
        throw invalid_argument("BigInteger: non-numeric string");
    }

    for (int i = 0; i < n; i++) {
        if (str[i] < '0' || str[i] > '9') {
            //cout << "x1: " << endl;
            throw invalid_argument("BigInteger: Constructor: non-numeric string");
        }
        //digits.insertBefore(s[i] - '0');
    }
    string firstChunk = str.substr(0, n % p);
    while(firstChunk.length() % p != 0){
        firstChunk = '0' + firstChunk;
    }
    if(!firstChunk.empty()) {
        long num = stol(firstChunk);
        digits.insertBefore(num);
    }

    for(int i = n - p; i >= 0; i -=p){
        string chunk = str.substr(max(i, 0), p);
        long num = stol(chunk);
        digits.insertAfter(num);
    }
    if (digits.length() == 0) {
        signum = 0;
        digits.insertBefore(0);
    }
    normalizeList(digits);
    //scalarMultList(digits, -10);
    //shiftList(digits, 4);
    //(*this).printList();
}


/*void BigInteger::printList(){
    List L = digits;
    L.moveFront();
    while(L.position() < L.length()){
        long k = L.peekNext();
        string x = std::to_string(k);
        if(k == 0){
            x = "000000000";
        }
        cout << x;
        cout << " ";
        L.moveNext();
    }
    cout << endl;
}*/


// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    digits = N.digits;
    signum = N.signum;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is negative, 
// positive or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    if (sign() < N.sign()) {
        //cout << "this1" << endl;
        return -1;
    }
    else if (sign() > N.sign()) {
        //cout << "this2" << endl;
        return 1;
    }
    else if (digits.length() < N.digits.length()) {
        //cout << "this3" << endl;
        return -1;
    }
    else if (digits.length() > N.digits.length()) {
        //cout << "this4" << endl;
        return 1;
    }
    else {
        List l = digits;
        List n = N.digits;
        //cout << "this5" << endl;
        l.moveFront();
        n.moveFront();
        while (l.position() != l.length() && n.position() != n.length()) {
            if (l.peekNext() < n.peekNext()) {
                return -1;
            }
            else if (l.peekNext() > n.peekNext()) {
                return 1;
            }
            l.moveNext();
            n.moveNext();
        }
    }
    return 0;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    if (signum != 0) {
        signum = -signum;
    }
}

// Helper Functions ----------------------------------------

//negateList()
//Changes the sign of each integer in List L. Used by sub()/
void negateList(List& L){
    long x;
    if(L.length() == 0) return;
    L.moveFront();
    while(L.position() != L.length()){
        x = L.peekNext() * -1;
        L.setAfter(x);
        L.moveNext();
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
    ListElement x;
    S.clear();
    A.moveBack();
    B.moveBack();
    while(A.position() != 0 && B.position() != 0){
        x = A.peekPrev() + (sgn * B.peekPrev());
        S.insertAfter(x);
        A.movePrev();
        B.movePrev();
    }
    while(A.position() != 0){
        x = A.peekPrev();
        S.insertAfter(x);
        A.movePrev();
    }
    while(B.position() != 0){
        x = sgn * B.peekPrev();
        S.insertAfter(x);
        B.movePrev();
    }
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
    int sign = 0;
    int carry = 0;
    ListElement x = 0;
    //int r = 0;
    //int q = 0;
    L.moveFront();
    while(L.length() > 1 && L.front() == 0){
            L.eraseAfter();
    }
    if(L.length() == 0) return sign;
    L.moveBack();
    while(L.position() != 0){
        x = L.peekPrev() + carry;
        //q = x/base; //carry
        //r = x % base; //new node
        if(x < 0){ //if the new value is negative
            carry = -1;
            x += base;
            sign = -1;
        }else{
            carry = x/base;
            x %= base;
            sign = 1;
        }
        L.setBefore(x);
        L.movePrev();
    }
    if(carry > 0){
        L.insertBefore(carry);
    }
    L.moveFront(); 
    /*
    if(L.length() > 0 && L.peekNext() == 0){
        // remove leading zeros
        while(L.length() > 1 && L.front() == 0){
            L.moveNext();
            L.eraseBefore();
        }
    }*/
    
    if(L.length() == 1 && L.front() == 0){
        sign = 0;
    }
    /*
    if(r < 0){
        sign = -1;
    }
    else if(r > 0){
        sign = 1;
    }
    else if(r == 0){
        sign = 0;
    }
    */
    return sign;

}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
    L.moveBack();
    for (int i = 0; i < p; i++) {
        L.insertAfter(0);
    }
}
// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
    ListElement x = 0;
    L.moveBack();
    while (L.position() != 0) {
        x = L.peekPrev() * m;
       	L.setBefore(x);
        L.movePrev();
    }
	//normalizeList(L);   
}


// BigInteger Arithmetic operations ----------------------------------------


// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger result;
    BigInteger A = (*this);
    BigInteger B = N;
    //A + B  *sign is always positive
    if(A.sign() > 0 && B.sign() > 0){
        sumList(result.digits, A.digits, B.digits, 1);
        //result.printList();
        result.signum = normalizeList(result.digits);
        result.signum = 1;
    }
    //-A + -B = -(A+B) *sign is always negative
    else if(A.sign() < 0 && B.sign() < 0){
        sumList(result.digits, A.digits, B.digits, 1);
        result.signum = normalizeList(result.digits);
        result.signum = -1;
    }
    //A + - B = A - B
    //-(B-A) if B > A
    else if(A.sign() > 0 && B.sign() < 0){
        B.negate();
        if(A < B){
            sumList(result.digits, B.digits, A.digits, -1);
            result.signum = normalizeList(result.digits);
            result.signum = -1;
        }
        else{
            sumList(result.digits, A.digits, B.digits, -1);
            result.signum = normalizeList(result.digits);
        }
    }
    //-A + B = B - A
    //-(A-B)
    else if(A.sign() < 0 && B.sign() > 0){
        A.negate();
        if(A > B){
            sumList(result.digits, A.digits, B.digits, -1);
            result.signum = normalizeList(result.digits);
            result.signum = -1;
        }
        else{
            sumList(result.digits, B.digits, A.digits, -1);
            result.signum = normalizeList(result.digits);
        }
    }
    
    return result;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger result;
    BigInteger A = (*this);
    BigInteger B = N;
    //A - B = -(B-A)
    if(A.sign() > 0 && B.sign() > 0){
        if(A >= B){
            sumList(result.digits, A.digits, B.digits, -1);
            result.signum = normalizeList(result.digits);
        }
        else if(A < B){
            sumList(result.digits, B.digits, A.digits, -1);
            result.signum = normalizeList(result.digits);
            result.signum = -1;
        }
    }
    //A - -B = A + B
    else if(A.sign() > 0 && B.sign() < 0){
        sumList(result.digits, A.digits, B.digits, 1);
        result.signum = normalizeList(result.digits);
        result.signum = 1;
    }
    //-A - B = -(A+B)
    else if(A.sign() < 0 && B.sign() > 0){
        sumList(result.digits, A.digits, B.digits, 1);
        result.signum = normalizeList(result.digits);
        result.signum = -1;
    }
    //-A - -B = -A + B = -(A - B) = B - A
    else if(A.sign() < 0 && B.sign() < 0){
        A.negate();
        B.negate();
        if(A >= B){
            sumList(result.digits, A.digits, B.digits, -1);
            result.signum = normalizeList(result.digits);
            result.signum *= -1;
        }
        else if(A < B){
            sumList(result.digits, B.digits, A.digits, -1);
            result.signum = normalizeList(result.digits);
        }
    }


    return result;

}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger result;
	List A, B;
	if((*this) < N){
		A = N.digits;
		B = digits;
	}else{
		A = digits;
		B = N.digits;
	}
	B.moveBack();
	int shift = 0;
	while(B.position() != 0){
		BigInteger temp;
        temp.digits = A;
	    ListElement x = B.peekPrev();
        shiftList(temp.digits, shift);
		scalarMultList(temp.digits, x);
        //temp.printList();
		sumList(result.digits, result.digits, temp.digits, 1);
        normalizeList(result.digits);
		B.movePrev();
		shift++;
	}
    if(signum == N.signum){
        result.signum = 1;
    }
    else if(signum == 0 || N.signum == 0){
        result.signum = 0;
    }
    else if((signum == -1 && N.signum == 1) || (signum == 1 && N.signum == -1)){
        result.signum = -1;
    }
  	  
    return result;
}




// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    std::string result;

	if (digits.length() == 0) {
        result += "0";
        return result;
    }

    if (sign() == -1) {
        result += "-";
    }

	digits.moveFront();
	while (digits.position() < digits.length()) {
        string chunk = std::to_string(digits.peekNext());
        if(digits.peekNext() != digits.front()){
            while(chunk.size() < power){
            chunk = '0' + chunk;
            }
        }
		result += chunk;
		digits.moveNext();
	}

	return result;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 0){
		return true;
	}
	return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    int x = A.compare(B);
    if(x == -1){
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    int x = A.compare(B);
    if(x == -1 || x == 0){
        return true;
    }
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    int x = A.compare(B);
    if(x == 1){
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    int x = A.compare(B);
    if(x == 1 || x == 0){
        return true;
    }
    return false;
}


// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    BigInteger result = A.add(B);
    return result;
}


// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}


// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}


// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A * B;
    return A;
}


