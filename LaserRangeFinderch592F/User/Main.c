/**
 ******************************************************************************
 * @file    Main.c
 * @author  雪豹
 * @version V1.0.0
 * @date    2025-10-3
 * @brief   激光测距仪主函数
 ******************************************************************************
 * @attention
 */

#include "CH59x_common.h"
#include <stdio.h> // 引入 snprintf

#include "M01LaserRangeFinder.h"

// 包含TFT驱动所需的头文件
#include "TFTh/TFT_CAD.h" // 包含绘图函数和 IO 函数
#include "TFTh/TFT_init.h"
#include "TFTh/TFT_text.h"
#include "TFTh/TFT_io.h" // 包含RGB转换函数

/* 按键相关定义 */
#define HOME_KEY GPIO_Pin_15    // 主页按键PA15
#define SET_KEY GPIO_Pin_10     // 设置按键PB10
#define HISTORY_KEY GPIO_Pin_11 // 历史按键PB11
#define UP_KEY GPIO_Pin_12      // 上按键PA12
#define DOWN_KEY GPIO_Pin_11    // 下按键PA11
#define SWITCH_KEY GPIO_Pin_13  // 切换按键PB13
#define MEASURE_KEY GPIO_Pin_10 // 测量按键PA10
#define SAVE_KEY GPIO_Pin_12    // 保存按键PB12

/* TFT屏幕相关定义 */
// TFT屏幕句柄和SPI句柄定义
TFT_HandleTypeDef htft1; // 第一个TFT屏幕把手
SPI_HandleTypeDef SPI0;  // 第一个TFT屏幕把手
// TFT屏幕引脚定义，根据实际连接修改
#define TFT_CS_GPIO_Port 0 // 0是GPIOA，1是GPIOB
#define TFT_CS_Pin GPIO_Pin_4
#define TFT_DC_GPIO_Port 0
#define TFT_DC_Pin GPIO_Pin_5
#define TFT_RES_GPIO_Port 1
#define TFT_RES_Pin GPIO_Pin_23
#define TFT_BLK_GPIO_Port 1
#define TFT_BLK_Pin GPIO_Pin_22
// SPI0引脚定义在TFTio.c文件中的SPI0_MasterDefInit函数之前。CH573F只有一个硬件SPI
// 屏幕分辨率定义，根据实际屏幕修改
#define HEIGHT 320
#define WIDTH 240

/**
 * @fn     main
 * @brief   主函数
 * @return  none
 */
