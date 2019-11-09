// http://lightoj.com/volume_showproblem.php?problem=1028

#include<bits/stdc++.h>

using namespace std;

constexpr int MAX_PRIME = 10e6; 

bitset<MAX_PRIME+1> sieve;
vector<int> primes;

void find_primes(){
    primes.push_back(2);
    for(int i = 3; i <= MAX_PRIME; i+=2){
        if(sieve[i] == 0){
            for(int j = i+i; j <= MAX_PRIME; j+= i){
                sieve[j] = 1;
            }
            primes.push_back(i);
        }
    }
}

int count_distinct_divisors(long long n){
    if(n == 1) return 1;
    int divisor = 0;
    int divisors = 1;
    long long divided = n;
    int power = 0;
    for(int i = 0; i < primes.size(); i++){
        if((long long)primes[i]*primes[i]>divided) break;
        if(divided%primes[i] == 0){
            divisor = primes[i];
            power = 0;
            while(divided%divisor == 0){
                power++;
                divided/=divisor;
            }
            divisors *= (power+1);
            if(divided == 1) break;
        }
    }
    if(divided != 1) divisors <<= 1;
    return divisors;
}

int main(){
    find_primes();
    int test_cases;
    scanf("%d", &test_cases);
    for(int test=1; test<=test_cases; test++){
        long long number;
        scanf("%lld", &number);
        int total_bases = count_distinct_divisors(number) - 1; // 1 as a base is excluded
        printf("Case %d: %d\n", test, total_bases); 
    }
    return 0;
}