#include <iostream>
#include <queue>
#include <assert.h>
#include "graph.h"

namespace CLRS {

int gTime = 0;

AdjListNode* VertexListNode::find_adjvertex(int num) const {
    AdjListNode* adj_ptr = adjlist_;
    while(adj_ptr) {
        if(adj_ptr->vertex_node()->vertex()->number() == num)  
            break;
        adj_ptr = adj_ptr->next_;
    }
    return adj_ptr;
}

VertexListNode* Graph::find_vertex(int num) {
    VertexListNode* v_ptr = vertex_list_;
    while(v_ptr) {
        if(v_ptr->vertex()->number() == num)
            break;
        v_ptr = v_ptr->next_;
    }
    return v_ptr;
}

Graph::~Graph() {
    VertexListNode* list_ptr = vertex_list_;
    while(list_ptr) {
        VertexListNode* tmp_ptr = list_ptr;
        list_ptr = list_ptr->next_;
        
        AdjListNode* adj_ptr = tmp_ptr->adjlist_;
        while(adj_ptr) {
            AdjListNode* tmp_adj_ptr = adj_ptr;
            adj_ptr = adj_ptr->next_;
            delete tmp_adj_ptr;
        }
        delete tmp_ptr;
    } 
}

VertexListNode* Graph::InsertVertex(int num) {
    VertexListNode* vertex = find_vertex(num);
    if(vertex != NULL) {
        //std::cout << num << " already exist !" << std::endl;
        return vertex;
    }

    //std::cout << "Insert vertex " << num << std::endl;
    Vertex* vert = new Vertex(num);
    vertex = new VertexListNode(vert);
    vertex->next_ = vertex_list_;
    vertex_list_ = vertex; 
    return vertex;
}

int Graph::InsertEdge(int startno, int endno, int weight) {
    VertexListNode *vertex_start = InsertVertex(startno);
    VertexListNode* vertex_end = InsertVertex(endno);

    //edge already exist
    if(vertex_start->find_adjvertex(endno) != NULL)
        return 0;

    AdjListNode* listnode = new AdjListNode(weight, vertex_end);
    listnode->next_ = vertex_start->adjlist_;
    vertex_start->adjlist_ = listnode;

    return 0;
}

void Graph::Print() const {
    std::cout << "Print Graph: " << std::endl;
    VertexListNode* vertex = vertex_list_;
    while(vertex) {
        AdjListNode* adj = vertex->adjlist_;
        std::cout << "[" << vertex->vertex_->number_ << "]"; 
        while(adj) {
            assert(adj->vertex_node_ != NULL);
            std::cout << adj->vertex_node_->vertex_->number() << ":" << adj->weight_ << std::endl;
            adj = adj->next_;
        }
        std:: cout << std::endl;
        vertex = vertex->next_;
    }
}

int BFS(Graph& graph, int startn) {
    VertexListNode* startv = graph.find_vertex(startn);
    if(startv == NULL) {
        std::cerr << startn << " not exist!" << std::endl;
        return -1;
    } 

    startv->vertex_->color_ = Gray;
    startv->vertex_->distance_ = 0;
    startv->vertex_->parent_ = NULL;

    std::queue<VertexListNode*> gray_vertex;
    gray_vertex.push(startv);
    while(!gray_vertex.empty()) {
        VertexListNode* vertex = gray_vertex.front();
        gray_vertex.pop();
        AdjListNode* adj = vertex->adjlist_;
        int dist = vertex->vertex_->distance_;
        while(adj) {
            if(adj->vertex_node_->vertex_->color_ == White) {
                adj->vertex_node_->vertex_->color_ = Gray;
                adj->vertex_node_->vertex_->distance_ = dist + 1;
                adj->vertex_node_->vertex_->parent_ = vertex->vertex_;
                gray_vertex.push(adj->vertex_node_);
            }

            adj = adj->next_;
        }
        vertex->vertex_->color_ = Black;
    }

    return 0;
}

int DFS(Graph& graph, std::list<int>& sort_list) {
    VertexListNode* vnode = graph.vertex_list_;
    while(vnode) {
        if(vnode->vertex_->color_ == White) 
            DFSVisit(graph, vnode, sort_list);
        vnode = vnode->next_;
    }  

    return 0;
}

int DFSVisit(Graph& graph, VertexListNode* vnode, 
        std::list<int>& sort_list) { 
    vnode->vertex_->color_ = Gray;
    vnode->vertex_->discovery_time_ = gTime++;

    AdjListNode* anode = vnode->adjlist_;
    while(anode) {
        VertexListNode* vert = anode->vertex_node_;
        if(vert->vertex_->color_ == White) {
            vert->vertex_->parent_ = vnode->vertex_; 
            DFSVisit(graph, vert, sort_list);
        }
        anode = anode->next_;
    }    

    vnode->vertex_->color_ = Black;
    vnode->vertex_->finish_time_ = gTime++;
    sort_list.push_back(vnode->vertex_->number_);
    return 0;
}

Graph ReverseGraph(Graph& graph) {
    Graph reverse_graph;
    VertexListNode* vertex = graph.vertex_list_;
    while(vertex) {
        int start_num = vertex->vertex_->number_;
        AdjListNode* adj = vertex->adjlist_;
        while(adj) {
            assert(adj->vertex_node_ != NULL);
            int end_num = adj->vertex_node_->vertex_->number_;
            reverse_graph.InsertEdge(end_num, start_num, adj->weight_);
            adj = adj->next_;
        }
        vertex = vertex->next_;
    }    
    return reverse_graph;
}

int ReverseDFS(Graph& graph, std::list<int>& sort_list) {
    std::list<int>::reverse_iterator it = sort_list.rbegin();
    for(; it != sort_list.rend(); it++) {
        VertexListNode* vertex = graph.find_vertex(*it);
        if(vertex->vertex_->color_ == White) {
            std::cout << "----------" << std::endl;
            ReverseDFSVisit(graph, vertex);
            std::cout << "----------" << std::endl;
        }
    }
        
    return 0;   
}

int ReverseDFSVisit(Graph& graph, VertexListNode* vnode) {
    vnode->vertex_->color_ = Gray;
    vnode->vertex_->discovery_time_ = gTime++;

    AdjListNode* anode = vnode->adjlist_;
    while(anode) {
        VertexListNode* vert = anode->vertex_node_;
        if(vert->vertex_->color_ == White) {
            vert->vertex_->parent_ = vnode->vertex_; 
            ReverseDFSVisit(graph, vert);
        }
        anode = anode->next_;
    }    

    vnode->vertex_->color_ = Black;
    vnode->vertex_->finish_time_ = gTime++;

    std::cout << vnode->vertex_->number_ << std::endl;
    return 0;   
}

void Relax(VertexListNode *u, VertexListNode *v, int weight) {
    int udist = u->vertex_->distance_;
    if(udist != INT_MAX && v->vertex_->distance_ > udist + weight) {
        v->vertex_->distance_ = udist + weight;
        v->vertex_->parent_ = u->vertex_;
    }
}

bool BellmanFord(Graph &graph, int source) {
    VertexListNode *source_node = graph.find_vertex(source);
    source_node->vertex_->distance_ = 0; 

    VertexListNode *list_node = graph.vertex_list_;
    //for each vertex
    for(; list_node; list_node = list_node->next_) {
        //for each edge
        VertexListNode *node = graph.vertex_list_;
        for(; node; node = node->next_) {
            AdjListNode *adj_node = node->adjlist_;
            for(; adj_node; adj_node = adj_node->next_) {
                Relax(node, adj_node->vertex_node_, adj_node->weight_);
            }
        }
    }
    
    VertexListNode *node = graph.vertex_list_;
    for(; node; node = node->next_) {
        AdjListNode *adj_node = node->adjlist_;
        for(; adj_node; adj_node = adj_node->next_) {
            if(node->vertex_->distance_ + adj_node->weight_ < adj_node->vertex_node_->vertex_->distance_)
                return false;
        }
    }

    return true;
}
};
