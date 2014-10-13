#include <iostream>
#include <vector>
using namespace std;

int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int n = gas.size();
    int i = 0, st = 0, sum = 0;
    do {
        if(sum >= 0) {
            sum += gas[i];
            sum -= cost[i];
            i++;
            if(i == n)
                i = 0
        } else {
            st--;
            if(st < 0)
                st += n;
            sum += gas[st];
            sum -= cost[st];
        }
    } while(i != st); 
    if(sum >= 0)
        return st;
    return -1;
}
