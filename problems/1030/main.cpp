// http://lightoj.com/volume_showproblem.php?problem=1030

#include<bits/stdc++.h>

using namespace std;

class Cave{
    int length;
    vector<int> golds;
    vector<double> gold_cache;
    double dp(int current_position){
        if(gold_cache[current_position] > 0) return gold_cache[current_position];
        double expected_value = golds[current_position];
        double next_values = 0;
        int possible_moves = 0;
        for(int i = 1; i <= 6; i++){
            if(current_position+i > length) break;
            next_values += dp(current_position+i);
            possible_moves++;
        }
        if(possible_moves != 0) expected_value += (next_values/possible_moves);
        return gold_cache[current_position] = expected_value;
    }
public:
    Cave(int _length){
        length = _length;
        golds.resize(length+1);
    }
    double expected_gold_to_be_found(){
        gold_cache.resize(length+1, -1);
        return dp(1);
    }
    void add_gold(int position, int amount){
        golds[position] = amount;
    }
};

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        int cave_length;
        scanf("%d", &cave_length);
        Cave cave(cave_length);
        for(int i = 1; i <= cave_length; i++){
            int amount;
            scanf("%d", &amount);
            cave.add_gold(i, amount);
        }
        double ans = cave.expected_gold_to_be_found();
        printf("Case %d: %lf\n", test, ans);
    }
    return 0;
}