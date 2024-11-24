#include "RTE_Components.h"             // Component selection
#include CMSIS_device_header
#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "appSimplePic.h"                     // Application header file

#include "main.h"

#include "Driver_SPI.h"
/* SPI Driver */
extern ARM_DRIVER_SPI Driver_SPI1;
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
uint8_t VFD_RowData_DEF[24] [24];
uint8_t VFD_RowData_ABC[24] [24];
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
 
    
    /* Initialize the SPI driver */
    SPIdrv->Initialize(VFD_SPI_callback);
    /* Power up the SPI peripheral */
    SPIdrv->PowerControl(ARM_POWER_FULL);
    /* Configure the SPI to Master, 8-bit mode @10000 kBits/sec */
    SPIdrv->Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL1_CPHA1 | ARM_SPI_LSB_MSB | ARM_SPI_SS_MASTER_UNUSED | ARM_SPI_DATA_BITS(8), 2000000);
    

    
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            VFD_RowData_DEF[i][j] = 0x00;
            VFD_RowData_ABC[i][j] = 0x00;
        }
    }
    
//    for (size_t i = 0; i < 32; i++){        // Cycle for original frame's rows
//        for (size_t j = 0; j < 15; j++){    // Cycle for original frame's columns
            //RowTemp =(((uint32_t)image[j + 2]) << 16) | (((uint32_t)image[j + 1]) << 8) | (uint32_t)image[j];
            //for (size_t k = 0; k < 24; k=k+6){// Cycle for individual bits
                //VFD_RowData_ABC[row_cnt][0] = ((RowTemp & 0x01 << k) == (1 << k) )  ;
                
                
                // 0B'abcdefab 0B'cdefabcd 0B'efabcdef - 4 rows of=== abcdef=abcdef=abcdef=abcdef ===
                // Every row of bitmap converted to 4 rows of gridmap 5 times. 
                // 1) In first cycle we move through all bitmap rows
                // 2) In second cycle we move through all row's bytes taking 3 at once (5 times, last is special AB grid)
                // 
                // first byte of first row bitmap
                VFD_RowData_ABC[0][0]  = ((image[0] & 0x80) != 0x80) << 0; // a00
                VFD_RowData_ABC[0][0] |= ((image[0] & 0x40) != 0x40) << 2; // b00
                VFD_RowData_ABC[0][0] |= ((image[0] & 0x20) != 0x20) << 4; // c00
                VFD_RowData_DEF[0][0]  = ((image[0] & 0x10) != 0x10) << 5; // d00
                VFD_RowData_DEF[0][0] |= ((image[0] & 0x08) != 0x08) << 3; // e00
                VFD_RowData_DEF[0][0] |= ((image[0] & 0x04) != 0x04) << 1; // f00
                
                VFD_RowData_ABC[1][0]  = ((image[0] & 0x02) != 0x02) << 0; // a01
                VFD_RowData_ABC[1][0] |= ((image[0] & 0x01) != 0x01) << 2; // b01
//                //Second byte
//                VFD_RowData_ABC[1][0] |= ((image[1] & 0x80) != 0x80) << 4; // c01
//                VFD_RowData_DEF[1][0]  = ((image[1] & 0x40) != 0x40) << 5; // d01
//                VFD_RowData_DEF[1][0] |= ((image[1] & 0x20) != 0x20) << 3; // e01
//                VFD_RowData_DEF[1][0] |= ((image[1] & 0x10) != 0x10) << 1; // f01
//                
//                VFD_RowData_ABC[2][0]  = ((image[1] & 0x08) != 0x08) << 0; // a02
//                VFD_RowData_ABC[2][0] |= ((image[1] & 0x04) != 0x04) << 2; // b02
//                VFD_RowData_ABC[2][0] |= ((image[1] & 0x02) != 0x02) << 4; // c02
//                VFD_RowData_DEF[2][0]  = ((image[1] & 0x01) != 0x01) << 5; // d02
//                //third byte
//                VFD_RowData_DEF[2][0] |= ((image[2] & 0x80) != 0x80) << 3; // e02
//                VFD_RowData_DEF[2][0] |= ((image[2] & 0x40) != 0x40) << 1; // f02
//                
//                VFD_RowData_ABC[3][0]  = ((image[2] & 0x20) != 0x20) << 0; // a03
//                VFD_RowData_ABC[3][0] |= ((image[2] & 0x10) != 0x10) << 2; // b03
//                VFD_RowData_ABC[3][0] |= ((image[2] & 0x08) != 0x08) << 4; // c03
//                VFD_RowData_DEF[3][0]  = ((image[2] & 0x04) != 0x04) << 5; // d03
//                VFD_RowData_DEF[3][0] |= ((image[2] & 0x02) != 0x02) << 3; // e03
//                VFD_RowData_DEF[3][0] |= ((image[2] & 0x01) != 0x01) << 1; // f03
                
                //first byte of second row of bitmap
                VFD_RowData_ABC[0][0] |= ((image[0 + 16] & 0x80) != 0x80) << 6; // a10
                VFD_RowData_ABC[0][1]  = ((image[0 + 16] & 0x40) != 0x40) << 0; // b10
                VFD_RowData_ABC[0][1] |= ((image[0 + 16] & 0x20) != 0x20) << 2; // c10
                
                VFD_RowData_DEF[0][1]  = ((image[0 + 16] & 0x10) != 0x10) << 3; // d10
                VFD_RowData_DEF[0][1] |= ((image[0 + 16] & 0x08) != 0x08) << 1; // e10
                VFD_RowData_DEF[0][0] |= ((image[0 + 16] & 0x04) != 0x04) << 7; // f10
                
                //VFD_RowData_ABC[1][1]  = ((image[0 + 16] & 0x02) != 0x02) << 0; // a11
                //VFD_RowData_ABC[1][1] |= ((image[0 + 16] & 0x01) != 0x01) << 2; // b11
                
                //first byte of third row of bitmap
                VFD_RowData_ABC[0][0] |= ((image[0 + 32] & 0x80) != 0x80) << 6; // a10
                VFD_RowData_ABC[0][1]  = ((image[0 + 32] & 0x40) != 0x40) << 0; // b10
                VFD_RowData_ABC[0][1] |= ((image[0 + 32] & 0x20) != 0x20) << 2; // c10
                
                VFD_RowData_DEF[0][1]  = ((image[0 + 32] & 0x10) != 0x10) << 3; // d10
                VFD_RowData_DEF[0][1] |= ((image[0 + 32] & 0x08) != 0x08) << 1; // e10
                VFD_RowData_DEF[0][0] |= ((image[0 + 32] & 0x04) != 0x04) << 7; // f10
                
                //VFD_RowData_ABC[1][1]  = ((image[0 + 16] & 0x02) != 0x02) << 0; // a11
                //VFD_RowData_ABC[1][1] |= ((image[0 + 16] & 0x01) != 0x01) << 2; // b11
