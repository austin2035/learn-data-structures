#include <stdio.h>
#include <stdlib.h>

typedef struct stack_node {
    struct stack_node *next;
    void *data;
}stack_node;

typedef struct stack {
    struct stack_node *top;
    int length; // 表示栈的高度
}stack;


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
    stack_node *curr = stack->top;
    if(curr==NULL) return NULL;
    void *data = curr->data;
    stack->top = stack->top->next;

    free(curr);
    stack->length--;
    return data;
}

/* 清空栈中所有元素，但不清除栈本身 */
void stack_empty(stack *stack)
{
    int length = stack->length;
    stack_node *curr, *next;
    curr = stack->top;
    /* 根据栈的高度确定删除节点的次数 */
    while (length--)
    {
        next = curr->next;
        free(curr);
        curr = next; 
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

int main()
{
    char a = 'a';
    char b = 'b';
    char c = 'c';

    /* 创建一个栈 */
    stack *stack = stack_create();

    printf("%p\n", stack_pop(stack));

    /* 压栈 */
    stack_push(stack, &a);
    stack_push(stack, &b);
    stack_push(stack, &c);

    /* 出栈 */
    while (stack->length > 0)
    {
        printf("%c\n", *(char *)stack_pop(stack));
    }

    /* 压栈 */
    stack_push(stack, &a);
    stack_empty(stack);
    printf("%p\n", stack_pop(stack));
    
    /* 释放栈 */
    stack_release(stack);
    return 0;
}