// http://lightoj.com/volume_showproblem.php?problem=1019

#include<bits/stdc++.h>

using namespace std;

// i forgot to add less function in priority queue
// so went little bit hacky with negative weight

class CityMap{
    int junctions;
    vector<vector<pair<int,int>>> graph;
public:
    CityMap(int _junctions){
        junctions = _junctions;
        graph.resize(junctions);
    }
    void add_road(int a, int b, int weight){
        a--, b--;
        graph[a].push_back({b,weight});
        graph[b].push_back({a,weight});
    }
    int find_shortest_path(){
        const int start = 0;
        const int destination = junctions-1;
        priority_queue<pair<int,int>> pq;
        vector<bool> visited(junctions);
        pq.push({0, start});
        while(!pq.empty()){
            auto current_node = pq.top();
            pq.pop();
            int node = current_node.second;
            int distance = current_node.first;
            if(node == destination) return -distance;
            if(visited[node]) continue;
            visited[node] = true;
            int parent = node;
            for(auto child: graph[parent]){
                int child_node = child.first;
                int child_distance = child.second;
                pq.push({distance-child_distance, child_node});
            }
        }
        return -1;
    }
};


int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        int junctions, roads;
        scanf("%d%d", &junctions, &roads);
        CityMap city_map(junctions);
        while(roads--){
            int a,b,weight;
            scanf("%d%d%d", &a, &b, &weight);
            city_map.add_road(a, b, weight);
        }
        int ans = city_map.find_shortest_path();
        if(ans == -1){
            printf("Case %d: Impossible\n", test);
        }else{
            printf("Case %d: %d\n", test, ans);
        }
    }
    return 0;
}