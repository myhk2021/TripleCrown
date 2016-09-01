/**
  ******************************************************************************
  * @file    STM32F4xx_IAP/src/menu.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    10-October-2011
  * @brief   This file provides the software which contains the main menu routine.
  *          The main menu gives the options of:
  *             - downloading a new binary file, 
  *             - uploading internal flash memory,
  *             - executing the binary file already loaded 
  *             - disabling the write protection of the Flash sectors where the 
  *               user loads his binary file.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/** @addtogroup STM32F4xx_IAP
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "common.h"
#include "flash_if.h"
#include "menu.h"
#include "ymodem.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
pFunction Jump_To_Application;
uint32_t JumpAddress;
//__IO uint32_t FlashProtection = 0;
uint8_t tab_1024[1024] =
  {
    0
  };
uint8_t FileName[FILE_NAME_LENGTH];

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);
void SerialDownload(void);
void SerialUpload(void);
void Main_Main(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Download a file via serial port
  * @param  None
  * @retval None
  */
void SerialDownload(void)
{
  uint8_t Number[10] = "          ";
  int32_t Size = 0;

  SerialPutString("Waiting for the file to be sent ... (press 'a' to abort)\n\r");
  Size = Ymodem_Receive(&tab_1024[0]);
  if (Size > 0)
  {
    SerialPutString("\n\n\r Programming Completed Successfully!\n\r--------------------------------\r\n Name: ");
    SerialPutString(FileName);
    Int2Str(Number, Size);
    SerialPutString("\n\r Size: ");
    SerialPutString(Number);
    SerialPutString(" Bytes\r\n");
    SerialPutString("-------------------\n");
  }
  else if (Size == -1)
  {
    SerialPutString("\n\n\rThe image size is higher than the allowed space memory!\n\r");
  }
  else if (Size == -2)
  {
    SerialPutString("\n\n\rVerification failed!\n\r");
  }
  else if (Size == -3)
  {
    SerialPutString("\r\n\nAborted by user.\n\r");
  }
  else
  {
    SerialPutString("\n\rFailed to receive the file!\n\r");
  }
}

/**
  * @brief  Upload a file via serial port.
  * @param  None
  * @retval None
  */
void SerialUpload(void)
{
  uint8_t status = 0 ; 

  SerialPutString("\n\n\rSelect Receive File\n\r");

  if (GetKey() == CRC16)
  {
    /* Transmit the flash image through ymodem protocol */
    status = Ymodem_Transmit((uint8_t*)ROM_BASE_ADDRESS, (const uint8_t*)"UploadedFlashImage.bin", DOWNLOAD_FLASH_SIZE);

    if (status != 0) 
    {
      SerialPutString("\n\rError Occurred while Transmitting File\n\r");
    }
    else
    {
      SerialPutString("\n\rFile uploaded successfully \n\r");
    }
  }
}

void Jump_To_Main_APP(void)
{
  SerialPutString("\r\n==Entering Jump_To_Main_APP==\r\n");

  /* Test if user code is programmed starting from address "MAIN_ROM_START_ADDRESS" */
  if (((*(__IO uint32_t*)MAIN_ROM_START_ADDRESS) & 0x2FFE0000 ) == 0x20000000)
  { 
    /* Jump to user application */
    JumpAddress = *(__IO uint32_t*) (MAIN_ROM_START_ADDRESS + 4);
    Jump_To_Application = (pFunction) JumpAddress;
    /* Initialize user application's Stack Pointer */
    __set_MSP(*(__IO uint32_t*) MAIN_ROM_START_ADDRESS);
    Jump_To_Application();
  }
}

void Jump_To_BootLoader(void)
{
  SerialPutString("\r\n==Entering Jump_To_BootLoader==\r\n");

  // If main FW present copy it to SDRAM
  memcpy((void *)ADDR_SDRAM_SECTOR_0, (void *)ADDR_FLASH_SECTOR_2, 16*1024);
  /* Jump to user application */
  JumpAddress = *(__IO uint32_t*) (ADDR_SDRAM_SECTOR_0 + 4);
  Jump_To_Application = (pFunction) JumpAddress;
  /* Initialize user application's Stack Pointer */
//  __set_MSP(*(__IO uint32_t*) ADDR_SDRAM_SECTOR_0);
  //patch, for switch from PSP to MSP, if FreeRTOS running in PSP
  __set_PSP(*(__IO uint32_t*) ADDR_SDRAM_SECTOR_0);
  __set_CONTROL(0x0000);
  Jump_To_Application();
}

/**
  * @brief  Display the Main Menu on HyperTerminal
  * @param  None
  * @retval None
  */
