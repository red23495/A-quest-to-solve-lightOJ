// http://lightoj.com/volume_showproblem.php?problem=1016
#include<bits/stdc++.h>

using namespace std;

// simple greedy solution

class DustHeightTracker{
    int total_dust_points, brush_width;
    set<int> DustHeights;
public:
    DustHeightTracker(int _total_dust_points, int _brush_width){
        total_dust_points = _total_dust_points;
        brush_width = _brush_width;
    }
    void add_dust_height(int y){
        DustHeights.insert(y);
    }
    int minimum_required_sweep(){
        int total_sweep = 0;
        int cleaned_so_far = 0;
        for(int height: DustHeights){
            if(height > cleaned_so_far || !total_sweep){
                total_sweep += 1;
                cleaned_so_far = height + brush_width;
            }
        }
        return total_sweep;
    }
};

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        int total_dust_points, brush_width;
        scanf("%d%d", &total_dust_points, &brush_width);
        DustHeightTracker sweep_counter(total_dust_points, brush_width);
        while(total_dust_points--){
            int x,y;
            scanf("%d%d", &x, &y);
            // x is not required for this greedy solution
            sweep_counter.add_dust_height(y);
        }
        int ans = sweep_counter.minimum_required_sweep();
        printf("Case %d: %d\n", test, ans);
    }
    return 0;
}