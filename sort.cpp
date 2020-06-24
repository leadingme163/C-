#include"sort.h"
#include<iostream>
using namespace std;

/*函数功能: 交换两数位置
函数名称: swap
参数: 
    arr 传入数组指针
    i -- 交换的数组下标
    j -- 交换的数组下标
返回值: void
*/

template<typename T>
void swap(T *arr, int i, int j)
{
    T temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

/*函数功能: 冒泡排序
函数名称: bubbleSort
参数: arr -- 传入数组指针
      len -- 数组长度
返回值: void
*/
template<typename T>
void bubbleSort(T *arr, int len)
{
    T temp;
    if(len <= 1)
        return;
    for(int i=0;i<len-1;i++)
    {
        for(int j=0;j<len-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(arr,j, j+1);
            }
        }
    }
}

/*函数功能: 插入排序
函数名称: insertSort
参数: arr -- 传入数组指针
      len -- 数组长度
返回值: void
*/
template<typename T>
void insertSort(T *arr, int len)
{
    T temp;
    int j;
    if(len <= 1)
        return;
    for(int i=1; i<len;i++)
    {
        j = i;
        while(j>0)
        {
            if(arr[j] < arr[j-1])
            {
                swap(arr, j, j-1);
                j--;
            }else{
                break;
            }
        }
    }
}

/*函数功能: 选择排序
函数名称: selectSort
参数: arr -- 传入数组指针
      len -- 数组长度
返回值: void
*/
template<typename T>
void selectSort(T *arr, int len)
{
    T temp;
    int j, min_index;
    if(len <= 1)
        return;
    for(int i=0; i<len; i++)
    {
        min_index = i;
        for(j=i+1;j<len;j++)
        {
            if(arr[j]<arr[min_index])
                min_index = j;
        }
        swap(arr, min_index, i);
    }
}

/*函数功能: 具体实现快速排序算法
函数名称: quickSort_code
参数: arr -- 传入数组指针
      strat -- 数组起始下标
      strat -- 数组结尾下标
返回值: void
*/

template<typename T>
void quickSort_code(T *arr, int strat, int end)
{
	// strat是数组的开始，将start作为基数
	int m = arr[strat];
    // 递归结束条件
	if (strat >= end)
		return;
	int i = strat, j = end;
	while (i != j)
	{
		while (j > i&&arr[j] >= m)
		{
			j--;
		}
		swap(arr,i, j);
		while (j > i&&arr[i] <= m)
		{
			i++;
		}
		swap(arr,i,j); 
	}
	quickSort_code(arr, strat, i - 1);
	quickSort_code(arr, i + 1, end);
}

/*函数功能: 调用快速排序算法，保持所有排序参数一致性
函数名称: quickSort
参数: arr -- 传入数组指针
      len -- 数组长度
返回值: void
*/
template<typename T>
void quickSort(T *arr, int len)
{
    if(len <= 1)
        return;
    quickSort_code(arr, 0, len-1);
}

/*函数功能: 基数排序(桶排序)算法
函数名称: radixSort
参数: arr -- 传入数组指针
      len -- 数组长度
返回值: void
*/
template<typename T>
void radixSort(T *arr, int len)
{
    if(len <= 1)
        return;
    int i, base = 1;
    T max = arr[0];
    // 求最大数
    for(int i=1; i<len;i++)
    {
        if(arr[i] > max)
            max = arr[i];
    }
    // 动态分配内存，存储桶中取出的数字
    int *t = new int[len];


    while (max/base>0)
    {
        int bucket[10] = {0};
        // 统计每个桶中数的个数
        for(i=0; i<len; i++)
        {
            bucket[arr[i] / base % 10]++;
        }
        // 累加每个桶的个数
        for(i=1;i<10; i++)
        {
            bucket[i] += bucket[i-1];
        }
        // 根据每个数对应的bucket的数作为下标，指定一次桶排新数组
        for(i=len-1; i>=0; i--)
        {
            t[bucket[arr[i] / base % 10] - 1] = arr[i];
            // 考虑一个桶有多个数字，取出一次减1
            bucket[arr[i] / base % 10] --;
        }
        // 更新原数组
        for(i=0; i<len; i++)
        {
            arr[i] = t[i];
        }

        base = base * 10;
    }
    delete []t;
}

