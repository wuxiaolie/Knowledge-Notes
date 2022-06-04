## 知识便条 - 汇总记录常用知识点 - HQ

[TOC]

------

#### 注意

- 

------

## PowerVim快捷键

**配置：**每个人都可以在这个基础上进行修改，改成一个属于自己的PowerVim。

* 改变快捷键的方式在.vimrc
* 可以添加支持代码补全的语言，你可以在.vim/dictionary文件下添加该编程语言的补全关键字文本，并且在.vimrc上添加一下dict

PowerVim的快捷键以`;`为开始
这里列出的快捷键是PowerVim配置的，vim通用的快捷键就不一一列出。

```
正常模式下的快捷键（非插入模式）
;n              // 打开文件目录树显示在屏幕左侧
;m              // 打开当前函数和变量目录树显示在屏幕右侧
;h              // 光标移动到左窗口 
;l              // 光标移动到右窗口
;k              // 光标移动到上窗口
;j              // 光标移动到下窗口 以上四个快捷键特别是打开多个窗口情况下。使用这个快捷键组合非常实用
;w              // 保存文件
;u              // 向上翻半屏
;d              // 向下翻半屏
;1              // 光标快速移动到行首
;2              // 光标快速移动到行末
;a              // 快速切换.h和cpp文件，写C++的时候很方便
;e              // 打开一个新文件
;z              // 切回shell交互命令，输入fg在切回vim，非常实用
;s              // 水平分屏，并打开文件目录选取想打开的文件，如果想新建文件，;e 就好 
;v              // 竖直分屏，并打开文件目录选取想打开的文件，如果想新建文件，;e 就好 
;fw             // 查找项目内关键字，前提是你的系统已经按照了ACK 
;ff             // 查找项目内文件名 
;gt             // 跳转到变量或者函数定义的地方，前提是安装ctags，并且在在PowerVim输入 ;tg命令 Jump to the definition of the keyword where the cursor is located, but make sure you have make ctags
;gr             // 跳回，对应着;gt
;tg             // 对当前目录打ctag 
;y              // 保存当前选中的目录到系统剪切板，前提是vim支持系统剪切板的寄存器
;gg             // 按顺序光标跳转各个窗口

// 一下快捷键是不用;的，直接在 非插入模式 下输入
e               // 快速删除光标所在的词 
tabc            // 关闭当前tab，可以用:tabnew来打开一个新的tab Close tab, of course you should :tabnew a file first. 
F1              // 编译并运行C++文件，自己写的C++例子的时候一键编译。前提手动在当前目录建一个bin文件夹，这是用来存放编译产生的执行文件 
F1              // 编译Java文件
F2              // 运行Java编译的class文件，一般如果要编译并运行Java文件 按F1编译，在按F2运行
gc              // 快速注释选中的块（是visual模式下选中的块） 
gcc             // 快速当前行
{               // 光标向上移动一个代码块
}               // 光标向下移动一个代码块
di(             // 删除括号里的内容
di{             // 删除花括号里的内容
```





## Linux查找命令

### 常用指令

| 指令                       | 功能                                                         |
| -------------------------- | ------------------------------------------------------------ |
| `file xxx`                 | 查看文件属性                                                 |
| `ps -aux | grep xxx.out`   | 筛选进程                                                     |
| `grep xxx * -nir`          | 在所有的文件当中去匹配xxx字段（*表示所有文件，n显示行号，i不区分大小写，r递归查找） |
| `md5sum xxx`               | 计算xxx文件的md5值（适用于拷贝后，判断文件是否相同）         |
| `du xxx -h`                | 计算xxx文件大小，-h表示以合适的方式显示（KB,M,G）            |
| `uname -r`                 | 查看内核版本                                                 |
| `df -T`                    | 查看文件系统                                                 |
| `su - root`                | 切换到root用户                                               |
| `cat /proc/cpuinfo`        | 查看cup信息                                                  |
| `tar -xzf xxx.tar.gz`      | 库包解压指令                                                 |
| `sudo -i`                  | 切换到root用户                                               |
| `su xx`                    | 切换到xx用户                                                 |
| `sync`                     | 安全退出U盘前在终端执行sync来同步数据                        |
| `ctrl+shift+v`             | linux中的粘贴                                                |
| `sudo apt-get remove xxx ` | 卸载软件xxx                                                  |
|                            |                                                              |
|                            |                                                              |
|                            |                                                              |
|                            |                                                              |
|                            |                                                              |
|                            |                                                              |
|                            |                                                              |
|                            |                                                              |
|                            |                                                              |
|                            |                                                              |
|                            |                                                              |
|                            |                                                              |
|                            |                                                              |
|                            |                                                              |

### man手册

首先man分为八个目录，每个目录用一个数字表示

- 1.可执行程序
- 2.系统调用
- 3.库函数
- 4.特殊文件
- 5.文件格式和规范
- 6.游戏
- 7.杂项，包括宏包和规范
- 8.系统管理命令

### 文件检索

