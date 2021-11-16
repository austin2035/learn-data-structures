
#ifndef __LIST_H__
#define __LIST_H__

/* 定义迭代器迭代方向 */
#define LIST_START_HEAD 0
#define LIST_START_TAIL 1


/* 链表节点 */
typedef struct list_node 
{
    struct list_node *prev;
    struct list_node *next;
    void *value;
} list_node;

/* 链表 */
typedef struct list
{
    unsigned long length;
    list_node *head;
    list_node *tail;
} list;

/* 迭代器结构 */
typedef struct list_iter
{
    list_node *next;
    int direction;
}list_iter;


/* 创建链表 */
list *list_create(void);
/* 创建一个迭代器 */
list_iter *list_get_iterator(list *list, int direction);
/* 返回链表下一个节点值 */
void * list_next(list_iter *iter);
/* 释放迭代器内存 */
void list_release_iterator(list_iter *iter);
/* 添加一个节点在链表头部 */
list *list_add_node_head(list *list, void *value);
/* 添加一个节点在链表尾部 */
list *list_add_node_tail(list *list, void *value);
/* 删除一个节点 */
void list_del_node(list *list, list_node *node);
/* 获取头部元素 */
void *list_get_value_head(list *list);
/* 获取尾部元素 */
void *list_get_value_tail(list *list);
/* 清空链表中所有的节点但是不删除链表本身 */
void list_empty(list *list);
/* 释放整个链表 */
void list_release(list *list);

#endif