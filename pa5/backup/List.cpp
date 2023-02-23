/*
----------------------------------------
Class: CSE101
Project: pa5
Name: Anderson Compalas
CRUZID: 1793470
Cruz Email: acompala
Filename: List.cpp
----------------------------------------
*/

//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<iostream>
#include<string> 
#include<stdexcept>
#include "List.h"

//---------------------------------------
//Constructors/Destructors
//---------------------------------------

// Node constructor
List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

// Creates new List in the empty state.
List::List(){
	frontDummy = new Node(-6);
	backDummy = new Node(-9);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	pos_cursor = 0;
	num_elements = 0;
}

// Copy constructor.
List::List(const List& L){
	//make this list an empty list
	frontDummy = new Node(-6);
	backDummy = new Node(-9);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	pos_cursor = 0;
	num_elements = 0;

	//load elements into the list
	for(Node* N = L.frontDummy->next; N != L.backDummy; N = N->next){
		insertAfter(N->data);
		moveNext();
	}
	moveFront();
}

// Destructor
List::~List(){
	clear();
	delete(frontDummy);
	delete(backDummy);
}
	

//---------------------------------------
//Access functions
//---------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
	return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
	if(length()<=0){
      throw std::length_error("List: front(): empty List");
   }
	return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
	if(length()<=0){
		throw std::length_error("List: back(): empty List");
	}
	return backDummy->prev->data ;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
	return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
	//if position is at the end of the list
	if(position() >= length()){
		throw std::range_error("List: peekNext(): cursor at back");
	}
	return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
	if(position() == 0){
		throw std::range_error("List: peekPrev(): cursor at front");
	}
	return beforeCursor->data;
}	

//-----------------------------------------------	
//Manipulation functions
//-----------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	moveFront();
    while (length() > 0) {
        eraseAfter();
    }
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
	pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
	beforeCursor = backDummy->prev;
	afterCursor = backDummy;
	pos_cursor = length();
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
	if(position() >= length()){
		throw std::range_error("List: moveNext(): cursor at back");
	}
	beforeCursor = afterCursor;
	afterCursor = afterCursor->next;
	pos_cursor++;
	return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
	if(position() <= 0){
		throw std::range_error("List: movePrev(): cursor at front");
	}
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
	Node* to_add = new Node(x);
	to_add->prev = beforeCursor;
	to_add->next = afterCursor;
	beforeCursor->next = to_add;
	afterCursor->prev = to_add;
	afterCursor = to_add;
	num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
	Node* to_add = new Node(x);
	to_add->prev = beforeCursor;
	to_add->next = afterCursor;
	beforeCursor->next = to_add;
	afterCursor->prev = to_add;
	beforeCursor = to_add;
	pos_cursor++;
	num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
	if(position()==length()){
		throw std::range_error("List: setAfter(): cursor at back");
	}
	afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
	if(position()==0){
		throw std::range_error("List: setAfter(): cursor at front");
	}
	beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
	if(position() == length()){
		throw std::range_error("List: eraseAfter(): cursor at back");
	}
	Node* to_delete = afterCursor;
	afterCursor = to_delete->next;
	beforeCursor->next = afterCursor;
	afterCursor->prev = beforeCursor;
	delete(to_delete);
	num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
	if(position() == 0){
		throw std::range_error("List: eraseBefore(): cursor at front");
	}
	Node* to_delete = beforeCursor;
	beforeCursor = to_delete->prev;
	afterCursor->prev = beforeCursor;
	beforeCursor->next = afterCursor;
	delete(to_delete);
	pos_cursor--;
	num_elements--;
}

//-----------------------------------------------
//Other functions
//-----------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
	if(length() == 0){
		throw std:: length_error("List: findNext(): empty List");
	}
	while(afterCursor != backDummy){
		if(afterCursor->data == x){
			moveNext();
			return position();
		}
		afterCursor = afterCursor->next;
		pos_cursor++;
	}
	beforeCursor = backDummy->prev;
	afterCursor = backDummy;
	pos_cursor = length();
	return(-1);
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
	if(length() == 0){
		throw std:: length_error("List: findPrev(): empty List");
	}
	Node* temp = beforeCursor;
	while(temp != frontDummy){
		if(temp->data == x){
			beforeCursor = temp->prev;
			afterCursor = temp;
			pos_cursor--;
			return pos_cursor;
		}
		temp = temp->prev;
		pos_cursor--;
	}
	moveFront();
	return(-1);
}


// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
	
	//Preserve original cursor position
	//int before = beforeCursor->data;
	//int after = afterCursor->data;
	//int after = peekNext();
	//int after = afterCursor->data; should already be implicit

	// Traverse the list
	
	Node* current = frontDummy->next;
	int cur_flag = 0;
    while (current != backDummy) {
		if(current == afterCursor){
			cur_flag = 1;
		}
        Node* runner = current->next;
        // Compare current node with all subsequent nodes
		int run_flag = 0;
        while (runner != backDummy) {
            // If a duplicate is found, remove the node *only if it isn't the cursor position node
            if (current->data == runner->data) {
				if(runner == beforeCursor){
					run_flag = 1;
				}
                Node* temp = runner;
                runner->prev->next = runner->next;
				runner->next->prev = runner->prev;
				delete temp;
				if(run_flag == 0 && cur_flag == 0){
					pos_cursor--;
				}
				num_elements--;
				
                runner = runner->next;
            }
            else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
	/*
	//Return cursor to original position
	moveFront();
	while(beforeCursor->data != before){
		moveNext();
	}*/
}


// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
	List result;
	Node* N = this->frontDummy->next;
	Node* M = L.frontDummy->next;

	while(N != backDummy){
		result.insertBefore(N->data);
		N = N->next;
	}
	while(M != L.backDummy){
		result.insertBefore(M->data);
		M = M->next;
	}
	result.moveFront();
	return result;
}


// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
	std::string result = "(";

	if (length() == 0) {
        result += ")";
        return result;
    }

	Node* current = frontDummy->next;
	while (current != backDummy) {
		result += std::to_string(current->data);
		if (current->next != backDummy) {
			result += ", ";
		}
		current = current->next;
	}

	result += ")";

	return result;
}


// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
	Node* current1 = frontDummy->next;
	Node* current2 = R.frontDummy->next;

	while (current1 != backDummy && current2 != R.backDummy) {
		if (current1->data != current2->data) {
			return false;
		}
		current1 = current1->next;
		current2 = current2->next;
	}

	return (current1 == backDummy && current2 == R.backDummy);
}

//-----------------------------------------------
//Overidden Operators
//-----------------------------------------------


// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.to_string();
}


// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
	if(A.equals(B) == true){
		return true;
	}
	return false;

}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
	if(this != &L){ // not self assignment
      // make a copy of L
      List temp = L;

      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
	  std::swap(beforeCursor, temp.beforeCursor);
	  std::swap(afterCursor, temp.afterCursor);
	  std::swap(pos_cursor, temp.pos_cursor);
      std::swap(num_elements, temp.num_elements);

   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}

