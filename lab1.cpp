//Иванчук Евгения, 9894

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

void* func1(void *flag1)
{
	bool *flag = (bool*)flag1;
	while (*flag == 1)
	{
		cout << "1 ";
		cout.flush();
		sleep(1);
	}
	int rv1 = 55;
	int *rv1pt = (int*)malloc(sizeof(int));
	*rv1pt = rv1;
	pthread_exit((void*)rv1pt);
}

void* func2(void *flag2)
{
	bool *flag = (bool*)flag2;
	while (*flag == 1)
	{
		cout << "2 ";
		cout.flush();
		sleep(1);
	}
	int rv2 = 77;
	int *rv2pt = (int*)malloc(sizeof(int));
	*rv2pt = rv2;
	pthread_exit((void*)rv2pt);
}

int main()
{
	bool flag1 = true, flag2 = true;
	pthread_t th1, th2;
	pthread_create(&th1, NULL, func1, (void*)&flag1);
	pthread_create(&th2, NULL, func2, (void*)&flag2);
	getchar();
	flag1 = false;
	flag2 = false;
	int *res1, *res2;
	pthread_join(th1, (void**)&res1);
	pthread_join(th2, (void**)&res2);
	cout << "Return value of the 1st thread: " << *res1 << endl;
	cout << "Return value of the 2nd thread: " << *res2 << endl;
	free(res1);
	free(res2);
	return 0;
}
