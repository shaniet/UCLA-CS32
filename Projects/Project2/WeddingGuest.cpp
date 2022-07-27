//
//  WeddingGuest.cpp
//  Project2
//
//  Created by Shanie Talor on 7/7/22.
//
//join guest test for aliasing (make sure inputs are not od 1 and od 1)
//follow up to this topic, what would happen if odjoined wasnt empty? do we just add to it or do we need to clear it
    //Clear it and overwrite it
//include if there is name in one and not the either
//create a local for what will be od joined(make it one of the two list)odjoined and end assign oddjoin the final result
#include "WeddingGuest.h"


WeddingGuest::WeddingGuest()
{
  head = nullptr;
  tail = nullptr;
  size = 0;// check if this is necessary
}
WeddingGuest:: WeddingGuest(const WeddingGuest& guest)
{
  if(guest.head  == nullptr){
    head = nullptr;
    tail = nullptr;
    size =0;
    return;
  }
  else{
    size = guest.size;
    Node *curr = guest.head;
    Node *temp = new Node;
    head = temp;
    Node * previous = nullptr;
    while(curr != nullptr){
      temp->firstName = curr->firstName;
      temp->lastName = curr->lastName;
      temp->val = curr->val;
      temp -> prev = previous;
      curr = curr->next;
    previous = temp;
      if(curr != nullptr){
        temp->next = new Node;
        temp = temp->next;
      }
      else{
          temp-> next = nullptr;
          tail = temp;
      }
     
    }
      
  }

}
//assignment operator
WeddingGuest& WeddingGuest:: operator = (const WeddingGuest & guest){
  if(this == &guest){
    return *this;
  }
  size = guest.size;
  WeddingGuest tempList = guest;
  swapWeddingGuests(tempList);
  return *this;

}

WeddingGuest:: ~WeddingGuest(){
    Node* curr = head;
    while (curr != nullptr){
        Node * temp = curr-> next;
        delete curr;
        curr = temp;
    }
    
}

