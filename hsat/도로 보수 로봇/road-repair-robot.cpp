#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int N, K;
vector<ll> positions;
int len = 1;

int main() {
    cin >> N >> K;

    positions.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> positions[i];
    }

    ll left = 0; ll right = positions.back() - positions.front();

    while (left < right){
        ll mid = (left + right) / 2;

        // mid로 채울 수 있는지 확인
        int used = 1; // 첫 번째 구멍 막으면서 시작 
        ll start_pos = positions[0]; // 패치가 시작된 구멍의 위치

        for (int i = 1; i < N; i++){
            if (positions[i] - start_pos > mid){
                used++;
                start_pos = positions[i];
            }
        }


        if (used <= K) {
            right = mid;
        }else{
            left = mid + 1;
        }
    }

    cout << left + 1 << "\n";

    return 0;
}
