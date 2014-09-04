#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

int main() {
    string s;

    getline(cin, s);

    istringstream iss(s);
        vector<string> sv;
        string word;
        while(iss >> word)
            sv.push_back(word);
        ostringstream oss;
        for(int i = sv.size() - 1; i >= 0; i--) {
            if(i == 0) {
                oss << sv[i];
                break;
            }
            oss << sv[i] << " ";   
        }
        
        cout << oss.str() << endl;
}
