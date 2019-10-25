// http://lightoj.com/volume_showproblem.php?problem=1007

#include<bits/stdc++.h>

using namespace std;
using llu = unsigned long long;

// generate phi using sieve

constexpr int MAX_N = 5e6;

llu phi[MAX_N];

void generate_phi(int n){
    vector<int> sieve(n+2);
    phi[2] = 1;
    for(int i = 4; i <= n; i+=2){
        sieve[i] = 2;
        if(!phi[i]) phi[i] = i;
        phi[i] /= 2;
    }
    for(int i = 3; i <= n; i+=2){
        if(sieve[i] == 0){
            phi[i] = i - 1;
            for(int j = i*2; j <= n; j+=i){
                sieve[j] = i;
                if(!phi[j]) phi[j] = j;
                phi[j] /= i;
                phi[j] *= (i-1);
            }
        }
    }
}



void prepare_phi_sum(){
    generate_phi(MAX_N);
    for(int i = 2; i <= MAX_N; i++){
        phi[i] = phi[i-1] + phi[i] * phi[i];
    }
}

llu ranged_phi_sum(int a, int b){
    return phi[b] - phi[a-1];
}

int main(){
    prepare_phi_sum();
    int test_cases;
    scanf("%d",&test_cases);
    for(int test = 1; test <= test_cases; test++){
        int a,b;
        scanf("%d%d",&a,&b);
        printf("Case %d: %llu\n", test, ranged_phi_sum(a,b));
    }
    return 0;
}