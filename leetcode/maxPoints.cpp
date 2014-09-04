#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

typedef struct Point {
    int x;
    int y;
    Point(int a = 0, int b = 0): x(a), y(b) {}
} Point;

int maxPoints(vector<Point> &points) {
    int ans = 0;
    for(int i = 0; i < points.size(); i++) {
        int x = points[i].x;
        int y = points[i].y;
        map<double, int> count;
        int dup = 0;
        for(int j = 0; j < points.size(); j++) {
            int x1 = points[j].x;
            int y1 = points[j].y;
            
            if(x == x1 && y == y1)
                dup++;
            else if(x == x1)
                count[INT_MAX]++;
            else {
                double k = (y - y1) / (x - x1);
                count[k]++;
            }
        }

        if(dup > ans)
            ans = dup;

        for(map<double, int>::iterator it = count.begin(); it != count.end(); it++) {
            if(it->second + dup > ans)
               ans = it->second + dup; 
        }
    }     

    return ans;
}

int main() {
    vector<Point> points;
    int x, y;
    while(cin >> x >> y) 
        points.push_back(Point(x, y));
    cout << maxPoints(points) << endl;
    return 0;
}
