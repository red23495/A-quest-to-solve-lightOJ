// http://lightoj.com/volume_showproblem.php?problem=1014

#include<bits/stdc++.h>

using namespace std;

int main(){
    int test_cases;
    scanf("%d",&test_cases);
    for(int test = 1; test <= test_cases; test++){
        int piajus, left;
        scanf("%d%d",&piajus,&left);
        vector<int> answers;
        for(int eaten = 1; eaten <= sqrt(piajus - left); eaten++){
            if ((piajus - left) % eaten == 0){
                int _eaten = eaten;
                int possible_students = (piajus - left) / _eaten;
                if(_eaten > left) answers.push_back(_eaten);
                if(_eaten == possible_students) continue;
                _eaten = possible_students;
                possible_students = (piajus - left) / _eaten;
                if(_eaten > left) answers.push_back(_eaten);
            }
        }
        printf("Case %d:", test);
        sort(answers.begin(), answers.end());
        for(int answer: answers){
            printf(" %d", answer);
        }
        if(answers.size() == 0) printf(" impossible");
        printf("\n");
    }
    return 0;
}