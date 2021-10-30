---
title: 双链表
type: docs
weight: 50
---

## 关于双端链表  

双端链表也叫双向链表或双链表，它是一种非常实用的数据结构。单链表的节点只有一个指针域，且指向下一个节点，而双链表则有两个指针域，分别指向直接前驱和直接后继。同时也意味着，表头和表尾都能方便的进行插入和删除的操作，进而能轻易实现**栈**和**队列**的功能。

## 双链表的表示  

双链表可以用表示链表节点的`list_node`和表示链表本身的`list`两个结构体来表示。**下面的代码，参考了redis的双端链表**。

![双链表](/images/list.png)  

```c
/* 链表节点 */
typedef struct list_node 
{   
    /* 前驱节点 */
    struct list_node *prev;
    /* 后继节点 */
    struct list_node *next;
    /* 值 */
    void *value;
} list_node;

/* 链表 */
typedef struct list
{   
    /* 表长度 */
    unsigned long length;
    /* 表头 */
    list_node *head;
    /* 表尾 */
    list_node *tail;
} list;
```

1. 链表节点(list_node)带有**prev**和**next**两个指针，这意味着，可以从表头到表尾或表尾到表头两个方向遍历或迭代链表。  
1. 链表本身(list)和队列(queue)类似，维护**head**和**tail**两个指针，这意味着，在表头或者表尾的插入的复杂度为O(1)，而单链表在表尾执行插入操作时，需要从表头遍历到表尾后插入，复杂度为O(n)。  

## 双链表的创建  

```c
/* 创建链表 */
list * create_list(void)
{
    /* 创建链表 */
    list *list = (struct list *)malloc(sizeof(struct list));
    if(list==NULL) return NULL;
    
    /* 初始化链表 */
    list->head = list->tail = NULL;
    list->length = 0;
    
    return list;
}
```

![双链表创建](/images/list_create.png)  


## 双链表的表头插入操作  

```c
/* 添加一个节点在链表头部 */
list * list_add_node_head(list *list, void *value)
{   
    /* 新建一个链表节点 */
    list_node *node = (list_node *)malloc(sizeof(list_node));
    if(node==NULL) return NULL;
    node->value = value;
    /* 如果链表为空 */
    if(list->length == 0) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    }else {
        /* 设置新节点 */
        node->prev = NULL;
        node->next = list->head;
        /* 设置链表 */
        list->head->prev = node;
        list->head = node;
    }
    list->length++;
    return list;
}
```

首先，创建一个新的链表节点。  
然后，判断双链表的长度，也即判断双链表是否为空。  
如果为空，则让链表的头尾指针`head`与`tail`都指向该新节点，且新节点(node)指向前驱节点的指针`prev`和指向后继节点的指针`next`都设置为**NULL**。

![双链表的表头插入操作1](/images/list_insert_head_0.png)

如果不为空，则说明链表中已有节点存在。  
此时，先设置新节点，指针`prev`置为`NULL`，指针`next`指向链表头指针(head)指向的节点，也即表头节点。  
然后让头指针指向的节点的`prev`指针指向新节点。  
最后，将指针`head`指向新节点。

![双链表的表头插入操作2](/images/list_insert_head_1.png) 

执行完节点的插入操作后，别忘了让链表长度自增1。

## 双链表的表尾插入操作  

```c
/* 添加一个节点在链表尾部 */
list * list_add_node_tail(list *list, void *value)
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
```

首先，也要创建一个新的链表节点。  
接着也需要判断链表是否为空，如果是，则与链表为空时表头的插入操作相同。  
否则，让新节点`prev`指向链表表尾节点，`next`置为`NULL`。  
然后，链表的`tail->next`指向新节点，表尾指针`tail`指向新节点。  
最后，插入完成，链表长度自增1。  


![双链表的表尾插入操作](/images/list_insert_tail.png) 