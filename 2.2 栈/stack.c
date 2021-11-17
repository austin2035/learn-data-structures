#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* 创建栈 */
stack *stack_create()
{
    stack *stack =  (struct stack*)malloc(sizeof(struct stack));
    /* 等价写法：
    stack *s =  (stack*)malloc(sizeof(stack)); */
    if(stack==NULL) return NULL;
    /* 初始化 */
    stack->length = 0;
    stack->top = NULL;
    return stack;
}

/* 入栈 */
stack *stack_push(stack *stack, void *data)
{
    /* 创建一个节点 */
    stack_node *node = (struct stack_node*)malloc(sizeof(struct stack_node));
    if(node==NULL) return NULL;
    node->data = data;

    /* 插入 */
    node->next = stack->top;
    stack->top = node;

    stack->length++;
    return stack;
}


/* 出栈 */
void *stack_pop(stack *stack)
{
    /* 临时保存栈顶元素 */
    stack_node *current = stack->top;
    if(current==NULL) return NULL;
    void *data = current->data;
    stack->top = stack->top->next;

    free(current);
    stack->length--;
    return data;
}

/* 清空栈中所有元素，但不清除栈本身 */
void stack_empty(stack *stack)
{
    int length = stack->length;
    stack_node *current, *next;
    current = stack->top;
    /* 根据栈的高度确定删除节点的次数 */
    while (length--)
    {
        next = current->next;
        free(current);
        current = next; 
    }
    
    stack->length = 0;
    stack->top = NULL;
}

/* 清空栈中所有元素并删除栈 */
void stack_release(stack *stack)
{
    stack_empty(stack);
    free(stack);
}
