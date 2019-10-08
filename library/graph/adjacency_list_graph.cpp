// Dependency:
// 1. Graph (graph/graph.cpp)

#include "graph.cpp"

using namespace std;

// copy from here

template<typename WeightType = int, typename NodeType = int>
class AdjacencyListGraph: public Graph<WeightType,NodeType>{
public:
    using Weight_t = WeightType;
    using Node_t = NodeType;
    using Neighbour_t = pair<NodeIndex_t,Weight_t>;
    using NeighboursList_t = vector<Neighbour_t>;
private:
    vector<NeighboursList_t> graph;
    int total_nodes;
public:
    AdjacencyListGraph(unsigned int total_nodes){
        graph.resize(total_nodes);
        this->total_nodes = total_nodes;
    }
    void add_edge(Node_t node_begin, Node_t node_end, Weight_t weight) override {
        graph[int(node_begin)].push_back({int(node_end), weight});
    }
    const NeighboursList_t& get_neighbours(Node_t parent_node) const override {
        return graph[int(parent_node)];
    }
    inline unsigned int get_total_nodes() const override {
        return total_nodes;
    }
    virtual ~AdjacencyListGraph() override {};
};

using ClassicGraph = AdjacencyListGraph<>;
