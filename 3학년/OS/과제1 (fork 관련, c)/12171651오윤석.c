//12171651 컴퓨터공학과 오윤석 오퍼레이팅 시스템 과제1 (Producer comsumer problem)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define BUFFER_SIZE 10 //버퍼 사이즈 설정 

typedef int buffer_item;

buffer_item buffer[BUFFER_SIZE];

int in = 0;
int out = 0;
int SLEEP_TIME; //sleep time 설정
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int seed; //시드 설정

sem_t empty; //empty semaphore
sem_t full; //full semaphore

int produce_item(void) //random한 item을 생성한다.
{
    int item = rand();

    return item;
}

int add_item(buffer_item item) //in++하고 아이템을 버퍼에 넣는 함수
{
    in++;
    in %= 10; //최대 버퍼가 10이기 때문에 %10을 해준다.

    return buffer[in] = item;
}

int remove_item(buffer_item *item) //out++하고 item[out]에 해당하는 값을 return하고 지워주는 함수
{
    out++;
    out %= 10;

    return item[out];
}

int consume_item(buffer_item item) //item을 return하는 함수 (출력할때 사용한다.)
{
    return item;
}

void *producer(void *pp)
{
    buffer_item item; //item 변수 선언
    int p_id = *((int*)pp); //pp에서 가져온 producer 파라미터 thread의 id값을 할당해준다.

    while(1)
    {
        sleep(rand_r(&seed)%SLEEP_TIME+ 1); //지연시간  and Entry section 시작
        item = produce_item(); //item을 할당해준다.
        sem_wait(&empty); //버퍼에 빈 공간이 생길 떄까지 기다림
        pthread_mutex_lock(&mutex); //임계 구역에 진입할 수 있을 때까지 기다린다.

        add_item(item); //아이템을 추가한다. and critical section 시작
        printf("P%d          produced %d\n", p_id, item); //thread id, item 출력
        printf("\n");

        pthread_mutex_unlock(&mutex); //임계 구역을 빠져나왔다고 알려준다. and Exit section 시작
        sem_post(&full); //버퍼에 아이템이 있다고 알려준다.
        sleep(SLEEP_TIME);
    }
}

void *consumer(void *cp)
{
    buffer_item item;   //item 변수 선언
    int c_id = *((int*)cp); //cp에서 가져온 consumer 파라미터 thread의 id값을 할당해준다.

    while(1)
    {
        sleep(rand_r(&seed)%SLEEP_TIME+ 1);
        sem_wait(&full); //버퍼에 빈 공간이 생길 떄까지 기다림
        pthread_mutex_lock(&mutex); //임계 구역에 진입할 수 있을 때까지 기다린다.

        item = remove_item(buffer); //아이템을 삭제한다. and critical section 시작
        printf("C%d          consumed %d\n", c_id-1, consume_item(item));   //thread id, item 출력
        printf("\n");

        pthread_mutex_unlock(&mutex);  //임계 구역을 빠져나왔다고 알려준다. and Exit section 시작
        sem_post(&empty); //버퍼에 빈 공간이 있다고 알려준다.
        sleep(SLEEP_TIME);
    }
}

void init() //mutex, semaphore, buffer 초기화 함수
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    for(int i=0; i<BUFFER_SIZE; i++)
    {
        buffer[i] = 0;
    }
}

int main(int argc, char *argv[])
{
    int duration = 0; //몇초동안 진행할 것인지 결정하는 변수
    int number_of_producers = 0; //producer 개수
    int number_of_consumers = 0; //consumer 개수
    int id = 0; //thread id

    seed = (unsigned int)time(NULL); //seed 값 조정
    srand(seed);

    duration = atoi(argv[1]);
    number_of_producers = atoi(argv[2]);
    number_of_consumers = atoi(argv[3]);

    init(); //초기화

    SLEEP_TIME = duration / 10 + duration % 10; //sleep time 설정

    pthread_t ptid[number_of_producers]; //thread 변수 5개 생성
    pthread_t ctid[number_of_consumers]; // //

    for(int i = 0; i < number_of_producers; ++i) //producer thread 5개 생성
    {
        int result = pthread_create(&ptid[i], NULL, producer, (void*) &id);
        ++id;

        if(result == -1) //잘못된 thread 생성시
        {
            printf("%s\n", "producer creation error!");
        }
    }

    id = 0;

    for(int j = 0; j < number_of_consumers; ++j) //consumer thread 5개 생성
    {
        int result =  pthread_create(&ctid[j], NULL, consumer, (void*) &id);
        ++id;

        if (result == -1) //잘못된 thread 생성시
        {
            printf("%s\n", "consumer creation error!");
        }
     }

    sleep(duration);

    for(int i = 0; i < number_of_producers;  ++i)   //producer thread 종료
    {
        pthread_join(ptid[i], NULL);
        pthread_cancel(ptid[i]);
    }

    for(int j = 0; j < number_of_consumers; ++j)    //consumer thread 종료
    {
        pthread_join(ctid[j], NULL);
        pthread_cancel(ctid[j]);
    }

    pthread_mutex_destroy(&mutex); //mutex 해체
    sem_destroy(&empty); //semaphore 해체
    sem_destroy(&full); //semaphore 해체

    return 0;

}