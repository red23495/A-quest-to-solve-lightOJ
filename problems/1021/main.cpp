// http://lightoj.com/volume_showproblem.php?problem=1021

#include<bits/stdc++.h>

using namespace std;

// dp(mask, modded_val) = dp(mask|new_digit, new_modded_val) for each untouched digit

long long pow_cache[17][16];
void calculate_pow_cache(){
    for(int i = 1; i < 17; i++){
        pow_cache[i][0] = 1;
        for(int j = 1; j < 16; j++){
            pow_cache[i][j] = pow_cache[i][j-1] * i;
        }
    }
}

class PermutationCounter{
    long long base, divisor;
    string digit_string;
    const int NOT_CACHED = -1;
    vector<vector<long long>> dp_cache;
    int get_digit_value(char digit){
        if(digit >= 'A' && digit <= 'F') return digit - 'A' + 10;
        return digit - '0';
    }
    long long dp(int mask, int mod){
        long long base_power = __builtin_popcount(mask);
        long long total_digits = digit_string.length();
        if(base_power == total_digits){
            if(mod == 0) return 1;
            return 0;
        }
        if(dp_cache[mask][mod] != NOT_CACHED) return dp_cache[mask][mod];
        long long combinations = 0;
        for(int index = 0; index < total_digits; index++){
            if((mask & (1<<index)) == 0){
                int digit_value = get_digit_value(digit_string[index]);
                long long new_val = mod +((digit_value%divisor)*(pow_cache[base][base_power]%divisor))%divisor;
                new_val %= divisor;
                combinations += dp(mask|(1<<index), new_val);
            }
        }
        return dp_cache[mask][mod] = combinations;
    }
public:
    PermutationCounter(int _base, int _divisor, char* digits){
        base = _base;
        divisor = _divisor;
        digit_string = string(digits);

    }
    long long get_permutations(){
        int total_digits = digit_string.length();
        dp_cache.resize((1 << total_digits), vector<long long>(divisor, NOT_CACHED));
        return dp(0,0);
    }
};

int main(){
    calculate_pow_cache();
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        int base, divisor;
        scanf("%d%d", &base, &divisor);
        char digit_string[20];
        scanf("%s", digit_string);
        PermutationCounter permutation_counter(base, divisor, digit_string);
        long long combinations = permutation_counter.get_permutations();
        printf("Case %d: %lld\n", test, combinations);
    }
    return 0;
}