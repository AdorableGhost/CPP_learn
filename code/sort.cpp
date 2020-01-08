#include <iostream>
#include <ctime>


using namespace std;


size_t time_merge = 0;


void BubbleSort(int arr1[])
{
    cout << "Bubble 冒泡排序开始了" << endl;
    static size_t  times = 0;

    int* arr = new int[10000];
    for (size_t i = 0; i < 10000; i++)
    {

        arr[i] = arr1[i];
    }


    for (size_t j = 0; j < 10000; j++)
    {
        for (size_t i = 0; i < 10000 - 1 - j; i++)
        {


            if (arr[i] <= arr[i + 1])
            {


            }
            else
            {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;

            }

            ++times;

        }

    }


    for (size_t i = 0; i < 10000; i++)
    {
        //a[i] = rand();
        cout << arr[i] << "\t";
    }


    cout << endl << endl << "times=" << times << endl;

}

void SelectionSort(int arr1[])
{
    static int times = 0;

    int* arr = new int[10000];
    for (size_t i = 0; i < 10000; i++)
    {

        arr[i] = arr1[i];
    }
    for (size_t i = 0; i < 10000; i++)
    {
        size_t min_index = i;

        for (size_t j = i; j < 10000; j++)
        {

            if (arr[i] > arr[j])
            {

                min_index = j;
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                ++times;

            }

        }



    }

    for (size_t i = 0; i < 10000; i++)
    {
        //a[i] = rand();
        cout << arr[i] << "\t";
    }

    cout << endl << endl << "times=" << times << endl;

}


void InsetionSort(int arr1[])
{
    static int times = 0;

    int* arr = new int[10000];
    for (size_t i = 0; i < 10000; i++)
    {

        arr[i] = arr1[i];
    }



    for (size_t i = 1; i < 10000; i++)
    {

        int current = arr[i];

        int pos = i;


        while (pos >= 0 && arr[pos - 1] > current)
        {

            arr[pos] = arr[pos - 1];
            pos = pos - 1;
            ++times;
        }

        arr[pos] = current;



    }







    for (size_t i = 0; i < 10000; i++)
    {
        //a[i] = rand();
        cout << arr[i] << "\t";
    }


    cout << endl << endl << "Insertion sort times=" << times << endl;

}


void ShellSort(int arr1[])
{
    static int times = 0;

    int* arr = new int[10000];
    for (size_t i = 0; i < 10000; i++)
    {

        arr[i] = arr1[i];
    }


    size_t len = 10000;
    size_t gap = 10000 / 5;

    while (gap > 0)
    {

        for (size_t i = gap; i < len; i++)	  //从增量中间分开
        {
            int tmp = arr[i];		  //要比较的数
            int preIndex = i - gap; //前面一个相聚gap远的数据
            while (preIndex > 0 && arr[preIndex] > tmp)
            {
                arr[preIndex + gap] = arr[preIndex];		//以gap 为间距的情况下用插入排序的方法向前移动，空出要插入的地方的位置
                preIndex -= gap;							 //继续往前以gap 为间距往前移动，找到arr[i] 的合适位置
                ++times;
            }
            //循环结束意味着找到了 arr[i]的合适位置  ，preIndex +gap 就是他的位置了
            arr[preIndex + gap] = tmp;


        }



        gap /= 2;
    }













    for (size_t i = 0; i < 10000; i++)
    {
        //a[i] = rand();
        cout << arr[i] << "\t";
    }


    cout << endl << endl << "Shell sort times=" << times << endl;

}


void Merge_1(int arr[], int start, int mid, int end)
{
    static int times = 0;
    int* temp = new int[end - start + 1];
    int i = start; //第一个有序数列的索引的开始
    int j = mid + 1; //第二个有序数列的索引的开始
    int k = 0; //临时区的索引

    while ((i <= mid) && (j <= end))
    {

        if (arr[i] < arr[j])
        {
            temp[k++] = arr[i];
            i++;
            ++time_merge;
        }
        else
        {

            temp[k++] = arr[j];
            j++;
            ++time_merge;
        }
    }


    while (i <= mid)
    {
        temp[k++] = arr[i++];
        ++time_merge;
    }
    while (j <= end) {
        temp[k++] = arr[j++];
        ++time_merge;

    }

    for (i = 0; i < k; i++)
    {
        arr[start + i] = temp[i];
        ++time_merge;
    }



}

