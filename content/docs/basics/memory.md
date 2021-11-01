---
title: 内存管理初步
type: docs
weight: 12
---

个人认为好的程序员总是会合理的使用内存，学习数据结构也需要对C语言的内存管理做个简单的了解，为什么是简单的了解而不是深入呢？因为C语言及其内存管理不是三言两语可以说清的，这里我们只谈谈常用的内存管理方法。

## 为什么是malloc？  

以往我们在学习c语言时，通常只是简单的使用int，float之类来声明变量。像这种变量，通常存放在栈区（stack），由编译器自动分配释放，存放函数的参数值，局部变量等值。而在实际编程中，我们需要足够的内存来保证程序的存储需求，由于stack区内存相对较小，所以我们需要使用malloc与free等函数来从堆区（heap）动态申请与释放内存，堆区要比栈区大得多。  

## malloc与内存

所有程序都需要预留足够的内存来存储程序使用的数据，malloc函数能够在程序运行时分配更多的内存。malloc函数会找到空闲的内存块并返回内存块的首地址，而恰好char表示1字节，malloc()的返回类型被定义为指向char类型的指针。但从ANSI C标准开始，有了些变化。malloc函数原型为：  

```c
void *malloc(unsigned int num_bytes);
```

一个指向void的指针，相当于是一个通用类型，所以通常我们需要什么类型的指针对应进行强制转换即可，分配失败将返回空指针。  

## 善用size_t类型  

我们一般用`size_t`类型来定义变量进而存储`sizeof`函数返回的值。
比如：

```c
size_t size = sizeof(int);
```

## malloc的使用  

**malloc**函数位于 <stdlib.h> 库，使用前不要忘记 `include`。

### 为简单变量申请内存

```c
int *p = (int*)malloc(sizeof(int));
*p = 100;
```

### 为结构体申请内存

```c
struct student *stu_ptr = (struct student *)malloc(sizeof(struct student));
char *name = (char *)malloc(sizeof(char) * 64);
strcpy(name, "austin");
stu_ptr->name = name;
stu_ptr->age = 19;
stu_ptr->class = 3;
printf("name: %s\nage: %d\nclass: %d\n", stu_ptr->name, stu_ptr->age, stu_ptr->class);
/* 输出如下：
name: austin
age: 19
class: 3 */
```

## free的使用  

一般来说，内存错误是C/C++编程中常见且令人头疼的问题。为了避免此类问题出现，就要养成良好的内存使用习惯。通常，`malloc`函数与`free`函数成对使用。
这是因为，`malloc`申请来内存后，并不会主动释放, C语言并没有类似高级语言如java、python等垃圾回收机制。这就需要我们手动使用`free`函数释放，避免不用的变量滞留在内存。  
`free`函数的使用较为简单, 原型: void free(void *ptr), 它会释放ptr指向的存储空间，被释放的空间通常被送入可用存储区池。
假如上文中定义的结构变量`stu_ptr`不再使用，我们就可以进行释放操作。

```c
free(stu_ptr);
```

## AddressSanitizer的使用  

在进行C编程时，一些内存错误可能会在运行时报出导致运行终止，但也可能会有内存错误的情况，而表面上却正常运行。
AddressSanitizer是一款用于内存诊断的工具，可以配合gcc使用，方便检测越界，非法访问等内存错误。  

gcc编译的时加上这些参数即可：

```bash
-fsanitize=address -fno-omit-frame-pointer  -g
# 例如 
gcc -fsanitize=address -fno-omit-frame-pointer  -g test.c
```

接着运行程序，如果内存异常，就会报出具体错误信息，比如下面这个：
![报错](/images/fsan.png)

如果编译时报出错误：

```bash
/usr/bin/ld: 找不到 /usr/lib64/libasan.so.0.0.0
collect2: 错误：ld 返回 1
```

那说明没有安装**AddressSanitizer**，centos下安装：

```bash
yum install libasan.x86_64
```
