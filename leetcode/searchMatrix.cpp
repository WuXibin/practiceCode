#include <iostream>
#include <vector>
using namespace std;

bool searchMatrix(vector<vector<int> > &matrix, int target) {
    int m = matrix.size();
    if(!m)
        return false;
    int n = matrix[0].size();
    
    int l = 0, u = m - 1, mid;
    while(l <= u) {
        mid = (l + u) / 2;
        if(matrix[mid][0] == target)
            return true;
        else if(matrix[mid][0] < target)
            l = mid + 1;
        else
            u = mid - 1;
    }
    int x;
    if(l == m || matrix[l][0] > target)
        x = u;
    else 
        x = l;

    int b = 0, e = n - 1;
    while(b <= e) {
        int mid = (b + e) / 2;
        if(matrix[x][mid] == target)
            return true;
        else if(matrix[x][mid] < target)
            b = mid + 1;
        else
            e = mid - 1;
    }
    return false;
}
