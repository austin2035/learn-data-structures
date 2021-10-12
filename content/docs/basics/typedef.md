---
title: typedef
type: docs
weight: 12
---

{{< hint info >}}
**测试提示**  
Lorem markdownum insigne. Olympo signis Delphis! Retexi Nereius nova develat
stringit, frustra Saturnius uteroque inter! Oculis non ritibus Telethusa
{{< /hint >}}
{{<hint warning>}}
**测试**  
你好
{{</hint>}}
### 我对快速排序的理解
快速排序，是九大排序里面平均性能最好的，是对冒泡排序的改进。其运用了分治的思想，不难理解，但是用编程语言描述的时候会相对来说有点困难。

### 快速排序的方法
步骤为：  
1. 挑选基准值：从数列中挑出一个元素，称为“基准”（pivot）   
2. 分割：重新排序数列，所有比基准值小的元素摆放在基准前面，所有比基准值大的元素摆在基准后面（与基准值相等的数可以到任何一边）。在这个分割结束之后，对基准值的排序就已经完成。    
3. 递归排序子序列：递归地将小于基准值元素的子序列和大于基准值元素的子序列排序。    
递归到最底部的判断条件是数列的大小是零或一，此时该数列显然已经有序。

上面这段话来自维基百科，如果我翻译翻译那就是：先在数列中随便找个数叫做基准数（pivot）。
![1.png][2]

然后将数列中小于pivot的数放到pivot的前面，把大于pivot的放到pivot的后面。

![2.png][3]  
这样就是一轮排序了，得到的结果就是pivot前面的数字都比pivot小，pivot后面的数字都比pivot要大。然后，我们再用此方法分别将pivot两边的数排一下，其实就是递归了。

![3.png][4]

### 难点分析  
看到这里，相信你应该已经知道快速排序是怎么一回事了。但是，说的轻巧，但如何用编程语言实现呢？其实是有挺多种方法的，这也就是为什么大家看的快速排序代码有很多版本。  
其中，我认为最好理解的是挖坑法。

### 图解挖坑法  
![4.png][5]

### 代码实现 （C语言） 
```c
/* 每一轮的排序 */
int sort(int arr[], int left, int right)
{   
    /* 选择arr[left]作为新坑，并将此值作为基准保存至pivot*/
    int pivot = arr[left];
    /* 当退出循环的时候，left与right相遇，left==right */
    while (left<right)
    {   
        /* right指针从右往左走，直到遇到比pivot值小的数 */
        while(arr[right] > pivot && left < right) right --;
        /* right指针遇到了比pivot值小的数，将其填入坑中, 此时产生新坑arr[right]*/
        arr[left] = arr[right];
        /* left指针从左往右走，直到遇到比pivot值大的数 */
        while(arr[left] < pivot && left < right) left ++;
        /*
        left指针遇到了比pivot值大的数，
        填入刚才的新坑 arr[right]中
        此时产生新坑arr[left] */
        arr[right] = arr[left];
    }
    /* 跳出循环，left==right，将基准值填入上一步产生的坑arr[left] */
    arr[left] = pivot;
    /* 至此所有坑填补完毕，pivot左边的都比pivot值大，右边反之。返回 pivot的下标*/
    return left;
}

void quick_sort(int arr[], int left, int right)
{   
    /* 递归的条件：如果left小于right表明arr数组至少有两个元素，可以进行排序 */
    if(left<right){
        /* 对arr排序，mid是排序后基准值的下标 */
        int mid = sort(arr, left, right);
        /* 由于mid左边的都比基准值小，mid右边的都比基准值大。
        所以，对mid两边的两部分分别排序 */
        quick_sort(arr, left, mid-1);
        quick_sort(arr, mid+1, right);
    }
}
```
如果觉得不够优雅，也可以整理成一个函数，多引入俩变量。
```c
void quick_sort(int arr[], int left, int right)
{   
    if(left<right){
        int i=left, j=right;
        int pivot = arr[left];
        while(i<j){
            while(arr[j]>pivot && i<j) j--;
            arr[i] = arr[j];
            while (arr[i]<pivot && i<j) i++;
            arr[j] = arr[i];   
        }
        arr[i] = pivot;
        quick_sort(arr, left, i-1);
        quick_sort(arr, i+1, right);
    }
}
```

### 数字是用在线网站随机选取的  
![5.png][6]
 

### end  
上面的代码可以作为理解快速排序用，实际上还有挺多小细节可以优化。  


  [1]: https://lookcos.cn/usr/uploads/2021/09/3916853719.png
  [2]: https://lookcos.cn/usr/uploads/2021/09/2887716166.png
  [3]: https://lookcos.cn/usr/uploads/2021/09/2036742653.png
  [4]: https://lookcos.cn/usr/uploads/2021/09/2425154117.png
  [5]: https://lookcos.cn/usr/uploads/2021/09/453870589.png
  [6]: https://lookcos.cn/usr/uploads/2021/09/1328850635.png