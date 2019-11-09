// http://lightoj.com/volume_showproblem.php?problem=1026

#include<bits/stdc++.h>

using namespace std;
class NetworkGraph{
    const int DFS_ROOT = -1;
    const int UNVISITED = -1;
    int total_nodes;
    vector<vector<int>> graph;
    vector<bool> visited;
    vector<int> dfs_entry_time;
    vector<int> dfs_lowest_backlink_entry_time;
    int entry_time;
    vector<pair<int,int>> critical_links;
    void mark_articulation_bridges(int node, int prev_parent){
        dfs_entry_time[node] = dfs_lowest_backlink_entry_time[node] = ++entry_time;
        visited[node] = true;
        auto children = graph[node];
        int parent = node;
        for(auto child: children){
            if(child == prev_parent) continue;
            if(!visited[child]){
                mark_articulation_bridges(child, parent);
                if(dfs_lowest_backlink_entry_time[child] > dfs_entry_time[parent]){
                    critical_links.push_back({min(parent,child), max(parent,child)});
                }
            }
            dfs_lowest_backlink_entry_time[parent] = min(
                dfs_lowest_backlink_entry_time[parent],
                dfs_lowest_backlink_entry_time[child]);
        }
    }
public:
    NetworkGraph(int _total_nodes){
        total_nodes = _total_nodes;
        graph.resize(total_nodes);
    }
    void add_link(int serverA, int serverB){
        graph[serverA].push_back(serverB);
        graph[serverB].push_back(serverA);
    }
    vector<pair<int,int>> find_critical_links(){
        dfs_entry_time.resize(total_nodes, UNVISITED);
        dfs_lowest_backlink_entry_time.resize(total_nodes, UNVISITED);
        for(int node = 0; node < total_nodes; node++){
            if(dfs_entry_time[node] == UNVISITED){
                visited.clear();
                visited.resize(total_nodes, false);
                mark_articulation_bridges(node, DFS_ROOT);
            }
        }
        sort(critical_links.begin(), critical_links.end());
        return critical_links;
    }
};

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        int total_servers;
        scanf("%d", &total_servers);
        NetworkGraph network_graph(total_servers);
        while(total_servers--){
            int source_server, total_edges;
            scanf("%d (%d) ", &source_server, &total_edges);
            while(total_edges--){
                int edge_server;
                scanf("%d", &edge_server);
                network_graph.add_link(source_server, edge_server);
            }
        }
        auto critical_links = network_graph.find_critical_links();
        printf("Case %d:\n", test);
        printf("%lu critical links\n", critical_links.size());
        for(auto link: critical_links){
            printf("%d - %d\n", link.first, link.second);
        }
    }
    return 0;
}