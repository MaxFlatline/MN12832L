#include "RTE_Components.h"             // Component selection
#include CMSIS_device_header
#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "appSimplePic.h"                     // Application header file

#include "Driver_SPI.h"
/* SPI Driver */
extern ARM_DRIVER_SPI Driver_SPI1;
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
uint8_t VFD_RowData_DEF[21] [24];
uint8_t VFD_RowData_ABC[21] [24];
// const uint16_t image_size PROGMEM = 512;
const uint8_t image[512] = {
  0b11111000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b11100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b11000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b10000000, 0b01110011, 0b11111111, 0b10000011, 0b11111111, 0b11110001, 0b11111110, 0b00000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000001, 0b11110011, 0b11111111, 0b10001100, 0b11111111, 0b11000111, 0b11111111, 0b00000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000001, 0b11110011, 0b11111111, 0b10001111, 0b11001110, 0b00011111, 0b11111000, 0b01000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000011, 0b11110011, 0b11111111, 0b10001111, 0b11001100, 0b01111111, 0b11100000, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000000, 0b00000011, 0b11111111, 0b10001111, 0b11000001, 0b11111111, 0b10001110, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000011, 0b11110011, 0b11111111, 0b10001111, 0b11000111, 0b11111110, 0b00001110, 0b00000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000001, 0b11110011, 0b11111111, 0b10001111, 0b00011111, 0b11111000, 0b11101110, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000001, 0b11110011, 0b11111111, 0b10001100, 0b01111111, 0b11100001, 0b11101110, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000011, 0b11110011, 0b11111111, 0b10000001, 0b11111111, 0b10001001, 0b11101110, 0b01000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000000, 0b00000011, 0b11111111, 0b10000111, 0b11111110, 0b00111001, 0b11101110, 0b01000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000011, 0b11110011, 0b11111110, 0b00111111, 0b11111000, 0b11100000, 0b00000000, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000011, 0b11110011, 0b11111000, 0b11111111, 0b11100000, 0b00011111, 0b11111110, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000011, 0b11110011, 0b11100011, 0b11111111, 0b10001111, 0b11111111, 0b11111111, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000011, 0b11110011, 0b11110001, 0b11111111, 0b10001111, 0b11111111, 0b11111111, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000011, 0b11110011, 0b11111100, 0b01111111, 0b11100000, 0b00011111, 0b11111110, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000001, 0b11110011, 0b11111111, 0b00011111, 0b11111000, 0b11100000, 0b00000000, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000001, 0b11110011, 0b11111111, 0b10000111, 0b11111110, 0b00011001, 0b11101110, 0b01000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000011, 0b11110011, 0b11111111, 0b10000001, 0b11111111, 0b11000001, 0b11101110, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000000, 0b00000011, 0b11111111, 0b10001100, 0b01111111, 0b11110001, 0b11101110, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000011, 0b11110011, 0b11111111, 0b10001111, 0b00001111, 0b11111100, 0b01101110, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000000, 0b00000011, 0b11111111, 0b10001111, 0b11000011, 0b11111111, 0b00001110, 0b00000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000011, 0b11110011, 0b11111111, 0b10001111, 0b11001000, 0b11111111, 0b11000110, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000011, 0b11110011, 0b11111111, 0b10001111, 0b11001110, 0b00111111, 0b11110000, 0b11000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000001, 0b11110011, 0b11111111, 0b10001110, 0b00000000, 0b00001111, 0b11111100, 0b00000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b00000000, 0b11110011, 0b11111111, 0b10001001, 0b11111111, 0b11100011, 0b11111111, 0b00000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b10000000, 0b00010011, 0b11111111, 0b10000011, 0b11111111, 0b11111000, 0b11111100, 0b00000000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b11000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000011, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b11110000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b11111110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
};

osThreadId_t tid_Thread;                        // thread id
 
void Thread (void *argument);                   // thread function


uint8_t VFD_Dummy[30] = {0xFF};

void VFD_SPI_callback(uint32_t event)
{
    switch (event)
    {
    case ARM_SPI_EVENT_TRANSFER_COMPLETE:
        /* Success: Wakeup Thread */
        osThreadFlagsSet(tid_Thread,0x01);
        break;
    case ARM_SPI_EVENT_DATA_LOST:
        /*  Occurs in slave mode when data is requested/sent by master
            but send/receive/transfer operation has not been started
            and indicates that data is lost. Occurs also in master mode
            when driver cannot transfer data fast enough. */
        __BKPT(0);  /* Error: Call debugger or replace with custom error handling */
        break;
    case ARM_SPI_EVENT_MODE_FAULT:
        /*  Occurs in master mode when Slave Select is deactivated and
            indicates Master Mode Fault. */
        __BKPT(0);  /* Error: Call debugger or replace with custom error handling */
        break;
    }
}
 

int Init_Thread (void) {
 
  tid_Thread = osThreadNew(Thread, NULL, NULL);
  if (tid_Thread == NULL) {
    return(-1);
  }
 
  return(0);
}
 
