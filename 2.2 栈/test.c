/* 编译并运行测试，参考如下命令
 * gcc -fsanitize=address -fno-omit-frame-pointer -g *.c  && ./a.out
 */

#include <stdio.h>
#include "stack.h"

int main()
{   
    char a = 'a';
    char b = 'b';
    char c = 'c';

    /* 创建一个栈 */
    stack *stack = stack_create();

    printf("%p\n", stack_pop(stack));

    /* 压栈 */
    stack_push(stack, &a);
    stack_push(stack, &b);
    stack_push(stack, &c);

    /* 出栈 */
    while (stack->length > 0)
    {
        printf("%c\n", *(char *)stack_pop(stack));
    }

    /* 压栈 */
    stack_push(stack, &a);
    stack_empty(stack);
    printf("%p\n", stack_pop(stack));
    
    /* 释放栈 */
    stack_release(stack);
    
    return 0;
}