1. `find /path/to/directory/ -name '*.py'`：搜索某个文件路径下的所有`*.py`文件
2. `grep xxx`：从`stdin`中读入若干行数据，如果某行中包含`xxx`，则输出该行；否则忽略该行。（过滤）
   - `find ../homework/ -name '*.cpp' | xargs cat | grep 'acs_2663'`
   - `find . -name '*.py' | xargs cat | grep 'thrift' | wc -l > ans2.txt`
3. ==`ag xxx`：搜索当前目录下的所有文件，检索`xxx`字符串==
4. `wc`：统计行数、单词数、字节数
   - 既可以从`stdin`中直接读入内容；也可以在命令行参数中传入文件名列表；
   - `wc -l`：统计行数
   - `wc -w`：统计单词数
   - `wc -c`：统计字节数
5. `tree`：展示当前目录的文件结构

   - `tree /path/to/directory/`：展示某个目录的文件结构
   - `tree -a`：展示隐藏文件
6. `cut`：分割一行内容
   - 从`stdin`中读入多行数据
   - `echo $PATH | cut -d ':' -f 3,5`：输出`PATH`用`:`分割后第3、5列数据
   - `echo $PATH | cut -d ':' -f 3-5`：输出`PATH`用`:`分割后第3-5列数据
   - `echo $PATH | cut -c 3,5`：输出`PATH`的第3、5个字符
   - `echo $PATH | cut -c 3-5`：输出`PATH`的第3-5个字符
   - `cat scores.txt | cut -d ' ' -f 1 | sort > names.txt`：将文件` scores.txt`内第一列内容按字典序从小到大排列写入文件`names.txt`
7. `sort`：将每行内容按字典序排序

   - 可以从`stdin`中读取多行数据
   - 可以从命令行参数中读取文件名列表
8. `xargs`：将`stdin` 中的数据用空格或回车分割成命令行参数
   - `find . -name '*.py' | xargs cat | wc -l`：统计当前目录下所有python文件的总行数
   - `find . -name '*.py' | xargs rm`：删除当前目录下所有的`.py`文件

### 查找指令

#### find

```shell
find
目的：查找符合条件的文件

1）在那些目录中查找
2）查找的内容

格式：  find    目录名    选项    查找条件

举例：
1）find /work/001_linux_basic/dira/ -name "test1.txt"
说明:
	a)/work/001_linux_basic/dira/指明了查找的路径
	b)-name表明以名字来查找文件
	c)"test1.txt"，就指明查找名为test1.txt的文件
同理：
	find /work/001_linux_basic/dira/  -name "*.txt"	
	查找指定目录下面所以以.txt结尾的文件，其中*是通配符。
	find /work/001_linux_basic  -name "dira"	
	查找指定目录下面是否存在dira这个目录，dira是目录名。

注意：
1）如果没有指定查找目录，则为当前目录。
	find . -name "*.txt"   其中.代表当前路径 
	find  -name "*.txt"
	都是一样的功能
	
2）find还有一些高级的用法，如查找最近几天(几个小时)之内(之前)有变动的文件
 find /home -mtime -2  查找/home目录下两天内有变动的文件	
```

#### grep

```shell
grep
目的：使用grep命令来查找文件中符合条件的字符串
格式：grep  [选项]	 [查找模式]  [文件名]

查找字符串时希望显示如下内容：
1）所在的文件名----grep查找时默认已经显示目标文件名
2）所在的行号------使用-n选项

grep -rn "字符串"  文件名
r(recursive)：递归查找
n(number)：显示目标位置的行号
字符串:要查找的字符串
文件名:要查找的目标文件，如果是*则表示查找当前目录下的所有文件和目录	

举例：
	grep -n "abc" test1.txt   在test1.txt中查找字符串abc
	grep -rn "abc" *          在当前目录递归查找字符串abc
	
注意：
1）可以加入-w全字匹配。
```

#### file

```shell
file
目的：识别文件类型
格式： file   文件名

linux下一切皆文件

举例：
file ~/.bashrc     为ASCII 编码的text类型
file ~/.vimrc      为UTF-8 Unicode 编码的text类型
file ~/Pictures/*  如图形文件JPEG/PNG/BMP格式
file ~/100ask/     为directory表明这是一个目录
file /bin/pwd      出现 ELF 64-bit LSB executable，即为ELF格式的可执行文件
file /dev/*        出现character special(字符设备文件)、 block special(块设备文件)等
```

#### which和whereis

```shell
which和whereis
目的：查找命令或应用程序的所在位置
格式：which  命令名/应用程序名

在终端上执行pwd实际上是去执行了/bin/pwd
举例：
	which pwd 定位到/bin/pwd
	which gcc 定位到/usr/bin/gcc
	whereis  pwd查找到可执行程序的位置/bin/pwd和手册页的位置/usr/share/man/man1/pwd.1.gz
```

### 压缩解压

#### .bz2 

解压

```
bzip2 -d FileName.bz2 
bunzip2 FileName.bz2 　　 
```

压缩

```
bzip2 -z FileName 
```

#### .tar.bz2 

解压

```
tar jxvf FileName.tar.bz2 
tar --bzip xvf 
```

压缩

```
tar jcvf FileName.tar.bz2 DirName
```

























































































































































