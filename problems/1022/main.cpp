// http://lightoj.com/volume_showproblem.php?problem=1022

#include<bits/stdc++.h>

using namespace std;

// area of square - area of circle
const double PI = 2 * acos(0.0);
constexpr double PRECESION_FIX = 1e-9;

int main(){
    int test_cases;
    scanf("%d", &test_cases);
    for(int test = 1; test <= test_cases; test++){
        double radius;
        scanf("%lf", &radius);
        double area_of_square = 4 * radius * radius;
        double area_of_circle = PI * radius * radius;
        double area_of_shaded_region = area_of_square - area_of_circle;
        printf("Case %d: %.2lf\n", test, area_of_shaded_region + PRECESION_FIX);
    }
    return 0;
}