bool WeddingGuest:: noGuests() const
{
  if(head == nullptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int WeddingGuest::guestCount() const
{
  return size;
}

bool WeddingGuest:: inviteGuest(const std::string& firstName, const std::string& lastName, const GuestType& value)
{
    if (invitedToTheWedding(firstName, lastName))
    {
        return false;
    }
    else{
        if (head == nullptr){
            Node* n = new Node;
            initNode(n, firstName, lastName, value);
            addToFront(n);
            return true;
        }
        else{
            Node* n = new Node;
            initNode(n, firstName, lastName, value);

            Node *temp = head; //traversal with just head
          

            while(temp != nullptr){
                
                if((temp-> lastName) == (n->lastName)){ //last names are the same
                    if (temp -> prev == nullptr && temp->firstName > n->firstName){ // if you are adding to the front of the list
                        addToFront(n);
                        return true;
                    }
                    else if(temp -> next == nullptr && temp->firstName < n->firstName){ // if you are adding to the back of the list
                        addToBack(n);
                        return true;
                    }
                    
                    else if(temp->firstName > n->firstName){ // if you are adding to the middle of the list
                        addToMiddle(n, temp);
                        return true;
                    }
                    else{
                        temp = temp-> next; // go to next node and skip the conditions below
                        continue;
                    }
                }
                else if (temp -> prev == nullptr && temp -> lastName > n-> lastName){ // if you are adding to the front of list
                    addToFront(n);
                    return true;
                }
                else if(temp-> next == nullptr && temp-> lastName < n->lastName ){ // if you are adding to the back of the list
                    addToBack(n);
                    return true;
                }
                else if(temp-> lastName > n->lastName){ // if you are adding to the middle of the list
                    addToMiddle(n, temp);
                    
                    return true;

                }
               

                else {
                    temp = temp->next; // go to next node
                }
            }
           
        }
       
    
        
    }

    return true;
    
}

bool WeddingGuest:: alterGuest(const std::string& firstName, const std::string& lastName, const GuestType& value)
{
    if(!invitedToTheWedding(firstName, lastName))
    {
        return false;
    }
    else
    {
        Node* h = head;
        Node* t = tail;
        while(h != nullptr || t != nullptr)
        {
            if(h->firstName == firstName && h->lastName == lastName)
            {
                h->val = value;
                return true;
            }
            else if(t->firstName == firstName && t->lastName == lastName)
            {
                t->val = value;
                return true;
            }
            else
            {
                h = h->next;
                t = t->prev;
            }
        }
    }
    return false;
}

bool WeddingGuest:: inviteOrAlter(const std::string& firstName, const std::string& lastName, const GuestType& value){
    if(invitedToTheWedding(firstName, lastName))
    {
        alterGuest(firstName, lastName, value);
        return true;
    }
    else
    {
        inviteGuest(firstName, lastName, value);
        return true;
    }
}

bool WeddingGuest:: crossGuestOff(const std::string& firstName, const std::string& lastName)
{
    if(!invitedToTheWedding(firstName, lastName))
    {
        return false;
    }
    else
    {
        Node * h = head;
        Node * t = tail;
        while(h != nullptr || t != nullptr)
        {
            if(h->firstName == firstName && h->lastName == lastName)
            {
                remove(h);
                return true;
            }
            else if(t->firstName == firstName && t->lastName == lastName)
            {
                remove(t);
                return true;
            }
            else
            {
                h = h->next;
                t = t->prev;
            }
        }
    }
    return false;
}

bool WeddingGuest:: invitedToTheWedding(const std::string& firstName, const std::string& lastName) const
{
    if(head == nullptr)
    {
        return false;
    }
    else
    {
        Node* h = head;
        Node* t = tail;
        while(h != nullptr || t != nullptr) 
        {
            if(h->firstName == firstName && h->lastName == lastName)
            {
                return true;
            }
            else if(t->firstName == firstName && t->lastName == lastName)
            {
                return true;
            }
            else if(h-> next == t||h == t ||t-> prev == h){
                break;
            }
            else
            {
                h = h->next;
                t = t->prev;
            }
        }
    }
    return false;
}

bool WeddingGuest:: matchInvitedGuest(const std::string& firstName, const std::string& lastName, GuestType& value) const
{
    if(!invitedToTheWedding(firstName, lastName))
    {
        return false;
    }
    else
    {
        Node* h = head;
        Node* t = tail;
        while(h != nullptr || t != nullptr)
        {
            if(h->firstName == firstName && h->lastName == lastName)
            {
                value = h->val;
                return true;
            }
            else if(t->firstName == firstName && t->lastName == lastName)
            {
                value = t->val;
                return true;
            }
            else
            {
                h = h->next;
                t = t->prev;
            }
        }
    }
    return false;
}

bool WeddingGuest::verifyGuestOnTheList(int i, std::string& firstName, std::string& lastName, GuestType & value) const{
    if (i < 0 || i > size-1)
    {
        return false;
    }
    else
    {
       Node * h = head;
       Node * t = tail;
       int start = 0;
       int end = size-1;
       while( h != nullptr || t != nullptr)
       {
           if(start == i){
                firstName = h->firstName;
                lastName = h->lastName;
                value = h->val;
                return true;
              }
              else if(end == i){
                firstName = t->firstName;
                lastName = t->lastName;
                value = t->val;
                return true;
              }
              else
              {
                h = h->next;
                t = t->prev;
                start++;
                end--;
           }


        }
    
    }
    return false;
}

void WeddingGuest:: swapWeddingGuests(WeddingGuest& other){
    if(this == &other){
        return;
    }
    else{
        Node * tempHead = head;
        Node* tempTail = tail;
        head = other.head;
        tail = other.tail;
        other.head = tempHead;
        other.tail = tempTail;
        int temp2 = size;
        size = other.size;
        other.size = temp2;
    }

}

bool joinGuests(const WeddingGuest & odOne,  const WeddingGuest & odTwo,  WeddingGuest & odJoined){
  if(odOne.noGuests() && !odTwo.noGuests()){
    odJoined = odTwo;
    return true;
  }
  if(!odOne.noGuests() && odTwo.noGuests()){
    odJoined = odOne;
    return true;
  }
  if(odOne.noGuests() && odTwo.noGuests()){
    odJoined = odOne;
      return true;
  }
    WeddingGuest result;
  result = odOne;
    bool check = true;

    for (int i = 0; i < odTwo.guestCount(); i++) {
        std::string firstName;
        std::string lastName;
        GuestType value;
        GuestType value2;
        odTwo.verifyGuestOnTheList(i, firstName, lastName, value);
        if(result.invitedToTheWedding(firstName,lastName)){
            odOne.matchInvitedGuest(firstName,lastName, value2);
            if(value != value2){
                result.crossGuestOff(firstName,lastName);
                check = false;
                continue;
            }
            else{continue;}
        }
        else
        result.inviteGuest(firstName,lastName, value);
        
    }
  odJoined = result;
    if (check == false){
        return false;}
  return true;
}

void attestGuests (const std::string& fsearch,const std::string& lsearch,const WeddingGuest& odOne,WeddingGuest& odResult){
    WeddingGuest result;
    if (fsearch == "*" && lsearch == "*"){
        odResult = odOne;
        return;
    }
    for (int i = 0; i < odOne.guestCount(); i++) {
        std::string firstName;
        std::string lastName;
        GuestType value;
        odOne.verifyGuestOnTheList(i, firstName, lastName, value);
        
        if(lsearch == "*" && firstName == fsearch){
            result.inviteGuest(firstName,lastName, value);
            continue;
        }
        else if(fsearch == "*" && lastName == lsearch){
            result.inviteGuest(firstName,lastName, value);
            continue;
        }
        
       else if(firstName == fsearch && lastName == lsearch){
            result.inviteGuest(firstName,lastName, value);
           continue;
        }
    }
    odResult = result;

}

// helper functions below

//void WeddingGuest:: dump() const{
//    Node* curr = head;
//    while (curr != nullptr){
//        cout << curr->firstName << " " << curr->lastName << " " << curr->val << endl;
//        curr = curr->next;
//    }
//}


void WeddingGuest::addToFront(Node* n)
{
  if(head == nullptr)
  {
    head = n;
    tail = n;
  }
  else
  {
    n->next = head;
    head->prev = n;
    head = n;
  }
  size++;
}


void WeddingGuest::addToBack(Node* n)
{
  if(tail == nullptr)
  {
    head = n;
    tail = n;
  }
  else
  {
    tail->next = n;
      n->prev = tail;
    tail = n;
  }
  size++;
}

void WeddingGuest:: addToMiddle(Node* n, Node* temp){
    n->next = temp;
    n-> prev = temp -> prev;
    temp->prev-> next = n;
    temp->prev = n;
    size ++;
}

void WeddingGuest::removeFromFront(){
  if(head == nullptr)
  {
    return;
  }
  else if(head == tail)
  {
    head = nullptr;
    tail = nullptr;
  }
    else
    {
        head = head->next;
        head->prev = nullptr;
    }
    
}

void WeddingGuest::removeFromBack()
{
  if(tail == nullptr)
  {
    return;
  }
  else if(head == tail)
  {
    head = nullptr;
    tail = nullptr;
  }
    else
    {
        tail = tail->prev;
        tail->next = nullptr;
    }
    
}

void WeddingGuest::remove(Node* n)
{
  if(n == head)
  {
    removeFromFront();
  }
  else if(n == tail)
  {
    removeFromBack();

  }
  else
  {
    n->prev->next = n->next;
    n->next->prev = n->prev;
      delete n;

  }
    size --;
  
}

void WeddingGuest::initNode(Node* n, const std::string& firstName, const std::string& lastName, const GuestType& value)
{
  n->firstName = firstName;
  n->lastName = lastName;
  n->val = value;
    n-> next = nullptr;
    n-> prev = nullptr;

}
