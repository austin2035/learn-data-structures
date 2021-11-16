#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "dict.h"

void test_stack(void)
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
    
    return ;
}

void test_queue(void)
{
    char a = 'a';
    char b = 'b';
    char c = 'c';
    
    queue *queue = queue_create();
    printf("%p\n", queue_pull_data(queue));
    
    queue_push_data(queue, &a);
    queue_push_data(queue, &b);
    queue_push_data(queue, &c);

    while (queue->length)
    {
        printf("%c\n", *(char *)queue_pull_data(queue));
    }
    
    queue_push_data(queue, &c);
    queue_push_data(queue, &c);
    
    /* 释放队列中节点 */
    queue_empty(queue);
    printf("%p\n", queue_pull_data(queue));
    
    /* 释放队列 */
    queue_release(queue);
}

void test_list(void) 
{
    /* 测试数据 */
    char a = 'A';
    char b = 'B';
    char c = 'C';

    /* 创建链表 */
    list *list = list_create(); 
    
    /* 测试空表是否报错 */
    printf("-----测试空链表是否报错\n");
    printf("%p\n", list_get_value_head(list));
    printf("%p\n", list_get_value_tail(list));

    /* 表头添加数据 */
    list_add_node_head(list, &a);
    list_add_node_head(list, &b);
    /* 表尾添加数据 */
    list_add_node_tail(list, &c);
    list_add_node_tail(list, &a);

    printf("-----此时链表长度：%d\n", list->length);
    printf("-----测试表头出队-----\n");
    /* 先出队两次，测试表头出队 */
    while (list->length>2)
    {   
        printf("%c\n", *(char*)list_get_value_head(list));
    }
    printf("-----测试表尾出队-----\n");
    /* 测试表尾出队 */
    while (list->length)
    {   
        printf("%c\n", *(char*)list_get_value_tail(list));
    }

    /* 添加数据 */
    list_add_node_head(list, &a);
    list_add_node_head(list, &b);
    list_add_node_head(list, &c);

    /* 创建一个正向迭代器迭代器 */
    list_iter *iter = list_get_iterator(list, LIST_START_HEAD);
    /* 测试迭代器 */
    printf("-----测试迭代器-------\n");
    printf("%c\n", *(char *)list_next(iter));
    printf("%c\n", *(char *)list_next(iter));

    /* 释放迭代器 */
    list_release_iterator(iter);

    /* 清除链表节点 */
    list_empty(list);
    
    printf("-----测试空链表是否报错\n");
    printf("%p\n", list_get_value_head(list));
    printf("%p\n", list_get_value_tail(list));

    /* 释放链表 */
    list_release(list);
}

void test_dict(void) 
{
    /* 创建一个key为字符串类型的字典 */
    dict * dict = dict_create(1);

    char str[] = "name";
    char str2[] = "Austin";
    char str3[] = "Lookcos";
    char str4[] = "age";
    int age = 18;

    dict_put_entry(dict, &str2, &str2);
    puts(dict_get_value(dict, &str2));

    dict_put_entry(dict, &str, &str2);
    puts(dict_get_value(dict, &str));

    dict_put_entry(dict, &str, &str3);
    puts(dict_get_value(dict, &str));
    
    dict_put_entry(dict, &str4, &age);
    printf("age: %d\n", *(int *)dict_get_value(dict, &str4));

    /* 字典的释放 */
    dict_empty(dict);
    dict_release(dict);
}

int main()
{   
    return 0;
}