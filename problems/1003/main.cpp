// http://lightoj.com/volume_showproblem.php?problem=1003

#include<bits/stdc++.h>

using namespace std;

// Hint: search for cycle (look for any back edges)

class DrinkList{
private:
    map<string,int> names;
    vector<pair<int,int>> edges;
    vector<vector<int>> graph;
    vector<int> visited;
    const int UNVISITED = -1;
    const int EXPLORED = 0;
    const int VISITED = 1;
    
    int get_id(string s){
        if(!names.count(s)){
            names[s] = names.size();
        }
        return names[s];
    }

    bool has_cycle(int node){
        if(visited[node] == EXPLORED) return true;
        if(visited[node] == VISITED) return false;
        if(visited[node] == UNVISITED) visited[node] = EXPLORED;
        for(int child: graph[node]){
            if(has_cycle(child)) return true;
        }
        visited[node] = VISITED;
        return false;
    }

public:
    DrinkList(){}
    void add_drink_dependency(string parent, string child){
        int parent_id = get_id(parent);
        int child_id = get_id(child);
        edges.push_back({parent_id,child_id});
    }
    void prepare_graph(){
        graph.resize(names.size());
        for(auto edge: edges){
            graph[edge.first].push_back(edge.second);
        }
    }
    bool can_get_drunk(){
        visited.resize(names.size(),UNVISITED);
        for(int i = 0; i < names.size(); i++){
            if(has_cycle(i)) return false;
        }
        return true;
    }
};

int main(){
    int test_cases;
    cin >> test_cases;
    for(int test = 1; test <= test_cases; test++){
        int relations;
        cin >> relations;
        DrinkList drink_list;
        while(relations--){
            string drink1, drink2;
            cin >> drink1 >> drink2;
            drink_list.add_drink_dependency(drink1, drink2);
        }
        drink_list.prepare_graph();
        printf("Case %d: ", test);
        if(drink_list.can_get_drunk()){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}