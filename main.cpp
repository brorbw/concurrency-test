#include <iostream>
#include "circular_array.h"


struct args_struct{
    Circular_array* cir;
    int id;
};

void* consumer(void* args){
    auto argsStruct = (args_struct*) args;
    auto cir = argsStruct->cir;
    int id = argsStruct->id;
    while(true){
        cir->get_next_thing(id);
        //std::cout << "I have consumed a thing" << std::endl;
        usleep(rand() % 10);
    }
}

void* producer(void* args){
    auto argsStruct = (args_struct*) args;
    auto cir = argsStruct->cir;
    int id = argsStruct->id;
    while(true){
        cir->place_next_thing(id,rand() % 100);
        //std::cout << "I have produced a thing" << std::endl;
        usleep(rand() % 1000000);
    }
}


int main() {
    int numberOfThreads = 500;
    pthread_t consume;
    pthread_t threadArray[numberOfThreads];
    int s;
    Circular_array cir_(5);

    for(int i = 0; i < numberOfThreads; i++){
        args_struct str;
        str.cir = &cir_;
        str.id = i;
        s = pthread_create(&threadArray[i], NULL, &producer, &str);
        if(s != 0){
            return -1;
        }
        printf("Created thread ID: %i\n",i);
    }
    args_struct str;
    str.cir = &cir_;
    str.id = 100;
    s = pthread_create(&consume, NULL, &consumer, &str);
    if(s != 0){
        return -1;
    }
    for(pthread_t p : threadArray){
        pthread_join(p,NULL);
    }
    pthread_join(consume,NULL);
    return 0;
}