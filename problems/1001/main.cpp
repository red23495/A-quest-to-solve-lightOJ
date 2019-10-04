// http://lightoj.com/volume_showproblem.php?problem=1001

#include<bits/stdc++.h>

using namespace std;

int main(){
    int test_cases;
    cin >> test_cases;
    for(int test = 1; test <= test_cases; test++){
        int total_problems;
        cin >> total_problems;
        int problem_set_1, problem_set_2;
        if(total_problems > 10){
            problem_set_1 = 10;
            problem_set_2 = (total_problems - 10);
        }
        else{
            problem_set_1 = total_problems;
            problem_set_2 = 0;
        }
        cout << problem_set_1 << " " << problem_set_2 << endl;
    }
    return 0;
}