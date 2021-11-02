#include <stdio.h>
#include <stdlib.h>

/* 未完待续 */

typedef struct tree_node{
    struct tree_node *lchild;
    struct tree_node *rchild;
    char data;
}tree_node;

tree_node *create_tree()
{   
    char s;
    tree_node *tree;
    scanf("%c", &s);
    if('#'==s) tree=NULL;
    else{
        tree = (tree_node *)malloc(sizeof(tree_node));
        tree->data = s;
        tree->lchild = create_tree();
        tree->rchild = create_tree();
    }
    return tree;
}

void inorder_treveser(tree_node *tree)
{
    if(tree){
        inorder_treveser(tree->lchild);
        printf("%c\n", tree->data);
        inorder_treveser(tree->rchild);
    }
}

int main()
{   
     tree_node *tree = create_tree();
    inorder_treveser(tree);
    return 0;
}