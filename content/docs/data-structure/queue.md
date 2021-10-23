---
title: 队列
type: docs
weight: 40
---

## 什么是队列

队列（queue）是一种先进先出（First In First Out， FIFO）的线性表。

## 队列的操作  

通常来说，队列常用的操作也是插入和删除两种。为了方便理解，可以将执行删除的一端称为队头（head），执行插入操作的一端称为队尾（tail）。

## 不雅的比喻  

栈，可以理解为吃进然后吐出来，食物后进先出。队列则是吃进去拉出来，先进先出。

## 队列的表示  

队列也有顺序和链式两种表示方法。同样，我们可以将链式队列理解为一种特殊的链表，只允许在表头删除，在表尾插入。

```c
typedef struct node_queue {
    struct node_queue *next;
    char data;
}node_queue;


typedef struct queue {
    struct node_queue *head;
    struct node_queue *tail;
    int length;
}queue;
```

## 入队  

