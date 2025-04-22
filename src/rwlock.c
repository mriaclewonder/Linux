#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>
#include <bits/pthreadtypes.h>

// 读写锁变量
pthread_rwlock_t rwlock;

int num = 0;

void* fun_read(void *arg)
{
	int index = (int)(long)arg;

	while(1)
	{
		// 加锁
		pthread_rwlock_rdlock(&rwlock);

		printf("线程%d读取num的值:%d\n",index ,num);
		
		// 解锁
		pthread_rwlock_unlock(&rwlock);

		sleep(random() % 3 +1);	
	}
	return NULL;
}

void* fun_write(void *arg)
{

	int index = (int)(long)arg;

	while(1)
	{
	
		// 加锁
		pthread_rwlock_wrlock(&rwlock);

		num++;
		printf("线程%d修改num的值:%d\n",index ,num);

		// 解锁
		pthread_rwlock_unlock(&rwlock);


		sleep(random() % 3 +1);	
	}

	return NULL;
}

int main(void)
{
	pthread_t pit[8];

	// 创建随机数种子
	srandom(getpid());

	// 初始化
	pthread_rwlock_init(&rwlock, NULL);

	// 创建8个线程
	int i = 0;
	for(i = 0;i < 8;i++)
	{
		if(i < 5)
		{
			pthread_create(&pit[i], NULL, fun_read, (void *)(long)i);
		}
		else
		{
			pthread_create(&pit[i], NULL, fun_write, (void *)(long)i);
		}

	}

	// 回收线程资源
	for(i = 0;i < 8;i++)
	{
	
		pthread_join(pit[i],NULL);
	}

	// 销毁
	pthread_rwlock_destroy(&rwlock);

	return 0;
}