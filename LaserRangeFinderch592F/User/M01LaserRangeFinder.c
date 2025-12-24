/**
 * @file    M01LaserRangeFinder.c
 * @author  雪豹  https://github.com/2827700630
 * @version V1.0
 * @date    2025-10-5
 * @brief   深圳市开腾通讯有限公司出产的M01激光测距模块驱动代码，参考数据手册编写。如有侵权请联系我删除
 */

// 在下面引用你单片机的头文件
#include "CH59x_common.h"

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

/**
 * @brief 发送原始指令
 * @param command 指令数组指针
 * @param length 指令长度
 */
void M01LRF_SendRawCommand (const uint8_t *command, uint16_t length) {

    // 在下面放入你平台的串口发送代码
    UART0_SendString ((uint8_t *)command, length);
}

/**
 * @brief 接收原始数据
 * @param buffer 接收缓冲区指针
 * @param buffer_len 缓冲区长度
 * @return 实际接收到的字节数
 */
uint16_t M01LRF_ReceiveRawdata (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) {
        return 0;
    }

    uint16_t total = 0;
    uint16_t idle_attempts = 20000;  // 增加超时时间：约 2000 ms 超时，100 us * 20000

    while ((idle_attempts > 0U) && (total < buffer_len)) {
        uint16_t chunk = UART0_RecvString (buffer + total);

        if (chunk != 0U) {
            total += chunk;
            idle_attempts = 5000; // 收到数据后，重置空闲等待时间为 500ms

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

/**
 * @brief 读取模块状态
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadModuleStatus (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) {
        return 0;
    }

    M01LRF_SendRawCommand (ReadModuleStatus, sizeof (ReadModuleStatus));
    mDelaymS (2);

    return M01LRF_ReceiveRawdata (buffer, buffer_len);
}

/**
 * @brief 读取硬件版本号
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadHardwareVersion (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) return 0;
    M01LRF_SendRawCommand (ReadHardwareVersion, sizeof (ReadHardwareVersion));
    mDelaymS (2);
    return M01LRF_ReceiveRawdata (buffer, buffer_len);
}

/**
 * @brief 发送开启激光指令
 */
void M01LRF_SendEnableCommand (void) {
    M01LRF_SendRawCommand (ENABLE_LASER, sizeof (ENABLE_LASER));
}

/**
 * @brief 发送关闭激光指令
 */
void M01LRF_SendDisableCommand (void) {
    M01LRF_SendRawCommand (DISABLE_LASER, sizeof (DISABLE_LASER));
}

/**
 * @brief 读取软件版本号
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadSoftwareVersion (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) return 0;
    M01LRF_SendRawCommand (ReadSoftwareVersion, sizeof (ReadSoftwareVersion));
    mDelaymS (2);
    return M01LRF_ReceiveRawdata (buffer, buffer_len);
}

/**
 * @brief 读取模块ID
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadID (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) return 0;
    M01LRF_SendRawCommand (ReadID, sizeof (ReadID));
    mDelaymS (2);
    return M01LRF_ReceiveRawdata (buffer, buffer_len);
}

/**
 * @brief 读取输入电压
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadInputVoltage (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) return 0;
    M01LRF_SendRawCommand (ReadInputVoltage, sizeof (ReadInputVoltage));
    mDelaymS (2);
    return M01LRF_ReceiveRawdata (buffer, buffer_len);
}

/**
 * @brief 读取模块温度
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadTemperature (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) return 0;
    M01LRF_SendRawCommand (ReadTemperature, sizeof (ReadTemperature));
    mDelaymS (2);
    return M01LRF_ReceiveRawdata (buffer, buffer_len);
}

/**
 * @brief 读取测距结果
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_ReadDistance (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) return 0;
    M01LRF_SendRawCommand (ReadDistance, sizeof (ReadDistance));
    mDelaymS (50); // 增加延时，给模块更多处理时间
    return M01LRF_ReceiveRawdata (buffer, buffer_len);
}

/**
 * @brief 启动单次测量
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_StartSingleMeasurement (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) return 0;
    M01LRF_SendRawCommand (StartSingleMeasurement, sizeof (StartSingleMeasurement));
    mDelaymS (2000); // 测量需要时间，增加延时
    return M01LRF_ReceiveRawdata (buffer, buffer_len);
}

/**
 * @brief 启动快速测量
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_StartFastMeasurement (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) return 0;
    M01LRF_SendRawCommand (StartFastMeasurement, sizeof (StartFastMeasurement));
    mDelaymS (2);
    return M01LRF_ReceiveRawdata (buffer, buffer_len);
}

/**
 * @brief 启动连续测量
 * @param buffer 接收缓冲区
 * @param buffer_len 缓冲区长度
 * @return 接收到的字节数
 */
uint16_t M01LRF_StartContinuousMeasurement (uint8_t *buffer, uint16_t buffer_len) {
    if ((buffer == NULL) || (buffer_len == 0U)) return 0;
    M01LRF_SendRawCommand (StartContinuousMeasurement, sizeof (StartContinuousMeasurement));
    mDelaymS (2);
    return M01LRF_ReceiveRawdata (buffer, buffer_len);
}

/**
 * @brief 设置波特率为9600
 */
void M01LRF_SetBaudRate9600 (void) {
    M01LRF_SendRawCommand (SetBaudRate9600, sizeof (SetBaudRate9600));
}

/**
 * @brief 设置波特率为115200
 */
void M01LRF_SetBaudRate115200 (void) {
    M01LRF_SendRawCommand (SetBaudRate115200, sizeof (SetBaudRate115200));
}
