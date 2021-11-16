#ifndef __QUEUE_H__
#define __QUEUE_H__

/* 队列节点 */
typedef struct queue_node {
    struct queue_node *next;
    void *data;
}queue_node;


/* 队列本身 */
typedef struct queue {
    struct queue_node *head;
    struct queue_node *tail;
    int length;
}queue;


/* 创建队列 */
queue *queue_create();
/* 入队 */
queue *queue_push_data(queue *queue, void *data);
/* 出队 */
void *queue_pull_data(queue *queue);
/* 释放队列中所有节点，但不释放队列本身 */
void queue_empty(queue *queue);
/* 释放队列，包括队列中节点 */
void queue_release(queue *queue);
#endif