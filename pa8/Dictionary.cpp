/*
----------------------------------------
Class: CSE101
Project: pa8
Name: Anderson Compalas
CRUZID: acompala
Filename: Dictionary.cpp
----------------------------------------
*/

#include<iostream>
#include<string>
#include "Dictionary.h"

#define RED  1
#define BLACK 2

using namespace std;

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
   if(R != nil){
      inOrderString(s, R->left);
      s += R->key + " : " + std::to_string(R->val) + "\n";
      inOrderString(s, R->right);
   }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
   if(R != nil){
      s += R->key + "\n";
      preOrderString(s, R->left);
      preOrderString(s, R->right);
   }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
   if(R != N){
      this->setValue(R->key, R->val);
      preOrderCopy(R->left, N);
      preOrderCopy(R->right, N);
   }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node*& R){
   if(R != nil){
      postOrderDelete(R->left);
      postOrderDelete(R->right);
      delete R;
   }
   R = nil;
}

void Dictionary::transplant(Node* u, Node* v){//u is what you want to delete, v is what you want to replace with
   if(u->parent == nil){//removing the root
      root = v;
   }
   else if(u == u->parent->left){//if left child
      u->parent->left = v;
   }
   else{//if right child
      u->parent->right = v;
   }
   if (v != nil){//ensure v is not nullptr
      v->parent = u->parent;
   }   
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
   if(R == nil || R->key == k){
      return R;
   }
   else if(k < R->key){
      return search(R->left, k);
   }else if(k > R->key){
      return search(R->right, k);
   }
   return nil;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
   Node* temp = R;
   while(temp->left != nil){
      temp = temp->left;
   }
   return temp;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
   Node* temp = R;
   while(temp->right != nil){
      temp = temp->right;
   }
   return temp;
}


// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
   if(N->right != nil){
      return findMin(N->right);
   }
   Node* y = N->parent;
   while(y != nil && N == y->right){
      N = y;
      y = y->parent;
   }
   return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
   if(N->left != nil){
      return findMax(N->left);
   }
   Node* y = N->parent;
   while(y != nil && N == y->left){
      N = y;
      y = y->parent;
   }
   return y;
}

