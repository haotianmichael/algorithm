#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define N 5
#define LEFT(i) i
#define RIGHT(i) (i+1)%N
#define THINKING 0
#define HUNGRY 2
#define EATING 3

//state of each philosopher
int state[N];

pthread_mutex_t mutex;    
pthread_mutex_t chop[N];



void testChop(int number) {
	if(state[number] == HUNGRY && 
		state[LEFT(number)] != EATING && 
		state[RIGHT(number)] != EATING) {

		state[number] = EATING;
		pthread_mutex_unlock(&chop[number]);	
	}
} 



void takeChop(int number) {
		
	pthread_mutex_lock(&mutex);
	state[number] = HUNGRY;	
	testChop(number);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_lock(&chop[number]);
}


void putChop(int number) {
	pthread_mutex_lock(&mutex);
	state[number] = THINKING;
	testChop(LEFT(number));	
	testChop(RIGHT(number));
	pthread_mutex_unlock(&mutex);
}


void thinking(int num) {
	pthread_mutex_lock(&mutex);
	state[num] = THINKING;
	printf("philosophre %d is thinking \n", num);
	pthread_mutex_unlock(&mutex);
	sleep(2);
}


void philosopher(int *num) {
	int number = *num;	
	while(1) {
		thinking(number);
				
		takeChop(number);
	
		printf("philosopher %d is eating \n", number);
		sleep(2);
	
		putChop(number);
	}
}
int main() {
		
	pthread_t tid[5];
	int i;
	for(i=0; i<5; i++) {
		pthread_mutex_init(&chop[i], NULL);
	}

	
	int pa[5];
	for(i=0; i<5; i++) {
		pa[i] = i+1;
		pthread_create(&tid[i], NULL, (void *)philosopher, &pa[i]);
	}	
		
	for(i=0; i<5; i++) {
		pthread_join(tid[i], NULL);	
	}

	for(i=0; i<5; i++) {
		pthread_mutex_destroy(&chop[i]);
	}
	return 0;
}


