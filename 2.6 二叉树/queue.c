#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

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

/* 出队 */
void *queue_pull_data(queue *queue)
{
    queue_node *current = queue->head->next;
    
    /* 判断队列中是否有数据 */
    if(current==NULL) return NULL;

    void *data = current->data;
    
    queue->head->next = current->next;
    
    /* 判断队列中除头结点外，是否只有一个节点，避免尾指针丢失 */
    if(queue->tail==current) {
        queue->tail = queue->head;
    }

    free(current);
    queue->length--;
    return data;
}

/* 释放队列中所有节点，但不释放队列本身 */
void queue_empty(queue *queue)
{   
    int length = queue->length;
    queue_node *current, *next;

    /* 注意这里不释放头节点 */
    current = queue->head->next;
    while (length--)
    {   
        next = current->next;
        free(current);
        current = next;
    }
    
    queue->head->next = NULL;
    queue->head->data = NULL;
    queue->tail = queue->head;
    queue->length = 0;
}

/* 释放队列，包括队列中节点 */
void queue_release(queue *queue)
{
    queue_empty(queue);
    /* 注意，头节点也要释放 */
    free(queue->head);
    free(queue);
}