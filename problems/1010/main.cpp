// http://lightoj.com/volume_showproblem.php?problem=1010

#include<bits/stdc++.h>

using namespace std;

// knights on same colored cell can't attack each other
// watch out for min(m,n) <= 2 cases though

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        int m,n;
        scanf("%d%d",&m,&n);
        if(m > n) swap(m,n);
        int ans;
        if(m == 1){
            ans = m*n;
        }
        else if(m == 2){
            ans = ((n/4)*2 + min(n%4, 2)) * 2;
        }
        else{
            ans = ceil((m*n)/2.0);
        }
        printf("Case %d: %d\n", test, ans);
    }
    return 0;
}