#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <limits.h>
#include <list>

namespace CLRS {

static const int kMaxDistance = 1000;

struct VertexListNode;
class Graph;

int BFS(Graph&);
int DFS(Graph&, std::list<int>&);
int DFSVisit(Graph&, VertexListNode*, std::list<int>&);
Graph ReverseGraph(Graph&);
int ReverseDFS(Graph&, std::list<int>&);
int ReverseDFSVisit(Graph&, VertexListNode*);
bool BellmanFord(Graph&, int);
int InitSingleSource(Graph&, int);
void Relax(VertexListNode*, VertexListNode*, int);

enum VertexColor {
    White,
    Gray,
    Black
};

struct Vertex {
    Vertex(int num): number_(num), distance_(INT_MAX), color_(White), 
        parent_(NULL), discovery_time_(0), finish_time_(0) { 
    }

    int number() const {
        return number_;        
    }

    int number_;

    //BFS
    int distance_;
    VertexColor color_;
    Vertex* parent_; 

    //DFS
    int discovery_time_;
    int finish_time_;
};

struct AdjListNode {
    AdjListNode(int weight, VertexListNode* vnode): 
        weight_(weight), vertex_node_(vnode), next_(NULL) {}
    VertexListNode* vertex_node() const {
        return vertex_node_;
    }

    int weight_;
    VertexListNode* vertex_node_;
    AdjListNode* next_;
};

struct VertexListNode {
    VertexListNode(Vertex* vert): vertex_(vert), adjlist_(NULL), next_(NULL) { 
    }

    AdjListNode* find_adjvertex(int) const;
    Vertex* vertex() const {
        return vertex_;
    }

    Vertex* vertex_;
    AdjListNode* adjlist_;
    VertexListNode* next_; 
};

class Graph {
public:
    Graph(): vertex_list_(NULL) { }
    ~Graph();

    void Print() const;

    VertexListNode* InsertVertex(int);
    int InsertEdge(int, int, int);

    friend int BFS(Graph&, int);
    friend int DFS(Graph&, std::list<int>&);
    friend int DFSVisit(Graph&, VertexListNode*, std::list<int>&);
    friend Graph ReverseGraph(Graph&);
    friend int ReverseDFS(Graph&, std::list<int>&);
    friend int ReverseDFSVisit(Graph&, VertexListNode*);
    friend bool BellmanFord(Graph&, int);

    VertexListNode* find_vertex(int);
    VertexListNode* vertex_list_;
};


}

#endif
