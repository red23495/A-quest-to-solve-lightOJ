// http://lightoj.com/volume_showproblem.php?problem=1009

#include<bits/stdc++.h>

using namespace std;

// count maximum nodes in each disjoint bipartite graph and sum it

class NewsGraph{
    const int BLACK = 1;
    const int WHITE = 2;
    const int GRAY = 0;
    vector<vector<int>> graph;
    map<int,int> node_map;
    vector<pair<int,int>> edges;
    vector<int> color;
    int get_node_for_fighter(int n){
        if(node_map.count(n) == 0) node_map[n] = node_map.size();
        return node_map[n];
    }
    void add_edges_to_graph(){
        for(auto edge: edges){
            int n1 = edge.first;
            int n2 = edge.second;
            graph[n1].push_back(n2);
            graph[n2].push_back(n1);
        }
    }
    pair<int,int> get_colors(int parent, int _color){
        if(color[parent] != GRAY) return {0,0};
        color[parent] = _color;
        pair<int,int> ret_color = {0,0};
        int child_color;
        if(_color == BLACK) {
            ret_color.first = 1;
            child_color = WHITE;
        }
        else {
            child_color = BLACK;
            ret_color.second = 1;
        }
        for(auto child: graph[parent]){
            auto found_colors = get_colors(child, child_color);
            ret_color.first += found_colors.first;
            ret_color.second += found_colors.second;
        }
        return ret_color;
    }
public:
    void add_news(int a, int b){
        a = get_node_for_fighter(a);
        b = get_node_for_fighter(b);
        edges.push_back({a,b});
    }
    int get_max_fighter(){
        graph.resize(node_map.size());
        add_edges_to_graph();
        color.resize(node_map.size(), GRAY);
        int max_fighters = 0;
        for(int node = 0; node < graph.size(); node++){
            auto found_colors = get_colors(node, BLACK);
            max_fighters += max(found_colors.first, found_colors.second);
        }
        return max_fighters;
    }
};

int main(){
    int test_cases;
    scanf("%d",&test_cases);
    for(int test = 1; test <= test_cases; test++){
        int news;
        NewsGraph graph;
        scanf("%d",&news);
        while(news--){
            int fighter1, fighter2;
            scanf("%d%d", &fighter1, &fighter2);
            graph.add_news(fighter1, fighter2);
        }
        int answer = graph.get_max_fighter();
        printf("Case %d: %d\n", test, answer);
    }
    return 0;
}