//
//  recursion.cpp
//  HW2
//
//  Created by Shanie Talor on 7/21/22.
//

#include <iostream>
using namespace std;




int multiplyTwoNumbers(unsigned int m, unsigned int n){
    if(m==0){ // this might not be neccesary but its the most efficient
        return 0;
    }
    if(n== 0){
        return 0;
    }
    else{
        return m+ multiplyTwoNumbers(m,n-1);
    }

}

int tabulationStation(int num, int digit)
{
    if(num == 0){
        if(num%10 == digit)
            return 1;
        else{
            return 0;
        }
    }
    if(num < 0){
        num *= -1;
    }
    
    int count;
       if (num%10==digit){
           count = 1;
       }
       else{
           count = 0;
       }
    count = count +tabulationStation(num/10,digit);
    return count;
   
}

string highFives(string n){
    if(n.size() <=1){
        return n;
    }
    else{
        string result = n.substr(0,1);
        if(n[0] == n[1]){
            result += "55";
        }
        return result + highFives(n.substr(1));
    }

}

string jheriCurls(string str) {
    if(str.size() == 0){
        return "";
    }
    else{
        if (str.substr(0,1) == "{" && str.substr(str.size()-1,1) == "}"){
            return str;
        }
        else if (str.substr(0,1) == "{"){
            return jheriCurls(str.substr(1));
        }
        else if (str.substr(str.size()-1,1) == "}"){
            return jheriCurls(str.substr(0,str.size()-1));
        }
        else{
            return jheriCurls(str.substr(1,str.size()-1));
        }
    }
}




bool aggregationNation(const int a[], int size, int target)
{
    if(size<0){
        return false;
    }
   
    if ( target == 0)
        return true;
    if (size == 0)
        return false;

    bool flag1 = aggregationNation(a+1, size-1, target);
    if (flag1)
        return true;
    bool flag2 = aggregationNation(a+1, size-1, target-a[0]);

    return (flag2);
}

bool onMyWayHome(string maze[], int nRows, int nCols,
                 int sr, int sc, int er, int ec){

    if(sr<0 || sr>=nRows || sc<0 || sc>=nCols || er<0 || er>=nRows || ec<0 || ec>=nCols){
        return false;
    }
    

   if(sr == er && sc == ec){
       return true;
    }
    if(maze[sr][sc] != '.'){
        return false;
    }
    else{
        maze[sr][sc] = '#';

        bool flag1 = onMyWayHome(maze, nRows, nCols, sr+1, sc, er, ec);
        if (flag1) return true;
        bool flag2 = onMyWayHome(maze, nRows, nCols, sr-1, sc, er, ec);
        if (flag2) return true;
        bool flag3 = onMyWayHome(maze, nRows, nCols, sr, sc+1, er, ec);
        if (flag3) return true;
        bool flag4 = onMyWayHome(maze, nRows, nCols, sr, sc-1, er, ec);
        if (flag4) return true;

    }


    return false;

}






