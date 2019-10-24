// http://lightoj.com/volume_showproblem.php?problem=1015

#include<bits/stdc++.h>

using namespace std;

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        int total_dust_counts;
        scanf("%d", &total_dust_counts);
        int dusts_to_collect = 0;
        while(total_dust_counts--){
            int dust_count;
            scanf("%d", &dust_count);
            if(dust_count > 0) dusts_to_collect += dust_count;
        }
        printf("Case %d: %d\n", test, dusts_to_collect);
    }
    return 0;
}