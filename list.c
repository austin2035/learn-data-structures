#include <stdio.h>
#include <stdlib.h>


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


/* 创建链表 */
list *list_create(void)
{
    list *list = (struct list *)malloc(sizeof(struct list));
    if(list==NULL) return NULL;
    list->head = list->tail = NULL;
    list->length = 0;
    return list;
}

/* 清空链表中所有的节点但是不删除链表本身 */
void list_empty(list *list)
{
    unsigned long length;
    list_node *current, *next;
    current = list->head;
    length = list->length;
    while (length--)
    {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = list->tail = NULL;
    list->length = 0;
}

/* 释放整个链表 */
void list_release(list *list)
{
    list_empty(list);
    free(list);
}

/* 创建一个迭代器 */
list_iter *list_get_iterator(list *list, int direction)
{
    list_iter *iter = (list_iter *) malloc(sizeof(list_iter));
    if(iter==NULL) return NULL;
    if(direction == LIST_START_HEAD)
        iter->next = list->head;
    else 
        iter->next = list->tail;
    iter->direction = direction;
    return iter;
}

/* 释放迭代器内存 */
void list_release_iterator(list_iter *iter)
{
    free(iter);
}

/* 返回链表下一个节点值 */
void *list_next(list_iter *iter)
{
    list_node *current = iter->next;
    if (current==NULL) return NULL;
    
    /* 判断迭代器方向，并将迭代器`next`指针指向下一个节点。 */
    if(iter->direction == LIST_START_HEAD)
        iter->next = current->next;
    else 
        iter->next = current->prev;

    return current->value;
}

/* 添加一个节点在链表头部 */
list *list_add_node_head(list *list, void *value)
{   
    /* 新建一个链表节点 */
    list_node *node = (list_node *)malloc(sizeof(list_node));
    if(node==NULL) return NULL;
    node->value = value;
    /* 如果链表为空 */
    if(list->length == 0) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    }else{
        node->prev = NULL;
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->length++;
    return list;
}

/* 添加一个节点在链表尾部 */
list *list_add_node_tail(list *list, void *value)
{
    /* 新建一个链表节点 */
    list_node *node = (list_node *)malloc(sizeof(list_node));
    if(node==NULL) return NULL;
    node->value = value;
    if(list->length==0) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    } else {
        node->prev = list->tail;
        node->next = NULL;
        list->tail->next = node;
        list->tail = node;
    }
    list->length++;
    return list;
}


/* 删除一个节点 */
void list_del_node(list *list, list_node *node)
{   
    /* 判断该节点是否有直接前驱 */
    if (node->prev)
        node->prev->next = node->next;
    else
        list->head = node->next;
    
    /* 判断该节点是否有直接后继 */
    if (node->next)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;
    
    /* 释放该节点 */
    free(node);
    list->length--;
}

/* 获取头部元素 */
void *list_get_value_head(list *list)
{
    if(list->head == NULL) return NULL;
    void *value = list->head->value;
    list_del_node(list, list->head);
    return value;
}

/* 获取尾部元素 */
void *list_get_value_tail(list *list)
{
    if(list->tail == NULL) return NULL;
    void *value = list->tail->value;
    list_del_node(list, list->tail);
    return value;
}

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