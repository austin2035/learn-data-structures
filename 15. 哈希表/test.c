#include <stdio.h>
#include "dict.h"

int main()
{   
    /* 创建一个key为字符串类型的字典 */
    dict * dict = dict_create(1);

    char str[] = "name";
    char str2[] = "Austin";
    char str3[] = "Lookcos";
    char str4[] = "age";
    int age = 18;

    dict_put_entry(dict, &str2, &str2);
    puts(dict_get_value(dict, &str2));

    dict_put_entry(dict, &str, &str2);
    puts(dict_get_value(dict, &str));

    dict_put_entry(dict, &str, &str3);
    puts(dict_get_value(dict, &str));
    
    dict_put_entry(dict, &str4, &age);
    printf("age: %d\n", *(int *)dict_get_value(dict, &str4));

    /* 字典的释放 */
    dict_empty(dict);
    dict_release(dict);
    return 0;
}