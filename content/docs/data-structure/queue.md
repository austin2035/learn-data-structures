---
title: 队列
type: docs
weight: 40
---

## 什么是队列

队列（queue）是一种先进先出（First In First Out， FIFO）的线性表。
![队列](/images/queue.png)  

## 队列的表示  

队列也有顺序和链式两种表示方法。同样，我们可以将链式队列理解为一种特殊的链表，只允许在表头删除，在表尾插入。

```c
typedef struct queue_node {
    struct queue_node *next;
    void *data;
}queue_node;


typedef struct queue {
    struct queue_node *head;
    struct queue_node *tail;
    int length;
}queue;
```

## 队列的操作  
  
通常来说，队列常用的操作也是插入和删除两种。为了方便理解，可以将执行删除的一端称为队头（head），执行插入操作的一端称为队尾（tail）。
![队列操作](/images/queue_push_pull.png)

## 函数清单  

下面是用于操作队列的函数名及其作用与复杂度  

|函数|作用|算法复杂度|
|----|----|----|
|queue_create|创建新队列|O(1)|
|queue_release|释放队列，以及队列中的节点|O(N)|
|queue_push_data|入队|O(1)|
|queue_pull_data|出队|O(1)|
|queue_empty|释放队列中节点(头节点除外)，但不释放队列本身|O(N)|

## 创建新队列  

```c
/* 创建队列 */
queue *queue_create()
{
    /* 创建一个队列 */
    queue *queue = (struct queue*)malloc(sizeof(struct queue));
    
    /* 为了方便操作，队列默认创建一个队列节点 */
    queue_node *node = (struct queue_node*)malloc(sizeof(struct queue_node));
    if(queue==NULL || node==NULL) return NULL;

    node->data = NULL;
    node->next = NULL;
    
    /* 初始化队列 */
    queue->head = queue->tail = node;
    queue->length = 0;

    return queue;
}
```

## 入队  

```c
/* 入队 */
queue *queue_push_data(queue *queue, void *data)
{
    /* 创建一个节点 */
    queue_node *node = (struct queue_node*)malloc(sizeof(struct queue_node));
    if(node==NULL) return NULL;
    node->data = data;

    /* 在队尾插入元素 */
    queue->tail->next = node;
    queue->tail = queue->tail->next;

    queue->length++;
    return queue;
}
```

## 出队  

```c
/* 出队 */
void* queue_pull_data(queue *queue)
{
    queue_node *curr = queue->head->next;
    
    /* 判断队列中是否有数据 */
    if(curr==NULL) return NULL;

    void *data = curr->data;
    
    queue->head->next = curr->next;
    
    /* 判断队列中除头结点外，是否只有一个节点，避免尾指针丢失 */
    if(queue->tail==curr) {
        queue->tail = queue->head;
    }

    free(curr);
    queue->length--;
    return data;
}
```

## 清空队列

```c
// 释放队列中所有节点，但不释放队列本身
void queue_empty(queue *queue)
{   
    int length = queue->length;
    queue_node *curr, *next;

    // 注意这里不释放头节点
    curr = queue->head->next;
    while (length--)
    {   
        next = curr->next;
        free(curr);
        curr = next;
    }
    
    queue->head->next = NULL;
    queue->head->data = NULL;
    queue->tail = queue->head;
    queue->length = 0;
}
```

## 清除队列  

```c
// 释放队列，包括队列中节点
void queue_release(queue *queue)
{
    queue_empty(queue);
    /* 注意，头节点也要释放 */
    free(queue->head);
    free(queue);
}
```

## 测试  

```c
int main()
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
    return 0;
}
```

## 完整代码  

完整代码，详见代码清单。  
