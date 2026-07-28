#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    int N;
    if (!(cin >> N)) return 0;

    unordered_map<int, int> m;

    while (N--){
        string cmd;
        cin >> cmd;

        if (cmd == "add"){
            int k, v;
            cin >> k >> v;
            m[k] = v;
        }else if (cmd == "find"){
            int k;
            cin >> k;

            if (m.find(k) != m.end()){
                cout << m[k] << "\n";
            }else{
                cout << "None\n";
            }
        }else if (cmd == "remove"){
            int k;
            cin >> k;
            m.erase(k);
        }
    }


    return 0;
}