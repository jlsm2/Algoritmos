#include <bits/stdc++.h>

using namespace std;

struct hashIndex {
    string val;
    hashIndex* next;
};

struct openHashTable {
    hashIndex** hash;
};

hashIndex* newItem(openHashTable* hashTable, string s) {
    hashIndex* newhasht_item = new hashIndex;
    newhasht_item->val = s;
    newhasht_item->next = nullptr;
    return newhasht_item;
} 

int sum(string s) {
    int soma = 0;
    int i = 1;
    for(char c : s) {
        soma += i * int(c);
        i++;
    }
    return soma;
}

int hashFunction(string s, int size) {
    return (sum(s) * 17) % size;
}

void post(openHashTable*& hashTable, string s, int size) {
    int index = hashFunction(s, size);
    hashIndex* hasht_item = newItem(hashTable, s);
    hasht_item->next = hashTable->hash[index];
    hashTable->hash[index] = hasht_item;
}

bool deletar(openHashTable*& hashTable, string s, int size) {
    int index = hashFunction(s, size);
    if (hashTable->hash[index] == nullptr) {
        return false;
    } 
    else {
        hashIndex* cur = hashTable->hash[index];
        hashIndex* prev = nullptr;

        while (cur != nullptr && cur->val != s) {
            prev = cur;
            cur = cur->next;
        }

        if (cur != nullptr) {
            if (prev != nullptr) {
                prev->next = cur->next;
            } 
            else {
                hashTable->hash[index] = cur->next;
            }
            delete cur;
            return true;
        } 
        else {
            return false;
        }
    }
}

void get(openHashTable* hashTable, string s, int size) {
    int index = hashFunction(s, size);
    if (hashTable->hash[index] == nullptr) {
        cout << "404 - NOT FOUND" << "\n";
    } 
    else {
        hashIndex* cur = hashTable->hash[index];
        int n = 1;
        while (cur->val != s && cur->val != "") {
            cur = cur->next;
            n++;
        } 
        if (cur->val == "") {
            cout << "404 - NOT FOUND" << "\n";
        } 
        else {
            cout << index << " " << n << "\n";
        }
    }
}

int main() {
    int m, c, n;
    string ign, command, s;
    
    cin >> m;
    cin >> c;
    openHashTable* Table = new openHashTable;
    Table->hash = new hashIndex*[m];
    
    for (int i=0;i<m;i++) {
        Table->hash[i] = nullptr;
    }
    
    for(int i=0;i<c;i++) {
        cin >> ign;
        cin >> s;
        post(Table, s, m);
    }
    
    cin >> n;
    for(int i=0;i<n;i++) {
        cin >> command;
        cin >> s;
        if (command == "GET") {
            get(Table, s, m);
        }
        else if (command == "POST") {
            post(Table, s, m);
        }
        else {
            if (deletar(Table, s, m)) {
                cout << "DELETADO" << "\n";
            }
        }
    }
    
    return 0;
}
