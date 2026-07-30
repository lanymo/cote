#include <iostream>
#include <algorithm>
using namespace std;

#define INT_MIN -1e16

int arr[100001];
int dp[100001];

int main() {
    // Please write your code here.
    int N; cin >> N;

    for (int i = 0; i < N; i++){
        cin >> arr[i];
        dp[i] = INT_MIN;
    }

    dp[0] = arr[0];

    for (int i = 1; i < N; i++){
        dp[i] = max(dp[i-1] + arr[i], arr[i]);
    }

    int ans = INT_MIN;
    for (int i = 0; i < N; i++){
        ans = max(ans, dp[i]);
    }

    cout << ans;

    return 0;
}