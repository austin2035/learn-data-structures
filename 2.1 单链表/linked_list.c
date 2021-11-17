#include <stdio.h>
#include <stdlib.h>

/* 定义表示单链表节点的结构体 */
typedef struct node {
    int data;
    struct node *next;
}list;

/* 创建一个单链表，返回头指针 */
list * create_list()
{
    /* 创建一个新的节点，由于使用了typedef关键字，此处 list *head与struct node *head等价    */
    list *head = (list *)malloc(sizeof(list));
    if(head==NULL) return NULL;
    /* 初始化节点 */
    head->data = 0; // 头结点数据域，我们用来表示链表长度
    head->next = NULL; // 头节点指针域，暂时没有下一个节点，所以为空
    return head;
}

list *list_insert_node(list *head, int data, int pos)
{   
    int i;
    list *current = head;

    /* 如果要插入的位置比链表长，则属于非法操作 */
    if(pos > current->data) return NULL;

    /* 创建一个节点，并初始化 */
    list *node = (list *)malloc(sizeof(list));
    if(node==NULL) return NULL;
    node->data = data;
    node->next = NULL;

    /* 遍历链表，找到要插入的位置 */
    for(i=0;i<pos;i++){
        current = current->next;
    }

    /* 插入 */
    node->next = current->next;
    current->next = node;

    /* 链表长度+1 */
    head->data++;
    return head;
}

/* 打印链表数据，但不包括头结点的数据*/
void print_list(list *head)
{
    list *current = head->next;
    while (current)
    {
        printf("%d \t", current->data);
        current = current->next;
    }
    printf("\n");
}


list *list_delete_data(list *head, int pos)
{
    int i;
    list *current = head;

    /* 如果要删除的位置比链表长，则属于非法操作 */
    if(pos > current->data) return NULL;

    /* 遍历链表，找到要删除的节点的前一个节点的指针 */
    for(i=0;i<pos;i++){
        current = current->next;
    }
    // 临时记录将被删除的节点
    list *temp = current->next;
    current->next = current->next->next;
    
    //释放掉被删除节点的内存
    free(temp);
    head->data--;
    return head;
}

int main()
{
    int i;
    list *l = create_list();
    for(i=0;i<5;i++){
        list_insert_node(l, i, 0);
        print_list(l);
    }
    list_delete_data(l, 0);
    print_list(l);
    return 0;
}

