//
//  WordTree.cpp
//  HW4
//
//  Created by Shanie Talor on 8/11/22.
//

#include "WordTree.h"
using namespace std;


//helper function for copy constructor
void WordTree::copy(WordNode *&thisRoot, WordNode *rhsRoot) {
   if (rhsRoot == NULL) {
      thisRoot = NULL;
   }
    else {
        thisRoot = new WordNode(rhsRoot->m_data);
        // add count
         thisRoot->m_count = rhsRoot->m_count;
        copy(thisRoot->m_left, rhsRoot->m_left);
        copy(thisRoot->m_right, rhsRoot->m_right);
   
    }
}

// helper function for assignment operator
void WordTree::destroy(WordNode *&thisRoot) {
   if (thisRoot != NULL) {
      destroy(thisRoot->m_left);
      destroy(thisRoot->m_right);
      delete thisRoot;
      thisRoot = NULL;
   }
}

//implement copy constructor
WordTree::WordTree(const WordTree& rhs) {
   root = NULL;
   copy(this->root, rhs.root);
}

//implement assignment operator
const WordTree& WordTree::operator=(const WordTree& rhs) {
   if (this != &rhs) {
      destroy(root);
      copy(root, rhs.root);
   }
   return *this;
}
//implement destructor
WordTree::~WordTree() {
   destroy(root);
}

//implement incrementTotal
void WordTree::AddTotal() {
    total++;
}
int WordTree:: GetTotal()const {
    return total;
}


//implement add function
void WordTree::add(WordType v) {
    
   WordNode *newNode = new WordNode(v);
   if (root == NULL) {
      root = newNode;
       AddTotal();
   }
   else {
      WordNode *curr = root;
      while (curr != NULL) {
         if (v < curr->m_data) {
            if (curr->m_left == NULL) {
               curr->m_left = newNode;
                AddTotal();
               break;
            }
            else {
               curr = curr->m_left;
            }
         }
         else if (v > curr->m_data) {
            if (curr->m_right == NULL) {
               curr->m_right = newNode;
                AddTotal();
               break;
            }
            else {
               curr = curr->m_right;
            }
         }
         else {
            curr->m_count++;
            delete newNode;
             AddTotal();
            break;
         }
      }
   }

}
int WordTree:: count(WordNode *&curr) const
{
   

    if (curr ==NULL)
        return 0;

    else
    {
        int c = 1;
          c += count(curr->m_left);
          c += count(curr->m_right);
        return c;
    }
   
}

//implement distinctWords function
int WordTree::distinctWords() const {
  
   WordNode *curr = root;
   
   return count(curr);
}


//implement totalWords function
int WordTree::totalWords() const {
    return GetTotal();
}



void WordTree::inOrder(ostream &out, WordNode *&curr) const {
   // print the word and how many times it appears
   if (curr != NULL) {
      inOrder(out, curr->m_left);
      out << curr->m_data << " " << curr->m_count << endl;
      inOrder(out, curr->m_right);
   }



  
}

ostream& operator<<(ostream &out, const WordTree& rhs) {
    WordNode *curr = rhs.root;
   rhs.inOrder(out, curr);
   return out;
}
