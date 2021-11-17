/* 编译并运行测试，参考如下命令
 * gcc -fsanitize=address -fno-omit-frame-pointer -g *.c  && ./a.out
 */

#include <stdio.h>
#include "queue.h"

int main() {
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