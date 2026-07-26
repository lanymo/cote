#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, q;
int m;
vector<int> fuel;

#define all(x) (x).begin(), (x).end()

int main() {
    cin >> n >> q;

    for (int i = 0; i < n; i++){
        int f; cin >> f;
        fuel.push_back(f);
    }

    sort(all(fuel));

    for (int i = 0; i < q; i++){
        cin >> m;

        //auto it = find(all(fuel), m);
        auto it = lower_bound(all(fuel), m);
        if (it == fuel.end() || *it != m){
            cout << 0 << "\n";
            continue;
        }

        int m_idx = it - fuel.begin();

        long long ans = (long long)m_idx * (n - 1 - m_idx);
        cout << ans << "\n";
    }


    return 0;
}