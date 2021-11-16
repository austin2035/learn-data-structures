
/* 基于哈希表的字典。
 * 支持整型或者字符型的键，值用空类型指针，所以可以表示各种数据，
 * 这也意味着节点不是直接保存数据，而是保存指向该值的指针变量。
 * 2021-10 <lookcos at gmail dot com> 
 */


#ifndef __DICT_H__
#define __DICT_H__

/* 字典类型 */
#define DICT_TYPE_INT 0
#define DICT_TYPE_STR 1


/* 键值对 */
typedef struct dict_entry {
    struct dict_entry * next;
    void *key;
    void *val;
}dict_entry;


/* 字典 */
typedef struct dict {
    /* 哈希函数 */
    unsigned int (*hash)(void *key);
    /* table数组用于存放dict_entry指针 */
    dict_entry **table;
    /* 指针数组 */
    int size;
    /* 掩码 */
    int sizemask;
}dict;

/* 哈希函数(适用整数) */
static unsigned int hash_integer(void *key);
/* 哈希函数 TIME33 算法 */
static unsigned int hash_33(void *key);
/* 创建一个dict */
dict *dict_create(int type);
/* 创建一个dict_entry */
dict_entry * dict_create_entry(void *key, void *val);
/* 字典插入一个键值对 */
dict *dict_put_entry(dict *dict, void *key, void *val);
/* dict获取值 */
void * dict_get_value(dict *dict, void *key);
/* 清除dict所有entry，而不清除dict本身 */
void dict_empty(dict *dict);
/* 释放dict */
void dict_release(dict *dict);

#endif