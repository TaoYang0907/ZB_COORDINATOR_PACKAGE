# ZigBee Coordinator MG21 #

## 1. 简介 ##

该软件包为了简化在ZigBee网络中对协调器的控制，并且参考 AT device 软件包的架构，将AT指令移植至mg21中，提供相应的控制API与应用实例。

### 1.1. 目录结构 ###

| 名称 | 说明 |
| ---- | ---- |
| src | 实现源码目录 |
| inc | 头文件目录 |
| sample | 示例文件目录 |
| class | 不同设备针对 AT 组件的移植适配目录 |
| class/mg21 | MG21 设备针对 AT 组件的移植目录，实现作为协调器的基本控制功能 |

### 1.2 许可证 ###

at_device package 遵循 LGPLv2.1 许可，详见 `LICENSE` 文件。

### 1.3 依赖 ###

- RT_Thread 4.0.2+
- RT_Thread AT 组件  1.3.0+

## 2. 获取方式 ##

该软件包是对 AT 组件的移植，需先开启 AT 组件库，随后再获取该软件包。


## 3. 注意事项  ##
- 在使用该软件包前需要自行开启AT组件的client模式，并根据自己需求进行相关配置；

## 4. 联系方式

* 维护：RT-Thread 开发团队及社区开发者
* 主页：https://github.com/RT-Thread-packages/at_device
* QQ：935343586
