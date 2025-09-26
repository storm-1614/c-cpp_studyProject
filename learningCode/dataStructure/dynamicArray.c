#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    // 指向 int 类型的指针，指向动态分配的内存区域，这个区域存储了数组的元素。
    // 通过这个指针可以访问和操作元素。
    // 由于是动态分配的，所以数组的大小可以在运行时改变，提供了比静态数组更大的灵活性。
    int *array;
    // 用于存储数组中当前存储的元素数量
    // size 成员能让程序知道数组中当前有多少个有效元素。
    // 这对于遍历数组、添加或删除元素等至关重要
    size_t size;
    // 存储数组当前容量，即数组可以存储的最大元素数量而不必重新分配内存
    // 当元素数量达到 capacity 时，如果还要添加新元素就要重新分配更大的内存空间，并相应更新 capacity 值
    // 有助于管理内存使用，避免内存溢出，减少不必要的内存分配操作
    size_t capacity;
} dynamic_array;

// 用于创建一个动态数组并进行初始化
dynamic_array *create_array(size_t initial_capatity)
{
    // 为 dynamic_array 结构体分配内存，并将返回的指针赋给 arr
    dynamic_array *arr = (dynamic_array *)malloc(sizeof(dynamic_array));
    if (arr == NULL)
    {
        printf("Error: Failed to allocate memory for dynamic array structure.\n");
        return NULL;
    }
    // 为内部整数数组分配内存
    // 内存大小根据 initial_capatity * sizeof(int) 得出
    arr->array = (int *)malloc(initial_capatity * sizeof(int));
    if (arr->array == NULL)
    {
        printf("Error: Failed to allocate memory for the internal integer array.\n");
        // 如果为 array 成员分配内存失败就会释放为 dynamic_array 结构体的内存防止内存泄漏
        free(arr);
        return NULL;
    }
    // 初始化 size 为 0，表示动态数组目前为空
    arr->size = 0;
    // 将 initial_capatity 赋给 capacity，记录数组的初始容量
    arr->capacity = initial_capatity;
    // 返回指向新创建的 dynamic_array 结构体指针 arr
    return arr;
}

// 用于从动态数组中读取指定索引处的元素
// 如果索引超出数组范围,就会打印错误信息并返回 -1
int read_array(dynamic_array *arr, size_t index)
{
    if (index < arr->size)
        return arr->array[index];
    else
    {
        printf("Error: index out of bound: %ld.\n", index);
        return -1;
    }
}

// 用于更新动态数组中指定索引处的元素。
// 如果索引超出数组范围，就会打印错误信息并返回
void update_array(dynamic_array *arr, size_t index, int value)
{
    if (index < arr->size)         // 检查索引的有效性
        arr->array[index] = value; // 更新对于索引处的元素
    else                           // 如果索引超出数组边界
        printf("Error: index out of bounds>: %ld.\n", index);
}

// 向动态数组追加一个新元素
// 如果数组已满，会先进行数组扩容,并重新分配内存
// 然后它将新元素添加到数组的末尾,并更新数组大小
// arr 为指向动态数组的指针， value 是要追加的新元素
int append_array(dynamic_array *arr, int value)
{
    // 检查容量
    if (arr->size >= arr->capacity) // 如果数组已满
    {
        // 计算新容量：通常新的容量是原容量的两倍。
        // 以减少因重新分配内存而导致的性能开销
        size_t new_capatity = arr->capacity * 2;
        // 调用 realloc ，尝试将 arr->array 指向的内存扩展到 new_capatity * sizeof(int) 大小
        int *new_array = (int *)realloc(arr->array, new_capatity * sizeof(int));
        if (new_array == NULL)
        {
            printf("Error: Failsed to reallocate memory for the internal integer array.\n");
            return -1;
        }

        // 如果内存重新分配成功，将 arr->array 更新为新内存块的指针,并更新 capacity
        arr->array = new_array;
        arr->capacity = new_capatity;
    }
    // 将新元素追加到数组末尾然后数组大小自增
    arr->array[arr->size] = value;
    arr->size++;
    return 0;
}

// 在动态数组的指定位置插入一个新的元素
int insert_array_element(dynamic_array *arr, size_t index, int value)
{
    // 检查索引是否有效
    if (index > arr->size)
    {
        printf("Error: index out of bound for insertion:%ld.\n", index);
        return -1;
    }

    // 如果是末尾插入，直接调用上面写的追加函数
    if (index == arr->size)
        return append_array(arr, value);

    // 检查容量
    if (arr->size >= arr->capacity)
    {
        size_t new_capatity = arr->capacity * 2;
        int *new_array = (int*)realloc(arr->array, new_capatity * sizeof(int));
        if (new_array == NULL)
        {
            printf("Error: Failed to reallocate memory for the internal integer array.\n");
            return -1;
        }
        arr->array = new_array;
        arr->capacity = new_capatity;
    }

    // 元素右移腾出空间
    for (size_t i = arr->size;i > index;i--)
        arr->array[i] = arr->array[i-1];

    //插入新的元素
    arr->array[index] = value;
    arr->size++;

    return 0;
}

// 在动态数组移除元素
int remove_array_element(dynamic_array *arr, size_t index)
{
    if (index > arr->size)
    {
        printf("Error: index out of bounds: %ld\n", index);
        return -1;
    }

    // 元素左移
    for (size_t i = index; i < arr->size;i++)
        arr->array[i] = arr->array[i+1];

    // 更新数组大小
    arr->size--;
    return 0;
}

// 打印动态数组中的所有元素
void print_array(dynamic_array* arr){
    for (size_t i = 0;i < arr->size;i++)
        printf("%d ", arr->array[i]);
    printf("\n");
}

// 删除动态数组
void delete_array(dynamic_array* arr){
    free(arr->array);
    arr->array = NULL;
    free(arr);
    arr = NULL;
}

int main(int argc, char *argv[])
{
    dynamic_array* arr = create_array(6);

    // 追加元素测试
    puts("追加元素测试...");
    append_array(arr, 10);
    append_array(arr, 20);
    append_array(arr, 30);
    append_array(arr, 40);

    // 打印数组测试
    puts("打印数组测试...");
    print_array(arr);

    // 插入元素测试
    insert_array_element(arr, 3, 999);
    puts("插入元素测试...");
    printf("%d\n", arr->array[3]);

    // 移除元素测试
    puts("移除元素测试...");
    remove_array_element(arr, 2);
    print_array(arr);

    //删除元素测试
    puts("删除元素测试...");
    delete_array(arr);

    return 0;
}
