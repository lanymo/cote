#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
typedef long long ll;

string digital_logic;
int K, M;
unordered_map<ll, int> counts;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> digital_logic;
    cin >> K >> M;

    ll curKey = 0;
    ll mask = (1LL << K) - 1; // k 개 비트 마스크 

    for (int i = 0; i < K; i++){
        curKey = (curKey << 1) | (digital_logic[i] - '0');
    }
    counts[curKey]++;

    for (int i = K; i < digital_logic.length(); i++){
        curKey = ((curKey << 1) | (digital_logic[i] - '0')) & mask;
        counts[curKey]++;

        if (counts[curKey] >= M){
            cout << 1 << "\n";
            return 0;
        }
    }

    cout << 0 << "\n";
    return 0;
}
