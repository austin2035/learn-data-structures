/* 编译并运行测试，参考如下命令
 * gcc -fsanitize=address -fno-omit-frame-pointer -g *.c  && ./a.out
 */

#include <stdio.h>
#include "list.h"

int main()
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
    
    return 0;
}