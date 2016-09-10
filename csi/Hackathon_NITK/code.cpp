#include <bits/stdc++.h>

using namespace std;

struct data{
    string company,name;
    int number;
}adam[100],rajat[100],ben[100];

int main() {
    ifstream in;
    int i;

    in.open("Adams_phone_book_1001.csv");
//    in[1].open("Bens_phone_book_1002.csv");
//    in[2].open("Rajats_phone_book_1030.csv");

//    for(i=0;i<3;i++)
        if(!in.is_open()){
            cerr << "failed to open file.";
            return 1; 
        }

    string line;

    while(std::getline(in,line)) {
        cout<<line;
    }
    std::getline(in,line);
    in.close();
}  
