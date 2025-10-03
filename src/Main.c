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

#include "CH57x_common.h"

// 包含TFT驱动所需的头文件
#include "TFTh/TFT_CAD.h" // 包含绘图函数和 IO 函数
#include "TFTh/TFT_init.h"
#include "TFTh/TFT_text.h"
#include "TFTh/TFT_io.h" // 包含RGB转换函数

/* 按键相关定义 */
#define KEY1_PIN GPIO_Pin_10 // PB10按键
#define KEY2_PIN GPIO_Pin_11 // PB11按键
#define KEY3_PIN GPIO_Pin_12 // PB12按键
#define KEY4_PIN GPIO_Pin_13 // PB13按键

/* TFT屏幕相关定义 */
// TFT屏幕句柄和SPI句柄定义
TFT_HandleTypeDef htft1; // 第一个TFT屏幕把手
SPI_HandleTypeDef SPI0;  // 第一个TFT屏幕把手
// TFT屏幕引脚定义，根据实际连接修改
#define TFT_CS_GPIO_Port 0 // 0是GPIOA，1是GPIOB
#define TFT_CS_Pin GPIO_Pin_12
#define TFT_DC_GPIO_Port 0
#define TFT_DC_Pin GPIO_Pin_10
#define TFT_RES_GPIO_Port 0
#define TFT_RES_Pin GPIO_Pin_11
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

    /* 配置串口调试 */
    GPIOA_SetBits(GPIO_Pin_9);
    GPIOA_ModeCfg(GPIO_Pin_8, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(GPIO_Pin_9, GPIO_ModeOut_PP_5mA);
    UART1_DefInit();
    PRINT("Start @ChipID=%02X\n", R8_CHIP_ID);
    /* 配置屏幕引脚，沁恒的单片机GPIOA和GPIOB操作函数是分开的。必须设置不然屏幕无法显示 */
    GPIOA_ModeCfg(TFT_CS_Pin, GPIO_ModeOut_PP_5mA);
    GPIOA_ModeCfg(TFT_RES_Pin, GPIO_ModeOut_PP_5mA);
    GPIOA_ModeCfg(TFT_DC_Pin, GPIO_ModeOut_PP_5mA);
    GPIOB_ModeCfg(TFT_BLK_Pin, GPIO_ModeOut_PP_5mA);
    /* 屏幕设置 */
    TFT_Init_Instance(&htft1, &SPI0, TFT_CS_GPIO_Port, TFT_CS_Pin);
    TFT_Config_Pins(&htft1, TFT_DC_GPIO_Port, TFT_DC_Pin, TFT_RES_GPIO_Port, TFT_RES_Pin, TFT_BLK_GPIO_Port, TFT_BLK_Pin); // 必须手动设置引脚
    TFT_Config_Display(&htft1, 0, 0, 0);                                                                                   // 设置方向、X/Y偏移
    TFT_Init_ST7789v3(&htft1);                                                                                             // ST7789v3屏幕初始化,右键进入tft_init.c查看更多屏幕的初始化函数
    TFT_Show_String(&htft1, 20, 20, "now ST7789v3", WHITE, BLACK, 16, 0);

    /* 按键中断配置 */
    // // 配置GPIOA中断，以PA4为例
    // GPIOA_ModeCfg(GPIO_Pin_4, GPIO_ModeIN_PU);         // PA4上拉输入
    // GPIOA_ITModeCfg(GPIO_Pin_4, GPIO_ITMode_FallEdge); // PA4下降沿触发
    // PFIC_EnableIRQ(GPIO_A_IRQn);                       // 开启GPIOA中断

    // 配置GPIOB中断，以PB11为例
    GPIOB_ModeCfg(KEY1_PIN, GPIO_ModeIN_PU);         // 按键1上拉输入
    GPIOB_ITModeCfg(KEY1_PIN, GPIO_ITMode_FallEdge); // 按键1下降沿触发
    GPIOB_ModeCfg(KEY2_PIN, GPIO_ModeIN_PU);         // 按键2上拉输入
    GPIOB_ITModeCfg(KEY2_PIN, GPIO_ITMode_FallEdge); // 按键2下降沿触发
    GPIOB_ModeCfg(KEY3_PIN, GPIO_ModeIN_PU);         // 按键3上拉输入
    GPIOB_ITModeCfg(KEY3_PIN, GPIO_ITMode_FallEdge); // 按键3下降沿触发
    GPIOB_ModeCfg(KEY4_PIN, GPIO_ModeIN_PU);         // 按键4上拉输入
    GPIOB_ITModeCfg(KEY4_PIN, GPIO_ITMode_FallEdge); // 按键4下降沿触发
    PFIC_EnableIRQ(GPIO_B_IRQn);                     // 开启GPIOB中断

    PRINT("Press Key \n");

    while (1) // 循环
    {
        /* 三种颜色填充，检查你的颜色显示是否正确 */
        TFT_Fill_Area(&htft1, 0, 40, WIDTH, HEIGHT, RED);
        TFT_Fill_Area(&htft1, 0, 40, WIDTH, HEIGHT, GREEN);
        TFT_Fill_Area(&htft1, 0, 40, WIDTH, HEIGHT, BLUE);
        DelayMs(500);
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
__attribute__((interrupt("WCH-Interrupt-fast")))
__attribute__((section(".highcode")))
/**
 * @brief GPIOB端口的中断处理函数
 * @note 记得清除中断标志位。锐刻5 RISC-V芯片对应的中断函数名在Startup\startup_CH573.S文件里查看
 */
void
GPIOB_IRQHandler(void)
{
    if (GPIOB_ReadITFlagBit(KEY1_PIN))
    {
        PRINT("key1 \n");
    }
    if (GPIOB_ReadITFlagBit(KEY2_PIN))
    {
        PRINT("key2 \n");
    }
    if (GPIOB_ReadITFlagBit(KEY3_PIN))
    {
        PRINT("key3 \n");
    }
    if (GPIOB_ReadITFlagBit(KEY4_PIN))
    {
        PRINT("key4 \n");
    }
    GPIOB_ClearITFlagBit(KEY1_PIN | KEY2_PIN | KEY3_PIN | KEY4_PIN); // 清除所有按键的中断标志位
}