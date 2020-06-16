#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define bool int
#define true 1
#define false 0
#define RUN 1
#define STOP 0



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; //修改status
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int status = RUN; //表示父亲线程运行状态
int total = 0; //总共的水果数
int org_num = 0; //橘子数
sem_t pla; //定义盘子信号量
sem_t app; //定义苹果信号量
sem_t org; //定义橘子信号量
pthread_mutex_t mutex;
int slp = 1; //表示sleep时长
int appe = 2; //表示胃口

void *mother(void* arg);
void *father(void* arg);
void *boy(void* arg);
void *girl(void* arg);
void *appetite(void* arg);
void thread_pause();
void thread_resume();
static void handler(int signo);

int main(){
	if(signal(SIGUSR1, handler) == SIG_ERR)
		printf("can not catch SIGUSR1\n");
	if(signal(SIGUSR2, handler) == SIG_ERR)
		printf("can not catch SIGUSR2\n");
	if(signal(SIGINT, handler) == SIG_ERR)
		printf("can not catch SIGINT\n");
	if(signal(SIGALRM, handler) == SIG_ERR)
		printf("can not catch SIGALRM\n");
	
#if 0
	if (pthread_mutex_init(&mut, NULL) != 0)
		printf("mutex init error\n");
	if (pthread_cond_init(&cond, NULL) != 0)
		printf("cond init error\n");
#endif
	alarm(1); //发送改变胃口的信号

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
			printf("Mom:I have put 1 apple. There are %d apple(s) and %d orange(s).\n",total - org_num,org_num);
			put_app = false; //放完苹果以后再放橘子
		}else{
			org_num++;
			sem_post(&org);
			printf("Mom:I have put 1 orange. There are %d apple(s) and %d orange(s) now.\n",total - org_num,org_num);
			put_app = true; //放完橘子以后再放苹果
		}
		pthread_mutex_unlock(&mutex);
		sleep(slp);
	}
}

void *father(void *arg){
	while(true){
		pthread_mutex_lock(&mut);//有电话打来就要阻塞
		while (!status){
			pthread_cond_wait(&cond, &mut);
		}
		pthread_mutex_unlock(&mut);

		sem_wait(&pla);
		pthread_mutex_lock(&mutex); //获得锁
		total++;
		org_num++;
		sem_post(&org);
		printf("Dad:I have put 1 orange. There are %d apple(s) and %d orange(s) now.\n",total - org_num,org_num);
		pthread_mutex_unlock(&mutex);
		sleep(slp);
	}
}	

void *boy(void *arg){
	while(true){
		sem_wait(&org);
		int a = appe; //获取当前胃口
		if(a == 1){
			pthread_mutex_lock(&mutex); //获得锁
			total -= 1;
                        org_num -= 1;
			sem_post(&pla);
			printf("Boy:I have eaten %d oranges. There are %d apple(s) and %d orange(s) now.\n",a,total - org_num,org_num);
			pthread_mutex_unlock(&mutex);
			sleep(slp);
		}else{
			sem_wait(&org);
			pthread_mutex_lock(&mutex); //获得锁
			int i = 0;
			for(i = 0;i < a;i++){
				total -= 1;
				org_num -= 1;
				sem_post(&pla); //根据当前的胃口吃掉相应个数的橘子
			}
	                printf("Boy:I have eaten %d oranges. There are %d apple(s) and %d orange(s) now.\n",a,total - org_num,org_num);
        	        pthread_mutex_unlock(&mutex);
               		sleep(slp);
		}
	}
}

void *girl(void *arg){
	while(true){
		sem_wait(&app);
		pthread_mutex_lock(&mutex); //获得锁
		total -= 1;
		sem_post(&pla);
		printf("Girl:I have eaten 1 apple. There are %d apple(s) and %d orange(s) now.\n",total - org_num,org_num);
		pthread_mutex_unlock(&mutex);
		sleep(slp);
	}
}


void thread_pause() //暂停父亲线程
{
	if (status == RUN)//根据当前状态来阻塞父亲线程
	{
		pthread_mutex_lock(&mut);
		status = STOP;
		printf("Dad is on the phone!\n");
		pthread_mutex_unlock(&mut);
	}else{
		printf("Dad is already on the phone!\n");
	}
}

void thread_resume()
{
	if (status == STOP)//根据当前状态来释放父亲线程
	{
		pthread_mutex_lock(&mut);
		status = RUN;
		pthread_cond_signal(&cond);
		printf("Dad's back for the fruit!\n");
		pthread_mutex_unlock(&mut);
	}else{
		printf("Dad is already putting the fruit!\n");
	}
}

static void handler(int signo)
{
	if(signo == SIGUSR1)
		thread_pause();
	else if(signo == SIGUSR2)
		thread_pause();
       	else if(signo == SIGINT)
		thread_resume();
	else if(signo == SIGALRM){//改变胃口
		alarm(1);//发出下一个SIGALRM信号
		if(appe == 1){
			appe = 2;
		}else{
			appe = 1;
		}
	}
	else
		printf("received signal %d\n", signo);
}
