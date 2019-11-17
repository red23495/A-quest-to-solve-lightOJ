// http://lightoj.com/volume_showproblem.php?problem=1017

#include<bits/stdc++.h>

using namespace std;

class DustSweeper{
    const int NO_NEXT = -1, NOT_CACHED = -1;
    int total_dusts, brush_width, max_moves;
    map<int,int> dust_count_on_y;
    vector<int> next_dust;
    vector<int> dust_sum;
    vector<vector<int>> dp_cache;
    void calculate_next_dust(){
        vector<int> dusts;
        for(auto& dust_pair: dust_count_on_y){
            int dust_y = dust_pair.first;
            dusts.push_back(dust_y);
        }
        // for(int i = 0; i < dusts.size(); i++) printf("%d, ", dusts[i]); printf("\n");
        next_dust.clear();
        next_dust.resize(dusts.size(), NO_NEXT);
        for(int i = 0; i < dusts.size(); i++){
            int current = dusts[i];
            int next = current + brush_width;
            for(int j = i+1; j < dusts.size(); j++){
                if(dusts[j] > next) {
                    next_dust[i] = j;
                    break;
                }
            }
        }
        // for(int i = 0; i < next_dust.size(); i++) printf("%d, ", next_dust[i]); printf("\n");
    }
    void calculate_dust_sum(){
        int sum = 0;
        for(auto dust_pair: dust_count_on_y){
            sum += dust_pair.second;
            dust_sum.push_back(sum);
        }
        // for(int i = 0; i < dust_sum.size(); i++) printf("%d, ", dust_sum[i]); printf("\n");
    }
    int dp(int current_index, int move_left){
        if(current_index < 0) return 0;
        if(move_left == 0) return 0;
        int total_distinct_dust = dust_count_on_y.size();
        if(current_index >= total_distinct_dust) return 0;
        if(dp_cache[current_index][move_left] != NOT_CACHED) return dp_cache[current_index][move_left];
        int clean, not_clean;
        int next = next_dust[current_index];
        int total_cleaned = 0;
        int left = current_index-1;
        if(next == -1){
            total_cleaned = dust_sum[dust_sum.size()-1];
        }
        else{
            total_cleaned = dust_sum[next-1];
        }
        if(left >= 0){
            total_cleaned -= dust_sum[left];
        }
        clean = total_cleaned + dp(next, move_left-1);
        not_clean = dp(current_index+1, move_left);
        return dp_cache[current_index][move_left] = max(clean,not_clean);
    }
public:
    DustSweeper(int _total_dusts, int _brush_width, int _max_moves){
        total_dusts = _total_dusts;
        brush_width = _brush_width;
        max_moves = _max_moves;
    }
    void add_dust(int x, int y){
        dust_count_on_y[y]++;
    }
    int calculate_maximum_cleanable(){
        calculate_next_dust();
        calculate_dust_sum();
        int total_distinct_dusts = dust_count_on_y.size();
        dp_cache.resize(total_distinct_dusts, vector<int>(max_moves+1, NOT_CACHED));
        return dp(0, max_moves);
    }
};

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test=1; test<=test_cases; test++){
        int total_dusts, brush_width, max_moves;
        scanf("%d%d%d", &total_dusts, &brush_width, &max_moves);
        DustSweeper sweeper(total_dusts, brush_width, max_moves);
        while(total_dusts--){
            int x,y;
            scanf("%d%d", &x, &y);
            sweeper.add_dust(x,y);
        }
        int ans = sweeper.calculate_maximum_cleanable();
        printf("Case %d: %d\n", test, ans);
    }
    return 0;
}