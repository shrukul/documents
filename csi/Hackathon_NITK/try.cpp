#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
int main(){
    int i;
    ifstream infile("Adams_phone_book_1001.csv"); // for example
    string line = "";
    int delim;
    int old;
    string name[100],num[100],comp[100];
    int count=0;
    int MAX = 25;

    while (getline(infile, line)){
        stringstream strstr(line);
        string word = "";

        while (getline(strstr,word, ';'))
         {
             count++;
             name[count] = word.substr(0, word.find(","));
             delim = word.find(",");
             word[delim] = 's';
             old=delim;
             delim = word.find(",");
             num[count] = word.substr(old + 1, delim-old-1);
             word[delim] = 's';
             old=delim;
             delim = word.find(",");
             comp[count] = word.substr(old + 1, delim-old-1);
//             cout << comp[count];
//             cout<<"\n";
         }
           cout<<word;
    }
   for(i=0;i<MAX;i++)
    cout<<name[i] << "\t\t" << num[i] << "\t\t" << comp[i] << "\n";
}
