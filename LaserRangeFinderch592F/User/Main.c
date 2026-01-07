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
SPI_HandleTypeDef SPI0;  // SPI句柄
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

// 测量历史记录全局变量
uint32_t history_dists[3] = {0};

// 开机时间纪录相关的全局变量
uint32_t max_uptime_sec = 0; // 历史最长开机时间
uint32_t current_uptime_sec = 0;

#define EEPROM_ADDR_MAX_UPTIME 0x0000 // EEPROM/Data-Flash 存储地址

void DrawStaticUI(void)
{
    // 清屏为白色
    TFT_Fill_Area(&htft1, 0, 0, WIDTH, HEIGHT, WHITE);

    // 顶部状态栏 (占位符)
    TFT_Show_String(&htft1, 5, 5, "20", BLACK, WHITE, 16, 0);
    // 图标...

    // 测量基准图标 (测量区域左上角)
    // 简单的矩形
    for (int i = 0; i < 20; i++)
    {
        TFT_Draw_Point(&htft1, 20 + i, 40, BLACK); // 顶部
        TFT_Draw_Point(&htft1, 20 + i, 60, RED);   // 底部 (红色)
    }
    for (int i = 0; i < 20; i++)
    {
        TFT_Draw_Point(&htft1, 20, 40 + i, BLACK); // 左侧
        TFT_Draw_Point(&htft1, 40, 40 + i, BLACK); // 右侧
    }
}

void UpdateMeasurementDisplay(void)
{
    char buf[32];

    // 清除测量区域 (简单填充)
    // 区域: x=50, y=40 到 200. 宽度=190.
    TFT_Fill_Area(&htft1, 50, 40, WIDTH, 200, WHITE);

    // 第1行 (顶部) - 历史记录[2]
    snprintf(buf, sizeof(buf), "%d.%03d m", history_dists[2] / 1000, history_dists[2] % 1000);
    // 大致右对齐
    TFT_Show_String(&htft1, 100, 50, buf, GRAY, WHITE, 16, 0);

    // 第2行 (中间) - 历史记录[1]
    snprintf(buf, sizeof(buf), "%d.%03d m", history_dists[1] / 1000, history_dists[1] % 1000);
    TFT_Show_String(&htft1, 100, 90, buf, GRAY, WHITE, 16, 0);

    // 第3行 (底部) - 历史记录[0] (当前)
    snprintf(buf, sizeof(buf), "%d.%03d m", history_dists[0] / 1000, history_dists[0] % 1000);
    // 使用16号字体 (24号显示可能异常)
    TFT_Show_String(&htft1, 60, 140, (uint8_t *)buf, BLACK, WHITE, 16, 0);
}

