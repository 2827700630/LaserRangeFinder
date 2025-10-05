/**
 * @file    M01LaserRangeFinder.h
 * @author  雪豹  https://github.com/2827700630
 * @version V1.0
 * @date    2025-10-5
 * @brief   深圳市开腾通讯有限公司出产的M01激光测距模块驱动代码，参考数据手册编写。如有侵权请联系我删除
 */

#ifndef __M01LASERRANGEFINDER_H
#define __M01LASERRANGEFINDER_H

#include <stdint.h>

// static uint8_t ENABLE_LASER_MODULE[] = {0xAA, 0x00, 0x01, 0xBE, 0x00, 0x01, 0x00, 0x01, 0xC1};   // 启动激光头
// static uint8_t DISABLE_LASER_MODULE[] = {0xAA, 0x00, 0x01, 0xBE, 0x00, 0x01, 0x00, 0x00, 0xC0};  // 关闭激光头

void M01LRF_SendEnableCommand(void);
void M01LRF_SendDisableCommand(void);
void M01LRF_SendRawCommand(const uint8_t *command, uint16_t length);
uint16_t M01LRF_ReceiveRawdata(uint8_t *buffer, uint16_t buffer_len);
uint16_t M01LRF_ReadModuleStatus(uint8_t *buffer, uint16_t buffer_len);

#endif // __M01LASERRANGEFINDER_H