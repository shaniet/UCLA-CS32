//
//  Previous.h
//  Project1
//
//  Created by Shanie Talor on 6/26/22.
//

#ifndef Previous_h
#define Previous_h
// #include "Arena.hpp"
#include <stdio.h>
#include "globals.h"


class Previous
 {
   public:
     Previous(int nRows, int nCols);
     bool dropACrumb(int r, int c);
     void showPreviousMoves() const;
    private:
        int m_nRows;
        int m_nCols;
        char m_crumbs[MAXROWS][MAXCOLS];
        char key[27] = {'.', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};


 };


#endif /* Previous_h */


// why not dynamically allocate
