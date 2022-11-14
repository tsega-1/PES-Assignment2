/*
 * cbfifo.c - a circular buffer implementation.
 * 
 * Author: Tsegazeab Taye Tefferi, ttefferi@andrew.cmu.edu
 * 
 */

//#include "./cbfifo.h"
//Including the cbfifo.h file breaks everything. The code won't compile raising a host of errors each more unpassable than the one before.
//If the definitions in the cbfifo.h file could be modifed to include 'static inline' then it could've been included without issues.
//
//Also, the functions had to be delcared 'static inline' so that the compiler won't throw 'multiple definitions' error.

#include <stdint.h>

#define MAX_LENGTH 128


extern struct CircularBuffer{
    char buffer[MAX_LENGTH];

    uint8_t head;
    uint8_t tail;
    
} cb;


/*
 * Returns the FIFO's capacity
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   The capacity, in bytes, for the FIFO
 */
static inline size_t cbfifo_capacity(){
    return MAX_LENGTH-1;
}


/*
 * Returns the number of bytes currently on the FIFO. 
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   Number of bytes currently available to be dequeued from the FIFO
 */
static inline size_t cbfifo_length(){
    if(cb.tail >= cb.head){
        return cb.tail - cb.head;
    }
    return (cb.tail-cb.head) % (cbfifo_capacity()+1);
}


/*
 * Returns the FIFO's available space
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   The available space, in bytes, for the FIFO
 */
static inline size_t cbfifo_available(){
    return cbfifo_capacity() - cbfifo_length();
}

/*
 * Enqueues data onto the FIFO, up to the limit of the available FIFO
 * capacity.
 *
 * Parameters:
 *   buf      Pointer to the data
 *   nbyte    Max number of bytes to enqueue
 * 
 * Returns:
 *   The number of bytes actually enqueued, which could be 0. In case
 * of an error, returns (size_t) -1.
 */
static inline size_t cbfifo_enqueue(void *buf, size_t nbyte){
    if(buf==NULL)
        return -1;

    void *s = buf;
    while(cbfifo_available() && (s-buf<nbyte)){
        cb.buffer[cb.tail] = *((char*)s++);
        cb.tail = (cb.tail+1)% (cbfifo_capacity()+1);
    }        
    return s-buf;
}


/*
 * Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * Parameters:
 *   buf      Destination for the dequeued data
 *   nbyte    Bytes of data requested
 * 
 * Returns:
 *   The number of bytes actually copied, which will be between 0 and
 * nbyte. 
 * 
 * To further explain the behavior: If the FIFO's current length is 24
 * bytes, and the caller requests 30 bytes, cbfifo_dequeue should
 * return the 24 bytes it has, and the new FIFO length will be 0. If
 * the FIFO is empty (current length is 0 bytes), a request to dequeue
 * any number of bytes will result in a return of 0 from
 * cbfifo_dequeue.
 */
static inline size_t cbfifo_dequeue(void *buf, size_t nbyte){
    char *s = buf;

    while(cbfifo_length() && (s-(char*)buf<nbyte)){
        *(s++) = cb.buffer[cb.head];
        cb.head = (cb.head+1)% (cbfifo_capacity()+1);
    }
    return s - (char*)buf;
}