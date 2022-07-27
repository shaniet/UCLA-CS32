//
//  Previous.cpp
//  Project1
//
//  Created by Shanie Talor on 6/26/22.
//

#include "Previous.h"
#include <iostream>
#include <string>

Previous::Previous(int nRows, int nCols)
{
    m_nRows = nRows;
    m_nCols = nCols;
    for (int r = 0; r < m_nRows; r++){
        for (int c = 0; c < m_nCols; c++){
            m_crumbs[r][c] = '.';
        }
    }
    

}

bool Previous ::  dropACrumb(int r, int c){
    if (r < 1 || r > m_nRows || c < 1 || c > m_nCols)
        return false;
    for (int i = 0; i < 26 ; i++){
        if(m_crumbs[r-1][c-1] == key[i]){
            m_crumbs[r-1][c-1] = key[i+1];
            return true;
        }
    }
    return true;

}

void Previous::  showPreviousMoves() const{
    clearScreen();
    for (int r = 0; r < m_nRows; r++){
        for (int c = 0; c < m_nCols; c++){
            std:: cout << m_crumbs[r][c];
        }
    std:: cout << std:: endl;
    }
    std:: cout << std:: endl;

}



