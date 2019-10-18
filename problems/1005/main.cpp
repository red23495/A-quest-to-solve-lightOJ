// http://lightoj.com/volume_showproblem.php?problem=1005

#include<bits/stdc++.h>

using namespace std;

// the combination among the rooks would be k!
// then there would be empty spaces left both horizontally and vertically
// combnitaion for each of them is nCn-k

unsigned long long factorial_cache[21];
unsigned long long nCr_cache[31][31];

unsigned long long factorial(int n){
    if(n == 0) return 1;
    if(n < 3) return n;
    if(factorial_cache[n] != 0) return factorial_cache[n];
    return factorial_cache[n] = n * factorial(n-1);
}

unsigned long long nCr(int n, int r){
    if(n < r) return 0;
    if(r == 0) return 1;
    if(n == r) return 1;
    if(r == 1) return n;
    if(nCr_cache[n][r] != 0) return nCr_cache[n][r];
    if(nCr_cache[n][n-r] != 0) return nCr_cache[n][n-r];
    return nCr_cache[n][r] = nCr(n-1,r) + nCr(n-1, r-1);
}

int main(){
    int test_cases;
    scanf("%d",&test_cases);
    for(int test = 1; test <= test_cases; test++){
        int n,k;
        scanf("%d%d",&n,&k);
        unsigned long long ans = 0;
        if(n >= k){
            ans = factorial(k) * nCr(n,k) * nCr(n,k);
        }
        printf("Case %d: %llu\n", test, ans);
    }
    return 0;
}