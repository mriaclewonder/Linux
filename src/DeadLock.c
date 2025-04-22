#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

// 互斥锁变量
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void* fun1(void *arg)
{
	int i = 0;

  // 线程1先申请资源1 在申请资源2
	pthread_mutex_lock(&mutex1);
	printf("thread 1 lock ok...\n");
  pthread_mutex_unlock(&mutex1);
	pthread_mutex_lock(&mutex2);
	printf("thread 2 lock ok...\n");

  pthread_mutex_unlock(&mutex2);
	
	printf("thread 1 do working\n");
	return NULL;
}

void* fun2(void *arg)
{
	int i = 0;
	// 线程2先申请资源2 在申请资源1
	pthread_mutex_lock(&mutex2);
	printf("thread 2 lock ok...\n");
  pthread_mutex_unlock(&mutex2);
	pthread_mutex_lock(&mutex1);
	printf("thread 1 lock ok...\n");
  pthread_mutex_unlock(&mutex1);
	
	printf("thread 2 do working\n");
}


int main(void)
{
	pthread_t pit1;
	pthread_t pit2;

	// 初始化2个互斥锁变量
	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);
	
	// 创建两个线程
	pthread_create(&pit1 ,NULL ,fun1 ,NULL);
	pthread_create(&pit2 ,NULL ,fun2 ,NULL);


	//回收资源
	pthread_join(pit1, NULL);
	pthread_join(pit2, NULL);
	
	// 销毁互斥锁
	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);
	printf("\n");

	return 0;

}