int main()
{
    SetSysClock(CLK_SOURCE_PLL_60MHz);

    /* 配置串口1调试 */
    GPIOA_SetBits(GPIO_Pin_9);
    GPIOA_ModeCfg(GPIO_Pin_8, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(GPIO_Pin_9, GPIO_ModeOut_PP_5mA);
    UART1_DefInit();
    PRINT("Start @ChipID=%02X\n", R8_CHIP_ID);

    /* 配置串口0与激光模块通讯 */
    uint8_t TxBuff[] = "This is a tx exam\r\n";
    uint8_t RxBuff[100];
    GPIOB_SetBits(GPIO_Pin_7);
    GPIOB_ModeCfg(GPIO_Pin_4, GPIO_ModeIN_PU);
    GPIOB_ModeCfg(GPIO_Pin_7, GPIO_ModeOut_PP_5mA);
    UART0_DefInit();
    UART0_BaudRateCfg(9600);

    /* 配置屏幕引脚，沁恒的单片机GPIOA和GPIOB操作函数是分开的。必须设置不然屏幕无法显示 */
    GPIOA_ModeCfg(TFT_CS_Pin, GPIO_ModeOut_PP_5mA);
    GPIOA_ModeCfg(TFT_RES_Pin, GPIO_ModeOut_PP_5mA);
    GPIOA_ModeCfg(TFT_DC_Pin, GPIO_ModeOut_PP_5mA);
    GPIOB_ModeCfg(TFT_BLK_Pin, GPIO_ModeOut_PP_5mA);
    /* 屏幕设置 */
    TFT_Init_Instance(&htft1, &SPI0, TFT_CS_GPIO_Port, TFT_CS_Pin);
    TFT_Config_Pins(&htft1, TFT_DC_GPIO_Port, TFT_DC_Pin, TFT_RES_GPIO_Port, TFT_RES_Pin, TFT_BLK_GPIO_Port, TFT_BLK_Pin); // 必须手动设置引脚
    TFT_Config_Display(&htft1, 2, 0, 0);                                                                                   // 设置方向、X/Y偏移

    TFT_Init_ST7789v3(&htft1);                         // ST7789v3屏幕初始化,右键进入tft_init.c查看更多屏幕的初始化函数
    TFT_Fill_Area(&htft1, 0, 0, WIDTH, HEIGHT, BLACK); // 全屏黑色填充
    TFT_Show_String(&htft1, 20, 20, "now ST7789v3", WHITE, BLACK, 16, 0);

    /* 按键中断配置 */
    // 配置GPIOA中断
    GPIOA_ModeCfg(HOME_KEY, GPIO_ModeIN_PU);         // 上拉输入
    GPIOA_ITModeCfg(HOME_KEY, GPIO_ITMode_FallEdge); // 下降沿触发
    GPIOA_ModeCfg(UP_KEY, GPIO_ModeIN_PU);           // 上拉输入
    GPIOA_ITModeCfg(UP_KEY, GPIO_ITMode_FallEdge);   // 下降沿触发
     GPIOA_ModeCfg(MEASURE_KEY, GPIO_ModeIN_PU);           // 上拉输入
    GPIOA_ITModeCfg(MEASURE_KEY, GPIO_ITMode_FallEdge);   // 下降沿触发
    PFIC_EnableIRQ(GPIO_A_IRQn);                     // 开启GPIOA中断

    // 配置GPIOB中断
    GPIOB_ModeCfg(SET_KEY, GPIO_ModeIN_PU);             // 上拉输入
    GPIOB_ITModeCfg(SET_KEY, GPIO_ITMode_FallEdge);     // 下降沿触发
    GPIOB_ModeCfg(HISTORY_KEY, GPIO_ModeIN_PU);         // 上拉输入
    GPIOB_ITModeCfg(HISTORY_KEY, GPIO_ITMode_FallEdge); // 下降沿触发

    PFIC_EnableIRQ(GPIO_B_IRQn); // 开启GPIOB中断

    PRINT("可以按下按键了\n");

    while (1) // 循环
    {
        // M01LRF_SendEnableCommand();
        DelayMs(2000);
        uint8_t dist_buf[64] = {0};
        uint8_t dist_buf2[64] = {0};
        uint16_t len = 13;
        // M01LRF_SendEnableCommand();
        // DelayMs(2000);
        // M01LRF_SendDisableCommand();
        // UART0_RecvString(dist_buf2);
        // M01LRF_StartFastMeasurement(dist_buf, sizeof(dist_buf));

        // if (len > 0)
        // {
        //     PRINT("Distance raw: ");
        //     for (uint16_t i = 0; i < len; i++)
        //     {
        //         PRINT("%02X ", dist_buf[i]);
        //     }
        //     PRINT("\n");
        // }
    }
}

// // 设置外部中断相关函数属性，指定声明相关特征
// __attribute__((interrupt("WCH-Interrupt-fast")))
// __attribute__((section(".highcode")))
// /**
//  * @brief GPIOA端口的中断处理函数
//  * @note 记得清除中断标志位。锐刻5 RISC-V芯片对应的中断函数名在Startup\startup_CH573.S文件里查看
//  */
// void
// GPIOA_IRQHandler(void)
// {
//     if (GPIOA_ReadITFlagBit(GPIO_Pin_4))
//     {
//         PRINT("GPIOA \n");
//         // DelayMs (500); // 不建议在中断中长时间延时
//         GPIOA_ClearITFlagBit(GPIO_Pin_4); // 清除中断标志位
//     }
// }

// 设置外部中断相关函数属性，指定声明相关特征
__INTERRUPT
__HIGH_CODE

/**
 * @brief GPIOB端口的中断处理函数
 * @note 记得清除中断标志位。锐刻5 RISC-V芯片对应的中断函数名在Startup\startup_CH573.S文件里查看
 */
void GPIOA_IRQHandler(void)
{
    if (GPIOA_ReadITFlagBit(MEASURE_KEY))
    {
        PRINT("key按下\n");
        TFT_Fill_Area(&htft1, 0, 0, WIDTH, HEIGHT, BLACK);
        uint8_t dist_buf[64] = {0};
        uint16_t len = 0;
        // M01LRF_SendEnableCommand();
        DelayMs(100);
        len = M01LRF_StartFastMeasurement(dist_buf, sizeof(dist_buf));
        if (len > 0)
        {
            PRINT("Distance raw: ");
            for (uint16_t i = 0; i < len; i++)
            {
                PRINT("%02X ", dist_buf[i]);
            }
            PRINT("\n");

            // 根据协议：AA 80 00 22 00 04 AA BB CC DD YY ZZ Checksum
            // 数据为BCD码，如 0xAABBCCDD = 0x12345678, 表示：12345.678m
            if (len >= 11 && dist_buf[0] == 0xAA && dist_buf[3] == 0x22)
            {
                uint32_t d1 = (dist_buf[6] >> 4) * 10 + (dist_buf[6] & 0x0F);
                uint32_t d2 = (dist_buf[7] >> 4) * 10 + (dist_buf[7] & 0x0F);
                uint32_t d3 = (dist_buf[8] >> 4) * 10 + (dist_buf[8] & 0x0F);
                uint32_t d4 = (dist_buf[9] >> 4) * 10 + (dist_buf[9] & 0x0F);
                
                uint32_t distance_mm = d1 * 1000000 + d2 * 10000 + d3 * 100 + d4;
                PRINT("Distance: %d mm\n", distance_mm);

                // 在屏幕上显示
                char disp_str[32];
                snprintf(disp_str, sizeof(disp_str), "Dist: %d.%03d m", distance_mm / 1000, distance_mm % 1000);
                TFT_Show_String(&htft1, 20, 60, disp_str, WHITE, BLACK, 16, 0);
            }

            // 显示原始数据
            TFT_Show_String(&htft1, 20, 80, "Raw:", WHITE, BLACK, 16, 0);
            char raw_part1[40] = {0};
            char raw_part2[40] = {0};
            int off1 = 0, off2 = 0;
            for (uint16_t i = 0; i < len; i++)
            {
                if (i < 8)
                    off1 += snprintf(raw_part1 + off1, sizeof(raw_part1) - off1, "%02X ", dist_buf[i]);
                else if (i < 16)
                    off2 += snprintf(raw_part2 + off2, sizeof(raw_part2) - off2, "%02X ", dist_buf[i]);
            }
            TFT_Show_String(&htft1, 20, 100, raw_part1, WHITE, BLACK, 16, 0);
            TFT_Show_String(&htft1, 20, 120, raw_part2, WHITE, BLACK, 16, 0);
        }
        else
        {
            PRINT("Read distance timeout\n");
        }
    }

    GPIOA_ClearITFlagBit(MEASURE_KEY | HOME_KEY); // 清除所有按键的中断标志位
}