/*函数功能: 希尔排序算法
函数名称: shellSort
参数: arr -- 传入数组指针
      len -- 数组长度
返回值: void
*/
template<typename T>
void shellSort(T *arr, int len)
{
    if(len <= 1)
        return;
    T temp;
    int j, gap = len/2;
    while(gap > 0)
    {
        for(int i=gap; i<len;i++)
        {
            j = i;
            while(j>0)
            {
                if(arr[j] < arr[j-gap])
                {
                    swap(arr,j,j-gap);
                    j -= gap;
                }else{
                    break;
                }
            }
        }
        gap /= 2;
    }
}

/*函数功能: 合并两个有序数组
函数名称: merge_achieve
参数: arr -- 传入数组指针
      start -- 数组起始下标
      mid -- 数组中间下标
      end -- 数组结尾下标
返回值: void
*/
template<typename T>
void merge_achieve(T *arr, int start, int mid, int end)
{
    int n1 = mid - start + 1;
    int n2 = end - mid;
    T *left = new T[n1];
    T *right = new T[n2];

    // int left[n1], right[n2];
    int i, j, k;

    for (i = 0; i < n1; i++)
        left[i] = arr[start+i];
    for (j = 0; j < n2; j++)
        right[j] = arr[mid+1+j];

    i = j = 0;
    k = start;
    while (i < n1 && j < n2)
        if (left[i] < right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];

    while (i < n1) /* left[] is not exhausted */
        arr[k++] = left[i++];
    while (j < n2) /* right[] is not exhausted */
        arr[k++] = right[j++];
}



/*函数功能: 具体实现归并排序算法
函数名称: merge
参数: arr -- 传入数组指针
      start -- 数组起始下标
      end -- 数组结尾下标
返回值: void
*/
template<typename T>
void merge(T *arr, int start, int end) // 先排序，再合并
{
    int mid;
    if (start < end)
    {
        mid = (start + end) / 2;
        merge(arr, start, mid); // 递归划分原数组左半边array[start...mid]
        merge(arr, mid+1, end); // 递归划分array[mid+1...end]
        merge_achieve(arr, start, mid, end); // 合并
    }
}

/*函数功能: 调用归并排序算法
函数名称: mergeSort
参数: arr -- 传入数组指针
      len -- 数组长度
返回值: void
*/
template<typename T>
void mergeSort(T *arr, int len)
{
    // 调用归并排序函数
    merge(arr, 0, len-1);
}


/*函数功能: 对数组进行堆化
函数名称: heapify
参数: tree -- 传入数组指针
      n -- 数组长度
      i -- 堆化的数组下标值
返回值: void
*/

template<typename T>
void heapify(T tree[], int n , int i)
{
    if (i >= n)
        return;
    int c1 = 2 * i + 1;
    int c2 = 2 * i + 2;
    int max = i;
    if(c1 < n && tree[c1] > tree[max])
        max = c1;
    if(c2 < n && tree[c2] > tree[max])
        max = c2;
    if(max != i)
    {
        swap(tree, max,i);
        heapify(tree, n, max);
    }
}
  
/*函数功能: 创建二叉堆树
函数名称: build_heap
参数: tree -- 传入数组指针
      n -- 数组长度
返回值: void
*/

template<typename T>
void build_heap(T tree[], int n)
{
    // 完全二叉树的叶子节点=非叶子节点-1
    int last_node = n-1;
    int parent = (last_node-1)/2;
    for(int i=parent; i >= 0; i--)
        heapify(tree, n, i);
}


/*函数功能: 堆排序算法
函数名称: heapSort
参数: arr -- 传入数组指针
      len -- 数组长度
返回值: void
*/

template<typename T>
void heapSort(T *arr, int len)
{
    build_heap(arr, len);
    for(int i = len - 1; i >= 0; i--)
    {
        swap(arr,i,0);
        heapify(arr, i, 0);
    }
}

// int main()
// {
//     int arr[] = {312,3121,414,123,122};
//     float arr2[] = {1.3,1.2,1.1};
//     char arr3[] = {'b','a','c'};
//     heapSort(arr, 5);
//     heapSort(arr2, 3);
//     heapSort(arr3, 3);
//     for(int i=0; i<5; i++)
//     {
//         cout << '\t' << arr[i];
//     }
//     cout << endl;
//     for(int i=0; i<3; i++)
//     {
//         cout << '\t' << arr2[i];
//     }
//     cout << endl;
//     for(int i=0; i<3; i++)
//     {
//         cout << '\t' << arr3[i];
//     }
//     cout << endl;
//     return 0;
// }
