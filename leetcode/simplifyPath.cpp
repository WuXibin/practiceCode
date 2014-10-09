#include <iostream>
#include <string>
#include <stack>
using namespace std;

string simplifyPath(string path) {
    stack<string> ans;
    string paths = path + '/';
    int sz = paths.size();
    string name = "/";
    for(int i = 0; i < sz; i++) {
        if(paths[i] == '/') {
            if(name == "/") 
                continue;
            else if(name == "/.")
                name = "/";
            else if(name == "/..") {
                if(!ans.empty())
                    ans.pop();
                name = "/";
            } else {
                ans.push(name);
                name = "/";
            }
        } else
            name += paths[i];
    }
    if(ans.empty())
        ans.push(name);
    string res;
    while(!ans.empty()) {
        res = ans.top() + res;
        ans.pop();
    }
    return res;
}

int main() {
    string path;
    while(cin >> path) 
        cout << simplifyPath(path) << endl;
    return 0;
}
