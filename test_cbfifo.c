/*
 * test_cbfifo.c - implementations of test functions for the cbfifo.c file
 * 
 * Author: Tsegazeab Taye Tefferi
 * 
 */


#include "./test_cbfifo.h"
#include "./cbfifo.c"
#include <string.h>
#include <assert.h>

struct CircularBuffer cb;

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

/*
 * Tests the cbfifo_enqueue function
 *
 * Parameters:
 *   buf      Pointer to the data
 *   nbyte    Max number of bytes to enqueue
 *   expected_return Expected return value
 *   expected_data   Expected data to be added to the buffer
 * 
 * Returns:
 *  1 on success
 *  0 on failure
 */
int test_cbfifo_enqueue(void *buf, size_t nbyte, size_t expected_return, void *expected_data){
    size_t n = cbfifo_enqueue(buf,nbyte);

    if(expected_return!=n){
        printf("Expected %d as byte written but got %d\n", (int)expected_return,(int)n);
        return 0;
    }

    if(expected_data){
        char v1[MAX_LENGTH];
        cbfifo_dequeue(v1,nbyte);

        char *v2 = expected_data;
        int LENGTH = MAX_LENGTH-1<nbyte?MAX_LENGTH-1:nbyte;
        for(int i =0;i<LENGTH;i++){
            if(*(v1+i)!=*(v2+i)){
                printf("Data Mismatch at index %d\n",i);
                return 0;
            }    
        }
    }
    return 1;
}


/*
 * Tests the cbfifo_dequeue function
 *
 * Parameters:
 *   buf      Pointer to the data
 *   nbyte    Max number of bytes to dequeue
 *   expected_return Expected return value
 *   expected_data   Expected data to be removed from the buffer
 * 
 * Returns:
 *  1 on success
 *  0 on failure
 */
int test_cbfifo_dequeue(void *buf, size_t nbyte, size_t expected_return, void *expected_data){
    size_t n = cbfifo_dequeue(buf,nbyte);

    if(expected_return!=n){
        printf("Expected %d as byte written but got %d\n", (int)expected_return,(int)n);
        return 0;
    }

    if(expected_data){
        char *v1 = buf;

        char *v2 = expected_data;
        int LENGTH = MAX_LENGTH-1<nbyte?MAX_LENGTH-1:nbyte;
        for(int i =0;i<LENGTH;i++){
            if(*(v1+i)!=*(v2+i)){
                printf("Data Mismatch at index %d\n",i);
                return 0;
            }    
        }
    }
    return 1;
}





int test_cbfifo(){
    char * buff;
    buff = "Hello There";
    assert(test_cbfifo_enqueue(buff,11,11,"Hello There")==1);
    assert(cb.tail==11);

    buff=NULL;
    assert(test_cbfifo_enqueue(buff,5,-1,NULL)==1);
    assert(cb.tail==11);

    buff="T";
    assert(test_cbfifo_enqueue(buff,1,1,"T")==1);
    assert(cb.tail==12);

    reset_fifo();
    assert(cb.tail==0);
    int numbers[32];
    for(int i =0;i<32;i++)
        numbers[i]=i;
    test_cbfifo_enqueue(numbers,126,126,numbers);
    assert(test_cbfifo_enqueue(numbers,128,127,numbers)==1);


    reset_fifo();
    int numbers2[64];
    for(int i =0;i<64;i++)
        numbers2[i]=i;
    assert(test_cbfifo_enqueue(numbers2,256,127,numbers2)==1);





    reset_fifo();
    buff="Test Data";
    cbfifo_enqueue(buff,8);
    char receiver[MAX_LENGTH];
    assert(test_cbfifo_dequeue(receiver,8,8,buff)==1);

    reset_fifo();
    cbfifo_enqueue("Hello",5);
    cbfifo_enqueue(" ",1);
    cbfifo_enqueue("There!",6);
    assert(test_cbfifo_dequeue(receiver,12,12,"Hello There!")==1);


    return 1;
    
}


int main(){
    test_cbfifo();
    printf("ALL TESTS PASSED!");
}
