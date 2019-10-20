// http://lightoj.com/volume_showproblem.php?problem=1006

#include<bits/stdc++.h>

// turn it into dp and mod it every time possible 

constexpr int MOD = 10000007;

int cache[10001];
int a,b,c,d,e,f;

int fn(int n){
    if( n == 0 ) return a % MOD;
    if( n == 1 ) return b % MOD;
    if( n == 2 ) return c % MOD;
    if( n == 3 ) return d % MOD;
    if( n == 4 ) return e % MOD;
    if( n == 5 ) return f % MOD;
    if(cache[n] != -1) return cache[n];
    return cache[n] = (fn(n-1)%MOD + fn(n-2)%MOD + fn(n-3)%MOD + fn(n-4)%MOD + fn(n-5)%MOD + fn(n-6)%MOD)%MOD;
}

int main(){
    int test_cases;
    scanf("%d",&test_cases);
    for(int test = 1; test <= test_cases; test++){
        int n;
        scanf("%d%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f,&n);
        memset(cache, -1, sizeof cache);
        int ans = fn(n);
        printf("Case %d: %d\n", test, ans);
    }
    return 0;
}