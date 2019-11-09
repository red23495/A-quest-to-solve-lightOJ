// http://lightoj.com/volume_showproblem.php?problem=1027

/* ====================================================================
let,
E = expected value
C_s = {x(i): i-th gate is escapable and x(i) = time cost of i-th gate}
C_f = {x(i): i-th gate is not escapable and x(i) = time cost of i-th gate}
C = (C_s) Union (C_f) 
for each get i:
    expected cost of i is
        (C(i)) if i is escapable
        (C(i) + E) if i is not escapable
so,
E = ((sum(C_s))+(sum(C_f)+|C_f|*E))/|C|
|C|*E = sum(C_s)+sum(C_f)+|C_f|*E
|C_s + C_f|*E - |C_f|*E= sum(C_s)+sum(C_f)
|C_s|*E = sum(C)
E = sum(C)/|C_s|
==================================================================== */

#include<bits/stdc++.h>

using namespace std;

int gcd(int a, int b){ return (b%a==0)?a:gcd(b%a, a);}

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        int total_gates;
        scanf("%d", &total_gates);
        int sum_of_gate_costs = 0, total_escapable_gates = 0;
        while(total_gates--){
            int gate_cost;
            scanf("%d", &gate_cost);
            sum_of_gate_costs += abs(gate_cost);
            if(gate_cost > 0) total_escapable_gates++;
        }
        if(total_escapable_gates > 0){
            int divisor = gcd(sum_of_gate_costs, total_escapable_gates);
            printf("Case %d: %d/%d\n", test, sum_of_gate_costs/divisor, total_escapable_gates/divisor);
        }else{
            printf("Case %d: inf\n", test);
        }
    }
    return 0;
}