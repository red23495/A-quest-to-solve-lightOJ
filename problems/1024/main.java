// http://lightoj.com/volume_showproblem.php?problem=1024

import java.util.Scanner;
import java.math.BigInteger;

class Main {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        int test_cases = sc.nextInt();
        for (int test = 1; test <= test_cases; test++) {
            int eating_periods = sc.nextInt();
            BigInteger eid_interval = BigInteger.valueOf(1);
            for (int i = 0; i < eating_periods; i++) {
                BigInteger eating_period = sc.nextBigInteger();
                eid_interval = eating_period.multiply(eid_interval).divide(eating_period.gcd(eid_interval));
            }
            System.out.println("Case " + test + ": " + eid_interval.toString());
            System.gc();
        }
        sc.close();
    }
}

