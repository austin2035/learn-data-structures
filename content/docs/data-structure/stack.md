---
title: 链栈
type: docs
weight: 30
---

## 什么是栈  

栈（stack）是一种后进先出（Last In First Out, LIFO）的线性表，表尾有特殊含义，称为栈顶（top）。

## 栈的操作  

栈最常用的操作有两种，一种是在表尾插入元素的操作称为入栈（push），也叫压栈；另一种是在表尾删除元素的操作称为出栈（pop）, 也叫弹栈。  

![栈的操作](/images/stack.png)

## 栈的表示  

栈有可以用数组表示，也即顺序栈，也可以用链表表示，叫做链式栈，简称链栈（本文主要讨论对象）。  
单链表可以在表头、表尾或者其他任意合法位置插入元素，如果只能在单链表的表尾插入和删除元素，那么就可以将其视为链栈。  
因此，在单链表的基础上，我们再维护一个**top**指针即可。  

![链式栈](/images/link_stack.png)  

{{< hint warning >}}
**注意**  
图中每个节点的指针域`next`指针指向下一个节点，而非下一个节点的指针域。
{{< /hint >}}

## 栈的节点定义与top指针  

定义表示链栈节点的结构体

```c
typedef struct node_stack {
    struct node_stack *next;
    void *data;
}node_stack;
```

定义表示链栈的结构体  

```c
typedef struct stack {
    struct node_stack *top;
    int length; // 表示栈的高度
}stack;
```

注意，**top**指针指向的是一个表示栈的结构体。

## 创建栈  

```c
/* 创建栈 */
stack *create_stack()
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
```

## 入栈  

![链栈的push操作](/images/stack_push.png)  

```c
/* 入栈 */
stack *stack_push(stack *stack, void *data)
{
    /* 创建一个节点 */
    node_stack *node = (struct node_stack*)malloc(sizeof(struct node_stack));
    if(node==NULL) return NULL;
    node->data = data;

    /* 插入 */
    node->next = stack->top;
    stack->top = node;

    stack->length++;
    return stack;
}
```

## 出栈  

```c
/* 出栈 */
void *stack_pop(stack *stack)
{
    /* 临时保存栈顶元素 */
    node_stack *curr = stack->top;
    if(curr==NULL) return NULL;
    void *data = curr->data;
    stack->top = stack->top->next;

    free(curr);
    stack->length--;
    return data;
}
```

## 清空栈  

```c
/* 清空栈中所有元素，但不释放栈本身 */
void stack_empty(stack *stack)
{
    int length = stack->length;
    node_stack *curr, *next;
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
```

## 释放栈  

```c
/* 清空栈中所有元素并删除栈 */
void stack_release(stack *stack)
{
    stack_empty(stack);
    free(stack);
}
```

## 测试  

同样的，我们在main函数中测试。

```c
int main()
{
    char a = 'a';
    char b = 'b';
    char c = 'c';

    /* 创建一个栈 */
    stack *stack = create_stack();

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
```

编译并输出  

```bash
# gcc -fsanitize=address -fno-omit-frame-pointer  -g stack.c  && ./a.out
(nil)
c
b
a
(nil)
```

## 完整代码  

完整代码，详见代码清单。  
