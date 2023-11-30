#include <iostream>
#include <string>
using namespace std;

struct tree {
    int data, height;
    tree* left;
    tree* right;
};

tree* root;

tree* newNode(int data) {  
    tree* node = new tree(); 
    node->data = data;  
    node->left = nullptr;  
    node->right = nullptr;  
    node->height = 1;
    
    return node;  
}

tree* search(tree* root, int x) {
	if(root == nullptr) {
		return 0;
	}
	else if(root->data == x) {
		return root;
	}
	else if(x < root->data) {
		return search(root->left, x);
	}
	else {
		return search(root->right, x);
	}
}

int getHeight(tree *x) {
    if (x == nullptr) {
        return 0;
    }
    return x->height;
}

int printHeight(tree* root, int num, int h=0) {
    if (root == nullptr) {
        return -1;
    }

    else if (num == root->data) {
        return h;
    }

    else if (num < root->data && root != nullptr) {
        root = root->left;
        return printHeight(root, num, h+=1);
    }
    else if (num > root->data && root != nullptr) {
        root = root->right;
        return printHeight(root, num, h+=1);
    }
}

int max(int a, int b)  {  
    return (a > b)? a : b;  
}  

int getFB (tree *x) {
    if (x == nullptr) {
        return 0;
    }
    return getHeight(x->left) - getHeight(x->right);
}

tree* min(tree* node) { 
    tree *current = node; 

    while (current->left != nullptr) { 
        current = current->left; 
    }
 
    return current; 
} 

tree *rightRotate(tree *y) {
    tree *x = y->left;
    tree *z = x->right;

    x->right = y;
    y->left = z;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

tree *leftRotate(tree *x) {
    tree *y = x->right;
    tree *z = y->left;

    y->left = x;
    x->right = z;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}


tree* insert(tree* node, int data) {  
    if (node == nullptr) {
        return newNode(data);
    }
  
    if (data < node->data) {  
        node->left = insert(node->left, data);
    }
    
    else if (data > node->data) {  
        node->right = insert(node->right, data);
    }
    
    else {  
        return node;
    }
  
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  
    int FB = getFB(node);  
  
    if (FB >= 2 && data < node->left->data) {
        return rightRotate(node);
    }
  
    if (FB <= -2 && data > node->right->data)  
        return leftRotate(node);  
  
    if (FB >= 2 && data > node->left->data)  
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  

    if (FB <= -2 && data < node->right->data)  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }
  
    return node;
}


tree* remover(tree* node, int data) {
    if (node == nullptr) {
        return node;
    }

    if (data < node->data) {
        node->left = remover(node->left, data);
    } 
    else if (data > node->data) {
        node->right = remover(node->right, data);
    } 
    else {
        if ((node->left == nullptr) || (node->right == nullptr)) {
            tree* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }

            delete temp;
        } 
        else {
            tree* temp = min(node->right);

            node->data = temp->data;

            node->right = remover(node->right, temp->data);
        }
    }

    if (node == nullptr) {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int FB = getFB(node);

    if (FB >= 2 && getFB(node->left) >= 0) {
        return rightRotate(node);
    }

    if (FB >= 2 && getFB(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (FB <= -2 && getFB(node->right) <= 0) {
        return leftRotate(node);
    }

    if (FB <= -2 && getFB(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


int maxvalue(tree* node) {
    tree* current = node;
    while (current->right != nullptr) {
        current = current->right;
    }
    return (current->data);
}

tree* lastValue_preorder(tree* node) {
    if (node == nullptr) {
        return nullptr;
    }
    tree* xLeft = lastValue_preorder(node->left);
    tree* xRight = lastValue_preorder(node->right);
    if (xRight != nullptr) {
        return xRight;
    } 
    else if (xLeft != nullptr) {
        return xLeft;
    } 
    else {
        return node;
    }
}

void Preordem(tree *node, int lastValue) {
    if (node != nullptr) {
        cout << node->data;
        if (node->data != lastValue) {
            cout << ",";
        }  
        Preordem(node->left, lastValue);
        Preordem(node->right, lastValue); 
    }
} 

void Emordem(tree* node, int max) {
    if (node != nullptr) {
        Emordem(node->left, max);
        cout << node->data;
        if (node->data != max) {
            cout << ",";
        }
        Emordem(node->right, max);
    }
}

void Posordem(tree* node) {
    if (node != nullptr) {
        Posordem(node->left);
        Posordem(node->right);
        cout << node->data;
        if (node->data != root->data) {
            cout << ",";
        }  
    }
}

int main() {
    string command;
    int num, a;
    while (true) {
        cin >> command;
        if (command == "ADICIONA") {
            cin >> num;
            root = insert(root, num);
        }
        else if (command == "REMOVE") {
            cin >> num;
            if (search(root, num) == 0) {
                  cout << "Valor " << num << " inexistente" << "\n";
            }
            else {
                root = remover(root, num);
            }
        }
        else if (command == "NIVEL") {
            cin >> num;
            a = printHeight(root, num);
            if (a==-1) {
                  cout << "Valor " << num << " inexistente" << "\n";
            }
            else {
                cout << "Nivel de " << num << ": " << a << "\n";
            }
        }
        else if (command == "PRINT") {
            cin >> command;
            if (command == "PREORDEM") {
                if (root == nullptr) {
                    cout << "[]" << "\n";
                }
                else {
                    cout << "[";
                    Preordem(root, lastValue_preorder(root)->data);
                    cout << "]" << "\n";
                }
            }
            else if (command == "EMORDEM") {
                if (root == nullptr) {
                    cout << "[]" << "\n";
                }
                else {
                    cout << "[";
                    Emordem(root, maxvalue(root));
                    cout << "]" << "\n";
                }
            }
            else if (command == "POSORDEM") {
                if (root == nullptr) {
                    cout << "[]" << "\n";
                }
                else {
                    cout << "[";
                    Posordem(root);
                    cout << "]" << "\n";
                }
            }
        }
        else if (command == "FIM") {
            break;
        }
    }
    
    return 0;
}
