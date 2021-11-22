#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    struct tree *left, *right;
    int value;
}node;

typedef struct tree {
    struct node *root;
    int size;
}tree;



void inorder_travese(node *node) {
    if(node != NULL) {
        inorder_travese(node->left);
        printf("%d\n", node->value);
        inorder_travese(node->right);
    }
}

int main() {
    int arr[] = {1, 3, 5, 7, 6, 8, 9, 11, 13, 16, 18, 20, 22, 23, 26, 29};
    int length = sizeof(arr) / sizeof(int);
    return 0;
}