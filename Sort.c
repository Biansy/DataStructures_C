#include <stdio.h>

/**
 * 插入排序
 */
void Insertion_Sort(int *arr, int length)
{
    int j;
    for (int i = 1; i < length; i ++) {
        int temp = arr[i];
        for (j = i; j > 0 && arr[j-1] < temp; j --) {
            arr[j] = arr[j-1];
        }
        arr[j] = temp; 
    }
}

/**
 * 冒泡排序
 */
void Bubble_Sort(int *arr, int length)
{
    int temp;
    for (int i = 0; i < length; i ++) {
        for (int j = i+1; j < length; j ++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

/**
 * 归并排序
 */
static void Merge(int *arr, int *backup, int left_start, int right_start, int right_end)
{
    int left_end = right_start - 1;
    int start = left_start;
    int length = right_end - left_start + 1;

    while(left_start <= left_end && right_start <= right_end)
    {
        if(arr[left_start] < arr[right_start])
            backup[start++] = arr[left_start++];
        else
            backup[start++] = arr[right_start++];
    }
    while(left_start <= left_end)
        backup[start++] = arr[left_start++];
    while(right_start <= right_end)
        backup[start++] = arr[right_start++];

    for(int i = 0; i < length; i ++, right_end--)
        arr[right_end] = backup[right_end];
}

void Merge_Sort(int *arr, int *backup, int left, int right)
{
    int center;
    if (left < right)
    {
        center = (left + right) / 2;
        Merge_Sort(arr, backup, left, center);
        Merge_Sort(arr, backup, center+1, right);
        Merge(arr, backup, left, center+1, right);
    }
}

int main()
{
    // int arr[] = {7,3,9,2,5,4,1,0,8,6};
    int arr[] = {9,8,7,6,5,4,3,2,1,0};
    int b[10];
    Merge_Sort(arr, b, 0, 9);

    for(int i = 0; i < 10; i ++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}