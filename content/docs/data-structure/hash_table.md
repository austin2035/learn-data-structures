---
title: 哈希表
type: docs
weight: 60
---

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 字典类型 */
#define DICT_TYPE_INT 0
#define DICT_TYPE_STR 1


typedef struct dict_entry {
    struct dict_entry * next;
    void *key;
    void *val;
}dict_entry;


typedef struct dict {
    /* 哈希函数 */
    unsigned int (*hash)(void *key);
    /* table数组用于存放dict_entry指针 */
    dict_entry ** table;
    /* 指针数组 */
    int size;
    /* 掩码 */
    int sizemask;
}dict;

/* 哈希函数(适用整数) */
static unsigned int hash_integer(void *key)
{
	return (*(int *)key * 2654435769) >> 28;
}

/* 哈希函数 TIME33 算法 */
static unsigned int hash_33(void *key)
{   
    unsigned int hash = 0;
	while (*(char *)key != 0)
	{
		hash = (hash << 5) + hash + *(char *)key++;//左移5位相当于*32，再+hash则相当于*33;
	}
	return hash;
}

/* 创建一个dict */
dict *dict_create(int type)
{
    dict *dict = (struct dict *)malloc(sizeof(struct dict));
    if(dict == NULL) return NULL;
    if(type == DICT_TYPE_INT)
        dict->hash = &hash_integer;
    else
        dict->hash = &hash_33;
    dict->size = 1;
    dict->sizemask = dict->size - 1;
    dict->table = (dict_entry **)malloc(sizeof(dict_entry *) * (dict->size));
    memset(dict->table, 0, sizeof(dict_entry *) * (dict->size));
    if (dict->table == NULL) return NULL;
    return dict;
}

/* 创建一个dict_entry */
dict_entry * dict_create_entry(void *key, void *val)
{
    dict_entry * entry = (dict_entry *)malloc(sizeof(dict_entry));
    if(entry == NULL) return NULL;
    entry->key = key;
    entry->val = val;
    entry->next = NULL;
    return entry;
}

/* 字典插入一个键值对 */
dict *dict_put_entry(dict *dict, void *key, void *val)
{
    unsigned int hash = dict->hash(key);
    int pos = hash & dict->sizemask;
    dict_entry *entry, *next;
    entry = dict_create_entry(key, val);
    /* 新增 */
    if(dict->table[pos]==0){
        //printf("新增\n");
        dict->table[pos] = entry;
    } else {
        next = dict->table[pos];
        /* 往下找，直到找到hash值相等的key，则更新，或者直到next==NULL，此时新增在链表尾部。 */
        while(next->next != NULL) {    
            if(dict->hash(next->key) == dict->hash(key)) break;
            next = next->next;
        }
        if(dict->hash(next->key) == dict->hash(key)) {
            //printf("更新\n");
            entry->next = next->next;
            next = entry;
        }
        else {
            //printf("尾部插入\n");
            next->next = entry;
        }
    }
    return dict;
}

/* dict获取值 */
void * dict_get_value(dict *dict, void *key) 
{
    unsigned int hash = dict->hash(key);
    int pos = hash & dict->sizemask;
    if(dict->table[pos]==0) return NULL;
    dict_entry *current = dict->table[pos];
    while (dict->hash(current->key) != dict->hash(key))
    {
        if(current->next != NULL) 
            current = current->next;
        else
            return NULL;
    }
    return current->val;
}


/* 清除dict所有entry，而不清除dict本身 */
void dict_empty(dict *dict)
{
    int i;
    for(i=0;i<dict->size;i++){
        if(dict->table[i] != 0){
            dict_entry * current, *next;
            current = dict->table[i];
            while (current)
            {   
                next = current->next;
                free(current);
                current = next;
            }
            dict->table[i] = 0;
        }
    }
}

/* 释放dict */
void dict_release(dict *dict)
{
    dict_empty(dict);
    free(dict);
}


int main()
{   
    dict * dict = dict_create(0);
    int str = 100;
    int str2 = 101;
    dict_put_entry(dict, &str, &str);
    printf("%d\n", *(int*)dict_get_value(dict, &str));
    dict_put_entry(dict, &str, &str);
    puts(dict_get_value(dict, &str));
    dict_put_entry(dict, &str2, &str);
    puts(dict_get_value(dict, &str2));
    dict_empty(dict);
    dict_release(dict);
    return 0;
}
```