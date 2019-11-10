// http://lightoj.com/volume_showproblem.php?problem=1012

#include<bits/stdc++.h>

using namespace std;

class IslandMap{
    int width, height;
    int start_w, start_h;
    vector<vector<char>> island_map;
    int flood_fill(int w, int h){
        if(w < 0 || w >= width) return 0;
        if(h < 0 || h >= height) return 0;
        if(island_map[w][h] != '.') return 0;
        island_map[w][h] = 'X';
        int sum = 1;
        sum += flood_fill(w+1,h);
        sum += flood_fill(w-1,h);
        sum += flood_fill(w,h+1);
        sum += flood_fill(w,h-1);
        return sum;
    }
public:
    IslandMap(int w, int h){
        width = w; height = h;
        island_map.resize(w, vector<char>(h));
    }
    void set_cell(int x, int y, char value){
        island_map[x][y] = value;
        if(value == '@'){
            start_h = y;
            start_w = x;
        }
    }
    int get_reachable_cells(){
        island_map[start_w][start_h] = '.';
        return flood_fill(start_w, start_h);
    }
};

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test=1; test<=test_cases; test++){
        int width, height;
        scanf("%d%d",&width,&height);
        IslandMap island(width, height);
        for(int h = 0; h < height; h++){
            for(int w = 0; w < width; w++){
                char cell;
                while(scanf("%c", &cell) && cell == 10);
                island.set_cell(w, h, cell);
            }
        }
        int ans = island.get_reachable_cells();
        printf("Case %d: %d\n", test, ans);
    }
    return 0;
}