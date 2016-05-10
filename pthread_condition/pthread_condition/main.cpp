//
//  main.cpp
//  pthread_condition
//
//  Created by jimmygao on 5/5/16.
//  Copyright © 2016 jimmygao. All rights reserved.
//

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutexEvent;

pthread_cond_t condiction;
int num = 100;

void* ThreadA(void *arg)
{
    while(num > 0)
    {
        pthread_mutex_lock(&mutex1);
//        sleep(1);
        num --;
        std::cout << "ThreadA:" << num << std::endl;
        if(num == 80)
        {
            pthread_cond_signal(&condiction);
        }
        pthread_mutex_unlock(&mutex1);
    }
    
    return NULL;
}
void* ThreadB(void *arg)
{
    pthread_mutex_lock(&mutexEvent);
    pthread_cond_wait(&condiction, &mutexEvent);
    pthread_mutex_unlock(&mutexEvent);
    
    while (num > 0) {
        pthread_mutex_lock(&mutex1);
//        sleep(1);
        num++;
        std::cout << "ThreadB:" << num << std::endl;
        pthread_mutex_unlock(&mutex1);
    }
    
    return NULL;
}

int main(int argc, const char * argv[]) {
    
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutexEvent, NULL);
    pthread_cond_init(&condiction, NULL);
    
    pthread_t thread1,thread2;
    pthread_create(&thread1, NULL, &ThreadA, NULL);
    pthread_create(&thread2, NULL, &ThreadB, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
