#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    // Please write your code here.
    int N; cin >> N;

    map<int, int> m;

    for (int i = 0; i < N; i++){
        string cmd;
        cin >> cmd;

        if (cmd == "add"){
            int k, v; cin >> k >> v;
            m[k] = v;
        }else if (cmd == "find"){
            int k; cin >> k;
            if (m.find(k) !=  m.end()){
                cout << m[k] << "\n";
            }else{
                cout << "None\n";
            }
        }else if (cmd == "remove"){
            int k; cin >> k;
            m.erase(k);
        }else if (cmd == "print_list"){
            if (m.empty()){
                cout << "None\n";
            }else{
                for (auto it = m.begin(); it != m.end(); it++){
                    cout << it->second << " ";
                }
                cout << "\n";
            }
        }
    }
    return 0;
}