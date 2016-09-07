/**
  ******************************************************************************
  * @file    STM32F4xx_IAP/inc/flash_if.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    10-October-2011
  * @brief   This file provides all the headers of the flash_if functions.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_H
#define __FLASH_IF_H

typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_PGS,
  FLASH_PGP,
  FLASH_PGA,
  FLASH_WRP,
  FLASH_PROGRAM,
  FLASH_OPERATION,
  FLASH_COMPLETE
}FLASH_Status;

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
#define VoltageRange_1        ((uint8_t)0x00)  /*!< Device operating range: 1.8V to 2.1V */
#define VoltageRange_2        ((uint8_t)0x01)  /*!<Device operating range: 2.1V to 2.7V */
#define VoltageRange_3        ((uint8_t)0x02)  /*!<Device operating range: 2.7V to 3.6V */
#define VoltageRange_4        ((uint8_t)0x03)  /*!<Device operating range: 2.7V to 3.6V + External Vpp */

#define OB_WRP_Sector_0       ((uint32_t)0x00000001) /*!< Write protection of Sector0 */
#define OB_WRP_Sector_1       ((uint32_t)0x00000002) /*!< Write protection of Sector1 */
#define OB_WRP_Sector_2       ((uint32_t)0x00000004) /*!< Write protection of Sector2 */
#define OB_WRP_Sector_3       ((uint32_t)0x00000008) /*!< Write protection of Sector3 */
#define OB_WRP_Sector_4       ((uint32_t)0x00000010) /*!< Write protection of Sector4 */
#define OB_WRP_Sector_5       ((uint32_t)0x00000020) /*!< Write protection of Sector5 */
#define OB_WRP_Sector_6       ((uint32_t)0x00000040) /*!< Write protection of Sector6 */
#define OB_WRP_Sector_7       ((uint32_t)0x00000080) /*!< Write protection of Sector7 */
#define OB_WRP_Sector_8       ((uint32_t)0x00000100) /*!< Write protection of Sector8 */
#define OB_WRP_Sector_9       ((uint32_t)0x00000200) /*!< Write protection of Sector9 */
#define OB_WRP_Sector_10      ((uint32_t)0x00000400) /*!< Write protection of Sector10 */
#define OB_WRP_Sector_11      ((uint32_t)0x00000800) /*!< Write protection of Sector11 */
#define OB_WRP_Sector_All     ((uint32_t)0x00000FFF) /*!< Write protection of all Sectors */

#define FLASH_Sector_0     ((uint16_t)0x0000) /*!< Sector Number 0 */
#define FLASH_Sector_1     ((uint16_t)0x0008) /*!< Sector Number 1 */
#define FLASH_Sector_2     ((uint16_t)0x0010) /*!< Sector Number 2 */
#define FLASH_Sector_3     ((uint16_t)0x0018) /*!< Sector Number 3 */
#define FLASH_Sector_4     ((uint16_t)0x0020) /*!< Sector Number 4 */
#define FLASH_Sector_5     ((uint16_t)0x0028) /*!< Sector Number 5 */
#define FLASH_Sector_6     ((uint16_t)0x0030) /*!< Sector Number 6 */
#define FLASH_Sector_7     ((uint16_t)0x0038) /*!< Sector Number 7 */
#define FLASH_Sector_8     ((uint16_t)0x0040) /*!< Sector Number 8 */
#define FLASH_Sector_9     ((uint16_t)0x0048) /*!< Sector Number 9 */
#define FLASH_Sector_10    ((uint16_t)0x0050) /*!< Sector Number 10 */
#define FLASH_Sector_11    ((uint16_t)0x0058) /*!< Sector Number 11 */

/* Exported constants --------------------------------------------------------*/

/* Base address of the internal SRAM sectors */
#define ADDR_SDRAM_SECTOR_0     ((uint32_t)0x20000000) /* Base @ of Sector 0, 16 Kbyte */

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbyte */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbyte */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbyte */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbyte */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbyte */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbyte */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbyte */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbyte */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbyte */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbyte */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbyte */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbyte */

/* Define the address from where user application will be loaded.
   Note: the 1st sector 0x08000000-0x08003FFF is reserved for the IAP code */
#define ROM_BASE_ADDRESS        ADDR_FLASH_SECTOR_0
#define BOOT_ROM_START_ADDRESS  ADDR_FLASH_SECTOR_0
#define BOOT_ROM_STOP_ADDRESS   ADDR_FLASH_SECTOR_1
#define BOOT_RAM_START_ADDRESS  ADDR_FLASH_SECTOR_2
#define BOOT_RAM_STOP_ADDRESS   ADDR_FLASH_SECTOR_3
#define MAIN_ROM_START_ADDRESS  ADDR_FLASH_SECTOR_4
#define MAIN_ROM_STOP_ADDRESS   ADDR_FLASH_SECTOR_5

/* End of the Flash address */
#define USER_FLASH_END_ADDRESS        0x0801FFFF
/* Define the user application size */
#define APP_FLASH_SIZE         (USER_FLASH_END_ADDRESS - MAIN_ROM_START_ADDRESS + 1)
#define DOWNLOAD_FLASH_SIZE    (USER_FLASH_END_ADDRESS - ROM_BASE_ADDRESS + 1)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void FLASH_If_Init(void);
uint32_t FLASH_If_Erase(uint32_t StartSector, uint32_t StopSector);
uint32_t FLASH_If_Write(__IO uint32_t* FlashAddress, uint32_t* Data, uint32_t DataLength);
uint16_t FLASH_If_GetWriteProtectionStatus(void);
uint32_t FLASH_If_DisableWriteProtection(void);

#endif  /* __FLASH_IF_H */

/*******************(C)COPYRIGHT 2011 STMicroelectronics *****END OF FILE******/
