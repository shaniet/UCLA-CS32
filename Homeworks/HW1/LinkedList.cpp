//
//  LinkedList.cpp
//  HW1
//
//  Created by Shanie Talor on 7/6/22.
//

#include "LinkedList.h"
using namespace std;


LinkedList::LinkedList() {
   head = nullptr; // create an empty LinkedList
}


LinkedList:: LinkedList(const LinkedList& rhs) {
    if (rhs.head == nullptr){
         head = nullptr;
     }
     else {
           head = new Node;
           head->value = rhs.head->value;
           Node *curr = head;
           Node *rhsPTR = rhs.head->next;
           while (rhsPTR!= nullptr) {
                curr->next = new Node;
                curr = curr->next;
                curr->value = rhsPTR->value;
                rhsPTR = rhsPTR->next;
           }
           curr->next = nullptr;
     }
}
LinkedList::~LinkedList(){
   Node *curr = head;
  
   while (curr != nullptr) {
       Node * temp = curr-> next;
       delete curr;
       curr = temp;


   }

}

const LinkedList& LinkedList::operator=(const LinkedList& rhs){
   if (&rhs == this) {
       return* this;
   }
      LinkedList temp(rhs);
      swap(temp);
   
   return *this;
}
void LinkedList:: insertToFront(const ItemType &val){
    Node* p;
    p = new Node;
    p -> value = val; // sets the value to the input val
    p-> next = head; // sets the adress of next in p = address of head so that the head node comes next
    head = p; // sets head to point to the memory of the p Node
}


void LinkedList:: printList() const{ // this is a linked list traversal
    Node *p = head;
    while(p != nullptr){
        cout<< p-> value<<" ";
        p = p-> next; // this sets p = address of the next node, so now it points to the next node (can't do p++)
    }
    cout<< endl;
}
bool LinkedList:: get(int i, ItemType& item) const{
    if( i < 0 || i > size()){
        return false;
    }
    int position = 0;
    Node* p = head;
    while (p != nullptr){
        if (position == i){
            item = p-> value;
            return true;
        }

        p= p-> next;
        position++;
    
    }
    return false;
}

void LinkedList:: reverseList(){
    Node *current = head;
      Node *prev = nullptr;
      Node *next = nullptr;
      while (current != nullptr) {
         next = current->next;
         current->next = prev;
         prev = current;
         current = next;
      }
      head = prev;
   }

void LinkedList:: printReverse() const {
   LinkedList temp(*this);
   temp.reverseList();
    temp.printList();
   
}

void LinkedList:: append(const LinkedList &other){
    LinkedList tempList =other;
    Node *p = head;
    Node * q = tempList.head;
    while (p->next != nullptr){
        p = p->next;
    }
    p -> next = q;
    tempList.head = nullptr;
}

void LinkedList:: swap(LinkedList &other){
   Node *temp = head;
   head = other.head;
   other.head = temp;
}

int LinkedList:: size() const {
   Node *current = head;
   int count = 0;
   while (current != nullptr) {
      current = current->next;
      count++;
   }
   return count;
}
