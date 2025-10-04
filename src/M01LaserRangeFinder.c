/**
 * @file    M01LaserRangeFinder.c
 * @author  雪豹  https://github.com/2827700630
 * @version V1.0
 * @date    2025-10-5
 * @brief   深圳市开腾通讯有限公司出产的M01激光测距模块驱动代码，参考数据手册编写。如有侵权请联系我删除
 */

#include "M01LaserRangeFinder.h"

#include "CH57x_common.h"

uint8_t ENABLE_LASER[] = {0xAA, 0x00, 0x01, 0xBE, 0x00, 0x01, 0x00, 0x01, 0xC1};  // 启动激光头aa0001be00010001c1
uint8_t DISABLE_LASER[] = {0xAA, 0x00, 0x01, 0xBE, 0x00, 0x01, 0x00, 0x00, 0xC0}; // 关闭激光头aa0001be00010000c0

static void M01LRF_SendRawCommand(uint8_t *command, uint16_t length)
{

    UART0_SendString(command, length);
}

void M01LRF_SendEnableCommand(void)
{
    M01LRF_SendRawCommand(ENABLE_LASER, sizeof(ENABLE_LASER));
}

void M01LRF_SendDisableCommand(void)
{
    M01LRF_SendRawCommand(DISABLE_LASER, sizeof(DISABLE_LASER));
}
