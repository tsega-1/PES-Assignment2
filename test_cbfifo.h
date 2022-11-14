/*
 * test_cbfifo.h - definitions for test functions of the cbfifo.c file
 * 
 * Author: Tsegazeab Taye Tefferi
 * 
 */



#include <stdio.h>
#include <stdint.h>

/*
 * Tests the cbfifo_enqueue function
 *
 * Parameters:
 *   buf      Pointer to the data
 *   nbyte    Max number of bytes to enqueue
 * 
 * Returns:
 *  1 on success
 *  0 on failure
 */
int test_cbfifo_enqueue(void *buf, size_t nbyte, size_t expected_return, void *expected_data);


/*
 * Tests the cbfifo_dequeue function
 *
 * Parameters:
 *   buf      Destination for the dequeued data
 *   nbyte    Bytes of data requested
 * 
 * Returns:
 *  1 on success
 *  0 on failure 
 * 
 */
int test_cbfifo_dequeue(void *buf, size_t nbyte, size_t expected_return, void *expected_data);


/*
 * Resets the circular buffer
 *
 * Parameters:
 *   none
 * 
 * Returns:
 * None
 */
void reset_fifo();