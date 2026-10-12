class Solution {
public:
    int myAtoi(string s) {
        int i = 0;
        int n = s.length();

        // Step 1: Skip leading spaces
        while (i < n && s[i] == ' ') {
            i++;
        }

        // Step 2: Check the sign
        int sign = 1;

        if (i < n && s[i] == '-') {
            sign = -1;
            i++;
        } 
        else if (i < n && s[i] == '+') {
            i++;
        }

        // Step 3: Convert digits into a number
        long long num = 0;
        long long limit = (sign == 1) ? INT_MAX : 2147483648LL;

        while (i < n && s[i] >= '0' && s[i] <= '9') {
            int digit = s[i] - '0';

            // Step 4: Check overflow before adding the digit
            if (num > (limit - digit) / 10) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }

            num = num * 10 + digit;
            i++;
        }

        // Step 5: Return the signed integer
        return (int)(sign * num);
    }
};