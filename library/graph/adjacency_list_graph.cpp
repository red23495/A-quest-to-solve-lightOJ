// Dependency:
// 1. Graph (graph/graph.cpp)

#include "graph.cpp"

using namespace std;

// copy from here

template<typename WeightType = int, typename NodeType = int>
class AdjacencyListGraph: public Graph<WeightType,NodeType>{
public:
    using BaseGraph_t = Graph<WeightType,NodeType>;
    using Weight_t = WeightType;
    using Node_t = NodeType;
private:
    vector<vector<pair<NodeIndex_t,Weight_t>>> graph;
    int total_nodes;
public:
    AdjacencyListGraph(unsigned int total_nodes){
        graph.resize(total_nodes);
        this->total_nodes = total_nodes;
    }
    void add_edge(Node_t node_begin, Node_t node_end, Weight_t weight) override {
        graph[int(node_begin)].push_back({int(node_end), weight});
    }
    const vector<pair<NodeIndex_t,Weight_t>>& get_neighbours(Node_t parent_node) const override {
        return graph[int(parent_node)];
    }
    inline unsigned int get_total_nodes() const {
        return total_nodes;
    }
    virtual ~AdjacencyListGraph() override {};
};

using ClassicGraph = AdjacencyListGraph<>;