// RBT Helper Functions (Optional) -----------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N){
   Node* x = N;
   // set y
   Node *y = x->right;
   
   // turn y's left subtree into x's right subtree
   x->right = y->left;
   if(y->left != nil){// not necessary if using sentinal nil node
       y->left->parent = x;
   }     
     
   // link y's parent to x
   y->parent = x->parent;
   if (x->parent == nil){
      root = y;
   }  
   else if(x == x->parent->left){
      x->parent->left = y;
   }
   else{
      x->parent->right = y;
   }
   // put x on y's left
   y->left = x;
   x->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
   Node* x = N;
   // set y
   Node* y = x->left; 
   
   // turn y's right subtree into x's left subtree
   x->left = y->right; 
   if (y->right != nil){ // not necessary if using sentinal nil node
      y->right->parent = x;
   }
   // link y's parent to x
   y->parent = x->parent;
   if (x->parent == nil){
      root = y;
   } 
   else if (x == x->parent->right){
      x->parent->right = y;
   }   
   else{
      x->parent->left = y;
   }
   // put x on y's right
   y->right = x;
   x->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
   Node* z = N;
   Node* y;
   while (z->parent->color == RED){
      if (z->parent == z->parent->parent->left){
		 //cout << "here 1: z color " << z->parent->color << endl;
         y = z->parent->parent->right;
         if (y->color == RED){
			//cout << "here 2: z color" << z->parent->color << endl;
            z->parent->color = BLACK;                 // case 1
            y->color = BLACK;                         // case 1
			//cout << "second print " << z->parent->color << endl;
            z->parent->parent->color = RED;           // case 1
			//cout << "third print " << z->parent->color << endl;
            z = z->parent->parent;                    // case 1
         }else{ 
			//cout << "here 3" << endl;
            if (z == z->parent->right){
			   //cout << "here 4" << endl;
               z = z->parent;                         // case 2
               LeftRotate(z);
            }                // case 2
            z->parent->color = BLACK;                 // case 3
            z->parent->parent->color = RED;           // case 3
            RightRotate(z->parent->parent);           // case 3
         }
      }else{
		 //cout << "here 5" << endl; 
         y = z->parent->parent->left;
         if(y->color == RED){
			//cout << "here 6" << endl;
            z->parent->color = BLACK;                 // case 4
            y->color = BLACK;                         // case 4
            z->parent->parent->color = RED;           // case 4
            z = z->parent->parent;                     // case 4
         }else{ 
			//cout << "here 7" << endl;
            if (z == z->parent->left){
			   //cout << "here 8" << endl;
               z = z->parent;                         // case 5
               RightRotate(z);                        // case 5
            }
            z->parent->color = BLACK;                 // case 6
            z->parent->parent->color = RED;           // case 6
            LeftRotate(z->parent->parent);            // case 6
         }
      }
   }
   //cout << "exits while loop" << endl;
   root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
   if(u->parent == nil){
      root = v;
   }
   else if (u == u->parent->left){
      u->parent->left = v;
   }
   else{
      u->parent->right = v;
   }
   v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
   Node* x = N;
   Node* w;
   while(x != root and x->color == BLACK){
      if (x == x->parent->left){
         w = x->parent->right;
         if(w->color == RED){
            w->color = BLACK;                        // case 1
            x->parent->color = RED;                   // case 1
            LeftRotate(x->parent);                // case 1
            w = x->parent->right;                     // case 1
         }
         if(w->left->color == BLACK and w->right->color == BLACK){
            w->color = RED;                          // case 2
            x = x->parent;                           // case 2
         }
         else{ 
            if (w->right->color == BLACK){
               w->left->color = BLACK;                // case 3
               w->color = RED;                       // case 3
               RightRotate(w);                   // case 3
               w = x->parent->right;                  // case 3
            }
            w->color = x->parent->color;               // case 4
            x->parent->color = BLACK;                 // case 4
            w->right->color = BLACK;                  // case 4
            LeftRotate(x->parent);                // case 4
            x = root;                             // case 4
         }
      }
      else{ 
         w = x->parent->left;
         if (w->color == RED){
            w->color = BLACK;                        // case 5
            x->parent->color = RED;                   // case 5
            RightRotate(x->parent);               // case 5
            w = x->parent->left;                      // case 5
         }
         if (w->right->color == BLACK and w->left->color == BLACK){
            w->color = RED;                          // case 6
            x = x->parent;                           // case 6
         }
         else{ 
            if (w->left->color == BLACK){
               w->right->color = BLACK;               // case 7
               w->color = RED;                       // case 7
               LeftRotate(w);                    // case 7
               w = x->parent->left;                   // case 7
            }
            w->color = x->parent->color;              // case 8
            x->parent->color = BLACK;                 // case 8
            w->left->color = BLACK;                   // case 8
            RightRotate(x->parent);               // case 8
            x = root;                             // case 8
         }
      }
   }
   x->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
   Node* z = N;
   Node* y = z;
   Node* x;
   int y_original_color = y->color;
   if(z->left == nil){
      x = z->right;
      RB_Transplant(z, z->right);
   }
   else if(z->right == nil){
      x = z->left;
      RB_Transplant(z, z->left);
   }
   else{ 
      y = findMin(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z){
         x->parent = y;
      }
      else{
         RB_Transplant(y, y->right);
         y->right = z->right;
         y->right->parent = y;
      }
      RB_Transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
   }
   if (y_original_color == BLACK){
      RB_DeleteFixUp(x);
   }
}

// Class Constructors & Destructors ----------------------------------------

