// http://lightoj.com/volume_showproblem.php?problem=1025

#include<bits/stdc++.h>

using namespace std;

class PalindromeCounter{
    string word;
    vector<vector<long long>> dp_cache;
    const int NOT_CACHED = -1;
    long long dp(int i, int j){
        if(i > j) return 0;
        if(i == j) return 1;
        if(dp_cache[i][j] != NOT_CACHED) return dp_cache[i][j];
        char char1 = word[i], char2 = word[j];
        long long palindrome_count = 0;
        if(char1 == char2){
            palindrome_count += 1 + dp(i+1, j-1);
        }
        palindrome_count += dp(i+1, j) + dp(i, j-1) - dp(i+1, j-1);
        return dp_cache[i][j] = palindrome_count;
    }
public:
    PalindromeCounter(char* _word){
        word = string(_word);
        int word_size = word.length();
        dp_cache.resize(word_size, vector<long long>(word_size, NOT_CACHED));
    }
    long long get_palindrome_count(){
        int word_size = word.length();
        return dp(0, word_size-1);
    }
};

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        char word[65];
        scanf("%s", word);
        PalindromeCounter counter(word);
        long long answer = counter.get_palindrome_count();
        printf("Case %d: %lld\n", test, answer);
    }
    return 0;
}