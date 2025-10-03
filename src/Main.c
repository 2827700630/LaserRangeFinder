/**
 ******************************************************************************
 * @file    Main.c
 * @author  ѩ��
 * @version V1.0.0
 * @date    2025-10-3
 * @brief   ��������������
 ******************************************************************************
 * @attention
 */

#include "CH57x_common.h"

// ����TFT���������ͷ�ļ�
#include "TFTh/TFT_CAD.h" // ������ͼ������ IO ����
#include "TFTh/TFT_init.h"
#include "TFTh/TFT_text.h"
#include "TFTh/TFT_io.h" // ����RGBת������

/* ������ض��� */
#define KEY1_PIN GPIO_Pin_10 // PB10����
#define KEY2_PIN GPIO_Pin_11 // PB11����
#define KEY3_PIN GPIO_Pin_12 // PB12����
#define KEY4_PIN GPIO_Pin_13 // PB13����

/* TFT��Ļ��ض��� */
// TFT��Ļ�����SPI�������
TFT_HandleTypeDef htft1; // ��һ��TFT��Ļ����
SPI_HandleTypeDef SPI0;  // ��һ��TFT��Ļ����
// TFT��Ļ���Ŷ��壬����ʵ�������޸�
#define TFT_CS_GPIO_Port 0 // 0��GPIOA��1��GPIOB
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
int main()
{
    SetSysClock(CLK_SOURCE_PLL_60MHz);

    /* ���ô��ڵ��� */
    GPIOA_SetBits(GPIO_Pin_9);
    GPIOA_ModeCfg(GPIO_Pin_8, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(GPIO_Pin_9, GPIO_ModeOut_PP_5mA);
    UART1_DefInit();
    PRINT("Start @ChipID=%02X\n", R8_CHIP_ID);
    /* ������Ļ���ţ��ߺ�ĵ�Ƭ��GPIOA��GPIOB���������Ƿֿ��ġ��������ò�Ȼ��Ļ�޷���ʾ */
    GPIOA_ModeCfg(TFT_CS_Pin, GPIO_ModeOut_PP_5mA);
    GPIOA_ModeCfg(TFT_RES_Pin, GPIO_ModeOut_PP_5mA);
    GPIOA_ModeCfg(TFT_DC_Pin, GPIO_ModeOut_PP_5mA);
    GPIOB_ModeCfg(TFT_BLK_Pin, GPIO_ModeOut_PP_5mA);
    /* ��Ļ���� */
    TFT_Init_Instance(&htft1, &SPI0, TFT_CS_GPIO_Port, TFT_CS_Pin);
    TFT_Config_Pins(&htft1, TFT_DC_GPIO_Port, TFT_DC_Pin, TFT_RES_GPIO_Port, TFT_RES_Pin, TFT_BLK_GPIO_Port, TFT_BLK_Pin); // �����ֶ���������
    TFT_Config_Display(&htft1, 0, 0, 0);                                                                                   // ���÷���X/Yƫ��
    TFT_Init_ST7789v3(&htft1);                                                                                             // ST7789v3��Ļ��ʼ��,�Ҽ�����tft_init.c�鿴������Ļ�ĳ�ʼ������
    TFT_Show_String(&htft1, 20, 20, "now ST7789v3", WHITE, BLACK, 16, 0);

    /* �����ж����� */
    // // ����GPIOA�жϣ���PA4Ϊ��
    // GPIOA_ModeCfg(GPIO_Pin_4, GPIO_ModeIN_PU);         // PA4��������
    // GPIOA_ITModeCfg(GPIO_Pin_4, GPIO_ITMode_FallEdge); // PA4�½��ش���
    // PFIC_EnableIRQ(GPIO_A_IRQn);                       // ����GPIOA�ж�

    // ����GPIOB�жϣ���PB11Ϊ��
    GPIOB_ModeCfg(KEY1_PIN, GPIO_ModeIN_PU);         // ����1��������
    GPIOB_ITModeCfg(KEY1_PIN, GPIO_ITMode_FallEdge); // ����1�½��ش���
    GPIOB_ModeCfg(KEY2_PIN, GPIO_ModeIN_PU);         // ����2��������
    GPIOB_ITModeCfg(KEY2_PIN, GPIO_ITMode_FallEdge); // ����2�½��ش���
    GPIOB_ModeCfg(KEY3_PIN, GPIO_ModeIN_PU);         // ����3��������
    GPIOB_ITModeCfg(KEY3_PIN, GPIO_ITMode_FallEdge); // ����3�½��ش���
    GPIOB_ModeCfg(KEY4_PIN, GPIO_ModeIN_PU);         // ����4��������
    GPIOB_ITModeCfg(KEY4_PIN, GPIO_ITMode_FallEdge); // ����4�½��ش���
    PFIC_EnableIRQ(GPIO_B_IRQn);                     // ����GPIOB�ж�

    PRINT("Press Key \n");

    while (1) // ѭ��
    {
        /* ������ɫ��䣬��������ɫ��ʾ�Ƿ���ȷ */
        TFT_Fill_Area(&htft1, 0, 40, WIDTH, HEIGHT, RED);
        TFT_Fill_Area(&htft1, 0, 40, WIDTH, HEIGHT, GREEN);
        TFT_Fill_Area(&htft1, 0, 40, WIDTH, HEIGHT, BLUE);
        DelayMs(500);
    }
}

// // �����ⲿ�ж���غ������ԣ�ָ�������������
// __attribute__((interrupt("WCH-Interrupt-fast")))
// __attribute__((section(".highcode")))
// /**
//  * @brief GPIOA�˿ڵ��жϴ�����
//  * @note �ǵ�����жϱ�־λ�����5 RISC-VоƬ��Ӧ���жϺ�������Startup\startup_CH573.S�ļ���鿴
//  */
// void
// GPIOA_IRQHandler(void)
// {
//     if (GPIOA_ReadITFlagBit(GPIO_Pin_4))
//     {
//         PRINT("GPIOA \n");
//         // DelayMs (500); // ���������ж��г�ʱ����ʱ
//         GPIOA_ClearITFlagBit(GPIO_Pin_4); // ����жϱ�־λ
//     }
// }

// �����ⲿ�ж���غ������ԣ�ָ�������������
__attribute__((interrupt("WCH-Interrupt-fast")))
__attribute__((section(".highcode")))
/**
 * @brief GPIOB�˿ڵ��жϴ�����
 * @note �ǵ�����жϱ�־λ�����5 RISC-VоƬ��Ӧ���жϺ�������Startup\startup_CH573.S�ļ���鿴
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
    GPIOB_ClearITFlagBit(KEY1_PIN | KEY2_PIN | KEY3_PIN | KEY4_PIN); // ������а������жϱ�־λ
}