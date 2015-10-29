//
// Created by Bror Winther on 28/10/15.
//

#ifndef GRAFJO_CIRCULARARRAY_H
#define GRAFJO_CIRCULARARRAY_H

class Circular_array {
public:
    Circular_array(unsigned long maxSize);

    int get_next_thing(int id);

    void place_next_thing(int id,int theThing);

    ~Circular_array();

private:
    int* theArray;
    unsigned long in;
    unsigned long out;
    unsigned long maxSize_;
    unsigned long numberOfObjects;
    pthread_cond_t cond;
    pthread_mutex_t mutx;
};

#endif //GRAFJO_CIRCULARARRAY_H
