## 开发遇到的问题汇总 - HQ

[TOC]

------

#### 注意

- 

------

## ./libtool: line 1723: arm-poky-linux-gnueabi-ranlib: command not found

在libpng库安装时执行 `sudo make install`出现错误

出现问题：

```
./libtool: line 1723: arm-poky-linux-gnueabi-ranlib: command not found
Makefile:932: recipe for target 'install-libLTLIBRARIES' failed
make[2]: *** [install-libLTLIBRARIES] Error 127
make[2]: 离开目录“/home/hq/daily/libpng/libpng-1.6.35”
Makefile:2008: recipe for target 'install-am' failed
make[1]: *** [install-am] Error 2
make[1]: 离开目录“/home/hq/daily/libpng/libpng-1.6.35”
Makefile:2002: recipe for target 'install' failed
make: *** [install] Error 2
```

 原因：

**make install 时加了sudo 而我是在普通用户~/.bashrc中加的交叉编译路径。而用了sudo后就成另一个用户了，此环境变量就不起作用了。**

解决方案：

1. 把交叉编译环境变量加到/etc/下的bash配制文件中去，使之对所有用户有效。

2. 切换到root然后配置环境变量，安装完成后再切换回普通用户

   > ```c
   > sudo -i
   > source /opt/fsl-imx-x11/4.1.15-2.1.0/environment-setup-cortexa7hf-neon-poky-linux-gnueabi
   > sudo make install
   > su hq
   > ```

3. 在make install前使用su，不用sudo （此方法是否可行，未知）

   > su 和 sudo 的区别：
   >
   > 1. 共同点：都具有root用户权限；
   > 2. 不同点：su仅仅取得root权限，工作环境不变；sudo是完全取得root的权限和root的工作环境





































































































































































