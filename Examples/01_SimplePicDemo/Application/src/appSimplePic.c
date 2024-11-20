#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "appSimplePic.h"                     // Application header file
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
osThreadId_t tid_Thread;                        // thread id
 
void Thread (void *argument);                   // thread function

int Init_Thread (void) {
 
  tid_Thread = osThreadNew(Thread, NULL, NULL);
  if (tid_Thread == NULL) {
    return(-1);
  }
 
  return(0);
}
 
void Thread (void *argument) {

    uint16_t Temp;
    uint8_t VFD_Grids [6] = {0,0,0,0,0,0};
    while (1) {
        
        VFD_Grids[0] = 0x03;
        //First Send 0th
        
        for(size_t i = 0; i < 40; i++)
        {
            Temp = (((uint16_t)VFD_Grids[i/8 + 1]) << 8) | ((uint16_t)(VFD_Grids[i/8]));
            
            Temp = Temp << 1;
            VFD_Grids[i/8      ] = (uint8_t)  Temp;
            
            VFD_Grids[i/8 + 1] = (uint8_t) (Temp >> 8);
            
            //Cycle Send 1-40th
        }
        
        VFD_Grids[5] = VFD_Grids[5] << 1;
        // 41th Send
        VFD_Grids[5] = 0x0C;
        // 42th Send
        VFD_Grids[5] = 0x00;
        
        
        osThreadYield();                            // suspend thread
    }
}
