#ifndef __GRAPH_H__
#define __GRAPH_H__

namespace CLRS {

class VertexListNode;

enum VertexColor {
    White,
    Gray,
    Black
};

class Vertex {
public:
    Vertex(int num): number_(num), color_(White), distance_(INT_MAX),
        parent_(NULL), discovery_time_(0), finish_time_(0) { 
    }

    int number() const {
        return number_;        
    }
private:
    int number_;

    //BFS
    int distance_;
    VertexColor color_;
    Vertex* parent_; 

    //DFS
    int discovery_time_;
    int finish_time_;
};

class AdjListNode {
public:
    AdjListNode(VertexListNode* vnode): vertex_node_(vnode), next_(NULL) {
    }
    VertexListNode* vertex_node() const {
        return vertex_node_;
    }
private:
    VertexListNode* vertex_node_;
    AdjListNode* next_;
};

class VertexListNode {
public:
    VertexListNode(Vertex* vert): vertex_(vert), adjlist_(NULL), next_(NULL) { 
    }

    AdjListNode* find_adjvertex(int) const;
    Vertex* vertex() const {
        return vertex_;
    }
private:
    Vertex* vertex_;
    AdjListNode* adjlist_;
    VertexListNode* next_; 
};

class Graph {
public:
    Graph(): vertex_list_(NULL) { }
    ~Graph();

    int InsertVertex(int);
    int InsertEdge(int, int);
private:
    VertexListNode* find_vertex(int);
    VertexListNode* vertex_list_;
};

}

#endif
