#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

vector<int> twoSum(vector<int> &numbers, int target){
        unordered_map<int, int> mapping;
        vector<int> index;
        int len = numbers.size();
        unordered_map<int,int>::iterator iter;

        for(int i = 0; i < len - 1;i++){
            iter = mapping.find(numbers[i]);
            if(iter==mapping.end()){
                mapping[numbers[i]] = i;
            }
            iter = mapping.find(target-numbers[i]);
            if(iter!=mapping.end()){
                index.push_back(i);
                index.push_back(mapping[target-numbers[i]]);
                break;
            }
        }
        return index;
    } 

int main() {
    vector<int> numbers;
    int num, target;
    cin >> target;
    while(cin >> num)
        numbers.push_back(num);

    vector<int> ret = twoSum(numbers, target);
    for(auto p = ret.begin(); p != ret.end(); p++)
        cout << *p << " ";
    cout << endl;
}
