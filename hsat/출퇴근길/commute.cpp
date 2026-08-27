#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
vector<pair<int, int>> edges;
int S, T;

vector<vector<int>> adj;
vector<vector<int>> rev;

vector<bool> visited_fromS;
vector<bool> visited_fromT;
vector<bool> visited_toT;
vector<bool> visited_toS;

void bfs(int start, const vector<vector<int>>& graph, vector<bool>& visited){
    queue<int> q;

    if (!visited[start]){
        visited[start] = true;
        q.push(start);
    }

    while (!q.empty()){
        int cur = q.front(); q.pop();

        for (int nxt : graph[cur]){
            if (!visited[nxt]){
                q.push(nxt);
                visited[nxt] = true;
            }
        }
    }
}


int main() {
    cin.tie(nullptr);

    cin >> n >> m;
    edges.resize(m);

    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }

    cin >> S >> T; // S - 1번, T - 1번이 집, 회사의 node 

    adj.resize(n + 1);
    rev.resize(n + 1);

    for (int i = 0; i < m; i++){
        int u = edges[i].first;
        int v = edges[i].second;
        adj[u].push_back(v);
        rev[v].push_back(u);
    }

    visited_fromS.resize(n + 1, false);
    visited_fromT.resize(n + 1, false);
    visited_toT.resize(n + 1, false);
    visited_toS.resize(n + 1, false);

    // S -> T
    visited_fromS[T] = true;
    bfs(S, adj, visited_fromS);

    // T -> S
    visited_fromT[S] = true;
    bfs(T, adj, visited_fromT);

    // X -> T 역방향
    bfs(T, rev, visited_toT);

    // X -> S 역방향
    bfs(S, rev, visited_toS);

    int ans = 0;
    for (int i = 1; i <= n; i++){
        if (i == S || i == T) continue;
        if (visited_fromS[i] && visited_toT[i] && visited_fromT[i] && visited_toS[i]){
            ans++;
        }
    }

    cout << ans << "\n";

    return 0;
}
