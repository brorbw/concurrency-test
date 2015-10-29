//
// Created by Bror Winther on 28/10/15.
//

#include <unistd.h>
#include <iostream>
#include "circular_array.h"


Circular_array::Circular_array(unsigned long maxSize){
    maxSize_ = maxSize;
    in = 0;
    out = 0;
    numberOfObjects = 0;
    theArray = new int[maxSize]();
}



int Circular_array::get_next_thing(int id) {
    pthread_mutex_lock(&mutx);
    while(numberOfObjects == 0){
        //printf("ArrayEmpty\n");
        pthread_cond_wait(&cond, &mutx);
    }
    int tmp = theArray[out];
    //printf("ID:%i taking out %i\n",id,tmp);
    numberOfObjects--;
    if(out == maxSize_){
        out = 0;
    } else{
        out++;
    }
    pthread_mutex_unlock(&mutx);
    pthread_cond_signal(&cond);
    return tmp;
}

void Circular_array::place_next_thing(int id, int theThing) {
    pthread_mutex_lock(&mutx);
    while(maxSize_ == numberOfObjects)
    {
        //printf("ArrayFull\n");
        pthread_cond_wait(&cond, &mutx);
    }
    //printf("ID:%i indsetting %i\n",id,theThing);
    theArray[in] = theThing;
    if(in == maxSize_){
        in = 0;
    } else {
        in++;
    }
    numberOfObjects++;
    pthread_mutex_unlock(&mutx);
    pthread_cond_signal(&cond);
}

Circular_array::~Circular_array() { };


