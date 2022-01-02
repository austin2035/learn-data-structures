#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


#define AVL_NODE_CHILD 0
#define AVL_NODE_PARENT 1

/* 平衡二叉树的节点 */
typedef struct avl_node {
    /* 关键字 */
    int key;

    /* 左右节点指针 */
    struct avl_node *left;
    struct avl_node *right;

    /* 节点的高度 */
    int height;
}avl_node;


/* 平衡树二叉树本身 */
typedef struct avl {
    /* 指向二叉树根节点 */
    struct avl_node *root;
    /* 树的节点数 */
    int size;
}avl;


/* 创建一个节点 */
avl_node *avl_create_node(int key)
{
    avl_node *node = (struct avl_node*)malloc(sizeof(struct avl_node));
    if(node==NULL) return NULL;
    node->height = 1;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}


/* 返回一个节点的高度 */
int avl_height(avl_node *node)
{
    if(node==NULL) return 0;
    return node->height;
}

/* 比较一个key和一个节点的key的大小
 * 如果key比较大，返回真，否则返回假。
 */
int avl_compare_key(int key, avl_node *node)
{
    if(node==NULL) return 0;
    if(key > node->key) return 1;
    return 0;
}

/* 返回两个节点中的高度较大值 */
int max(avl_node *x, avl_node *y)
{
    int m = avl_height(x);
    int n = avl_height(y);

    return m>=n?m:n;
}

/* 创建一棵平衡二叉树 */
avl *avl_create(void)
{
    avl *avl = (struct avl*)malloc(sizeof(struct avl));
    if(avl==NULL) return NULL;
    avl->root = NULL;
    avl->size = 0;
    return avl;
}

/* 中序遍历 */
void avl_inorder_traversal(avl_node *node) {
    if(node != NULL) {
        avl_inorder_traversal(node->left);
        printf("%d\t", node->key);
        avl_inorder_traversal(node->right);
    } 
}

/* LL型，需要向右旋 */
avl_node *avl_rotate_ll(avl_node *node)
{
    /* 新的“根” */
    avl_node *top = node->left;
    node->left = top->right;
    top->right = node;
    /* 重新计算高度, 注意：node与top的高度计算次序千万不能颠倒 */
    node->height = max(node->left, node->right) + 1;
    top->height = max(top->left, top->right) + 1;

    return top;
}

/* RR型，需要向左旋 */
avl_node *avl_rotate_rr(avl_node *node)
{

    avl_node *top = node->right;
    node->right = top->left;
    top->left = node;
    /* 重新计算高度 */
    node->height = max(node->left, node->right) + 1;
    top->height = max(top->left, top->right) + 1;
    return top;
}

/* LR型，先左旋再右旋 */
avl_node *avl_balance_lr(avl_node *node)
{
    node->left = avl_rotate_rr(node->left);
    return avl_rotate_ll(node);
}

/* RL型，先右旋再左旋 */
avl_node *avl_balance_rl(avl_node *node)
{
    node->right = avl_rotate_ll(node->right);
    return avl_rotate_rr(node);
}

/* 搜索节点 */
avl_node *avl_search_node(avl_node *node, int type, int key)
{

    avl_node *current = node;
    avl_node *parent = NULL;

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

    if(type == AVL_NODE_CHILD) return current;
    return parent;
}

/* 平衡树二叉树，插入一个节点 */
avl *avl_insert_node(avl *avl, int key)
{

    stack *stack = stack_create();
    
    avl_node *current, *parent;
    current = avl->root;

    /* 如果是空树则直接插入 */
    if(current==NULL) {
        avl->root = avl_create_node(key);
        avl->size++;
        stack_release(stack);
        return avl;
    }
    
    /* 找到待插入节点的位置，同时将路过的节点放入栈中 */
    while (current != NULL)
    {
        stack_push(stack, current);
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

    /* 插入节点 */
    if(key < parent->key) {
        parent->left = avl_create_node(key);
    } else if(key == parent->key)  {
        stack_release(stack);
        return NULL;
    } else {
        parent->right = avl_create_node(key);
    }

    /* 回溯经过的节点，判断是否需要调整 */
    while (stack->length)
    {
        current = stack_pop(stack);
        /* 注意：这里只是取栈顶元素，并没有出栈 */
        parent = stack->top == NULL ? NULL : stack->top->data;
        /* 调整高度 */
        current->height = max(current->left, current->right) + 1;
        /* 计算平衡因子 (balance factor) */
        int bf = avl_height(current->left) - avl_height(current->right);
        printf("回退：%d, left: %d , right: %d , bf: %d\n", current->key, avl_height(current->left), avl_height(current->right), bf);
        /* 可能是RR或者RL型 */
        if(bf == -2) {
            /* 如果插入key比当前最小不平衡子树的右子树key大,则是RR型 */
            if(avl_compare_key(key, current->right)) {
                /* 最小不平衡子树，是否有父节点 */
                if(parent == NULL){
                    avl->root = avl_rotate_rr(current);
                } else {
                    /* 如果有父节点，则需要判断，该最小不平衡子树属于父节点的左子树还是右子树 */
                    if(current->key > parent->key) {
                        parent->right = avl_rotate_rr(current);
                    } else {
                        parent->left = avl_rotate_rr(current);
                    }
                }
            }
            /* 否则就是RL型 */
            else { 
                if(parent==NULL) {
                    avl->root = avl_balance_rl(current);
                } else {
                    if(current->key > parent->key) {
                        parent->right = avl_balance_rl(current);
                    } else {
                        parent->left = avl_balance_rl(current);
                    }
                }
            }
        }
        else if(bf==2) {
            /* LR型 */
            if(avl_compare_key(key, current->left)) {
                if(parent==NULL) {
                    avl->root = avl_balance_lr(current);
                } else {
                    if(current->key > parent->key) {
                        parent->right = avl_balance_lr(current);
                    } else {
                        parent->left = avl_balance_lr(current);
                    }
                }
            }
            /* LL型 */
            else {
                if(parent==NULL) {
                    avl->root = avl_rotate_ll(current);
                } else {
                    if(current->key > parent->key) {
                        parent->right = avl_rotate_ll(current);
                    } else {
                        parent->left = avl_rotate_ll(current);
                    }
                }
            }
        }
        if(parent != NULL) {
            parent->height = max(parent->left, parent->right) + 1;
        }
    }

    avl->size++;
    stack_release(stack);
    return avl;
}


int main()
{
    avl *avl = avl_create();
    
    int arr[] = {21, 3, 5, 26, 29, 50, 18, 53, 8, 67, 1, 78, 6};
    //int arr[] = {  21, 3, 5, 26, 29, 50};
    int length = sizeof(arr) / sizeof(int);
    int i;
    for(i=0;i<length;i++) {
        printf("--------\n");
        printf("插入：%d\n", arr[i]);
        avl_insert_node(avl, arr[i]);
        printf("中序: ");
        avl_inorder_traversal(avl->root);
        printf("\n");
    }
    return 0;
}