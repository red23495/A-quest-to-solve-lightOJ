// http://lightoj.com/volume_showproblem.php?problem=1018

#include<bits/stdc++.h>

using namespace std;

class DustKeeper{
    const int NOT_CACHED = -1;
    vector<pair<int,int>> dust_points;
    vector<vector<int>> colinear_mask;
    vector<int> sweep_cache;
    // coliear: (x-x1)/(x1-x2) == (y-y1)/(y1-y2)
    bool is_colinear(pair<int,int> start, pair<int,int> end, pair<int,int> target){
        int x1 = start.first, y1 = start.second, x2 = end.first, y2 = end.second;
        int x = target.first, y = target.second;
        return ((x-x1)*(y1-y2) == (y-y1)*(x1-x2)); 
    }
    void generate_colinear_masks(){
        int total_dusts = dust_points.size();
        colinear_mask.resize(total_dusts, vector<int>(total_dusts));
        for(int i = 0; i < total_dusts; i++){
            for(int j = 0; j < total_dusts; j++){
                auto start = dust_points[i];
                auto end = dust_points[j];
                int mask = 0;
                if(i == j) {
                    mask |= (1 << i);
                    colinear_mask[i][j] = mask;
                    continue;
                }
                for(int k = 0; k < total_dusts; k++){
                    auto target = dust_points[k];
                    if(is_colinear(start, end, target)){
                        mask |= (1 << k);
                    }
                }
                colinear_mask[i][j] = mask;
            }
        }
    }
    int dp(int mask){
        int total_dusts = dust_points.size();
        if(__builtin_popcount(mask) == total_dusts) return 0;
        if(sweep_cache[mask] != NOT_CACHED) return sweep_cache[mask];
        int uncleaned = rightmost_unset_bit(mask);
        int min_sweep = INT_MAX;
        for(int point = 0; point < total_dusts; point++){
            min_sweep = min(dp(mask|colinear_mask[uncleaned][point]), min_sweep);
        }
        return sweep_cache[mask] = min_sweep + 1;
    }
    int rightmost_unset_bit(int mask){
        for(int i = 0; i < 32; i++){
            if((mask&(1<<i)) == 0) return i;
        }
        return 32;
    }
public:
    DustKeeper(){}
    void add_dust(int x, int y){
        dust_points.push_back({x,y});
    }
    int get_minimum_sweep(){
        generate_colinear_masks();
        int total_dusts =  dust_points.size();
        int total_masks = (1 << total_dusts) - 1;
        sweep_cache.resize(total_masks, NOT_CACHED);
        return dp(0);
    }
};

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        int total_dusts;
        scanf("%d", &total_dusts);
        DustKeeper dust_keeper;
        while(total_dusts--){
            int x, y;
            scanf("%d%d", &x, &y);
            dust_keeper.add_dust(x, y);
        }
        int ans = dust_keeper.get_minimum_sweep();
        printf("Case %d: %d\n", test, ans);
    }
    return 0;
}