void UpdateUptime(void)
{
    static uint32_t last_sec = 0xFFFFFFFF;
    static uint32_t last_sync_sec = 0;
    uint32_t total_sec = (uint32_t)(SysTick->CNT / GetSysClock());
    current_uptime_sec = total_sec;

    // 每秒更新一次显示
    if (total_sec != last_sec)
    {
        last_sec = total_sec;
        char buf[24];
        uint32_t hour, min, sec;

        // 更新历史最长开机记录 (实时)
        if (current_uptime_sec > max_uptime_sec)
        {
            max_uptime_sec = current_uptime_sec;
        }

        // 计算当前开机时间 (时:分:秒)
        hour = total_sec / 3600;
        min = (total_sec % 3600) / 60;
        sec = total_sec % 60;
        snprintf(buf, sizeof(buf), "Up: %02d:%02d:%02d", hour, min, sec);
        TFT_Show_String(&htft1, WIDTH - 100, 5, (uint8_t *)buf, BLACK, WHITE, 16, 0);

        // 计算历史最长开机时间 (时:分:秒)
        hour = max_uptime_sec / 3600;
        min = (max_uptime_sec % 3600) / 60;
        sec = max_uptime_sec % 60;
        snprintf(buf, sizeof(buf), "Max:%02d:%02d:%02d", hour, min, sec);
        TFT_Show_String(&htft1, WIDTH - 100, 22, (uint8_t *)buf, RED, WHITE, 16, 0);

        // 每隔 1 秒如果记录增加则保存一次到 Flash，避免频繁擦写
        if (total_sec - last_sync_sec >= 1)
        {
            last_sync_sec = total_sec;
            // 只有当当前时长突破了历史记录，且满足同步时间间隔时，才执行写入
            if (current_uptime_sec >= max_uptime_sec) 
            {
                EEPROM_WRITE(EEPROM_ADDR_MAX_UPTIME, &max_uptime_sec, sizeof(max_uptime_sec));
            }
        }
    }
}

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

    TFT_Init_ST7789v3(&htft1); // ST7789v3屏幕初始化,右键进入tft_init.c查看更多屏幕的初始化函数

    /* 从 Flash 读取历史最长开机记录 */
    EEPROM_READ(EEPROM_ADDR_MAX_UPTIME, &max_uptime_sec, sizeof(max_uptime_sec));
    // 如果读取到的是 0xFFFFFFFF (空 Flash 状态)，重置为 0
    if (max_uptime_sec == 0xFFFFFFFF)
        max_uptime_sec = 0;

    /* 开启系统计数器 (SysTick) 用于显示开机时间 */
    SysTick->CTLR |= SysTick_CTLR_STE | SysTick_CTLR_STCLK;

    DrawStaticUI();
    UpdateMeasurementDisplay();

    /* 按键中断配置 */
    // 配置GPIOA中断
    GPIOA_ModeCfg(HOME_KEY, GPIO_ModeIN_PU);            // 上拉输入
    GPIOA_ITModeCfg(HOME_KEY, GPIO_ITMode_FallEdge);    // 下降沿触发
    GPIOA_ModeCfg(UP_KEY, GPIO_ModeIN_PU);              // 上拉输入
    GPIOA_ITModeCfg(UP_KEY, GPIO_ITMode_FallEdge);      // 下降沿触发
    GPIOA_ModeCfg(MEASURE_KEY, GPIO_ModeIN_PU);         // 上拉输入
    GPIOA_ITModeCfg(MEASURE_KEY, GPIO_ITMode_FallEdge); // 下降沿触发
    PFIC_EnableIRQ(GPIO_A_IRQn);                        // 开启GPIOA中断

    // 配置GPIOB中断
    GPIOB_ModeCfg(SET_KEY, GPIO_ModeIN_PU);             // 上拉输入
    GPIOB_ITModeCfg(SET_KEY, GPIO_ITMode_FallEdge);     // 下降沿触发
    GPIOB_ModeCfg(HISTORY_KEY, GPIO_ModeIN_PU);         // 上拉输入
    GPIOB_ITModeCfg(HISTORY_KEY, GPIO_ITMode_FallEdge); // 下降沿触发

    PFIC_EnableIRQ(GPIO_B_IRQn); // 开启GPIOB中断

    PRINT("可以按下按键了\n");

    while (1) // 循环
    {
        // 持续更新开机时间显示
        UpdateUptime();

        // 连续自动测量逻辑 (移除之前的 3 秒间隔限制)
        uint8_t dist_buf[64] = {0};
        uint16_t len = 0;

        // 发送测量指令并获取结果
        len = M01LRF_StartFastMeasurement(dist_buf, sizeof(dist_buf));

        if (len > 0)
        {
            // 收到有效数据，根据协议解析：AA 80 00 22 ... 数据为 BCD 码
            if (len >= 11 && dist_buf[0] == 0xAA && (dist_buf[3] == 0x22 || dist_buf[3] == 0x20))
            {
                uint32_t d1 = (dist_buf[6] >> 4) * 10 + (dist_buf[6] & 0x0F);
                uint32_t d2 = (dist_buf[7] >> 4) * 10 + (dist_buf[7] & 0x0F);
                uint32_t d3 = (dist_buf[8] >> 4) * 10 + (dist_buf[8] & 0x0F);
                uint32_t d4 = (dist_buf[9] >> 4) * 10 + (dist_buf[9] & 0x0F);

                uint32_t distance_mm = d1 * 1000000 + d2 * 10000 + d3 * 100 + d4;
                
                // 仅当距离发生有效变化或收到新数据时打印并记录 (可选：也可直接刷新)
                PRINT("Continuous Distance: %d mm\n", distance_mm);

                // 更新历史记录 (前移旧数据)
                history_dists[2] = history_dists[1];
                history_dists[1] = history_dists[0];
                history_dists[0] = distance_mm;

                UpdateMeasurementDisplay();
            }
        }
        
        // 连续测量模式下，加入一个极小延时确保系统响应按键或时间刷新
        DelayMs(10);
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

                // 更新历史记录
                history_dists[2] = history_dists[1];
                history_dists[1] = history_dists[0];
                history_dists[0] = distance_mm;

                UpdateMeasurementDisplay();
            }
        }
        else
        {
            PRINT("Read distance timeout\n");
        }
    }

    GPIOA_ClearITFlagBit(MEASURE_KEY | HOME_KEY); // 清除所有按键的中断标志位
}