// http://lightoj.com/volume_showproblem.php?problem=1002

#include<bits/stdc++.h>

using namespace std;

// Hint: Dijkstra can find all shortest paths from a single source in one pass

// cities are nodes, roads are edges
class RoadMap{
private:
    vector<vector<int>> weight;
    vector<vector<int>> graph;
    int total_nodes;
public:
    RoadMap(int nodes){
        total_nodes = nodes;
        weight.resize(nodes, vector<int>(nodes,INT_MAX));
        graph.resize(nodes,{});
    }
    void add_road(int from, int to, int _weight){
        weight[from][to] = min(_weight, weight[from][to]);
        weight[to][from] = min(_weight, weight[to][from]);
    }
    void prepare_graph(){
        for(int i = 0; i < total_nodes; i++){
            for(int j = 0; j < total_nodes; j++){
                if(weight[i][j] != INT_MAX) graph[i].push_back(j);
            }
        }
    }
    vector<int> get_shortest_path_costs(int from){
        vector<int> visited(total_nodes, -1);
        priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0,from});
        while(!pq.empty()){
            auto parent_node = pq.top();
            pq.pop();
            int parent = parent_node.second;
            int parent_weight = parent_node.first;
            if(visited[parent] == -1) visited[parent] = parent_weight;
            auto children = graph[parent];
            for(auto child: children){
                if(visited[child] != -1) continue;
                int child_weight = weight[parent][child];
                int new_weight = max(parent_weight, child_weight);
                pq.push({new_weight, child});
            }
        }
        return visited;
    }
};

int main(){
    int test_cases;
    scanf("%d",&test_cases);
    for(int test = 1; test <= test_cases; test++){
        int cities, roads;
        scanf("%d%d",&cities, &roads);
        RoadMap roadmap(cities);
        for(int road = 0; road < roads; road++){
            int from,to,weight;
            scanf("%d%d%d",&from,&to,&weight);
            roadmap.add_road(from,to,weight);
        }
        roadmap.prepare_graph();
        int home_city;
        scanf("%d",&home_city);
        printf("Case %d:\n", test);
        vector<int> costs = roadmap.get_shortest_path_costs(home_city);
        for(int cost : costs){
            if(cost == -1) printf("Impossible\n");
            else printf("%d\n",cost);
        }
    }
    return 0;
}