#include <iostream>
#include <ctime>


using namespace std;


void BubbleSort(int arr1[])
{
	cout << "Bubble 冒泡排序开始了" << endl;
	static size_t  times = 0;

	int arr[10000];
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

	int arr[10000];
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

	int arr[10000];
	for (size_t i = 0; i < 10000; i++)
	{

		arr[i] = arr1[i];
	}



	for (size_t i = 1; i < 10000; i++)
	{

		int current = arr[i];

		int pos=i;

		
		while (pos>=0 && arr[pos-1]>current)
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

	int arr[10000];
	for (size_t i = 0; i < 10000; i++)
	{

		arr[i] = arr1[i];
	}


	size_t len = 10000;
	size_t gap = 10000 / 3;

	while (gap >0)
	{

		for (size_t i = gap; i <len; i++)	  //从增量中间分开
		{
			int tmp = arr[i];		  //要比较的数
			int preIndex = i - gap; //前面一个相聚gap远的数据
			while (preIndex>0 && arr[preIndex]>tmp)
			{
				arr[preIndex+gap] = arr[preIndex];		//以gap 为间距的情况下用插入排序的方法向前移动，空出要插入的地方的位置
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

int main(int argc, char **)
{

	int a[10000];

	srand((unsigned int)time(0));

	for (size_t i = 0; i < 10000; i++)
	{
		a[i] = rand();
		//cout << a[i] << "\t";
	}

	//BubbleSort(a);

	//SelectionSort(a);

	InsetionSort(a);
	ShellSort(a);

	//for (size_t i = 0; i < 10000; i++)
	//{
	//	//a[i] = rand();
	//	cout << a[i] << "\t";
	//}





	cin.get();
	return 0;
}