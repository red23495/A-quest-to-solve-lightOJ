// http://lightoj.com/volume_showproblem.php?problem=1011

#include<bits/stdc++.h>

using namespace std;

// Hungerian assignment problem using bipartite matching

class CoupleMatrix{
    int n;
    vector<vector<int>> matrix;
    vector<int> man_label, woman_label;
    vector<int> matchings;
    vector<bool> visited;
    vector<bool> altered_man, altered_woman;
    void set_label(){
        man_label.resize(n);
        woman_label.resize(n);
        for(int man = 0; man < n; man++){
            int max_priority = 0;
            for(int woman = 0; woman < n; woman++){
                max_priority = max(matrix[man][woman], max_priority);
            }
            man_label[man] = max_priority;
        }
    }
    void find_match(int man){
        visited.clear();
        visited.resize(n);
        altered_man.clear();
        altered_man.resize(n);
        altered_woman.clear();
        altered_woman.resize(n);
        while(!find_augmenting_path(man)){
            recalculate_edges();
            visited.clear();
            visited.resize(n);
            altered_man.clear();
            altered_man.resize(n);
            altered_woman.clear();
            altered_woman.resize(n);
        }
    }
    bool find_augmenting_path(int man){
        if(visited[man]) return false;
        visited[man] = true;
        altered_man[man] = true;
        for(int woman = 0; woman < n; woman++){
            if(!is_valid_edge(man, woman)) continue;
            altered_woman[woman] = true;
            if(matchings[woman] == -1 || find_augmenting_path(matchings[woman])){
                matchings[woman] = man;
                return true;
            }
        }
        return false;
    }
    bool is_valid_edge(int man, int woman){
        return man_label[man] + woman_label[woman] == matrix[man][woman];
    }
    void recalculate_edges(){
        int delta = get_delta();
        for(int i = 0; i < n; i++){
            if(altered_man[i]) man_label[i] -= delta;
            if(altered_woman[i]) woman_label[i] += delta;
        }
    }
    int get_delta(){
        int delta = INT_MAX;
        for(int man = 0; man < n; man++){
            if(!altered_man[man]) continue;
            for(int woman = 0; woman < n; woman++){
                if(altered_woman[woman]) continue;
                delta = min(delta, man_label[man] + woman_label[woman] - matrix[man][woman]);
            }
        }
        return delta;
    }
    bool is_complete(){
        for(int i = 0; i < n; i++){
            if(matchings[i] == -1) return false;
        }
        return true;
    }
    int calculate_cost(){
        int cost = 0;
        for(int i = 0; i < n; i++){
            cost += man_label[i] + woman_label[i];
        }
        return cost;
    }
public:
    CoupleMatrix(int couples){
        n = couples;
        matrix.resize(n, vector<int>(n));
        matchings.resize(n, -1);
    }
    void set_couple_priority(int man, int woman, int priority){
        matrix[man][woman] = priority;
    }
    int get_maximal_matching(){
        set_label();
        for(int man = 0; man < n; man++){
            find_match(man);
            if(is_complete()) break;
        }
        return calculate_cost();
    }
};

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        int total_couples;
        scanf("%d", &total_couples);
        CoupleMatrix couples(total_couples);
        for(int man = 0; man < total_couples; man++){
            for(int woman = 0; woman < total_couples; woman++){
                int priority;
                scanf("%d", &priority);
                couples.set_couple_priority(man, woman, priority);
            }
        }
        int answer = couples.get_maximal_matching();
        printf("Case %d: %d\n", test, answer);
    }
    return 0;
}