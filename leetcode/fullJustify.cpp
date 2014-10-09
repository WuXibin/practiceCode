#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> fullJustify(vector<string> &words, int L) {
    vector<string> ans;
    int sz = words.size();
    int wc = 0, wl = 0;
    for(int i = 0; i < sz; i++) {
        int ws = words[i].size();
        if(wl + ws + wc > L) {
            if(wc == 1) {
                string t = words[i-1] + string(L-wl, ' ');
                ans.push_back(t);
            } else {
                string t;
                int spaces = L-wl, slots = wc - 1;
                int pads = spaces / slots, cnt = spaces % slots;
                for(int j = i - wc, k = 0; j < i; j++, k++) {
                    if(!k) 
                        t = words[j];
                    else {
                        if(k <= cnt)
                            t += string(pads+1, ' '); 
                        else
                            t += string(pads, ' ');
                        t += words[j];
                    }
                }
                ans.push_back(t);
            } 
            wc = 1;
            wl = ws;
        } else {
            wc++;
            wl += ws;
        } 
    }
    if(!wc)
        return ans;

    string t = words[sz-wc];
    for(int j = sz-wc+1; j < sz; j++) 
        t += " " + words[j]; 

    t += string(L-wl-wc+1, ' ');
    ans.push_back(t);

    return ans;
}

int main() {
    int L;
    cin >> L;

    vector<string> words;
    string word(0, ' ');

    while(cin >> word)
        words.push_back(word);

    vector<string> res = fullJustify(words, L);

    for(auto p = res.begin(); p != res.end(); p++)
        cout << *p << endl;
    return 0;
}
