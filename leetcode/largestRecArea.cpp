#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int largestRectangleArea(vector<int> &height) {
    int ans = 0;

    stack<int> st;
    int n = height.size();
    for(int i = 0; i < n; i++) {
        if(st.empty() || height[i] >= height[st.top()])
            st.push(i);
        else {
            int hgt = height[st.top()];
            st.pop();
            int width = st.empty() ? i : (i - st.top() - 1);
            ans = max(ans, hgt * width);
            i--;
        }    
    }
    while(!st.empty()) {
        int hgt = height[st.top()];
        st.pop();
        int width = st.empty() ? n : n - st.top() - 1;
        ans = max(ans, hgt * width);
    }
    return ans;
}

int main() {
    int n;
    vector<int> height;
    while(cin >> n)
        height.push_back(n);
    cout << largestRectangleArea(height) << endl;
    return 0;
}
