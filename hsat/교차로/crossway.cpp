#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
vector<long long> t;
vector<string> w;
vector<long long> ans;

queue<int> lane[4];
queue<int> gq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    t.resize(N);
    w.resize(N);
    ans.resize(N, -1); 

    for (int i = 0; i < N; i++) {
        cin >> t[i] >> w[i];
        gq.push(i);
    }

    long long cur_time = -1;
    int cnt = 0;

    while (cnt < N) {
        if (lane[0].empty() && lane[1].empty() && lane[2].empty() && lane[3].empty()) {
            if (!gq.empty()) {
                cur_time = max(cur_time, t[gq.front()]);
            } else {
                break;
            }
        }

        while (!gq.empty() && t[gq.front()] <= cur_time) {
            int idx = gq.front();
            int dir = w[idx][0] - 'A';
            lane[dir].push(idx);
            gq.pop();
        }

        if (!lane[0].empty() && !lane[1].empty() && !lane[2].empty() && !lane[3].empty()) {
            break;
        }

        vector<bool> can_go(4, false);
        for (int i = 0; i < 4; i++) {
            int right = (i + 3) % 4;
            if (!lane[i].empty() && lane[right].empty()) {
                can_go[i] = true;
            }
        }

        bool moved = false;
        for (int i = 0; i < 4; i++) {
            if (can_go[i]) {
                int idx = lane[i].front();
                lane[i].pop();
                ans[idx] = cur_time; 
                cnt++;
                moved = true;
            }
        }

        cur_time++;
    }

    for (int i = 0; i < N; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}