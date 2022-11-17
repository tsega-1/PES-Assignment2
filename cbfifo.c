/*
 * cbfifo.c - a circular buffer implementation.
 * 
 * Author: Tsegazeab Taye Tefferi, ttefferi@andrew.cmu.edu
 * 
 */

#include "cbfifo.h"
#include "utility.h"

#include <stdint.h>

#define MAX_LENGTH 128


struct CircularBuffer{
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
size_t cbfifo_capacity(){
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
size_t cbfifo_length(){
    if(cb.tail >= cb.head){
        return cb.tail - cb.head;
    }
    return (cb.tail-cb.head) & cbfifo_capacity();
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
size_t cbfifo_available(){
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
size_t cbfifo_enqueue(void *buf, size_t nbyte){
    if(buf==NULL)
        return -1;

    void *s = buf;
    while(cbfifo_available() && (s-buf<nbyte)){
        cb.buffer[cb.tail] = *((char*)s++);
        cb.tail = (cb.tail+1)& cbfifo_capacity();
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
size_t cbfifo_dequeue(void *buf, size_t nbyte){
    char *s = buf;

    while(cbfifo_length() && (s-(char*)buf<nbyte)){
        *(s++) = cb.buffer[cb.head];
        cb.head = (cb.head+1)& cbfifo_capacity();
    }
    return s - (char*)buf;
}


/*
 * Resets the circular buffer
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *  none
 */
void reset_fifo(){
    for(int i =0; i<cbfifo_capacity();i++)
        cb.buffer[i]=0;
    cb.head = 0;
    cb.tail = 0;
}



uint32_t get_tail(){
    return cb.tail;
}

uint32_t get_head(){
    return cb.head;
}