void Thread (void *argument) {
    uint32_t flags;
    uint16_t Temp;
    uint8_t VFD_Grids [6] = {0,0,0,0,0,0};
    
    size_t row_cnt = 0;
    
    uint32_t RowTemp;
    
    
     ARM_DRIVER_SPI* SPIdrv = &Driver_SPI1;
 
#ifdef DEBUG
    ARM_DRIVER_VERSION   version;
    ARM_SPI_CAPABILITIES drv_capabilities;
 
    version = SPIdrv->GetVersion();
    if (version.api < 0x200) /* requires at minimum API version 2.00 or higher */
    {                        /* error handling                                 */
        return;
    }
 
    drv_capabilities = SPIdrv->GetCapabilities();
    if (drv_capabilities.event_mode_fault == 0)
    {                        /* error handling */
        return;
    }
#endif
 
    for(int i = 0; i < 30; i++)
    {
        VFD_Dummy[i] = 0xff;
    }
    /* Initialize the SPI driver */
    SPIdrv->Initialize(VFD_SPI_callback);
    /* Power up the SPI peripheral */
    SPIdrv->PowerControl(ARM_POWER_FULL);
    /* Configure the SPI to Master, 8-bit mode @10000 kBits/sec */
    SPIdrv->Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL1_CPHA1 | ARM_SPI_MSB_LSB | ARM_SPI_SS_MASTER_UNUSED | ARM_SPI_DATA_BITS(8), 2000000);
 

    
    for (size_t i = 0; i < 32; i++){        // Cycle for original frame's rows
        for (size_t j = 0; j < 15; j++){    // Cycle for original frame's columns
            RowTemp =(((uint32_t)image[j + 2]) << 16) | (((uint32_t)image[j + 1]) << 8) | (uint32_t)image[j];
            for (size_t k = 0; k < 24; k=k+6){// Cycle for individual bits
                VFD_RowData_ABC[row_cnt][0] = ((RowTemp & 0x01 << k) == (1 << k) )  ;
                
                //VFD_RowData_ABC[row_cnt]
                //VFD_RowData_DEF[row_cnt]
            }

        }
        
        { // Last column
            
        }
        
    }
    
    
    while (1) {
        
        VFD_Grids[0] = 0x03;
        //First Send 0th
        /* Transmit some data */
        SPIdrv->Send(VFD_Dummy, 24);
        /* Wait for completion */
        flags = osThreadFlagsWait(0x01,osFlagsWaitAny,osWaitForever);
        if (flags == osFlagsErrorTimeout) {
            __BKPT(0); /* Timeout error: Call debugger */
        }
        /* Transmit some data */
        SPIdrv->Send(VFD_Grids, 6);
        /* Wait for completion */
        flags = osThreadFlagsWait(0x01,osFlagsWaitAny,osWaitForever);
        if (flags == osFlagsErrorTimeout) {
            __BKPT(0); /* Timeout error: Call debugger */
        }
        for(size_t i = 0; i < 40; i++)
        {
            Temp = (((uint16_t)VFD_Grids[i/8 + 1]) << 8) | ((uint16_t)(VFD_Grids[i/8]));
            
            Temp = Temp << 1;
            VFD_Grids[i/8      ] = (uint8_t)  Temp;
            
            VFD_Grids[i/8 + 1] = (uint8_t) (Temp >> 8);
            
            //Cycle Send 1-40th
            /* Transmit some data */
            SPIdrv->Send(VFD_Dummy, 24);
            /* Wait for completion */
            flags = osThreadFlagsWait(0x01,osFlagsWaitAny,osWaitForever);
            if (flags == osFlagsErrorTimeout) {
                __BKPT(0); /* Timeout error: Call debugger */
            }
            /* Transmit some data */
            SPIdrv->Send(VFD_Grids, 6);
            /* Wait for completion */
            flags = osThreadFlagsWait(0x01,osFlagsWaitAny,osWaitForever);
            if (flags == osFlagsErrorTimeout) {
                __BKPT(0); /* Timeout error: Call debugger */
            }
        }
        
        VFD_Grids[5] = VFD_Grids[5] << 1;
        // 41th Send
        /* Transmit some data */
        SPIdrv->Send(VFD_Dummy, 24);
        /* Wait for completion */
        flags = osThreadFlagsWait(0x01,osFlagsWaitAny,osWaitForever);
        if (flags == osFlagsErrorTimeout) {
            __BKPT(0); /* Timeout error: Call debugger */
        }
        /* Transmit some data */
        SPIdrv->Send(VFD_Grids, 6);
        /* Wait for completion */
        flags = osThreadFlagsWait(0x01,osFlagsWaitAny,osWaitForever);
        if (flags == osFlagsErrorTimeout) {
            __BKPT(0); /* Timeout error: Call debugger */
        }
        VFD_Grids[5] = 0x0C;
        // 42th Send
        /* Transmit some data */
        SPIdrv->Send(VFD_Dummy, 24);
        /* Wait for completion */
        flags = osThreadFlagsWait(0x01,osFlagsWaitAny,osWaitForever);
        if (flags == osFlagsErrorTimeout) {
            __BKPT(0); /* Timeout error: Call debugger */
        }
        /* Transmit some data */
        SPIdrv->Send(VFD_Grids, 6);
        /* Wait for completion */
        flags = osThreadFlagsWait(0x01,osFlagsWaitAny,osWaitForever);
        if (flags == osFlagsErrorTimeout) {
            __BKPT(0); /* Timeout error: Call debugger */
        }
        VFD_Grids[5] = 0x00;
        
        
        osThreadYield();                            // suspend thread
    }
}



