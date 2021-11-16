#include <stdio.h>
#include <stdlib.h>

typedef struct bst_node
{
    int val;
    struct bst_node *left;
    struct bst_node *right;
}bst_node;

typedef struct bst {
    struct bst_node *root;
    int size;
}bst;

bst *bst_create(void) {
    bst *bst = (struct bst*)malloc(sizeof(struct bst));
    if(bst==NULL) return NULL;
    bst->root = NULL;
    bst->size = 0;
    return bst;
}

bst_node *bst_create_node(int val) {
    bst_node *node = (struct bst_node*)malloc(sizeof(struct bst_node));
    if(node==NULL) return NULL;
    node->left = NULL;
    node->right = NULL;
    node->val = val;
    return node;
}

bst *bst_insert_node(bst *bst, int val) {
    bst_node *curr = bst->root;
    bst_node *parent = NULL;

    if (curr==NULL)
    {
        bst->root = bst_create_node(val);
    }

    while (curr != NULL)
    {
        if(val < curr->val) {
            parent = curr;
            curr = curr->left;
        } else if(val == curr->val) {
            break;
        } else{
            parent = curr;
            curr = curr->right;
        }
    }
    
    if(parent != NULL) {
        if(val < parent->val) {
            parent->left = bst_create_node(val);
        } else {
            parent->right = bst_create_node(val);
        }
    }

    bst->size ++;
    return bst;
}

void bst_inorder_traversal(bst_node *node) {
    if(node != NULL) {
        bst_inorder_traversal(node->left);
        printf("%d\t", node->val);
        bst_inorder_traversal(node->right);
    } 
}

int main() {
    bst *bst = bst_create();
    int arr[] = {1, 1, 3, 5, 7, 6, 8, 9, 11, 13, 16, 18, 20, 22, 23, 26, 29};
    int length = sizeof(arr) / sizeof(int);
    int i;
    for(i=0;i<length;i++) {
        printf("insert: %d\n", arr[i]);
        bst_insert_node(bst, arr[i]);
    }
    bst_inorder_traversal(bst->root);
    printf("\n");
    return 0;
}