void Mergeup2down(int a[], size_t start, size_t end)
{
    if (a == nullptr || start >= end)
    {

        return;
    }

    //    cout<<"Mergeing sorting"<<endl;
    size_t mid = (start + end) / 2;
    Mergeup2down(a, start, mid);
    Mergeup2down(a, mid + 1, end);

    Merge_1(a, start, mid, end);
}

void Merge_Group(int a[], size_t len, size_t gap)
{
    int i;
    int twolen = 2 * gap;


    // 将"每2个相邻的子数组" 进行合并排序。
    for (i = 0; i + 2 * gap - 1 < len; i += (2 * gap))
    {
        Merge_1(a, i, i + gap - 1, i + 2 * gap - 1);
    }



    // 若 i+gap-1 < len-1，则剩余一个子数组没有配对。
    // 将该子数组合并到已排序的数组中。
    if (i + gap - 1 < len - 1)
    {
        Merge_1(a, i, i + gap - 1, len - 1);
    }
}


/*
 * 归并排序(从下往上)
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     len -- 数组的长度
 */
void MergeDown2up(int a[], size_t len)
{
    int n;
    if (a == NULL || len <= 0)
        return;

    for (n = 1; n < len; n *= 2)
    {
        Merge_Group(a, len, n);
    }
}


void quick_sort(int a[], int l, int r)
{
    if (l < r)
    {
        int i, j, x;
        cout << "Now the array is :" << endl;
        for (size_t xk = 0; xk < 10; xk++)
        {
                        cout << "\t" << a[xk];
        }
        cout<< endl << "The next is operations :\n\n";

        i = l;
        j = r;
        x = a[i]; //单独保存a[i]，防止丢失，同时空出一个位置来交换

        while (i < j)
        {
            while (i < j && a[j] > x) //a[j]>x 说明 后面的元素大，下一个
            {
                cout << "we are finding the smallest fromt right ,and missed! \t  i=" << i << "\tj=" << j << endl;
                j--; // 从右向左找第一个小于x的数

            }

//            上面循环完已经找到 a[i]<=x 所以存到a[i] 的地方来
            if (i < j)
            {
                a[i++] = a[j];  //i++ 是为了此次循环结束自增跳到下一个去
                cout  << "a[" << i << "]=a[" << j << "]" << endl;

            }

            while (i < j && a[i] < x)

            {
                  cout << "we are finding the biggest fromt left ,and missed! \t i=" << i << "\tj=" << j << endl;
                i++; // 从左向右找第一个大于x的数

            }

            //            上面循环完已经找到 a[i]>=x 所以存到j (后面元素)的地方来，不是大就是小，所以上面交换了下面一定也会交换
            if (i < j)
            {
                cout << "a[" << j << "]=a[" << i << "]" << endl;
                a[j--] = a[i];
            }

        }
        a[i] = x; //把丢出去的元素找回来
        quick_sort(a, l, i - 1); /* 递归调用  */
        quick_sort(a, i + 1, r); /* 递归调用 */
    }
}


int main(int argc, char**)
{

    int* a = new int[10000];

    srand((unsigned int)time(0));

    for (size_t i = 0; i < 10000; i++)
    {
        a[i] = rand();
        //cout << a[i] << "\t";
    }

    //BubbleSort(a);

    //SelectionSort(a);

    //InsetionSort(a);
    //ShellSort(a);


//    Mergeup2down(a,0,9999);

//    for (size_t i = 0; i < 10000; i++)
//    {
//        //a[i] = rand();
//        cout << a[i] << "\t";
//    }
//    cout <<endl<<"Times for Merging sort is \t"<<time_merge;


    //MergeDown2up(a, 10000);

    //for (size_t i = 0; i < 10000; i++)
    //{
    //	//a[i] = rand();
    //	cout << a[i] << "\t";
    //}
    //cout << endl << "Times for Merging sort is \t" << time_merge;

    //cout << endl << "Times for Merging sort is \t" << time_merge;

    quick_sort(a, 0, 9);
    cout << "Then the array is :\n";
    for (size_t i = 0; i < 10; i++)
    {
        cout << a[i] << "\t";
    }
    cin.get();
    return 0;
}
