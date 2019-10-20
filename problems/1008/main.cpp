// http://lightoj.com/volume_showproblem.php?problem=1008

#include<bits/stdc++.h>

using namespace std;

// calculate row and offset, it's very easy

int main(){
    int test_cases;
    scanf("%d",&test_cases);
    for(int test = 1; test <= test_cases; test++){
        long long n, row, offset, x, y;
        scanf("%lld", &n);
        row = ceil(sqrt(n));
        offset = (row << 1) + n - (row * row) - 1;
        if(row & 1){
            if(offset <= row){
                x = row;
                y = offset;
            }else{
                x = (row << 1) - offset;
                y = row;
            }
        }else{
            if(offset <= row){
                x = offset;
                y = row;
            }else{
                x = row;
                y = (row << 1) - offset;
            }
        }
        printf("Case %d: %lld %lld\n", test, x, y);
    }
    return 0;
}