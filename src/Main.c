/* CH573F TFT��Ļ�������Գ���
 * ѩ�� ��д   https://github.com/2827700630
 * ����޸����� 2025-10-2
 * ������CH573F��Ƭ������дʱ�ο����ߺ��SPI0ʾ������ʹ��Ӳ��SPI0��DMA����
 * ֧��ST7735S��ST7789v3��Ļ����ֻ��Ҫ����Ļ����ȥ���У���������ST7735S��ST7789v3������Ļ
 * ���߷�ʽ��
 * GND      -> GND
 * VCC      -> 3.3V
 * SCL(SCK) -> PA13 (SPI0_SCK)
 * SDA(MOSI)-> PA14 (SPI0_MOSI)
 * TFT_CS   -> PA12
 * TFT_RES  -> PA11 (Ҳ���Խӵ���Ƭ���ĸ�λ��RST)
 * TFT_DC   -> PA10
 * TFT_BLK  -> PB22 (Ҳ���԰����ӵ�3.3V)
 * ������Ϣ��ο�README.md
 */

#include "CH57x_common.h"

// ����TFT���������ͷ�ļ�
#include "TFTh/TFT_CAD.h"  // ������ͼ������ IO ����
#include "TFTh/TFT_init.h"
#include "TFTh/TFT_text.h"
#include "TFTh/TFT_io.h"  // ����RGBת������

// TFT��Ļ�����SPI�������
TFT_HandleTypeDef htft1;  // ��һ��TFT��Ļ����
SPI_HandleTypeDef SPI0;   // ��һ��TFT��Ļ����
// TFT��Ļ���Ŷ��壬����ʵ�������޸�
#define TFT_CS_GPIO_Port 0  // 0��GPIOA��1��GPIOB
#define TFT_CS_Pin GPIO_Pin_12
#define TFT_DC_GPIO_Port 0
#define TFT_DC_Pin GPIO_Pin_10
#define TFT_RES_GPIO_Port 0
#define TFT_RES_Pin GPIO_Pin_11
#define TFT_BLK_GPIO_Port 1
#define TFT_BLK_Pin GPIO_Pin_22
// SPI0���Ŷ�����TFTio.c�ļ��е�SPI0_MasterDefInit����֮ǰ��CH573Fֻ��һ��Ӳ��SPI
// ��Ļ�ֱ��ʶ��壬����ʵ����Ļ�޸�
#define HEIGHT 320
#define WIDTH 240

/**
 * @fn     main
 * @brief   ������
 * @return  none
 */
int main() {
    SetSysClock (CLK_SOURCE_PLL_60MHz);

    /* ���ô��ڵ��� */
    GPIOA_SetBits (GPIO_Pin_9);
    GPIOA_ModeCfg (GPIO_Pin_8, GPIO_ModeIN_PU);
    GPIOA_ModeCfg (GPIO_Pin_9, GPIO_ModeOut_PP_5mA);
    UART1_DefInit();
    PRINT ("Start @ChipID=%02X\n", R8_CHIP_ID);
    // /* ������Ļ���ţ��ߺ�ĵ�Ƭ��GPIOA��GPIOB���������Ƿֿ��ġ��������ò�Ȼ��Ļ�޷���ʾ */
    // GPIOA_ModeCfg (TFT_CS_Pin, GPIO_ModeOut_PP_5mA);
    // GPIOA_ModeCfg (TFT_RES_Pin, GPIO_ModeOut_PP_5mA);
    // GPIOA_ModeCfg (TFT_DC_Pin, GPIO_ModeOut_PP_5mA);
    // GPIOB_ModeCfg (TFT_BLK_Pin, GPIO_ModeOut_PP_5mA);
    // /* ��Ļ���� */
    // TFT_Init_Instance (&htft1, &SPI0, TFT_CS_GPIO_Port, TFT_CS_Pin);
    // TFT_Config_Pins (&htft1, TFT_DC_GPIO_Port, TFT_DC_Pin, TFT_RES_GPIO_Port, TFT_RES_Pin, TFT_BLK_GPIO_Port, TFT_BLK_Pin);  // �����ֶ���������
    // TFT_Config_Display (&htft1, 0, 0, 0);                                                                                    // ���÷���X/Yƫ��
    // TFT_Init_ST7789v3 (&htft1);                                                                                              // ST7789v3��Ļ��ʼ��,�Ҽ�����tft_init.c�鿴������Ļ�ĳ�ʼ������
    // TFT_Show_String (&htft1, 20, 20, "now ST7789v3", WHITE, BLACK, 16, 0);

    // �����ж�����
    // GPIOB_ModeCfg (GPIO_Pin_10, GPIO_ModeIN_Floating);    // PB10��������
    // GPIOB_ITModeCfg (GPIO_Pin_10, GPIO_ITMode_LowLevel);  // PB10�½��ش���
    GPIOA_ModeCfg (GPIO_Pin_4, GPIO_ModeIN_PU);    // PA4��������
    GPIOA_ITModeCfg (GPIO_Pin_4, GPIO_ITMode_FallEdge);  // PA4�½��ش���
    PFIC_EnableIRQ (GPIO_A_IRQn);                // ����GPIOA�ж�
    // GPIOB_ModeCfg (GPIO_Pin_11, GPIO_ModeIN_PU);          // PB10��������
    // GPIOB_ModeCfg (GPIO_Pin_12, GPIO_ModeIN_PU);          // PB10��������
    // GPIOB_ModeCfg (GPIO_Pin_13, GPIO_ModeIN_PD);          // PB10��������
    // GPIOB_ModeCfg (GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
    // GPIOB_SetBits (GPIO_Pin_10);

    while (1)  // ѭ��
    {
        // /* ������ɫ��䣬��������ɫ��ʾ�Ƿ���ȷ */
        // TFT_Fill_Area (&htft1, 0, 40, WIDTH, HEIGHT, RED);
        // TFT_Fill_Area (&htft1, 0, 40, WIDTH, HEIGHT, GREEN);
        // TFT_Fill_Area (&htft1, 0, 40, WIDTH, HEIGHT, BLUE);
        DelayMs (500);
    }
}

// �����ⲿ�ж���غ������ԣ�ָ�������������
__attribute__ ((interrupt ("WCH-Interrupt-fast")))
__attribute__ ((section (".highcode")))
/**
 * ��������GPIOB_IRQHandler
 * ��������
 * ����ֵ����
 * ����˵����GPIOB�˿ڵ��жϴ�����
 */
void GPIOA_IRQHandler (void) {
    if(GPIOA_ReadITFlagBit(GPIO_Pin_4))
    {
        PRINT ("GPIO����A \n");
        // DelayMs (500); // ���������ж��г�ʱ����ʱ
        GPIOA_ClearITFlagBit (GPIO_Pin_4);
    }
}