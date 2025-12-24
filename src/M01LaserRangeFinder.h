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

/**
 * @brief 发送开启激光指令
 */
void M01LRF_SendEnableCommand(void);

/**
 * @brief 发送关闭激光指令
 */
void M01LRF_SendDisableCommand(void);

/**
 * @brief 发送原始指令
 * @param command 指令数组指针
 * @param length 指令长度
 */
void M01LRF_SendRawCommand(const uint8_t *command, uint16_t length);

/**
 * @brief 接收原始数据
 * @param buffer 接收缓冲区指针
 * @param buffer_len 缓冲区长度
 * @return 实际接收到的字节数
 */
uint16_t M01LRF_ReceiveRawdata(uint8_t *buffer, uint16_t buffer_len);

/**
 * @brief 读取模块状态
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadModuleStatus(uint8_t *buffer, uint16_t buffer_len);

// Convenience read wrappers: send command and receive response into `buffer`.

/**
 * @brief 读取硬件版本号
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadHardwareVersion(uint8_t *buffer, uint16_t buffer_len);

/**
 * @brief 读取软件版本号
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadSoftwareVersion(uint8_t *buffer, uint16_t buffer_len);

/**
 * @brief 读取模块ID
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadID(uint8_t *buffer, uint16_t buffer_len);

/**
 * @brief 读取输入电压
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadInputVoltage(uint8_t *buffer, uint16_t buffer_len);

/**
 * @brief 读取模块温度
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadTemperature(uint8_t *buffer, uint16_t buffer_len);

/**
 * @brief 读取测距结果
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadDistance(uint8_t *buffer, uint16_t buffer_len);

/**
 * @brief 启动单次测量
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_StartSingleMeasurement(uint8_t *buffer, uint16_t buffer_len);

/**
 * @brief 启动快速测量
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_StartFastMeasurement(uint8_t *buffer, uint16_t buffer_len);

/**
 * @brief 启动连续测量
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_StartContinuousMeasurement(uint8_t *buffer, uint16_t buffer_len);

/**
 * @brief 设置波特率为9600
 */
void M01LRF_SetBaudRate9600(void);

/**
 * @brief 设置波特率为115200
 */
void M01LRF_SetBaudRate115200(void);

#endif // __M01LASERRANGEFINDER_H