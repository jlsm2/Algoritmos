#include <bits/stdc++.h>
#define endl '\n'
#include <iostream>
#include <string>

using namespace std;

int main() {

    string maior_lista = "[]";
    int virgulas_atual = 0;
    
    while (1) {
        string linha;
        int virgulas = 0;
        getline(cin,linha);

        if (linha == "") {
            break;
        }

        for (char i : linha) {
            if (i == ',') {
                virgulas++;
            }
        }

        if (virgulas == 0 && maior_lista == "[]") {
            maior_lista = linha;
        }

        if (virgulas > virgulas_atual) {
            virgulas_atual = virgulas;
            maior_lista = linha;
        }
    }

    cout << maior_lista << '\n';

    return 0;
}
