#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    int height;
};

Node* root = NULL;

// height
int height(Node* n){
    if(n == NULL) return -1;
    return n->height;
}

// maximum
int maximum(int a, int b){
    if(a > b) return a;
    else return b;
}

// right rotate
Node* rightRotate(Node* node){
    Node* child = node->left;
    Node* temp = child->right;

    child->right = node;
    node->left = temp;

    node->height = maximum(height(node->left), height(node->right)) + 1;
    child->height = maximum(height(child->left), height(child->right)) + 1;

    return child;
}

// left rotate
Node* leftRotate(Node* node){
    Node* child = node->right;
    Node* temp = child->left;

    child->left = node;
    node->right = temp;

    node->height = maximum(height(node->left), height(node->right)) + 1;
    child->height = maximum(height(child->left), height(child->right)) + 1;

    return child;
}

// insert
Node* insert(Node* node, int value){
    if(node == NULL){
        Node* temp = new Node();
        temp->data = value;
        temp->left = temp->right = NULL;
        temp->height = 0;
        return temp;
    }

    if(value < node->data)
        node->left = insert(node->left, value);
    else
        node->right = insert(node->right, value);

    node->height = maximum(height(node->left), height(node->right)) + 1;

    int balance = height(node->left) - height(node->right);

    if(balance > 1 && value < node->left->data)
        return rightRotate(node);

    if(balance < -1 && value > node->right->data)
        return leftRotate(node);

    if(balance > 1 && value > node->left->data){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if(balance < -1 && value < node->right->data){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// minimum
Node* minimum(Node* node){
    while(node->left != NULL)
        node = node->left;
    return node;
}

// delete
Node* del(Node* node, int value){
    if(node == NULL) return node;

    if(value < node->data)
        node->left = del(node->left, value);
    else if(value > node->data)
        node->right = del(node->right, value);
    else{
        if(node->left == NULL || node->right == NULL){
            Node* temp;

            if(node->left != NULL)
                temp = node->left;
            else
                temp = node->right;

            if(temp == NULL){
                delete node;
                return NULL;
            }
            else{
                *node = *temp;
                delete temp;
            }
        }
        else{
            Node* temp = minimum(node->right);
            node->data = temp->data;
            node->right = del(node->right, temp->data);
        }
    }

    node->height = maximum(height(node->left), height(node->right)) + 1;

    int balance = height(node->left) - height(node->right);

    if(balance > 1 && height(node->left->left) >= height(node->left->right))
        return rightRotate(node);

    if(balance > 1 && height(node->left->left) < height(node->left->right)){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if(balance < -1 && height(node->right->right) >= height(node->right->left))
        return leftRotate(node);

    if(balance < -1 && height(node->right->right) < height(node->right->left)){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// search (void)
void search(Node* node, int key){
    if(node == NULL){
        cout << "Not Found";
        return;
    }

    if(node->data == key){
        cout << "Found";
        return;
    }

    if(key < node->data)
        search(node->left, key);
    else
        search(node->right, key);
}

// display
void show(Node* node){
    if(node != NULL){
        cout << node->data << " ";
        show(node->left);
        show(node->right);
    }
}

int main(){
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    cout << "Tree: ";
    show(root);

    cout << "\nDelete 30\n";
    root = del(root, 30);

    cout << "After delete: ";
    show(root);

    int key;
    cout << "\nEnter value: ";
    cin >> key;

    search(root, key);

    return 0;
}
