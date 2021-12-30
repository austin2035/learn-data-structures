/* 二叉搜索树 (binary search tree, BST) */


#include <stdio.h>
#include <stdlib.h>

#define BST_NODE_CHILD 0
#define BST_NODE_PARENT 1

/* BST的节点 */
typedef struct bst_node
{
    /* 关键字项 */   
    int key;
    /* 左孩子 */
    struct bst_node *left;
    /* 右孩子 */
    struct bst_node *right;
    /* 这里还可以带上其他数据，比如 void *value */
}bst_node;


/* BST本身 */
typedef struct bst {
    /* 树的根节点 */
    struct bst_node *root;
    /* 树的节点数量 */
    int size;
}bst;


/* 创建一棵空二叉排序树 */
bst *bst_create(void) {
    bst *bst = (struct bst*)malloc(sizeof(struct bst));
    if(bst==NULL) return NULL;
    bst->root = NULL;
    bst->size = 0;
    return bst;
}

/* 创建一个BST的节点 */
bst_node *bst_create_node(int key) {
    bst_node *node = (struct bst_node*)malloc(sizeof(struct bst_node));
    if(node==NULL) return NULL;
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    return node;
}

/* Return：一个节点指针
 * Args:
 *   bst：在此树或子树中查找
 *   type：节点类型：
 *      BST_NODE_CHILD：叶子节点
 *      BST_NODE_PARENT：父节点 
 *   key：要查找的节点key值
 * 
 * 注意：在查找给定参数key的父节点时，即便在树中没有任何节点的key等于给定的参数key
 * (说明树中没有这个节点)，也会返回一个它的理论父节点。
 */

bst_node *bst_search_node(bst_node *node, int type, int key)
{

    bst_node *current = node;
    bst_node *parent = NULL;

    if(current==NULL) return NULL;
    while (current != NULL)
    {
        if(key < current->key) {
            parent = current;
            current = current->left;
        } else if(key == current->key) {
            break;
        } else{
            parent = current;
            current = current->right;
        }
    }

    if(type == BST_NODE_CHILD) return current;
    return parent;
}

/* 搜索给定子树中，关键字最大的节点或者它的父节点 */
bst_node *bst_find_max_node(bst_node *node, int type)
{
    bst_node *current = node;
    bst_node *parent = NULL;
    if(current==NULL) return NULL;
    while (current->right != NULL)
    {   
        parent = current;
        current = current->right;
    }
    if(type==BST_NODE_CHILD) return current;
    return parent;
}

/* 插入一个节点 */
bst *bst_insert_node(bst *bst, int key)
{
    bst_node *current = bst->root;
    bst_node *parent = NULL;
    /* 如果是空二叉搜索树，则直接新建节点作为根节点即可 */
    if (current==NULL) {
        bst->root = bst_create_node(key);
    } else {
        /* 找到要插入节点的父节点 */
        parent = bst_search_node(bst->root, BST_NODE_PARENT, key);
        if(parent==NULL) return NULL;
        /* 与父节点比大小，看应该在父节点的左子树还是右子树 */
        if(key < parent->key) {
            parent->left = bst_create_node(key);
        } else if(key == parent->key)  {
            /* 如果key重复则取消插入 */
            return NULL;
        } else {
            parent->right = bst_create_node(key);
        }
    }
    /* 二叉搜索树的节点数增加1 */
    bst->size ++;
    return bst;
}

/* 删除一个节点，存在三种情况
 *      1. 该节点是终端节点，删除后不影响树的结构，直接删除即可
 *      2. 该节点有父节点，但只有一个分支，删除后不影响结构，直接删除。
 *      3. 该节点有两个分支，删除后需要重建树。重建的思路有两个，第一种
 *         是寻找该节点左子树中key值最小的节点，并替换该节点。第二种是，
 *         寻找该节点右子树中key值最大的节点，并替换改节点，以使树的结构保持不变。
 */
void bst_delete_node(bst *bst, int key)
{
    bst_node *parent = bst_search_node(bst->root, BST_NODE_PARENT, key);
    bst_node *current, *temp, *max;
    current = bst_search_node(parent, BST_NODE_CHILD, key);

    /* 如果这是一颗只有根节点的树 (情况 1)*/
    if(parent==NULL && current==NULL) {
        temp = bst->root;
        bst->root = NULL;
    }
    /* 如果该节点是终端节点 （情况 1） */
    else if(current->left==NULL && current->right==NULL) {
        /* 易错点，可能会写成parent->left->key == current->key */
        if(current->key < parent->key) {
            temp = parent->left;
            parent->left = NULL;
        } else {
            temp = parent->right;
            parent->right = NULL;
        }
    }
    /* 如果该节点左子树为空（情况 2） */ 
    else if(current->left==NULL) {
        temp = current->right;
        current->key = current->right->key;
        current->left = current->right->left;
        current->right = current->right->right;
    }
    /* 如果该节点右子树为空（情况 2） */ 
    else if(current->right==NULL) {
        temp = current->left;
        current->key = current->left->key;
        current->left = current->left->left;
        current->right = current->left->right;
    }
    /* 如果该节点左右子树都不为空（情况 3） */
    else {
        max = bst_find_max_node(current->left, BST_NODE_PARENT);
        /* 如果被删除的节点，其左子树中最大的节点的父节点为空，则说明该节点左子树中最大的节点为此被删除节点的左孩子。 */
        if (max==NULL) {
            temp = current->left;
            current->key = current->left->key;
            current->left = current->left->left;
        } else {
            temp = max->right;
            current->key = max->right->key;
            max->right = max->right->left;
        }
    }
    free(temp);
    bst->size--;
    return ;
}

/* 中序遍历 */
void bst_inorder_traversal(bst_node *node) {
    if(node != NULL) {
        bst_inorder_traversal(node->left);
        printf("%d\t", node->key);
        bst_inorder_traversal(node->right);
    } 
}

int main() {
    bst *bst = bst_create();
    int arr[] = {21, 3, 5, 26, 29, 50, 18, 53, 8, 67, 1, 78, 6};
    //int arr[] = {5, 6, 4};
    int length = sizeof(arr) / sizeof(int);
    int i;
    
    for(i=0;i<length;i++) {
        bst_insert_node(bst, arr[i]);
        printf("size: %d ", bst->size);
        printf("Inorder Traversal: ");
        bst_inorder_traversal(bst->root);
        printf("\n");
    }

    for(i=length-1;i>=0;i--) {
        bst_delete_node(bst, arr[i]);
        printf("size: %d ", bst->size);
        printf("Inorder Traversal: ");
        bst_inorder_traversal(bst->root);
        printf("\n");
    }
    /* 释放这棵二叉树 */
    free(bst);
    return 0;
}