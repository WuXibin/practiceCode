#include <iostream>
#include "graph.h"

using namespace std;
using namespace CLRS;

int main() {
    Graph graph;
    int start_num, end_num;

    while(cin >> start_num >> end_num) {
        graph.InsertEdge(start_num, end_num);
    }
        
    //cin.clear();
    //cout << "Enter start point" << endl;
    //int startn;
    //cin >> startn;
    //BFS(graph, startn);
    
    list<int> sort_list;
    DFS(graph, sort_list);
    graph.Print();
    list<int>::iterator it = sort_list.begin();
    for(; it != sort_list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    Graph reverse_graph = ReverseGraph(graph);
    ReverseDFS(reverse_graph, sort_list);
    reverse_graph.Print();

    return 0;
}
