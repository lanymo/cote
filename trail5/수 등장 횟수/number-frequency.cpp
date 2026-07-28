#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    // Please write your code here.
    int N, M; cin >> N >> M;

    unordered_map<int, int> cnt;

    for (int i = 0; i < N; i++){
        int a; cin >> a;
        cnt[a]++;
    }

    for(int i = 0; i < M; i++){
        int q;
        cin >> q;
        cout << cnt[q] << " ";
    }
    return 0;
}