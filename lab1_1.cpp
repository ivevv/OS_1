//Иванчук Евгения, 9894

#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <exception>

using namespace std;

static exception_ptr expt = NULL;

void* func1(void *npt)
{
	try
	{
		int *temp = (int*)npt;
		int size = *temp;
		if (size < 1)
		{
			throw (size);
		}
		int *arr;
		arr = (int*)malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
		{
			arr[i] = i + 1;
		}
		pthread_exit((void*)arr);
	}
	catch (int ex)
	{
		expt = current_exception();
	}
}

int main()
{
	int n;
	cout << "Введите число N:" << endl;
	cin >> n;
	int *npt = (int*)malloc(sizeof(int));
	*npt = n;
	pthread_t th1;
	pthread_create(&th1, NULL, func1, (void*)npt);
	int *rvarr;
	pthread_join(th1, (void**)&rvarr);
	if (expt != NULL)
	{
		try
		{
			rethrow_exception(expt);
		}
		catch (int ex)
		{
			cout << "№2. Было поймано исключение: некорректное значение N = " << ex << "." << endl;
		}
	}
	else
	{
		cout << "№1. Массив " << n << " чисел, созданный в потоке: " << endl;
		for (int i = 0; i < n; i++)
		{
			cout << rvarr[i] << " ";
		}
		cout << endl;
		free(rvarr);
	}
	cout << "№3. Потоки позволяют выполнять несколько функций одновременно, а не по порядку, то есть их использование ускоряет работу программы." << endl;
	free(npt);
	return 0;
}
