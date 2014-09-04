#include <iostream>
#include <stack>
#include <cstdlib>
#include <vector>
#include <sstream>
using namespace std;
int evalRPN(vector<string> &tokens) {
        stack<string> expr;
        string lval, rval;
        for(vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
                if(*it == "+") {
                    rval = expr.top();
                    expr.pop();
                    lval = expr.top();
                    expr.pop();
                    int ires = atoi(lval.c_str()) + atoi(rval.c_str());
                    stringstream ss;
                    ss << ires;
                    expr.push(ss.str());
                } else if(*it == "-") {
                    rval = expr.top();
                    expr.pop();
                    lval = expr.top();
                    expr.pop();
                    int ires = atoi(lval.c_str()) - atoi(rval.c_str());
                    stringstream ss;
                    ss << ires;
                    expr.push(ss.str());
                } else if(*it == "*") {
                    rval = expr.top();
                    expr.pop();
                    lval = expr.top();
                    expr.pop();
                    int ires = atoi(lval.c_str()) * atoi(rval.c_str());
                    stringstream ss;
                    ss << ires;
                    expr.push(ss.str());
                } else if(*it == "/") {
                    rval = expr.top();
                    expr.pop();
                    lval = expr.top();
                    expr.pop();
                    int ires = atoi(lval.c_str()) / atoi(rval.c_str());
                    stringstream ss;
                    ss << ires;
                    expr.push(ss.str());
                } else 
                    expr.push(*it);
        }
        return atoi(expr.top().c_str());
}

int main() {
    vector<string> tokens;
    string token;
    while(cin >> token) {
        cout << token << endl;
        tokens.push_back(token);
    }
    cout << evalRPN(tokens) << endl;
    return 0;
}
