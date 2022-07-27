//
//  WeddingGuest.hpp
//  Project2
//
//  Created by Shanie Talor on 7/7/22.
//

#ifndef WeddingGuest_h
#define WeddingGuest_h
#include <string>


typedef std::string GuestType; // This can change to other types such
                               // as double and int, not just string
 
class WeddingGuest
{
  public:
    WeddingGuest();       // Create an empty WeddingGuest list
    
    WeddingGuest(const WeddingGuest& guest); // Copy constructor

    ~WeddingGuest();      // Destructor

    WeddingGuest& operator=(const WeddingGuest& guest);    // assignment operator

//    void dump() const;    // Print the list of guests

    bool noGuests() const;  // Return true if the WeddingGuest list
                               // is empty, otherwise false.
 
    int guestCount() const;  // Return the number of matches
                                 // on the WeddingGuest list.
 
    bool inviteGuest(const std::string& firstName, const std::string&
               lastName, const GuestType& value);
      // If the full name (both the first and last name) is not equal
      // to any full name currently in the list then add it and return
      // true. Elements should be added according to their last name.
      // Elements with the same last name should be added according to
      // their first names. Otherwise, make no change to the list and
      // return false (indicating that the name is already in the
      // list).
 
    bool alterGuest(const std::string& firstName, const std::string&
lastName, const GuestType & value);
      // If the full name is equal to a full name currently in the
      // list, then make that full name no longer map to the value it
      // currently maps to, but instead map to the value of the third

    // parameter; return true in this case. Otherwise, make no
      // change to the list and return false.
 
    bool inviteOrAlter(const std::string& firstName, const
std::string& lastName, const GuestType& value);
      // If full name is equal to a name currently in the list, then
      // make that full name no longer map to the value it currently
      // maps to, but instead map to the value of the third parameter;
      // return true in this case. If the full name is not equal to
      // any full name currently in the list then add it and return
      // true. In fact, this function always returns true.
 
    bool crossGuestOff(const std::string& firstName, const
std::string& lastName);
      // If the full name is equal to a full name currently in the
      // list, remove the full name and value from the list and return
      // true.  Otherwise, make no change to the list and return
      // false.
 
    bool invitedToTheWedding(const std::string& firstName, const
std::string& lastName) const;
      // Return true if the full name is equal to a full name
      // currently in the list, otherwise false.
 
    bool matchInvitedGuest(const std::string& firstName, const
std::string& lastName, GuestType& value) const;
      // If the full name is equal to a full name currently in the
      // list, set value to the value in the list that that full name
      // maps to, and return true.  Otherwise, make no change to the
      // value parameter of this function and return false.
 
    bool verifyGuestOnTheList(int i, std::string& firstName,
std::string& lastName, GuestType & value) const;
      // If 0 <= i < size(), copy into firstName, lastName and value
      // parameters the corresponding information of the element at
      // position i in the list and return true.  Otherwise, leave the
      // parameters unchanged and return false. (See below for details
      // about this function.)
           
    void swapWeddingGuests(WeddingGuest& other);
      // Exchange the contents of this list with the other one.
private:
    struct Node
        {
          GuestType val;
          std::string firstName;
          std::string lastName;
          Node* next;
          Node* prev;
        };
        Node* head;
        Node* tail;
        int size;
        void addToFront(Node* n);
        void addToBack(Node* n);
        void addToMiddle(Node* n, Node* temp);
        void removeFromFront();
        void removeFromBack();
        void remove(Node* n);
        void initNode(Node* n, const std::string& firstName, const std::string& lastName, const GuestType& value);
};

bool joinGuests(const WeddingGuest & odOne,  const WeddingGuest & odTwo,  WeddingGuest & odJoined);
void attestGuests (const std::string& fsearch,const std::string& lsearch,const WeddingGuest& odOne,WeddingGuest& odResult);
 

#endif /* WeddingGuest_h */
