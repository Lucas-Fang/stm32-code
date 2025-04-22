# 项目名称： FDCAN驱动DJ电机
## 一、 项目简介
本项目基于 STM32H7 系列开发板，使用 HAL 库开发，主要实现通过 CAN 总线控制 DJI GM3508 电机，读取反馈信息，并可拓展多电调同步控制等功能。

> ✅ 适用于 CAN 总线通信、FDCAN 配置、RTOS 系统嵌入、STM32 外设控制等学习或实战项目。
## 二、软硬件环境
### 1.硬件
- 板卡：达妙 DM-02 开发板
- MCU：STM32H723VGT6
### 2.软件
- keil MDK5/VScode MDK6
### 3. 外设与接口
- CAN 外设：FDCAN1 / FDCAN2
- 接口协议：经典 CAN2.0A（非 CAN-FD）
- 电机类型：DJI GM3508 / M3508（支持标准 CAN 协议）
## 三、作者信息
- 作者: 房梓豪
- 时间: 2025.4.22
- GitHub: [Lucas-Fang](https://github.com/Lucas-Fang/stm32-code.git)
- 邮箱: luckpark20@gmail.com
