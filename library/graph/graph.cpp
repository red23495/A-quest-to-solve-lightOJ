// Dependency:
// 1. Standard C++ Library

#include<bits/stdc++.h>

using namespace std;

// copy from here

using NodeIndex_t = unsigned int;
template<typename WeightType, typename NodeType>
class Graph{
public:
    using Weight_t = WeightType;
    using Node_t = NodeType;
    virtual void add_edge(Node_t node_begin, Node_t node_end, Weight_t weight) = 0;
    virtual void add_bidirectional_edge( Node_t node_begin, Node_t node_end, Weight_t weight){
        add_edge(node_begin, node_end, weight);
        add_edge(node_end, node_begin, weight);
    }
    virtual const vector<pair<NodeIndex_t,Weight_t>>& get_neighbours(Node_t parent_node) const = 0;
    virtual ~Graph() {};
};
