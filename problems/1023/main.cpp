// http://lightoj.com/volume_showproblem.php?problem=1023

#include<bits/stdc++.h>

using namespace std;

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        int letters,permutations;
        scanf("%d%d", &letters, &permutations);
        string perm_string;
        for(char letter = 'A'; letter < ('A'+letters) ; letter++){
            perm_string.push_back(letter);
        }
        int printed = 0;
        printf("Case %d:\n", test);
        do{
            printf("%s\n", perm_string.c_str());
            printed++;
        }while(printed < permutations && next_permutation(perm_string.begin(), perm_string.end()));
    }
    return 0;
}