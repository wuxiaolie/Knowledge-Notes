# 静态库与动态库 - HQ

[TOC]

------

#### 注意

- [参考文章1 - 未摘录](https://www.cnblogs.com/sunsky303/p/7731911.html)
- [参考文章2 - 未摘录](https://blog.csdn.net/wk_bjut_edu_cn/article/details/81735956)

------

### 库的制作

#### 静态库的制作

格式  xxxx.a

1. `gcc calcufuncs.c -c` 生成xxx.o文件
2. `ar rcs libcalcufunc.a calcufuncs.o` xxx.o文件生成xxx.a静态库文件

#### 动态库的制作

格式  xxxx.so

`gcc -shared -fpic calcufuncs.c -o libcalc.so`

> -shared 指定生成动态库
>
> -fpic 标准，fPIC 选项作用于编译阶段,在生成目标文件时就得使用该选项,以生成位置无关的代码。



### 库的使用

#### 静态库使用

`gcc calculatorT.c -lcalcufunc -L ./ -o mainProStatic` 

> -lcalcufunc -l（小写l）是指定要用的动态库，库名砍头去尾，只要用中间的名字
>
> -L告诉gcc编译器从-L指定的路径去找静态库，默认是从/usr/lib /usr/local/lib去找

#### 动态库使用

`gcc calculatorT.c -lcalc -L ./ -o mainProDy` 

带动态库的程序，可以指定该程序运行时候，在LD_LIBRARY_PATH 所指定的路径去找库文件

`export LD_LIBRARY_PATH="/home/pi/back/test"`



### linux动态库(.so)搜索路径(目录)设置方法

**在Linux 中，动态库的搜索路径除了默认的搜索路径外，还可通过三种方法来指定：**

方法一：在配置文件/etc/ld.so.conf中指定动态库搜索路径；

方法二：通过环境变量LD_LIBRARY_PATH指定动态库搜索路径；

方法三：在编译目标代码时指定该程序的动态库搜索路径。

众所周知，==Linux动态库的默认搜索路径是/lib和/usr/lib==。动态库被创建后，一般都复制到这两个目录中。

当程序执行时需要某动态库，并且该动 态库还未加载到内存中，则系统会自动到这两个默认搜索路径中去查找相应的动态库文件，然后加载该文件到内存中，这样程序就可以使用该动态库中的函数，以及该动态库的其它资源了。

**在Linux 中，动态库的搜索路径除了默认的搜索路径外，还可以通过以下三种方法来指定。** 

#### 方法一：在配置文件/etc/ld.so.conf中指定动态库搜索路径。

`vi /etc/ld.so.conf`

添加 lib目录 ldconfig

#### 方法二：通过环境变量LD_LIBRARY_PATH指定动态库搜索路径。

`export LD_LIBRARY_PATH=”LD_LIBRARY_PATH:/opt/”`

#### 方法三：在编译目标代码时指定该程序的动态库搜索路径。

还可以在编译目标代码时指定程序的动态库搜索路径。

通过gcc 的参数 ”-Wl,-rpath,” 指定

==其中方法三可以避免安装部署的麻烦==

**方法三示例**

假设main.cpp,hello.h,hello.cpp,其中main.cpp调用了hello类中的方法

1、生成hello.so

 `g++ -shared hello.cpp -o libhello.so`

2、编译main.cpp,并链接,并指定运行时libhello.so的位置

 `g++ main.cpp -lhello -L./ -Wl,-rpath=./ -o main` 

> 值得一提的是,如果采用带版本号的库,例如libhello.so.2
>
> 链接命令可使用`g++ main.cpp libhello.so.2 -L./ -Wl,-rpath=./ -o main` 

3、加入第二个so库

`g++ main.cpp -L./second/ -Wl,-rpath=./second/ -lsecond -L./hello/ -Wl,-rpath=./hello/ -lhello -o main`

> ps,遇到过一个奇怪的问题,就是假设libhello.so还用到了libother.so,由于在/etc/ld.so.conf里配置错误了libother.so的目录路径,导致一直产生undefined reference to错误,但是在工程里对libother目录路径配置是正确的,有可能于查找路径顺序有关。
>





































































































































































