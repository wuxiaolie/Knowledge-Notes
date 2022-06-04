# 语言识别模块开发 - HQ

[TOC]

------

#### 注意

- 

------

## 语言模块 STC11L08XE

### 程序运行流程

```c
Led_test();  //开机闪灯3次
MCU_init();  //单片机本身初始化，开启中断
LD_Reset();  //ld3320初始化
Uartlni();   //串口初始化
while (1) {
    RunASR();  //启动识别
    	LD_AsrStart();
    		LD_Init_ASR();  //厂家提供的启动时序代码
    LD_AsrAddFixed();  //向LD模块添加关键词
    LD_AsrRun();  //运行ASR，启动ASR运算，开始识别
    	ProcessInit();  //判断识别是否有结果
}
```

### 需要更改的程序

1. `LD_AsrAddFixed();`  向LD模块添加关键词，在LDchip.c
2. 识别出结果后，把数据从语言模块发出来 `void User_handle(uint8 dat);` 在main()中





































































































































































