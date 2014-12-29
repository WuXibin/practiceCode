#include <iostream>
#include "graph.h"

using namespace std;
using namespace CLRS;

int main() {
    Graph graph;
    int start_num, end_num, weight;

    while(cin >> start_num >> end_num >> weight) {
        graph.InsertEdge(start_num, end_num, weight);
    }
        
    /*
    cin.clear();
    cout << "Enter start point" << endl;
    int startn;
    cin >> startn;
    BFS(graph, startn);
    */
    
    /*
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
    */

    graph.Print();
    if(BellmanFord(graph, 0)) {
        cout << "No negtive cycle" << endl;
    } else {
        cout << "Detect negtive cycle" << endl;
    }

    VertexListNode *list_node = graph.vertex_list_;
    for(; list_node; list_node = list_node->next_) {
        cout << list_node->vertex_->number_ << " : " << list_node->vertex_->distance_ << endl;
    }

    return 0;
}
