//
//  WordTree.hpp
//  HW4
//
//  Created by Shanie Talor on 8/11/22.
//

#ifndef WordTree_h
#define WordTree_h


#include <iostream>
#include <string>
         
typedef std::string WordType;
         
struct WordNode {
   WordType m_data;
   WordNode *m_left;
   WordNode *m_right;
   int m_count;
   WordNode () {
      m_data = "";
      m_left = NULL;
      m_right = NULL;
      m_count = 0;

   }
   WordNode (const WordType& data) {
      m_data = data;
      m_left = NULL;
      m_right = NULL;
      m_count = 1;
   }
};
         
class WordTree {
   private:
      WordNode *root;
    int total = 0;
      void destroy(WordNode *&);
      void copy(WordNode *&, WordNode *);
    void AddTotal();
      int GetTotal() const;
    void inOrder(std::ostream &out,WordNode *&) const;
    int count(WordNode *&curr) const;
    int wordCount(WordType v) const ;
      
   public:
      // default constructor
      WordTree() : root(nullptr) { };
     
      // copy constructor
      WordTree(const WordTree& rhs);
     
      // assignment operator
      const WordTree& operator=(const WordTree& rhs);
 
      // Inserts v into the WordTree
      void add(WordType v);
 
      // Returns the number of distinct words / nodes
      int distinctWords() const;
 
      // Returns the total number of words inserted, including
      // duplicate values
      int totalWords() const;
     
      // Prints the WordTree
      friend std::ostream& operator<<(std::ostream &out, const
WordTree& rhs);
 
      // Destroys all the dynamically allocated memory in the
      // tree
      ~WordTree();
};


#endif /* WordTree_h */
