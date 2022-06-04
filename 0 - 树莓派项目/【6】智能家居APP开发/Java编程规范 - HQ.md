# Java编程规范 - HQ

[TOC]

------

#### 注意

- 

------

## JAVA 项目编程规范 

### 一、命名规范

**1、 项目名全部小写**

**2、 包名全部小写**

**3、 类名首字母大写** ，如果类名由多个单词组成， **每个单词的首字母都要大写。**

如： public class MyFirstClass{}

**4、 变量名、方法名首字母小写** ，如果名称由多个单词组成， **每个单词的首字母都要大写。**

如： int index=0;

public void toString(){}

**5、 常量名全部大写**

如： public static final String GAME_COLOR= ” RED ” ;

6 、所有命名规则必须遵循以下规则：

1) 名称只能由字母、数字、下划线、 $ 符号组成

2) 不能以数字开头

3) 名称不能使用 JAVA 中的关键字。

4) ==坚决不允许出现中文及拼音命名。==

参考例程

```java
/**
* Java编码格式个人推荐，参考JDK源码和Hyperic HQ源码（原spring旗下著名开源软件，现vmware）。
* @author lihzh(苦逼coder)
* 本文地址：http://mushiqianmeng.blog.51cto.com/3970029/737120
*/
public class CodeRule {
     
    //声明变量，等号两边有空格。
    private static int i = 1;
     
    //方法声明，右括号和左大括号中间有空格。
    public static void main(String[] args) {
        //if语句，比较连接符(>)左右有空格，小括号和大括号中间有空格。
        //if 与 左括号中间有空格
        if (i > 0) {
            System.out.println(i);
        }
        //两个条件的连接(&&)，左右有空格。
        if (i > 0 && i < 2) {
            System.out.println(i);
        }
         
        //if..else 语句两种格式
        //1.参考JDK，个人使用方式，else跟大括号，前后都有空格
        if (i > 0 && i < 2) {
            System.out.println(i);
        } else if (i > 2) {
            System.out.println(i + 1);
        } else {
            System.out.println(i);
        }
        //2.参考Hyperic HQ源码, else另起一行，后仍有空格
         if (i == 1) {
             System.out.println(i);
         }
         else {
             System.out.println(i);
         }
          
         //while语句，与if语句类型，while与括号中间有空格，括号内格式与if相同
         while (i > 0 && i < 2) {
             System.out.println(i);
             i++;
         }
          
         //for语句，两种格式
         //1.参考Hyperic HQ，个人使用方式。分号后带空格，每个子语句中，连接符左右都带空格。
         //for与括号中间带空格，大小括号中间带空格。
         for (int j = 0; j < 10; j++) {
             System.out.println(i);
         }
         //2.参考JDK，区别在于子语句中，连接符左右无空格。
         for (int j=0; j<10; j++) {
             System.out.println(i);
         }
          
         //+-*/，格式，四则运算符号前后有空格。
         //在JDK的有些代码里，在方法调用的参传递或在判断语句中存在的四则运算中，四则运算符号前后无空格。
         //为了不造成困扰和混淆，个人为均保留空格。
         int a = 1 + 2;
         int b = 1 - 2;
         int c = 1 * 2;
         int d = 1 / 2;
          
         //三元表达式格式，每个符号中间均有空格
         int j = i > 2 ? 1 : -1;
          
         //方法声明和调用，用逗号分隔的参数，逗号后有空格。
         sum(a, b);
         sum(c + d, j);
    }
     
    //方法声明，多个参数，逗号后有空格
    private static int sum(int i, int j) {
        return i + j;
    }
     
}
```

 

### 二、注释规范

**1、** **类注释**

在每个类前面必须加上类注释，注释模板如下：

```
/**

 \* Copyright (C), 2006-2010 , ChengDu Lovo info . Co., Ltd .

 \* FileName: Test.java

 \* 类的详细说明

 *

 

 \* @author 类创建者姓名

 \* @Date   创建日期

 \* @version 1.00

 */
```

 **2、** 属性注释

在每个属性前面必须加上属性注释，注释模板如下：

```
/**

*提示信息 

*/

private String strMsg = null;
```

 **3、** 方法注释

在每个方法前面必须加上方法注释，注释模板如下：

```
/**

 \* 类方法的详细使用说明

 *

 \* @param  参数 1 参数 1的使用说明

 \* @return 返回结果的说明

 \* @throws 异常类型 . 错误代码 注明从此类方法中抛出异常的说明

 */
```

**4、** **构造方法注释**

在每个构造方法前面必须加上注释，注释模板如下：

```
/**

 \* 构造方法的详细使用说明

 *

 \* @param  参数 1 参数 1的使用说明

 \* @throws 异常类型 . 错误代码 注明从此类方法中抛出异常的说明

 */
```

 **5、** **方法内部注释**

在方法内部使用单行或者多行注释，该注释根据实际情况添加。

```
如： // 背景颜色

Color bgColor = Color.RED;

```



### 三、基本语法

编写 Java 程序时，应注意以下几点：

**大小写敏感** ： ==Java 是大小写敏感的== ，这就意味着标识符 Hello 与 hello 是不同的。

==**类名** ：对于所有的类来说，类名的首字母应该大写 。== 如果类名由若干单词组成，那么每个单词的首字母应该大写，例如 MyFirstJavaClass 。

==**方法名** ：所有的方法名都应该以小写字母开头 。==如果方法名含有若干单词，则后面的每个单词首字母大写。

==**源文件名** ：源文件名必须和类名相同。== 当保存文件的时候，你应该使用类名作为文件名保存（切记 Java 是大小写敏感的），文件名的后缀为 .java 。（如果文件名和类名不相同则会导致编译错误）。

**主方法入口** ：所有的 Java 程序由 **public static void main(String []args)** 方法开始执行。

 

#### Java 标识符

Java 所有的组成部分都需要名字。类名、变量名以及方法名都被称为标识符。

关于 Java 标识符，有以下几点需要注意：

- 所有的标识符都应该以字母（ A-Z 或者 a-z ） , 美元符（ $ ）、或者下划线（ _ ）开始
- 首字符之后可以是任何字符的组合
- 关键字不能用作标识符
- 标识符是大小写敏感的
- 合法标识符举例： age 、 $salary 、 _value 、 __1_value
- 非法标识符举例： 123abc 、 -salary

 





































































































































































