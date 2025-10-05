/**
 * @file    M01LaserRangeFinder.c
 * @author  雪豹  https://github.com/2827700630
 * @version V1.0
 * @date    2025-10-5
 * @brief   深圳市开腾通讯有限公司出产的M01激光测距模块驱动代码，参考数据手册编写。如有侵权请联系我删除
 */

// 在下面引用你单片机的头文件
#include "CH57x_common.h"

#include "M01LaserRangeFinder.h"

// 指令集
static const uint8_t ReadModuleStatus[] = {0xAA, 0x80, 0x00, 0x00, 0x80};     // 读取模块最新状态aa80000080
static const uint8_t ReadHardwareVersion[] = {0xAA, 0x80, 0x00, 0x0A, 0x8A};  // 读取硬件版本号aa80000a8a
static const uint8_t ReadSoftwareVersion[] = {0xAA, 0x80, 0x00, 0x0C, 0x8C};  // 读取软件版本号aa80000c8c
static const uint8_t ReadID[] = {0xAA, 0x80, 0x00, 0x0E, 0x8E};               // 读取模块序列号aa80000e8e
static const uint8_t ReadInputVoltage[] = {0xAA, 0x80, 0x00, 0x06, 0x86};     // 读取模块输入电压aa80000686
static const uint8_t ReadTemperature[] = {0xAA, 0x80, 0x00, 0x07, 0x87};      // 读取模块当前温度aa80000787
static const uint8_t ReadDistance[] = {0xAA, 0x80, 0x00, 0x22, 0xA2};         // 读取模块测距结果aa800022a2
// static const uint8_t SetModuleAddress[] = {0xAA, 0x00, 0x00, 0x10, 0x00, 0x01, 0x00, 0x01, 0x12}; // 设置模块地址aa00001000010012
// static const uint8_t SetMeasurementOffset[] = {0xAA, 0x00, 0x00, 0x12, 0x00, 0x01, 0x00, 0x64, 0x77}; // 设置测量偏移量aa0000120001006477
static const uint8_t ENABLE_LASER[] = {0xAA, 0x00, 0x01, 0xBE, 0x00, 0x01, 0x00, 0x01, 0xC1};                // 启动激光头aa0001be00010001c1
static const uint8_t DISABLE_LASER[] = {0xAA, 0x00, 0x01, 0xBE, 0x00, 0x01, 0x00, 0x00, 0xC0};               // 关闭激光头aa0001be00010000c0
static const uint8_t AngleMeasurement[] = {0xAA, 0x80, 0x00, 0x23, 0xA3};                                    // 角度测量aa800023a3
static const uint8_t StartSingleMeasurement[] = {0xAA, 0x00, 0x00, 0x20, 0x00, 0x01, 0x00, 0x00, 0x21};      // 启动一次单次测量aa0000200001000021
static const uint8_t StartFastMeasurement[] = {0xAA, 0x00, 0x00, 0x22, 0x00, 0x01, 0x00, 0x00, 0x23};        // 启动一次快速测量aa0000200001000023
static const uint8_t StartContinuousMeasurement[] = {0xAA, 0x00, 0x00, 0x21, 0x00, 0x01, 0x00, 0x00, 0x22};  // 开启自动连续测量aa0000200001000022
static const uint8_t SetBaudRate9600[] = {0xAA, 0x00, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0x15};       // 设置波特率9600:aa000014000100000015
static const uint8_t SetBaudRate115200[] = {0xAA, 0x00, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x01, 0x16};     // 设置波特率115200:aa000014000100000116

void M01LRF_SendRawCommand (const uint8_t *command, uint16_t length) {

    // 在下面放入你平台的串口发送代码
    UART0_SendString ((uint8_t *)command, length);
}

uint16_t M01LRF_ReceiveRawdata (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) {
        return 0;
    }

    uint16_t total = 0;
    uint16_t idle_attempts = 50;  // 约 5 ms 超时，100 us * 50

    while ((idle_attempts > 0U) && (total < buffer_len)) {
        uint16_t chunk = UART0_RecvString (buffer + total);

        if (chunk != 0U) {
            total += chunk;
            idle_attempts = 50;

            if (total >= buffer_len) {
                break;
            }
        } else {
            idle_attempts--;
            mDelayuS (100);
        }
    }

    return total;
}

uint16_t M01LRF_ReadModuleStatus (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) {
        return 0;
    }

    M01LRF_SendRawCommand (ReadModuleStatus, sizeof (ReadModuleStatus));
    mDelaymS (2);

    return M01LRF_ReceiveRawdata (buffer, buffer_len);
}

void M01LRF_ReadHardwareVersion (void) {
    M01LRF_SendRawCommand (ReadHardwareVersion, sizeof (ReadHardwareVersion));
}

void M01LRF_SendEnableCommand (void) {
    M01LRF_SendRawCommand (ENABLE_LASER, sizeof (ENABLE_LASER));
}

void M01LRF_SendDisableCommand (void) {
    M01LRF_SendRawCommand (DISABLE_LASER, sizeof (DISABLE_LASER));
}
