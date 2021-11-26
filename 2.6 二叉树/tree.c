#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"


/* 树的节点 */
typedef struct tree_node {
    /* 左孩子指针 */
    struct tree_node *left;
    /* 右孩子指针 */
    struct tree_node *right;
    /* 关键字 */
    char key;
}tree_node;


/* 创建一个节点 */
tree_node *tree_create_node(char key)
{
    tree_node *node = (struct tree_node*)malloc(sizeof(struct tree_node));
    if(node==NULL) return NULL;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

/* 创建一棵二叉树 */
tree_node *tree_create()
{
    char str;
    tree_node *current;   
    scanf("%c", &str);
    if('#' == str)
    {
        current = NULL;   
    } 
    else {
        current = tree_create_node(str);
        current->left = tree_create();
        current->right = tree_create();
    }
    return current;
}


/* 前序遍历1 */
void preorder_traverse1(tree_node *node)
{
    if(node != NULL) {
        printf("%c\t", node->key);
        preorder_traverse1(node->left);
        preorder_traverse1(node->right);
    }
}

/* 前序遍历2 */
void preorder_traverse2(tree_node *node)
{
    stack *stack = stack_create();
    tree_node *current = node;   
    
    while (current != NULL || stack->length)
    {
        if(current != NULL) {
            printf("%c\t", current->key);
            stack_push(stack, current);
            current = current->left;
        } else {
            current = stack_pop(stack);
            current = current->right;
        }
    }
    
    stack_release(stack);
}

/* 中序遍历 */
void inorder_traverse1(tree_node *node)
{
    if(node != NULL) {
        inorder_traverse1(node->left);
        printf("%c\t", node->key);
        inorder_traverse1(node->right);
    }
}

/* 中序遍历2 */
void inorder_traverse2(tree_node *node)
{
    stack *stack = stack_create();
    tree_node *current = node;   
    
    while (current != NULL || stack->length)
    {
        if(current != NULL) {
            stack_push(stack, current);
            current = current->left;
        } else {
            current = stack_pop(stack);
            printf("%c\t", current->key);
            current = current->right;
        }
    }

    stack_release(stack);
}

/* 后序遍历 */
void postorder_traverse1(tree_node *node)
{
    if(node != NULL) {
        postorder_traverse1(node->left);
        postorder_traverse1(node->right);
        printf("%c\t", node->key);
    }
}

/* 后序遍历2 */
void postorder_traverse2(tree_node *node)
{
    stack *s = stack_create();
    stack *stack = stack_create();

    tree_node *current = node;   
    
    while (current != NULL || stack->length)
    {
        if(current != NULL) {
            stack_push(s, &(current->key));
            stack_push(stack, current);
            current = current->right;
        } else {
            current = stack_pop(stack);
            current = current->left;
        }
    }
    while (s->length)
    {
        printf("%c\t", *(char *)stack_pop(s));
    }
    stack_release(s);
    stack_release(stack);
}

/* 层次遍历 */
void level_traversel(tree_node *root)
{
    /* 创建一个队列 */
    queue *queue = queue_create();
    

    if(root != NULL)
    {
        queue_push_data(queue, root);
    }

    while (queue->length)
    {
        tree_node *current = queue_pull_data(queue);
        printf("%c\t", current->key);
        if(current->left) queue_push_data(queue, current->left);
        if(current->right) queue_push_data(queue, current->right);
    }

    /* 队列用完后，释放 */
    queue_release(queue);
}


int main() {

    /* ABD##E##CF##G## */
    tree_node *root = tree_create();

    printf("\n前序遍历1：");
    preorder_traverse1(root);
    
    printf("\n前序遍历2：");
    preorder_traverse2(root);

    printf("\n\n中序遍历1：");
    inorder_traverse1(root);
    
    printf("\n中序遍历2：");
    inorder_traverse2(root);

    printf("\n\n后序遍历1：");
    postorder_traverse1(root);
    
    printf("\n后序遍历2：");
    postorder_traverse2(root);

    printf("\n\n层次遍历0：");
    level_traversel(root);
    printf("\n");
    return 0;
}