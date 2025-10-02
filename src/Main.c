/********************************** (C) COPYRIGHT *******************************
 * File Name          : Main.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2020/08/06
 * Description        : SPI0演示 Master/Slave 模式数据收发
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "CH57x_common.h"

#include "TFTh/TFT_CAD.h"  // 包含绘图函数和 IO 函数
#include "TFTh/TFT_init.h"
#include "TFTh/TFT_text.h"
#include "TFTh/TFT_io.h"  // 包含RGB转换函数

TFT_HandleTypeDef htft1;  // 第一个TFT屏幕句柄
SPI_HandleTypeDef SPI0;   // 第一个TFT屏幕句柄
#define TFT_CS_GPIO_Port 0
#define TFT_CS_Pin GPIO_Pin_12
#define TFT_DC_GPIO_Port 0
#define TFT_DC_Pin GPIO_Pin_10
#define TFT_RES_GPIO_Port 0
#define TFT_RES_Pin GPIO_Pin_11
#define TFT_BLK_GPIO_Port 1
#define TFT_BLK_Pin GPIO_Pin_22

/**
 * @fn      mai                                                                                                                                                                                                        n
 *
 * @brief   主函数
 *
 * @return  none
 */
int main() {
    SetSysClock (CLK_SOURCE_PLL_60MHz);

    /* 配置串口调试 */
    GPIOA_SetBits (GPIO_Pin_9);
    GPIOA_ModeCfg (GPIO_Pin_8, GPIO_ModeIN_PU);
    GPIOA_ModeCfg (GPIO_Pin_9, GPIO_ModeOut_PP_5mA);
    UART1_DefInit();
    PRINT ("Start @ChipID=%02X\n", R8_CHIP_ID);
    PRINT ("1\n");
    GPIOA_ModeCfg (GPIO_Pin_12, GPIO_ModeOut_PP_5mA);
    GPIOA_ModeCfg (GPIO_Pin_11, GPIO_ModeOut_PP_5mA);
    GPIOA_ModeCfg (GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
    GPIOB_ModeCfg (GPIO_Pin_22, GPIO_ModeOut_PP_5mA);
    PRINT ("2\n");
    TFT_Init_Instance (&htft1, &SPI0, TFT_CS_GPIO_Port, TFT_CS_Pin);
    PRINT ("2\n");
    TFT_Config_Pins (&htft1, TFT_DC_GPIO_Port, TFT_DC_Pin, TFT_RES_GPIO_Port, TFT_RES_Pin, TFT_BLK_GPIO_Port, TFT_BLK_Pin);  // 必须手动设置引脚
    TFT_Config_Display (&htft1, 0, 0, 0);                                                                                    // 设置方向、X/Y偏移
    TFT_Init_ST7789v3 (&htft1);                                                                                               // ST7789屏幕初始化
    PRINT ("3\n");
    while (1) {
        TFT_Fill_Area (&htft1, 0, 0, 240, 320, BLACK);
             mDelaymS (100);
        TFT_Fill_Area (&htft1, 0, 0, 240, 320, GREEN);
        // PRINT ("Start @ChipID=%02X\n", R8_CHIP_ID);
        PRINT ("while\n");
        mDelaymS (100);
    }
}
