#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;

int n, m, k;
vector<vector<int>> graph;
vector<int> people;

int max_dist[100001];
int reach_cnt[100001];

void bfs(int start){
    vector<int> dist(n+1, -1);
    queue<int> q;

    q.push(start);
    dist[start] = 0;

    while(!q.empty()){
        int curr = q.front(); q.pop();

        for (int next : graph[curr]){
            if (dist[next] == -1){
                q.push(next);
                dist[next] = dist[curr] + 1;
            }
        }
    }

    for (int i = 1; i <= n; i++){
        if (dist[i] != -1){
            reach_cnt[i]++;
            max_dist[i] = max(max_dist[i], dist[i]);
        }
    }
}

int main() {
    // Please write your code here.
    cin >> n >> m >> k;

    graph.resize(n+1);

    for (int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
    }
    
    people.resize(k);
    for (int i = 0; i < k; i++){
        cin >> people[i];
    }

    for (int p : people){
        bfs(p);
    }

    int ans = 1e9;
    for (int i = 1; i <= n; i++){
        if (reach_cnt[i] == k){
            ans = min(ans, max_dist[i]);
        }
    }

    if (ans == 1e9) cout << -1;
    else cout << ans;

    return 0;
}