//            }

 //       }
        
        { // Last column
            
        }
        
//    }
    
    HAL_GPIO_WritePin(VFD_EF_GPIO_Port,VFD_EF_Pin, GPIO_PIN_SET);
    
    osDelay(5);
    
    HAL_GPIO_WritePin(VFD_HV_GPIO_Port,VFD_HV_Pin, GPIO_PIN_SET);
    while (1) {
        
        VFD_Grids[0] = 0x03;
        //First Send 0th
        
        HAL_GPIO_WritePin(VFD_BLK_GPIO_Port,VFD_BLK_Pin, GPIO_PIN_SET);
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        HAL_GPIO_WritePin(VFD_LAT_GPIO_Port,VFD_LAT_Pin, GPIO_PIN_SET);
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        HAL_GPIO_WritePin(VFD_LAT_GPIO_Port,VFD_LAT_Pin, GPIO_PIN_RESET);
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        HAL_GPIO_WritePin(VFD_BLK_GPIO_Port,VFD_BLK_Pin, GPIO_PIN_RESET);
        /* Transmit some data */
        SPIdrv->Send(VFD_RowData_ABC[0], 24);
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
        for(size_t i = 1; i < 40; i++)
        {
            Temp = (((uint16_t)VFD_Grids[i/8 + 1]) << 8) | ((uint16_t)(VFD_Grids[i/8]));
            
            Temp = Temp << 1;
            VFD_Grids[i/8      ] = (uint8_t)  Temp;
            
            VFD_Grids[i/8 + 1] = (uint8_t) (Temp >> 8);
            
            //Cycle Send 1-40th
            HAL_GPIO_WritePin(VFD_BLK_GPIO_Port,VFD_BLK_Pin, GPIO_PIN_SET);
            __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
            HAL_GPIO_WritePin(VFD_LAT_GPIO_Port,VFD_LAT_Pin, GPIO_PIN_SET);
            __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
            HAL_GPIO_WritePin(VFD_LAT_GPIO_Port,VFD_LAT_Pin, GPIO_PIN_RESET);
            __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
            HAL_GPIO_WritePin(VFD_BLK_GPIO_Port,VFD_BLK_Pin, GPIO_PIN_RESET);
            /* Transmit some data */
            if(i & (size_t)0x01)
            {
                SPIdrv->Send(VFD_RowData_DEF[i/2], 24);
            }
            else{
                SPIdrv->Send(VFD_RowData_ABC[i/2], 24);
            }
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
        HAL_GPIO_WritePin(VFD_BLK_GPIO_Port,VFD_BLK_Pin, GPIO_PIN_SET);
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        HAL_GPIO_WritePin(VFD_LAT_GPIO_Port,VFD_LAT_Pin, GPIO_PIN_SET);
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        HAL_GPIO_WritePin(VFD_LAT_GPIO_Port,VFD_LAT_Pin, GPIO_PIN_RESET);
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        HAL_GPIO_WritePin(VFD_BLK_GPIO_Port,VFD_BLK_Pin, GPIO_PIN_RESET);
        /* Transmit some data */
        SPIdrv->Send(VFD_RowData_DEF[20], 24);
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
        HAL_GPIO_WritePin(VFD_BLK_GPIO_Port,VFD_BLK_Pin, GPIO_PIN_SET);
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        HAL_GPIO_WritePin(VFD_LAT_GPIO_Port,VFD_LAT_Pin, GPIO_PIN_SET);
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        HAL_GPIO_WritePin(VFD_LAT_GPIO_Port,VFD_LAT_Pin, GPIO_PIN_RESET);
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        HAL_GPIO_WritePin(VFD_BLK_GPIO_Port,VFD_BLK_Pin, GPIO_PIN_RESET);
        /* Transmit some data */
        SPIdrv->Send(VFD_RowData_ABC[20], 24);
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



