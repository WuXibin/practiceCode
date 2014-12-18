#include "graph.h"

namespace CLRS {

AdjListNode* VertexListNode::find_adjvertex(int num) const {
    AdjListNode* adj_ptr = adjlist_;
    while(adj_ptr) {
        if(adj_ptr->vertex_node()->vertex()->number() == num)  
            break;
    }
    return adj_ptr;
}
VertexListNode* Graph::find_vertex(int num) {
    VertexListNode* v_ptr = vertex_list_;
    while(v_ptr) {
        if(v_ptr->vertex()->number() == num)
            break;
    }
    return v_ptr;
}

Graph::~Graph() {
    VertexListNode* v_ptr = vertex_list_;
    
}

int Graph::InsertVertex(int num) {
    if(find_vertex(num) != NULL)
        return 0;

    Vertex* vert = new Vertex(num);
    VertexListNode* vlistnode = new VertexListNode(vert);
    vlistnode->next_ = vertex_list_;
    vertex_list_ = vlistnode; 
    return 0;
}

int Graph::InsertEdge(int startno, int endno) {
    VertexListNode* v_start = find_vertex(startno);
    if(v_start == NULL)
        InsertVertex(startno);
    VertexListNode* v_end = find_vertex(endno);
    if(v_end == NULL)
        InsertVertex(endno);

    //edge already exist
    if(v_start.find_adjvertex() != NULL)
        return 0;

    AdjListNode* listnode = new AdjListNode(v_end);
    listnode->next_ = v_start->adjlist_;
    v_start->adjlist_ = listnode;

    return 0;
}

};
