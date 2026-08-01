#include <iostream>
#include <unordered_map>

using namespace std;

int n, k;
int arr[100000];
unordered_map<int, int> freq;

int main() {
    cin >> n >> k;

    // Please write your code here.
    int cnt = 0;

    for (int i = 0; i < n; i++){
        int x;
        cin >> x;

        int target = k - x;
        if (freq.count(target)){
            cnt += freq[target];
        }

        freq[x]++;
    }

    cout << cnt << "\n";

    return 0;
}
