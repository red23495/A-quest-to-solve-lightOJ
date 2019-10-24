// http://lightoj.com/volume_showproblem.php?problem=1020

#include<bits/stdc++.h>

using namespace std;

// Alice wins for every case when she starts except when marbles % 3 == 1
// Bob wins for every case when he starts except when the marbles % 3 == 0

int main(){
    int test_cases;
    scanf("%d",&test_cases);
    for(int test = 1; test <= test_cases; test++){
        int marbles;
        char _starter[10];
        scanf("%d%s",&marbles, _starter);
        string starter(_starter);
        string winner;
        if(starter == "Alice"){
            if(marbles % 3 == 1) winner = "Bob";
            else winner = "Alice";
        } else{
            if(marbles % 3 == 0) winner = "Alice";
            else winner = "Bob";
        }
        printf("Case %d: %s\n", test, winner.c_str());
    }
    return 0;
}