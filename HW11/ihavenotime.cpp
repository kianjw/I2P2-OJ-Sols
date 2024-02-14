#include <iostream>
#include <climits>

using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        int arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        long long dp[305][305] = {};
        long long pre[305] = {};

        for (int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] + arr[i - 1];
        }

        for (int i = 1; i <= n; i++) {
            dp[i][1] = pre[i];
        }

        for (int i = 2; i <= n; i++) {
            int mini = min(i, k);
            for (int j = 2; j <= mini; j++) {
                dp[i][j] = LLONG_MAX;
                for (int alpha = j - 1; alpha < i; alpha++) {
                    dp[i][j] = min(max(dp[alpha][j - 1], pre[i] - pre[alpha]), dp[i][j]);
                }
            }
        }

        cout << dp[n][k] << endl;
    }

    return 0;
}
