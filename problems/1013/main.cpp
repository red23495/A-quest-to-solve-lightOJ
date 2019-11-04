// http://lightoj.com/volume_showproblem.php?problem=1013

#include<bits/stdc++.h>

using namespace std;
// LCS
// count is count(index_of_name1, index_of_name2, length_of_the_string_so_far)
class LoveCalculator{
    const int NOT_CACHED = -1;
    const int MAX_LENGTH = 65;
    string name1, name2;
    vector<vector<int>> LCS_cache;
    vector<vector<vector<long long>>> unique_string_cache;
    int get_LCS(int i, int j){
        if(i >= name1.length() || j >= name2.length()) return 0;
        if(LCS_cache[i][j] != NOT_CACHED) return LCS_cache[i][j];
        int max_lcs = -1;
        if(name1[i] == name2[j]){
            max_lcs = 1 + get_LCS(i+1, j+1);
        }else{
            max_lcs = max(max_lcs, max(get_LCS(i+1, j), get_LCS(i, j+1)));
        }
        return LCS_cache[i][j] = max_lcs;
    }
    long long get_unique_string_count(int i, int j, int length){
        if(i == name1.length() && j == name2.length()){
            if(length == get_love_rating()) return 1;
            else return 0;
        }
        if(i >= name1.length()){
            return get_unique_string_count(i,j+1,length+1);
        }
        if(j >= name2.length()){
            return get_unique_string_count(i+1,j,length+1);
        }
        if(unique_string_cache[i][j][length] != NOT_CACHED) return unique_string_cache[i][j][length];
        if(name1[i] == name2[j]){
            return unique_string_cache[i][j][length] = get_unique_string_count(i+1, j+1, length+1);
        }
        return unique_string_cache[i][j][length] = get_unique_string_count(i+1,j,length+1) + get_unique_string_count(i,j+1,length+1);
    }
public:
    LoveCalculator(char* __name1, char* __name2){
        name1 = string(__name1);
        name2 = string(__name2);
        LCS_cache.resize(name1.length(), vector<int>(name2.length(), NOT_CACHED));
        unique_string_cache.resize(name1.length(),
         vector<vector<long long>>(name2.length(), vector<long long>(MAX_LENGTH, NOT_CACHED))
         );
    }
    int get_love_rating(){
        int common_letters = get_LCS(0,0);
        int rating = name1.length() + name2.length() - common_letters;
        return rating;
    }
    long long get_unique_string_count(){
        return get_unique_string_count(0, 0, 0);
    }
};

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        char name1[30], name2[30];
        scanf("%s%s", name1, name2);
        LoveCalculator calculator(name1, name2);
        int love_rating = calculator.get_love_rating();
        long long unique_strings = calculator.get_unique_string_count();
        printf("Case %d: %d %lld\n", test, love_rating, unique_strings);
    }
    return 0;
}