void BOOT_RAM(void)
{
  uint8_t key = 0;

  SerialPutString("\r\n======================================================================");
  SerialPutString("\r\n=            (C) COPYRIGHT 2016 CompleteGenomics Inc.                =");
  SerialPutString("\r\n=                                                                    =");
  SerialPutString("\r\n=  STM32F407 In-Application Programming Application  (Version 1.0.0) =");
  SerialPutString("\r\n=                                                                    =");
  SerialPutString("\r\n=                                   Modified by Michael Yeh          =");
  SerialPutString("\r\n======================================================================");
  SerialPutString("\r\n\r\n");

  /* Test if any sector of Flash memory where user application will be loaded is write protected */
//  if (FLASH_If_GetWriteProtectionStatus() == 0)   
//  {
//    FlashProtection = 1;
//  }
//  else
//  {
//    FlashProtection = 0;
//  }

  while (1)
  {
    SerialPutString("\r\n================== Main Menu ============================\r\n\n");
    SerialPutString("  Download Image To the STM32F4xx Internal Flash ------- 1\r\n\n");
    SerialPutString("  Upload Image From the STM32F4xx Internal Flash ------- 2\r\n\n");
    SerialPutString("  Execute The New Program ------------------------------ 3\r\n\n");

//    if(FlashProtection != 0)
//    {
//      SerialPutString("  Disable the write protection ------------------------- 4\r\n\n");
//    }

    SerialPutString("==========================================================\r\n\n");

    /* Insert delay */
    Delay(100);
          
    /* Receive key */
    key = GetKey();

    if (key == 0x31)
    {
      /* Download user application in the Flash */
      SerialDownload();
    }
    else if (key == 0x32)
    {
      /* Upload user application from the Flash */
      SerialUpload();
    }
    else if (key == 0x33) /* execute the new program */
    {
#if 1
      Jump_To_Main_APP();
#else        
      JumpAddress = *(__IO uint32_t*) (MAIN_ROM_START_ADDRESS + 4);
      /* Jump to user application */
      Jump_To_Application = (pFunction) JumpAddress;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) MAIN_ROM_START_ADDRESS);
      Jump_To_Application();
#endif        
    }
//    else if ((key == 0x34) && (FlashProtection == 1))
//    {
//      /* Disable the write protection */
//      switch (FLASH_If_DisableWriteProtection())
//      {
//        case 1:
//        {
//          SerialPutString("Write Protection disabled...\r\n");
//          FlashProtection = 0;
//          break;
//        }
//        case 2:
//        {
//          SerialPutString("Error: Flash write unprotection failed...\r\n");
//          break;
//        }
//        default:
//        {
//        }
//      }
//    }
    else
    {
//      if (FlashProtection == 0)
//      {
//        SerialPutString("Invalid Number ! ==> The number should be either 1, 2 or 3\r");
//      }
//      else
//      {
//        SerialPutString("Invalid Number ! ==> The number should be either 1, 2, 3 or 4\r");
//      }
    }
  }
}

void BOOT_ROM(void)
{
  SerialPutString("\r\n======================================================================");
  SerialPutString("\r\n=            (C) COPYRIGHT 2016 CompleteGenomics Inc.                =");
  SerialPutString("\r\n=                                                                    =");
  SerialPutString("\r\n=            STM32F407 BOOT Application  (Version 1.0.0)             =");
  SerialPutString("\r\n=                                                                    =");
  SerialPutString("\r\n=                                   Modified by Michael Yeh          =");
  SerialPutString("\r\n======================================================================");
  SerialPutString("\r\n\r\n");
  Jump_To_Main_APP();
}

void Main_DBG(void)
{
  SerialPutString("\r\n======================================================================");
  SerialPutString("\r\n=            (C) COPYRIGHT 2016 CompleteGenomics Inc.                =");
  SerialPutString("\r\n=                                                                    =");
  SerialPutString("\r\n=            STM32F407 DBG Application  (Version 1.0.0)              =");
  SerialPutString("\r\n=                                                                    =");
  SerialPutString("\r\n=                                   Modified by Michael Yeh          =");
  SerialPutString("\r\n======================================================================");
  SerialPutString("\r\n\r\n");
  Main_Main();
}

void Main_ROM(void)
{
  SerialPutString("\r\n======================================================================");
  SerialPutString("\r\n=            (C) COPYRIGHT 2016 CompleteGenomics Inc.                =");
  SerialPutString("\r\n=                                                                    =");
  SerialPutString("\r\n=            STM32F407 ROM Application  (Version 1.0.0)              =");
  SerialPutString("\r\n=                                                                    =");
  SerialPutString("\r\n=                                   Modified by Michael Yeh          =");
  SerialPutString("\r\n======================================================================");
  SerialPutString("\r\n\r\n");
  Main_Main();
}

void Main_Main(void)
{
  Jump_To_BootLoader();
}

/**
  * @}
  */

/*******************(C)COPYRIGHT 2011 STMicroelectronics *****END OF FILE******/
