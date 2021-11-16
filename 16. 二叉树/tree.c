#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    struct tree *left, *right;
    int value;
}tree;

tree *create_node (int value) {
    tree *node = (struct tree*)malloc(sizeof(struct tree));
    if(node==NULL) return NULL;
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    return node;
}

tree *insert(tree *tree, int value) {
   if(tree==NULL) {
       return create_node(value);
   }
   if(value < tree->value) {
       tree->left = insert(tree->left, value);
   } else {
       tree->right = insert(tree->right, value);
   } 
   return tree;
}

void inorder_travese(tree *tree) {
    if(tree != NULL) {
        inorder_travese(tree->left);
        printf("%d\n", tree->value);
        inorder_travese(tree->right);
    }
}

int main() {
    tree *tree = create_node(15);
    int arr[] = {1, 3, 5, 7, 6, 8, 9, 11, 13, 16, 18, 20, 22, 23, 26, 29};
    int length = sizeof(arr) / sizeof(int);
    int i;
    for(i=0;i<length;i++) {
        printf("insert: %d\n", arr[i]);
        insert(tree, arr[i]);
    }
    inorder_travese(tree);
    return 0;
}