#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <csignal>
#include <regex>
#include <type_traits>
#include <set>
#include <iostream>
using namespace std;
void testone(int n)
{
    static string maze1[10] = {
        { "XXXXXXXXXX" },
        { "X.X..X...X" },
        { "X.XX.X.XXX" },
        { "X....X.X.X" },
        { "XX.X.X...X" },
        { "XXX..X.X.X" },
        { "X...X...XX" },
        { "X.XX..X.XX" },
        { "X....X...X" },
        { "XXXXXXXXXX" },
    };
    static string maze2[10] = {
        { "XXXXXXXXXX" },
        { "X.X..X...X" },
        { "X.XX.X.XXX" },
        { "X....X.X.X" },
        { "XX.X.X...X" },
        { "XXX.XX.X.X" },
        { "X...X...XX" },
        { "X.XX..X.XX" },
        { "X....X...X" },
        { "XXXXXXXXXX" },
    };
    static string maze3[10] = {
        { "XXXXXXXXXX" },
        { "XX.....XXX" },
        { "X..XX....X" },
        { "X...X...XX" },
        { "X.X.XXX..X" },
        { "XXXX..X..X" },
        { "XX....X..X" },
        { "X.......XX" },
        { "X..XXXXXXX" },
        { "XXXXXXXXXX" },
    };
    static string maze4[10] = {
        { "XXXXXXXXXX" },
        { "XX.....XXX" },
        { "X..XX....X" },
        { "X...X...XX" },
        { "X.X.XXX..X" },
        { "XXXX..X..X" },
        { "XX....X..X" },
        { "X.....X.XX" },
        { "X..XXXXXXX" },
        { "XXXXXXXXXX" },
    };
    static string maze5[10] = {
        { "XXXXXXXXXX" },
        { "X.X..X...X" },
        { "X.XX.X.XXX" },
        { "X....X.X.X" },
        { "XX.X.X...X" },
        { "XXX.XX.X.X" },
        { "X...X...XX" },
        { "X.XX..X.XX" },
        { "X....X...X" },
        { "XXXXXXXXXX" },
    };
    int a[4] = { 2,  25, -1, 3 };
    int b[3] = { 2,  4,  8 };
    int c[3] = { 1,  2,  3 };
    switch (n)
    {
    default: {
        assert(false);
    } break; case  1: {
        assert(multiplyTwoNumbers(3, 5) == 15);
    } break; case  2: {
        assert(multiplyTwoNumbers(4, 3) == 12);
    } break; case  3: {
        assert(multiplyTwoNumbers(0, 8) == 0);
    } break; case  4: {
        assert(multiplyTwoNumbers(1, 2));
    } break; case  5: {
        assert(tabulationStation(18838, 8) == 3);
    } break; case  6: {
        assert(true);
    } break; case  7: {
        assert(tabulationStation(1234, 5) == 0);
    } break; case  8: {
        assert(tabulationStation(4245, 4) == 2);
    } break; case  9: {
        assert(tabulationStation(1111111, 1) == 7);
    } break; case 10: {
        assert(jheriCurls("abcd{ghj}789") == "{ghj}");
    } break; case 11: {
        assert(jheriCurls("{xxx}789") == "{xxx}");
    } break; case 12: {
        assert(jheriCurls("789{xxx}") == "{xxx}");
    } break; case 13: {
        assert(jheriCurls("{asdf}") == "{asdf}");
    } break; case 14: {
        assert(jheriCurls("a{}a") == "{}");
    } break; case 15: {
        assert(aggregationNation(a, 0, 0));
        assert(!aggregationNation(a, 0, 1));
    } break; case 16: {
        assert(aggregationNation(a, 4, 24));
        assert(!aggregationNation(a, 4, 31));
    } break; case 17: {
        assert(aggregationNation(b, 3, 12));
        assert(!aggregationNation(b, 3, 11));
    } break; case 18: {
        assert(aggregationNation(b, 3, 10));
        assert(aggregationNation(b, 3, 0));
        assert(!aggregationNation(b, 3, 1));
    } break; case 19: {
        assert(aggregationNation(c, 3, 6));
        assert(!aggregationNation(c, 3, 7));
    } break; case 20: {
        assert(aggregationNation(c, 3, 1));
        assert(!aggregationNation(c, 3, 10));
    } break; case 21: {
        assert(highFives("goodbye") == "go55odbye");
    } break; case 22: {
        assert(highFives("nothinghere") == "nothinghere");
    } break; case 23: {
        assert(highFives("yyasdf") == "y55yasdf");
    } break; case 24: {
        assert(highFives("axxyya") == "ax55xy55ya");
    } break; case 25: {
        assert(highFives("aaa") == "a55a55a");
    } break; case 26: {
        assert(onMyWayHome(maze1, 10, 10, 8, 6, 1, 1));
    } break; case 27: {
        assert(!onMyWayHome(maze2, 10, 10, 8, 6, 1, 1));
    } break; case 28: {
        assert(onMyWayHome(maze5, 10, 10, 8, 6, 1, 8));
    } break; case 29: {
        assert(onMyWayHome(maze3, 10, 10, 4, 3, 7, 1));
    } break; case 30: {
        assert(!onMyWayHome(maze4, 10, 10, 4, 3, 7, 1));
    }
    }
}
int main()
{
for (int n = 1; n <= 30; n++) {
testone(n);
cout << n << " passed" << endl;
}
return 0;
}
