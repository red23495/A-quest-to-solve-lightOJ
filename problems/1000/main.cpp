// http://lightoj.com/volume_showproblem.php?problem=1000

#include<bits/stdc++.h>

using namespace std;

int main(){
    int test_cases;
    cin >> test_cases;
    for(int test = 1; test <= test_cases; test++){
        int problem_count_1, problem_count_2;
        cin >> problem_count_1 >> problem_count_2;
        int total_problems = problem_count_1 + problem_count_2;
        cout << "Case " << test << ": " << total_problems << endl;
    }
    return 0;
}