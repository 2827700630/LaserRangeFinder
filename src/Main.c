/* CH573F TFT屏幕驱动测试程序
 * 雪豹 编写   https://github.com/2827700630
 * 最后修改日期 2025-10-2
 * 适用于CH573F单片机，编写时参考了沁恒的SPI0示例程序。使用硬件SPI0和DMA传输
 * 支持ST7735S和ST7789v3屏幕。你只需要把屏幕插上去就行，程序会测试ST7735S和ST7789v3两种屏幕
 * 连线方式：
 * GND      -> GND
 * VCC      -> 3.3V
 * SCL(SCK) -> PA13 (SPI0_SCK)
 * SDA(MOSI)-> PA14 (SPI0_MOSI)
 * TFT_CS   -> PA12
 * TFT_RES  -> PA11 (也可以接到单片机的复位脚RST)
 * TFT_DC   -> PA10
 * TFT_BLK  -> PB22 (也可以把它接到3.3V)
 * 更多信息请参考README.md
 */

#include "CH57x_common.h"

// 包含TFT驱动所需的头文件
#include "TFTh/TFT_CAD.h"  // 包含绘图函数和 IO 函数
#include "TFTh/TFT_init.h"
#include "TFTh/TFT_text.h"
#include "TFTh/TFT_io.h"  // 包含RGB转换函数

// TFT屏幕句柄和SPI句柄定义
TFT_HandleTypeDef htft1;  // 第一个TFT屏幕把手
SPI_HandleTypeDef SPI0;   // 第一个TFT屏幕把手
// TFT屏幕引脚定义，根据实际连接修改
#define TFT_CS_GPIO_Port 0  // 0是GPIOA，1是GPIOB
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
int main() {
    SetSysClock (CLK_SOURCE_PLL_60MHz);

    /* 配置串口调试 */
    GPIOA_SetBits (GPIO_Pin_9);
    GPIOA_ModeCfg (GPIO_Pin_8, GPIO_ModeIN_PU);
    GPIOA_ModeCfg (GPIO_Pin_9, GPIO_ModeOut_PP_5mA);
    UART1_DefInit();
    PRINT ("Start @ChipID=%02X\n", R8_CHIP_ID);
    // /* 配置屏幕引脚，沁恒的单片机GPIOA和GPIOB操作函数是分开的。必须设置不然屏幕无法显示 */
    // GPIOA_ModeCfg (TFT_CS_Pin, GPIO_ModeOut_PP_5mA);
    // GPIOA_ModeCfg (TFT_RES_Pin, GPIO_ModeOut_PP_5mA);
    // GPIOA_ModeCfg (TFT_DC_Pin, GPIO_ModeOut_PP_5mA);
    // GPIOB_ModeCfg (TFT_BLK_Pin, GPIO_ModeOut_PP_5mA);
    // /* 屏幕设置 */
    // TFT_Init_Instance (&htft1, &SPI0, TFT_CS_GPIO_Port, TFT_CS_Pin);
    // TFT_Config_Pins (&htft1, TFT_DC_GPIO_Port, TFT_DC_Pin, TFT_RES_GPIO_Port, TFT_RES_Pin, TFT_BLK_GPIO_Port, TFT_BLK_Pin);  // 必须手动设置引脚
    // TFT_Config_Display (&htft1, 0, 0, 0);                                                                                    // 设置方向、X/Y偏移
    // TFT_Init_ST7789v3 (&htft1);                                                                                              // ST7789v3屏幕初始化,右键进入tft_init.c查看更多屏幕的初始化函数
    // TFT_Show_String (&htft1, 20, 20, "now ST7789v3", WHITE, BLACK, 16, 0);

    // 按键中断配置
    // GPIOB_ModeCfg (GPIO_Pin_10, GPIO_ModeIN_Floating);    // PB10上拉输入
    // GPIOB_ITModeCfg (GPIO_Pin_10, GPIO_ITMode_LowLevel);  // PB10下降沿触发
    GPIOA_ModeCfg (GPIO_Pin_4, GPIO_ModeIN_PU);    // PA4上拉输入
    GPIOA_ITModeCfg (GPIO_Pin_4, GPIO_ITMode_FallEdge);  // PA4下降沿触发
    PFIC_EnableIRQ (GPIO_A_IRQn);                // 开启GPIOA中断
    // GPIOB_ModeCfg (GPIO_Pin_11, GPIO_ModeIN_PU);          // PB10上拉输入
    // GPIOB_ModeCfg (GPIO_Pin_12, GPIO_ModeIN_PU);          // PB10上拉输入
    // GPIOB_ModeCfg (GPIO_Pin_13, GPIO_ModeIN_PD);          // PB10上拉输入
    // GPIOB_ModeCfg (GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
    // GPIOB_SetBits (GPIO_Pin_10);

    while (1)  // 循环
    {
        // /* 三种颜色填充，检查你的颜色显示是否正确 */
        // TFT_Fill_Area (&htft1, 0, 40, WIDTH, HEIGHT, RED);
        // TFT_Fill_Area (&htft1, 0, 40, WIDTH, HEIGHT, GREEN);
        // TFT_Fill_Area (&htft1, 0, 40, WIDTH, HEIGHT, BLUE);
        DelayMs (500);
    }
}

// 设置外部中断相关函数属性，指定声明相关特征
__attribute__ ((interrupt ("WCH-Interrupt-fast")))
__attribute__ ((section (".highcode")))
/**
 * 函数名：GPIOB_IRQHandler
 * 参数：无
 * 返回值：无
 * 功能说明：GPIOB端口的中断处理函数
 */
void GPIOA_IRQHandler (void) {
    if(GPIOA_ReadITFlagBit(GPIO_Pin_4))
    {
        PRINT ("GPIO——A \n");
        // DelayMs (500); // 不建议在中断中长时间延时
        GPIOA_ClearITFlagBit (GPIO_Pin_4);
    }
}