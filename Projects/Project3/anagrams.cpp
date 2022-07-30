
#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
using namespace std;
const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

//create a recursive helper function to check that dict is not greater than maxdictwords

int addToDict(istream &dictFile, int maxDictWords, string dict[])
{
    // base case to check if the dict has reached max capacity
    if (maxDictWords <= 0)
    {
        return 0;
    }
    else
    {   // read in a word from the dictFile
        string word;
        if(!getline(dictFile, word))
        {
            return 0;
        }
        // add the word to the dict
        else
        {
            dict[0] = word;
            // keep track of the number of words added to the dict
            return 1 + addToDict(dictFile, maxDictWords - 1, dict + 1);
        }
    }
}

int lexiconBuilder(istream &dictfile, string dict[]){
    
    int max = MAXDICTWORDS; // create a copy so we don't change a global const
    return addToDict(dictfile, max, dict);

}

// hi shanie <3

//insertPerm();
void getPermutations(string prefix,string rest, const string dict[], int dictSize, string results[], int &count);
bool Loop( string prefix, string rest, const string dict[], int dictSize, string results[], int &count,int i);
int insertPerm(string prefix, const string dict[], int dictSize , string results[],  int &count );
bool isDuplicate(string prefix, string results[], int i, int count);


int theJumbler(string word, const string dict[], int dictSize,
string results[]){
    int count = 0;
    
       
        getPermutations(word.substr(0,0), word.substr(0), dict, dictSize, results, count);
//    getPermutations("", word, dict, dictSize, results, count);
    
    
    return count;
}

// function to loop through every letter of word
bool Loop( string prefix, string rest, const string dict[], int dictSize, string results[], int &count,int i){
    // base case for loop to check if we have reached the end of the string
    if(i >= rest.size()){
        return true;
    }
    else{
        //loop through the string excluding the current index
        getPermutations( prefix + rest[i], rest.substr(0, i) + rest.substr(i+1),  dict, dictSize,results, count);
       // increment the index
        Loop(prefix, rest, dict, dictSize, results, count, i+1);
    }
    return true;
}

void getPermutations(string prefix,string rest, const string dict[], int dictSize, string results[], int &count){
    
  
    if(rest.size() <= 0){
        if(count >0 && count>= MAXRESULTS){
            return;
        }

        count += insertPerm(prefix, dict, dictSize, results, count);
//
        
    }
    
    else{
        Loop( prefix, rest, dict, dictSize,results, count, 0);
    }
        
    
}

int insertPerm(string prefix, const string dict[], int dictSize , string results[],  int &count ){
    if(dictSize == 0){
        return 0;
    }
    else{
        if(prefix == dict[0]){
        
            if(isDuplicate(prefix, results, 0, count)){
                return 0;
            }
            else{
                results[count] = prefix;
                return 1;
            }
        }
        else{
            return insertPerm(prefix, dict+1, dictSize-1, results, count);
        }
    }
}

bool isDuplicate(string prefix, string results[], int i, int count){
    if(i >= count ){
        return false;
    }
    if(results[i] == prefix){
        return true;
    }
    else{
        return isDuplicate(prefix, results+1, i+1, count);
    }
}
void divulgeSolutions(const string results[], int size){
    if(size == 0){
        return;
    }
    else{
        cout<< results[0]<< " "<< endl;
        divulgeSolutions(results+1, size-1);
    }
}


int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    dictfile.open("/Users/shanietalor/Desktop/CS 32/Project3/words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
    nwords = lexiconBuilder(dictfile, dict);
    
    cout << "Please enter a string for an anagram: ";
    cin >> word;
    int numMatches = theJumbler(word, dict, nwords, results);
    if (!numMatches) {
        cout << "No matches found" << endl;
}
    else {
        divulgeSolutions(results, numMatches);
}
return 0;
}
