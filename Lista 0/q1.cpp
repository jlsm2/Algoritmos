#include <bits/stdc++.h>
#define endl '\n'
#include <string>

using namespace std;

int main() {
    int ChavesAbrindo = 0;
    int ChavesFechando = 0;
    string entrada;
    getline (cin, entrada);

    for (char i : entrada) {
        if (i == '{') {
            ChavesAbrindo++;
        }
        else if (i == '}') {
            ChavesFechando++;
        }

        if (ChavesFechando > ChavesAbrindo) {
            break;
        }
    }
    
    if (ChavesAbrindo == ChavesFechando) {
        cout << 'S' << '\n';
    }
    else {
        cout << 'N' << '\n';
    }

    return 0;
}
