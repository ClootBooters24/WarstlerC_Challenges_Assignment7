#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string input;

    while(true) {
        cin >> input;

        if(input == "0") {
            return 0;
        }

        vector<long long> dp(input.length() + 1);

        dp[0] = 1;
        dp[1] = input[0] != '0' ? 1 : 0;

        for(int i = 2; i <= input.length(); i++) {
            int oneDigit = stoi(input.substr(i - 1, 1));
            int twoDigit = stoi(input.substr(i - 2, 2));

            if(oneDigit >= 1) {
                dp[i] += dp[i - 1];
            }
            if(twoDigit >= 10 && twoDigit <= 26) {
                dp[i] += dp[i - 2];
            }
        }
        cout << dp[input.length()] << endl;
    }

    return 0;
}