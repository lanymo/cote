#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int first_cards[1000];
int second_cards[1000];
int dp[1005][1005];

int solve(int i, int j){
    if (i == n || j == n) return 0;

    if (dp[i][j] != -1) return dp[i][j];

    int ret = 0;

    if (first_cards[i] > second_cards[j]){
        ret = max(ret, solve(i, j + 1) + second_cards[j]);
    }

    if (first_cards[i] < second_cards[j]){
        ret = max(ret, solve(i + 1, j));
    }

    ret = max(ret, solve(i + 1, j + 1));

    return dp[i][j] = ret;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> first_cards[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> second_cards[i];
    }

    // Please write your code here.
    memset(dp, -1, sizeof(dp));

    cout << solve(0, 0);

    return 0;
}
