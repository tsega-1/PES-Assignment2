/*
Utility functions helpful for testing
Necessary since cbfifo.h can't be modified
*/


#include <stdint.h>


/*
 * Resets the circular buffer
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *  none
 */
void reset_fifo();



/*
 * Returns the current tail value
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *  The current tail value of the FIFO
 */
uint32_t get_tail();



/*
 * Returns the current head value
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *  The current head value of the FIFO
 */
uint32_t get_head();