//Node constructor
Dictionary::Node::Node(keyType k, valType v){
   key = k;
   val = v;
   parent = left = right = nullptr;
   color = RED;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
   nil = new Node("", 0);
   nil->parent = nil->left = nil->right = nil;
   root = nil;
   current = nil;
   num_pairs = 0;
   nil->color = BLACK;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
   nil = new Node("", 0);
   nil->parent = nil->left = nil->right = nil;
   root = nil;
   current = nil;
   num_pairs = 0;
   nil->color = BLACK;
   preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
   postOrderDelete(root); // Delete all nodes in the tree
   delete nil; // Delete the sentinel node
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
   return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
   Node* node = search(root, k);
   return node != nil;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
   Node* node = search(root, k);
   if(node == nil){
      throw logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
   }
   return node->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
   return current != nil;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
   if(!hasCurrent()){
      throw logic_error("Dictionary: currentKey(): current undefined");
   }
   return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
   if (!hasCurrent()) {
      throw logic_error("Dictionary: currentVal(): current undefined");
   }
   return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
   postOrderDelete(root);
   root = nil;
   num_pairs = 0;
   current = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
   Node* node = search(this->root, k);
   if(node != nil){
      node->val = v;
      return;
   }
   //insert new pair
   Node* z = new Node(k, v);
   Node* y = nil;
   Node* x = root;
   while(x != nil){
      y = x;
      if(z->key < x->key){
         x = x->left;
      }else{
         x = x->right;
      }
   }
   z->parent = y;
   if(y == nil){//if tree was empty
      root = z;
   }
   else if(z->key < y->key){
      y->left = z;
   }
   else if(z->key > y->key){
      y->right = z;
   }
   z->left = nil;
   z->right = nil;
   z->color = RED;
   RB_InsertFixUp(z);
   num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
   Node* node = search(root, k);
   if(node == nil){
      throw logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
   }
   
   if(node == current){
      current = nil;
   }
   /*
   //if it has left, right, or both children
   if (node->left == nil) {
      transplant(node, node->right);
   } 
   else if (node->right == nil) {
      transplant(node, node->left);
   } 
   else {
      Node* y = findMin(node->right);
      if (y->parent != node) {
         transplant(y, y->right);
         y->right = node->right;
         y->right->parent = y;
      }
      transplant(node, y);
      y->left = node->left;
      y->left->parent = y;
   }*/
   RB_Delete(node);
   num_pairs--;
   delete node;

}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
   if(root == nil){
      return;
   }
   Node* node = root;
   while(node->left != nil){
      node = node->left;
   }
   current = node;
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
   if(root == nil){
      return;
   }
   Node* node = root;
   while(node->right != nil){
      node = node->right;
   }
   current = node;
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
   if(!hasCurrent()){
      throw logic_error("Dictionary: next(): current undefined");
   }
   if(current->right != nil){
      current = current->right;
      while(current->left != nil){
         current = current->left;
      }
   }
   else{
      Node* parent = current->parent;
      while(parent != nil && current == parent->right){
         current = parent;
         parent = parent->parent;
      }
      current = parent;
   }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
   if(!hasCurrent()){
      throw logic_error("Dictionary: prev(): current undefined");
   }
   if(current->left != nil){
      current = current->left;
      while(current->right != nil){
         current = current->right;
      }
   }
   else{
      Node* parent = current->parent;
      while(parent != nil && current == parent->left){
         current = parent;
         parent = parent->parent;
      }
      current = parent;
   }
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
   string result;
   inOrderString(result, root);
   return result;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
   string result;
   preOrderString(result, root);
   return result;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
   //if(num_pairs != D.num_pairs) return false; // If the number of pairs is not equal, return false.
   string s1 = to_string();
   string s2 = D.to_string();
   return s1 == s2; // If the string representations are equal, return true. Otherwise, return false.
}



// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
   std::string s = "";
   s = D.to_string();
   stream << s;
   return stream;
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator== (const Dictionary& A, const Dictionary& B) {
    return A.equals(B); 
}
// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=(const Dictionary& D){
   if(this->num_pairs != 0){
      this->clear();
   }
   num_pairs = 0;
   this->preOrderCopy(D.root, D.nil);
   return *this;
}


