## C 段错误 - HQ

[TOC]

------

#### 注意

- [编程那些年文章](https://mp.weixin.qq.com/s?__biz=MzkzMDE4MDM2NQ==&mid=2247484090&idx=1&sn=7112ad4cbf5e7467608bbf6695f7e65d&chksm=c27f7ed8f508f7ceaf938b07d9f9efbc0cefdc7e89a217455ad738f512771fa4d0ca1cd43929&scene=178&cur_album_id=1893764190448746499#rd)

------

### 段错误产生原因

#### 1.访问不存在的内存地址

如下面代码，ptr没有申请空间就直接拷贝数据：

```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   char *ptr = NULL;
   //This is the wrong implementation：
   strncpy(ptr, "abc", 3);//ptr没有申请空间就直接使用

   //The right way:
   //ptr = (char *)malloc(sizeof(char) * 10);
   //memset(ptr, 0, 10);
   //strncpy(ptr, "abc", 3);

   return 0;
}
```

#### 2.访问只读的内存地址

错误做法：往字符串常量空间拷贝新的数据

```
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *ptr = "test";
    strcpy(ptr, "TEST1");

    return 0;
}
```

#### 3.访问系统保护的内存地址

如：

```
#include <stdio.h>

int main(int argc, char *argv[])
{
    int *ptr = (int *)0;
    *ptr = 100;

    return 0;
}
```

#### 4.栈溢出

如：

```
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    main(argc, argv);
}
```

### 初学时两种常用的段错误调试方法

#### 1.使用printf输出调试信息

这个是看似最简单但往往很多情况下是十分有效的调试方式，也许可以说是程序员用的最多的调试方式。简单来说，就是在程序的重要代码附近加上printf输出信息，这样可以跟踪并打印出段错误在代码中最可能出现的位置。



##### 使用案例：

以下面这段错误代码为例：

```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   char *ptr = NULL;
   //This is the wrong implementation：
   strncpy(ptr, "abc", 3);//ptr没有申请空间就直接使用

   return 0;
}
```

可以在代码中添加printf调试信息：

```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("line:%d\n", __LINE__); //单纯打印代码行数
   char *ptr = NULL;
   //This is the wrong implementation：
   printf("line:%d\n", __LINE__); //单纯打印代码行数
   strncpy(ptr, "abc", 3);//ptr没有申请空间就直接使用
    printf("line:%d\n", __LINE__); //单纯打印代码行数

   return 0;
}
```

编译运行后，会有如下输出：

```
line:7
line:10
Segmentation fault (core dumped)
```

通过日志信息，就可以看到strncpy(ptr, "abc", 3);语句没有被执行，我们就可以根据定位到的位置来排除ptr是否是未分配空间或者分配的空间不足引发的问题

#### 2.使用gcc和gdb

##### 调试步骤：

1、为了能够使用gdb调试程序，在编译阶段加上-g参数,还是以下面这段错误代码为例：

```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   char *ptr = NULL;
   //This is the wrong implementation：
   strncpy(ptr, "abc", 3);//ptr没有申请空间就直接使用

   return 0;
}
```

编译代码添加-g选项

```
gcc -g -o test test.c
```

编译出test程序，然后用gdb调试：

```
linux@linux:~/test$ gdb ./test
GNU gdb (Ubuntu 8.1-0ubuntu3) 8.1.0.20180409-git
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./test...done.
(gdb) r
Starting program: /home/linux/test/test 

Program received signal SIGSEGV, Segmentation fault.
0x0000555555554611 in main (argc=1, argv=0x7fffffffe528) at test.c:9
9                               strncpy(ptr, "abc", 3);//ptr没有申请空间就直接使用
(gdb) quit
A debugging session is active.

        Inferior 1 [process 15829] will be killed.

Quit anyway? (y or n) y
```

从输出看出，程序到SIGSEGV信号，触发段错误，并提示地址0x0000555555554611以及代码第9行出错。

当然，还有利用core文件和gdb配置配合调试、使用objdump以及catchsegv命令的其他更为复杂的调试手段，这里就不展开讲。





































































































































































