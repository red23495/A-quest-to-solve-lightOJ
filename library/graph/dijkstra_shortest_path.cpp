// Dependency
// 1. Graph (graph/graph.cpp)

#include "graph.cpp"

using namespace std;

template<typename WeightType = int, typename NodeType = int>
class DijkstraShortestPathPlugin{
public:
    using HeapElement_t = pair<WeightType,NodeIndex_t>;
    using BaseGraph_t = Graph<WeightType,NodeType>;
    using CompFunction = bool(*)(HeapElement_t&,HeapElement_t&);
    using WeightAggregateFunction = WeightType(*)(WeightType&,WeightType&);
private:
    static constexpr NodeIndex_t PARENT_FLAG = -99;
    static constexpr NodeIndex_t UNVISITED_FLAG = -1;
    Graph<WeightType,NodeType>* base_graph;
    CompFunction less;
    WeightAggregateFunction aggregate_weight;
    class CompFunctor{
    public:
        bool operator() (HeapElement_t& a, HeapElement_t& b){
            return less(a,b);
        }
    };
    bool is_found;
    WeightType shortest_path_cost;
    NodeIndex_t shortest_path_source;
    NodeIndex_t shortest_path_destination;
    vector<NodeIndex_t> shortest_path_visited_flag;
public:
    DijkstraShortestPathPlugin(BaseGraph_t *base_graph){
        this->base_graph = base_graph;
        this->less = [](HeapElement_t& a, HeapElement_t& b)->bool{
             return a < b; 
        };
        this->aggregate_weight = [](WeightType& a, WeightType& b)->WeightType{
            return a + b;
        };
        this->is_found = false;
        this->shortest_path_cost = {};
        this->shortest_path_source = 0;
        this->shortest_path_destination = 0;
        shortest_path_visited_flag = {};
    }
    void set_compare_function(CompFunction cmp){
        this->less = cmp;
    }
    void set_weight_aggregate_function(WeightAggregateFunction aggr){
        this->aggregate_weight = aggr;
    }
    void FindShortestPath(NodeType source, NodeType destination){
        NodeIndex_t source_node = int(source);
        NodeIndex_t destination_node = int(destination);
        priority_queue<HeapElement_t,vector<HeapElement_t>,CompFunctor> heap;
        vector<NodeIndex_t> visited_from(this->base_graph->get_total_nodes(), this->UNVISITED_FLAG);
        heap.push({{}, source_node});
        visited_from[source_node] = this->PARENT_FLAG;
        bool is_found = false;
        WeightType final_cost = {};
        while(!is_found && !heap.empty()){
            HeapElement_t top = heap.top();
            heap.pop();
            NodeIndex_t parent_index = top.second;
            NodeIndex_t parent_weight = top.first;
            auto child_list = this->base_graph->get_neighbours(parent_index);
            for(const auto& child : child_list){
                NodeIndex_t child_index = child.first;
                WeightType child_weight = child.second;
                if(visited_from[child_index] != this->UNVISITED_FLAG) continue;
                visited_from[child_index] = parent_index;
                WeightType aggregated_weight = this->aggregate_weight(parent_weight, child_weight);
                if(child_index == destination_node){
                    is_found = true;
                    final_cost = aggregated_weight;
                    break;
                }
                heap.push({aggregated_weight, child_index});
            }
        }
        if(is_found){
            this->is_found = true;
            this->shortest_path_cost = final_cost;
            this->shortest_path_source = source_node;
            this->shortest_path_destination = destination_node;
            this->shortest_path_visited_flag = visited_from;
        }else {
            this->is_found = false;
            this->shortest_path_cost = {};
            this->shortest_path_source = 0;
            this->shortest_path_destination = 0;
            this->shortest_path_visited_flag = {};
        }
    }
    bool is_shortest_path_found() const {
        return this->is_found;
    }
    WeightType get_cost() const {
        return this->shortest_path_cost;
    }
    const list<NodeIndex_t>& trace_shortest_path() const {
        list<NodeIndex_t> shortest_path_list;
        NodeIndex_t current_node = this->shortest_path_destination;
        while(current_node != this->PARENT_FLAG){
            shortest_path_list.push_front(current_node);
            current_node = this->shortest_path_visited_flag[current_node];
        }
        return shortest_path_list;
    }
};
