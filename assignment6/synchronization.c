#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define bool int
#define true 1
#define false 0

int total = 0;
int org_num = 0;
sem_t pla; //定义盘子信号量
sem_t app; //定义苹果信号量
sem_t org; //定义橘子信号量
pthread_mutex_t mutex;
int slp = 2; //表示sleep时长

void *mother(void* arg);
void *father(void* arg);
void *boy(void* arg);
void *girl(void* arg);

int main(){
	sem_init(&app,0,0);
	sem_init(&org,0,0);
	sem_init(&pla,0,5);

	pthread_t mo,fa,bo,gi;

	pthread_create(&mo, NULL, mother, NULL);
	pthread_create(&fa, NULL, father, NULL);
	pthread_create(&bo, NULL, boy, NULL);
	pthread_create(&gi, NULL, girl,NULL);
	
	pthread_join(mo, NULL);
	pthread_join(bo, NULL);
	pthread_join(gi, NULL);
	pthread_join(fa, NULL);

	
	sem_destroy(&pla);
	sem_destroy(&app);
	sem_destroy(&org);

	return 0;
}

void *mother(void *arg){
	bool put_app = true;
	while(true){
		sem_wait(&pla);
		pthread_mutex_lock(&mutex); //获得锁
		total++;
		if(put_app){
			sem_post(&app);
			printf("Mom:I have put an apple. There are %d apple(s) and %d orange(s).\n",total - org_num,org_num);
			put_app = false; //放完苹果以后再放橘子
		}else{
			org_num++;
			if(org_num % 2 == 0){ //盘子中的橘子数量为2的倍数是才可post一次org信号量
				sem_post(&org);
			}
			printf("Mom:I have put an orange. There are %d apple(s) and %d orange(s) now.\n",total - org_num,org_num);
			put_app = true; //放完橘子以后再放苹果
		}
		pthread_mutex_unlock(&mutex);
		sleep(slp);
	}
}

void *father(void *arg){
	while(true){
		sem_wait(&pla);
		pthread_mutex_lock(&mutex); //获得锁
		total++;
		org_num++;
		if(org_num % 2 == 0){
			sem_post(&org);
		}
		printf("Dad:I have put an orange. There are %d apple(s) and %d orange(s) now.\n",total - org_num,org_num);
		pthread_mutex_unlock(&mutex);
		sleep(slp);
	}
}	

void *boy(void *arg){
	while(true){
		sem_wait(&org);
		pthread_mutex_lock(&mutex); //获得锁
		total -= 2;
		org_num -= 2;
		sem_post(&pla); //吃掉两个橘子
		sem_post(&pla);
		printf("Boy:I have eaten two oranges. There are %d apple(s) and %d orange(s) now.\n",total - org_num,org_num);
		pthread_mutex_unlock(&mutex);
		sleep(slp);
	}
}

void *girl(void *arg){
	while(true){
		sem_wait(&app);
		pthread_mutex_lock(&mutex); //获得锁
		total -= 1;
		sem_post(&pla);
		printf("Girl:I have eaten one apple. There are %d apple(s) and %d orange(s) now.\n",total - org_num,org_num);
		pthread_mutex_unlock(&mutex);
		sleep(slp);
	}
}
