// Dependency:
// 1. Standard C++ Library

#include<bits/stdc++.h>

using namespace std;

// complexity: O(|E| + |V|log|V|)

// copy from here

using NodeIndex_t = unsigned int;
template<typename WeightType, typename NodeType>
class Graph{
public:
    using Weight_t = WeightType;
    using Node_t = NodeType;
    using Neighbour_t = pair<NodeIndex_t,Weight_t>;
    using NeighboursList_t = vector<Neighbour_t>;
    virtual void add_edge(Node_t node_begin, Node_t node_end, Weight_t weight) = 0;
    virtual void add_bidirectional_edge( Node_t node_begin, Node_t node_end, Weight_t weight){
        add_edge(node_begin, node_end, weight);
        add_edge(node_end, node_begin, weight);
    }
    // you should be able to retrive neighbours with both node index and the node itself
    // casting does the trick (side-effect)
    // I know it's probably a bit of bad design but it's too late to change it
    virtual const NeighboursList_t& get_neighbours(Node_t parent_node) const = 0;
    virtual unsigned int get_total_nodes() const = 0;
    virtual ~Graph() {};
};
