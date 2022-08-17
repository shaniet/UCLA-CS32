#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include "WordTree.h"



using namespace std;
int main() {
ifstream fin;
ofstream fout;
string filename;
cout << "Enter name of file with text to analyze: ";
cin >> filename;
fin.open(filename.c_str());
if (fin.fail()) {
cout << "Error opening file.\n";
exit(1);
}
cout << "\nAnalyzing " << filename << ".\n";
WordTree myTree;
    WordType v;
    while (fin >> v) {
            WordType v2 = "";
            for (int i = 0; i < v.size(); i++) {
                if (v[i] == '-' && i+1 != v.size() && v[i+1] != '-') {
                    if (v2 != "") {
                        myTree.add(v2);
                    }
                    v2 = "";
                    continue;
                }
                if (isalpha(v[i])) {
                    v2 += tolower(v[i]);
                }
            }
            if (v2 != "") {
            myTree.add(v2);
            }
        }
// insert code here
fin.close();
    fout.open("results.txt");
cout << "\nWord counts:\n\n";
cout << myTree;
fout << myTree;
cout << "\nTotal number of words in text: " << myTree.totalWords() << ".\n";
fout << "\nTotal number of words in text: " << myTree.totalWords() << ".\n";
cout << "Number of distinct words appearing in text: "
 << myTree.distinctWords() << ".\n";
fout << "Number of distinct words appearing in text: "
 << myTree.distinctWords() << ".\n";
fout.close();
return 0;
}
