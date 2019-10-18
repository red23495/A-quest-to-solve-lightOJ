// http://lightoj.com/volume_showproblem.php?problem=1004

#include<bits/stdc++.h>

using namespace std;

// we implement the maze with one dimensional array
// this will eventually represent a DAG
// we break the nodes of the diamond shaped maze in three parts
// upper nodes - resides in upper triangle of the maze
// lower nodes - resides in lower triangle of the maze
// axis nodes - resides in the middle row, the asymmetric part of the maze

class Maze{
private:
    int axis;
    int maze_size;
    vector<int> maze;
    vector<int> cache;
    vector<int> get_children(int parent){
        if(is_upper_node(parent)){
            return get_upper_node_child(parent);
        }
        if(is_lower_node(parent)){
            return get_lower_node_child(parent);
        }
        return get_axis_node_child(parent);
    }
    bool is_upper_node(int node){
        int n = axis;
        if(node <= ((n*(n-1))/2)){
            return true;
        }
        return false;
    }
    bool is_lower_node(int node){
        int n = axis;
        if(node >= (((n*(n+1))/2)+1)){
            return true;
        }
        return false;
    }
    bool is_axis_node(int node){
        int n = axis;
        int lower_limit = ((n*(n-1))/2)+1;
        int upper_limit = (n*(n+1))/2;
        if(node >= lower_limit && node <= upper_limit){
            return true;
        }
        return false;
    }
    vector<int> get_upper_node_child(int parent){
        int row = get_upper_node_row(parent);
        int offset = get_upper_node_offset(parent, row);
        int first_child = (row*(row+1))/2 + offset;
        int second_child = first_child + 1;
        return {first_child, second_child};
    }
    int get_upper_node_row(int node){
        int n = axis;
        int low = 1;
        int high = (n*(n-1))/2;
        int row = (low+high)/2;
        while(!(node > ((row*(row-1))/2) && node <= ((row*(row+1))/2))){
            if(node > ((row*(row-1))/2)){
                low = row + 1;
            }else{
                high = row - 1;
            }
            row = (low+high)/2;
        }
        return row;
    }
    int get_upper_node_offset(int node, int row){
        return node - ((row*(row-1))/2);
    }
    int flip_node(int node){
        return maze_size - node + 1;
    }
    vector<int> get_lower_node_child(int parent){
        int flipped_parent = flip_node(parent);
        // flipping basically turns a lower node into a upper node equivalent
        // however now the child resides upwards
        int flipped_row = get_upper_node_row(flipped_parent);
        int flipped_offset = get_upper_node_offset(flipped_parent, flipped_row);
        int flipped_first_child = ((flipped_row-1)*(flipped_row-2))/2 + flipped_offset;
        int flipped_second_child = flipped_first_child - 1;
        vector<int> children;
        if(flipped_offset != flipped_row){
            children.push_back(flip_node(flipped_first_child));
        }
        if(flipped_offset != 1){
            children.push_back(flip_node(flipped_second_child));
        }
        return children;
    }
    vector<int> get_axis_node_child(int parent){
        int row = axis;
        int offset = get_upper_node_offset(parent, row);
        int first_child = (row*(row+1))/2 + offset;
        int second_child = first_child - 1;
        vector<int> children;
        if(offset != 1){
            children.push_back(second_child);
        }
        if(offset != row){
            children.push_back(first_child);
        }
        return children;
    }
    int dp(int node){
        if(node == maze_size){
            return maze[node];
        }
        if(cache[node] != 0){
            return cache[node];
        }
        int cell_bananas = maze[node];
        auto children = get_children(node);
        for(int child: children){
            cache[node] = max(cache[node], cell_bananas + dp(child));
        }
        return cache[node];
    }
public:
    Maze(int n){
        axis = n;
        maze_size = n*n;
        // we'll leave the 0th cell alone
        // cause 0 indexing makes calculation more complicated
        maze.resize(maze_size + 1);
        cache.resize(maze_size + 1);
    }
    void set_banana_count(int index, int bananas){
        maze[index] = bananas;
    }
    int get_maze_size(){
        return maze_size;
    }
    int get_maximum_consumption(){
        return dp(1);
    }
};

int main(){
    int test_cases;
    scanf("%d",&test_cases);
    for(int test = 1; test <= test_cases; test++){
        int n;
        scanf("%d",&n);
        Maze maze(n);
        for(int cell = 1; cell <= maze.get_maze_size(); cell++){
            int banana_count;
            scanf("%d", &banana_count);
            maze.set_banana_count(cell, banana_count);
        }
        printf("Case %d: %d\n", test, maze.get_maximum_consumption());
    }
    return 0;
}