## C 结构体 - HQ

[TOC]

------

#### 注意

- 参考资料  [菜鸟教程C 结构体](https://www.runoob.com/w3cnote/c-structures-intro.html)

------

# 结构体知识 - 个人整理

### C99标准下的Struct的初始化方法

- 我们在阅读GNU/Linux内核代码时，我们会经常遇到这样一种特殊的结构初始化方式，这种方式称为指定初始化。这种初始化方法源自C99标准。

  - ```cpp
    static struct usb_driver usb_storage_driver = {   
        .owner = THIS_MODULE,      
        .name = \"usb-storage\",      
        .probe = storage_probe,      
        .disconnect = storage_disconnect,      
        .id_table = storage_usb_ids, };   
    
    ```

- 下文摘录了C Primer Plus第五版中相关章节的内容，从而就可以很好的理解Linux内核采用这种方式的优势就在于由此初始化不必严格按照定义时的顺序。

- 已知一个结构，定义如下:

  - ```cpp
    struct Book   
    {     
        char title[MAXTITLE];     
        char author[MAXAUTHOR];     
        float value;   
    };     
    ```

- C99支持结构的指定初始化项目，其语法与数组的指定初始化项目近似。只是，结构的指定初始化项目使用点运算符和成员名（而不是方括号和索引值）来标识具体的元素。例如，只初始化book结构的成员value，可以这样做：

  - ```cpp
    struct Book surprise =   
    {  
        .value = 10.99   
    };     
    ```

- 可以按照任意的顺序使用指定初始化项目：

  - ```cpp
    struct Book gift =   
    {   
        .value = 25.99,                    
        .author = \"James Broadfool\",                    
        .title = \"Rue for the Toad\"  
    };    
    ```

- 正像数组一样，跟在一个指定初始化项目之后的常规初始化项目为跟在指定成员后的成员提供了初始值。另外，对特定成员的最后一次赋值是它实际获得的值。例如，考虑下列声明：

  - ```cpp
    struct Book gift =   
    {   
        .value = 18.90,                    
        .author = \"hilionna pestle\",                    
        0.25  
    };    
    ```

- 这将把值0.25赋给成员value，因为它在结构声明中紧跟在author成员之后。新的值0.25代替了早先的赋值18.90。



### 结构体初始化

#### 1、指定初始化

- 点号 + 赋值符号
  - `struct A a={.b = 1,.c = 2};`

- 冒号
  - `struct A a={b:1,c:2}；`

- Linux内核喜欢用`.fieldname=value`的方式进行初始化，使用指定初始化，一个明显的优点是成员初始化顺序和个数可变，并且扩展性好，比如增加字段时，避免了传统顺序初始化带来的大量修改。

#### 2、顺序初始化

- 是我们最常用的初始化方式，因为书写起来较为简约，但相对于指定初始化，无法变更初始化顺序，灵活性较差。
  - `struct A a1={1,2};`

#### 3、构造函数初始化

- 常见于C++代码中，因为C++中的struct可以看作class，结构体也可以拥有构造函数，所以我们可以通过结构体的构造函数来初始化结构体对象。给定带有构造函数的结构体：

  - `struct A a(1,2);`

  - ```cpp
    struct A {
        int a;
    	int b;
        A(int a,int b) {
    		this->a=a;
    		this->b=b;
    	};
    }
    ```

  - ```cpp
    struct TreeNode {
    	int val;
    	TreeNode *left;
    	TreeNode *right;
    	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    ```

  - 注意： struct如果定义了构造函数的话，就不能用大括号进行初始化了，即不能再使用指定初始化与顺序初始化了。

  - 数组里的对象，不论是类对象（struct或者class），还是基础数据类型，如果没有给初始化列表，一律执行**值初始化**，即基础数据类型都初始化为0，类对象执行**默认构造函数**（**即不接受任何参数的构造函数**）。

### 结构体的赋值

结构体变量的赋值和初始化是不一样的，初始化是在变量定义的时候完成的，是属于变量定义的一部分，赋值是在变量定义完成之后想改变变量值的时候所采取的操作。

- 结构体变量的赋值是不能采用大括号的方式进行赋值的，例如下面的赋值是不允许的。

  - ```cpp
    struct A {
    int b;
    int c;
    }
    struct A a;
    //错误赋值
    a = {1,2};
    ```

#### 1、使用memset对结构体变量进行置空操作 (只能是POD的类型)

- 按照编译器默认的方式进行初始化（如果a是全局静态存储区的变量，默认初始化为0，如果是栈上的局部变量，默认初始化为随机值）
  - `struct A a;`
  - `memset(&a, 0, sizeof(a));`

#### 2、依次给每一个结构体成员变量进行赋值

- ```cpp
  struct A a;
  a.b = 1;
  a.c = 2;
  ```

#### 3、使用已有的结构体变量给另一个结构体变量赋值

- 结构体变量之间是可以相互赋值的

- ```cpp
  struct A a = {1,2};
  struct A aa;
  aa = a;   //将已有的结构体变量付给aa
  ```





# 结构体知识 - 菜鸟教程

## 1、概述

C 语言允许用户自己指定这样一种数据结构，它由不同类型的数据组合成一个整体，以便引用，这些组合在一个整体中的数据是互相联系的，这样的数据结构称为结构体，它相当于其它高级语言中记录。

声明一个结构休类型的一般形式如下：

```c
struct 结构体名
{成员列表};
```

结构体名，用作结构体类型的标志，它又称 结构体标记，大括号内是该结构体中的各个成员，由它们组成一个结构体，对各成员都应进行类型声明如：

```c
类型名 成员名;
```

也可以成员列表称为域表，第一个成员也称为结构体中的一个域。成员名定名规则写变量名同。

```c
struct student
{
    int num;
    char name[20];
    char sex;
    int age;
    float score;
    char addr[30];
};
```

## 2、定义结构体类型变量的方法

前面只是指定了一个结构体类型，它相当于一个模型，但其中并无具体数据，系统对之也不分配实际内存单元，为了能在程序中使用结构类型的数据，应当定义结构体类型的变量，并在其中存放具体的数据，可以采取以下3种方法定义结构体类型变量。

### （1）先声明结构体类型再定义变量名

如上面已定义了一个结构体类型 struct student，可以用它来定义变量。如：

```c
struct student{  //结构体类型名
    ...
    ...
    ...
}student1, student2 //结构体变量名
```

定义了 student1, student2 为 struct student 类型的变量。

在定义了结构体变量后，系统会为之分配内存单元。例如 student1 和 student2 在内存中各占 59 个字节。

应当注意，将一个变量定义为标准类型（基本数据类型）与定义为结构体类型不同之处在于后者不仅要求指定变量为结构体类型，而且要求指定为某一特定的结构体类型（例如 struct student 类型），因为可以定义出许多种具体的结构体类型。而在定义变量为整形时，只需指定为 int 型即可。

### （2）在声明类型的同时定义变量

例如：

```c
struct student
{
    int num;
    char name[20];
    char sex;
    int age;
    float score;
    char addr[30];
}student1, student2;
```

它的作用与第一种方法相同，即定义了两个 struct student 类型的变量 student1, student2 这种形式的定义的一般形式为

```c
struct 结构体名
{
    成员表列
}变量名表列;
```

### （3）直接定义结构类型变量

其一般形式为:

```c
struct
{
    成员表列
}变量名表列;
```

即不出现结构体名。

关于结构体类型，有几点要说明：

- a. 类型与变量是不同的概念，不是混同，只能对变量赋值，存取或运算，而不能对一个类型赋值，存取或运算。在编译时，对类型是不分配空间的，只对变量分配空间。

- b. 对结构体中的成员（即 域）可以单元使用，它的作用与地位相当于普通变量。

- c. 成员也可以是一个结构体变量。如：

  ```c
  struct date // 声明一个结构体类型
  {
      int month;
      int day;
      int year;
  }
  
  struct student
  {
      int num;
      char name[20];
      char sex;
      int age;
      struct date birthday;
      char addr[30];
  }student1, student2;
  ```

  先声明一个 struct date 类型，它代表 日期 包括3个成员 month, day, year。然后在声明 struct student 类型时，将成员 birthday 指定为 struct date 类型。

- d. 成员名可以与程序中的变量名相同，二者不代表同一对象。

------

## 3、结构体变量的引用

**（1）不能将一个结构体变量作为一个整体进行输入和输出。**

只能对结构体变量中的各个成员分别进行输入输出。引用结构体变量中的成员的方式为：

```c
结构体变量名.成员名
```

例如 student1.num 表示 student1 变量中的 num 成员，即 student1 的 num 项，可以对变量的成员赋值。例如： student1.num = 10010;

**.** 是成员（分量）运算符，它在所有的运算符中优先级最高，因此可以把 student1.num 作为一个整体来看待。上面的赋值语句作用是将整数 10010赋给 student1 变量中的成员 num。

**（2）如果成员本身又属一个结构体类型，则要用若干个成员运算符，一级一级地找到最低一级的成员。只能对最低的成员进行赋值或存取以及运算。**

例如：结构体变量 student1 可以这样访问各成员：

```c
student1.num
student1.birthday.month
```

注意，不能用 student1.birthday 来访问 student1 变量中的成员 birthday，因为 birthday 本身是一个结构体变量。

（**3）对结构体变量的成员可以像普通变量一样进行各种运算（根据其类型决定可以进行的运算）。**

```c
student2.score = student1.score;
sum = student1.score + student2.score;
student1.age ++;
++ student1.age;
```

由于 **.** 运算符的优先级最高，因此 student1.age ++ 是对 student1.age 进行自加运算。而不是先对 age 进行自加运算。

**（4）可以引用结构体变量成员的地址。也可以引用结构体变量的地址。如：**

```c
scanf("%d", &student1.num);// 输入 student1.num 的值
printf("%o", &student1);// 输出 student1 的首地址
```

但不能用以下语句整体读入结构体变量如：

```c
scanf("%d,%s,%c,%d,%f,%s", &student1);
```

结构体变量的地址主要用于作函数参数，传递结构体的地址。

------

## 4、结构体变量的初始化

和其它类型变量一样，对结构体变量可以在定义时指定初始值。

## 实例

```c
#include <stdio.h>
struct student
{
    long int num;
    char name[20];
    char sex;
    char addr[30];
}a = {89031, "Li Lin", 'M', "123 Beijing Road"};
 
void main()
{
    printf("NO. : %ld\nname: %s\nsex: %c\naddress: %s\n", a.num, a.name, a.sex, a.addr);
}
```

------

## 5、结构体数组

一个结构体变量中可以存放一组数据（如一个学生的学号，姓名，成绩等数据）。如果有10个学生的数据需要参加运算，显然应该用数组，这就是结构体数组。结构体数组与以前介绍过的数据值型数组不同之处在于每个数组元素都一个结构体类型的数据，它们分别包括各个成员（分量）项。

### 5.1 定义结构体数组

和定义结构体变量的方法相仿，只需说明其为数组即可。

```c
struct student
{
    int num;
    char name[20];
    char sex;
    int age;
    float score;
    char addr[30];
};
struct student stu[3];
```

以上定义了一个数组 stu，其元素为 struct student 类型数据，数组有 3 个元素。也可以直接定义一个结构体数组。如：

```c
struct student
{
    int num;
    ....

}stu[3];

或

struct

{
    int num;
    　...
}stu[3];
```

### 5.2 结构体数组的初始化

与其它类型数组一样，对结构体数组可以初始化如：

```c
struct student
{
    int mum;
    char name[20];
    char sex;
    int age;
    float score;
    char addr[30];
}stu[3] = {{10101,"Li Lin", 'M', 18, 87.5, "103 Beijing Road"},
            {10101,"Li Lin", 'M', 18, 87.5, "103 Beijing Road"},
            {10101,"Li Lin", 'M', 18, 87.5, "103 Beijing Road"}};
```

定义数组 stu 时，元素个数可以不指定，即写成以下形式：

```c
stu[] = {{...},{...},{...}};
```

编译时，系统会根据给出初值的结构体常量的个数来确定数组元素的个数。

当然，数组的初始化也可以用以下形式：

```c
struct student
{
    int num;
    ...
};
struct student stu[] = {{...},{...},{...}};
```

即先声明结构体类型，然后定义数组为该结构体类型，在定义数组时初始化。

从以上可以看到，结构体数组初始化的一般形式是在定义数组的后面加上：

### 5.3 结构体数组应用举例

下面例子说明结构体数组的定义和引用。

## 实例

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
struct person
{
    char name[20];
    int count;
 
}leader[3] = {{"Li", 0},
            　{"Zhang", 0},
            　{"Fun", 0}};
 
void main()
{
    int i, j;
    char leader_name[20];
    for(i = 1; i<= 10;i++)
    {
        scanf("%s", leader_name);
        for(j=0;j<3;j++)
            if(strcmp(leader_name, leader[j].name) == 0)
                leader[j].count ++;
    }
    printf("\n");
    for(i=0;i<3;i++)
        printf("%5s: %d\n", leader[i].name, leader[i].count);
    system("pause");
}
```

运行结果如下：

```c
LI
Li
Fun
Zhang
Zhang
Fun
Li
Fun
Zhang
Li

   Li: 3
Zhang: 3
  Fun: 3
```

------

## 6、指向结构体类型数据的指针

一个结构体变量的指针就是该变量所占据的内存段的起始地址，可以设一个指针变量，用来指向一个结构体变量，此时该指针变量的值是结构体变量的起始地址。指针变量也可以用来指向结构体数组中的元素。

### 6.1 指向结构体变量的指针

指向结构体变量的指针的应用：

## 实例

```c
#include <string.h>
#include <stdio.h>
#include <stdlib.b>
 
struct student
{
    long num;
    char name[20];
    char sex;
    float score;
};
 
void main()
{
    struct student stu_1;
    struct student *p;
    p = &stu_1;
    stu_1.num = 89101;
    strcpy(stu_1.name, "Li Lin");
    stu_1.sex = 'M';
    stu_1.score = 89.5;
    printf("NO. :%ld\nname: %s\nsex:%c\nscore:%f\n", stu_1.num, stu_1.name, stu_1.sex, stu_1.score);
    printf("NO. :%ld\nname: %s\nsex:%c\nscore:%f\n", (*p).num, (*p).name, (*p).sex, (*p).score);
    system("pause");
}
```

在主函数中声明了 struct student 类型，然后定义了一个 struct student 类型的变量，stu_1 同时又定义一个指针变量 p ，它指向一个 struct student 类型的数据，在函数的执行部分将结构体变量 stu_1 的起始地址赋给指针变量 p ，也就是使 p 指向 stu_1 然后对 stu_1 的各成员赋值，第二个 printf 函数也是用来输出 stu_1 各成员的值，但使用的是 (*p).num 这样的形式， (*p) 表示 p 指向的结构体变量，(*p).num 是 p 指向的结构体变量中的成员 num 。注意 *p 两侧的括弧不可省略，因为成员运算符 '.' 优先于 '*' 运算符，*p.num 就等价于 *(p.num)

运行结果如下：

```c
NO. :89101
name: Li Lin
sex:M
score:89.500000
NO. :89101
name: Li Lin
sex:M
score:89.500000
```

可以看到两个 printf 输出的结果相同。

在C语言中，为了使用方便和使之直观，可以把 (*p).num 改用 p->num 来代替，它表示 *p 所指向的结构体变量中的 num 成员，同样，(*p).name 等价于 p->name。

也就是说以下三种形式等价：

- a. **结构体变量.成员名**
- b. **(\*p).成员名**
- c. **p-> 成员名**

上面的最后一个 printf 函数输了项可以改写为:

```c
printf("NO. :%ld\nname: %s\nsex:%c\nscore:%f\n",p->num, p->name, p->sex, p->score);
```

其中 **->** 称为指向运算符。

分析以下几种运算符:

- p -> n 得到 p 指向的结构体变量中的成员 n 的值
- p -> n ++ 得到 p 指向的结构体变量中的成员 n 的值，用完值后使它加 1
- ++p -> n 得到 p 指向的结构体变量中的成员 n 的值使之加 1 （先加）

### 6.2 指向结构体数组的指针

以前介绍过可以使用指向数组或数组元素的指针和指针变量，同样，对结构体数组及其元素也可以用指针变量来指向。

指向结构体数组的指针的应用。

## 实例

```c
#include <stdio.h>
#inlcude <stdlib.h>
 
struct student
{
    int num;
    char name[20];
    char sex;
    int age;
};
 
struct student stu[3] = {{10101, "Li Lin", 'M', 18},
                        　{10102, "Zhang Fun", 'M', 19},
                        　{10103, "Wang Min", 'F', 20}};
 
int main()
{
    struct student *p;
    printf("No.    name        sex        age\n");
    for(p=stu; p<stu+3;p++)
        printf("%5d %-20s %2c %4d\n", p->num, p->name, p->sex, p->age);
    system("pause");
}
```

运行结果如下：

```c
No.    name        sex        age
10101 Li Lin                M       18
10102 Zhang Fun        M       19
10103 Wang Min          F        20
```

**注意以下两点：**

（

1）如果 p 的初值为 stu，即指向第一个元素，则 p + 1 后指向下一个元素的起始地址。例如：

(++p) -> num 先使 p 自加 1 ，然后得到它指向的元素中的 num 成员的值（即10102）。

(p++) ->num 先得到 p->num 的值（即10101），然后使 p 自加 1 ，指向 stu[1]。

注意以上二者的不同。

（2）程序已定义了指针 p 为指向 struct student 类型数据的变量，它只能指向一个 struct student 型的数据（p 的值是 stu 数组的一个元素的起始地址），而不能指向 stu 数组元素中的某一成员，（即 p 的地址不能是成员地址）。例如，下面是不对的：

```c
p = &stu[1].name
```

编译时将出错。千万不要认为反正 p 是存放地址的，可以将任何地址赋给它。如果地址类型不相同，可以用强制类型转换。例如：

```c
p = (struct student *)&stu[1].name;
```

此时，在 p 中存放 stu[1] 元素的 name 成员的起始地址。

### 6.3 用结构体变量和指向结构体的指针作函数参数

将一个结构体变量的值传递给另一个函数，有3个方法：

- （1）用结构体变量的成员作参数，例如：用 stu[1].num 或 stu[2].name 作函数实参，将实参值传给形参。用法和用普通变量作实参是一样的，属于 值传递 方式。应当注意实参与形参的类型保持一致。
- （2）用结构体变量作参数。老版本的C系统不允许用结构体变量作实参，ANSI C取消了这一限制。但是用结构体变量作实参时，采取的是 值传递 的方式，将结构体变量所占的内存单元全部顺序传递给形参。形参也必须是同类型的结构体变量。在函数调用期间形参也要占用内存单元。这种传递方式在空间和时间上开销较大，如果结构体的规模很大时，开销是很可观的，此外由于采用值传递方式，如果在执行被调用函数期间改变了形参（也是结构体变量）的值，该值不能返回主调函数，这往往造成使用上的不便。因此一般较少用这种方法。
- （3）用指向结构体变量（或数组）的指针作实参，将结构体变量（或数组）的地址传给形参。

用结构体变量作函数参数。

## 实例

```c
#include <stdio.h>
#define FORMAT "%d\n%s\n%f\n%f\n%f\n"
 
struct student
{
    int num;
    char name[20];
    float score[3];
};
 
void print(struct student stu)
{
    printf(FORMAT, stu.num, stu.score[0], stu.score[1], stu.score[2]);
    printf("\n");
}
 
void main()
{
    struct student stu;
    stu.num = 12345;
    strcpy(stu.name, "Li Li");
    stu.score[0] = 67.5;
    stu.score[1] = 89;
    stu.score[2] = 78.6;
    printf(stu);
}
```

将上面改用指向结构体变量的指针作实参。

## 实例

```c
#include <stdio.h>
#define FORMAT "%d\n%s\n%f\n%f\n%f\n"
 
struct student
{
    int num;
    char name[20];
    float score[3];
}stu = {12345, "Li Li", 67.5, 89, 78.6};
 
void print(struct student *p)
{
    printf(FORMAT, p->num, p->name, p->score[0], p->score[1], p->score[2]);
    printf("\n");
}
 
void main()
{
    print(&stu);
}
```

------

## 7、用指针处理链表

### 7.1 链表概述

链表是一种常见的重要的数据结构。它是动态地进行存储分配的一种结构。

链表有一个 头指针 变量，它存放一个地址，该地址指向一个元素，链表中每一个元素称为 结点，每个结点都应包括两个部分，一为用户需要用的实际数据，二为下一个结点的地址。可以看出，头指针 head 指向第一个元素，第一个元素又指向第二个元素，。。。。直到最后一个元素，该元素不再指向其他元素，它称为 表尾，它的地址部分放一个 NULL（表示 空地址）链表到此结束。

可以看到链表中各元素在内存中可以不是连续存放的，要找某一元素，必须先找到上一个元素，根据它提供的下一元素地址才能找到下一个元素。如果不提供 头指针 head 则整个链表无法访问。

可以看到。这种链表的数据结构，必须利用指针变量才能实现，即一个结点中应包含一个指针变量，用它存放下一结点的地址。

前面介绍了结构体变量，用它作链表中的结点是最合适的，一个结构体变量包含若干成员，这些成员可以是数值类型，字符类型，数组类型，也可以是指针类型，我们用这个指针类型成员来存放下一个结点的地址。例如可以设计这样一个结构体类型：

```c
struct student
{
    int num;
    float score;
    struct student *next;
};
```

其中成员 num 和 score 用来存放结点中的有用数据（用户需要用到的数据），next 是指针类型成员，它指向 struct student 类型数据（这是 next 所在结构体类型）。一个指针类型的成员既可以指向其他类型的结构体数据，也可以指向自己所在的结构体类型的数据。现在 next 是 struct student 类型中的一个成员，它又指向 struct student 类型的数据。用这种方法就可以建立链表。

请注意：只是定义一个 struct student 类型，并未实际分配存储空间，只有定义了变量才分配内存单元。

### 7.2 简单链表

下面通过一个例子来说明如何建立和输出一个简单链表:

## 实例

```c
#include <stdio.h>
#include <stdlib.h>
 
#define NULL 0
 
struct student
{
    long num;
    float score;
    struct student *next;
};
 
void main()
{
    struct student a, b, c, *head, *p;
    a.num = 99101; a.score = 89.5;
    b.num = 99103; b.score = 90;
    c.num = 99107; c.score = 85;//对结点的 num 和 score 成员赋值
    head = &a;//将结点 a 的起始地址赋给头指针 head
    a.next = &b;//将结点 b 的起始地址赋给 a 结点的 next 成员
    b.next = &c;
    c.next = NULL;// c 结点的 next 成员不存放其他结点地址
    p = head;//使 p 指针指向 a 结点
    do
    {
        printf("%ld %5.1f\n", p->num, p->score);// 输出 p 指向的结点的数据
        p = p->next;//使 p 指向下一结点
    }while(p != NULL);//输出完 c 结点后 p 的值为 NULL
    system("pause");
}
```

运行结果:

```c
99101  89.5
99103  90.0
99107  85.0
```

### 7.3 处理动态链表所需的函数

**（1）malloc 函数**

```c
void *malloc(unsigned int size);
```

作用是在内存的动态存储区中分配一个长度为 size 的连接空间。些函数的值（即返回值）是一个指向分配空间起始地址的指针（基类型为 void）。如果些函数未能成功地执行（例如内存空间不足）则返回空指针 NULL。

**（2）calloc 函数**

```c
void *calloc(unsigned n, unsigned size);
```

其作用是在内存的动态区存储中分配 n 个长度为 size 的连续空间。函数返回一个指向分配空间起始地址的指针，如果分配不成功，返回 NULL。 用 calloc 函数可以为一维数组开辟动态存储空间， n 为数组元素个数，每个元素长度为 size。

**（3）free 函数**

```c
void free(void *p);
```

其作用是释放由 p 指向的内存区，使这部分内存区能被其它变量使用， p 是最后一次调用 calloc 或 malloc 函数时返回的值。free 函数无返回值。 请注意：以前的C版本提供的 malloc 和 calloc 函数得到的是指向字符型数据的指针。ANSI C 提供的 malloc 和 calloc 函数规定为 void * 类型。

### 7.4 建立动态链表

所谓建立动态链表是指在程序执行过程中从无到有地建立起一个键表，即一个一个地开辟结点和输入各结点数据，并建立起前后相链的关系。

## 实例

```c
#include <stdio.h>
#include <stdlib.h>
 
#define NULL 0
#define LEN sizeof(struct student)
 
struct student
{
    long num;
    float score;
    struct student *next;
};
 
struct student *create()
{
    struct student *p1, *p2, *head;
    int num;
    float score;
    int n = 0;
 
    head = NULL;
 
    p1 = p2 = (struct student *)malloc(LEN);
 
    printf("please input num and score.\n");
    scanf("%d,%f", &p1->num, &p1->score);
 
    while(p1->num != 0)
    {
        n ++;
        if(n == 1)
            head = p1;
        else
            p2->next = p1;
        p2 = p1;
        p1 = (struct student *)malloc(sizeof(struct student));
 
        printf("please input num and score.\n");
 
        scanf("%d,%f", &p1->num, &p1->score);
    }
    p2->next = NULL;
    return head;
}
 
void printlist(struct student *head)
{
    struct student *p;
    p = head;
    if(head != NULL)
    {
        do
        {
            printf("num=%d score=%f\n", p->num, p->score);
            p = p->next;
        }while(p != NULL);
    }
}
 
void main()
{
    struct student *head;
    head = create();
    printlist(head);
    system("pause");
}
```

**以下是对链表的各种操作**

打印链表:

```c
void printlist(struct student *head)
{
    struct student *p;
    p = head;

    if(head != NULL)
    {
        do 
        {
            printf("num=%d score=%5.2f\n", p->num, p->score);
            p = p->next;
        } while (p != NULL);
    }
    /* while(p -> next != NULL)
    {
        printf("num=%d score=%f\n", p->num, p->score);
        p = p->next;
    }*/
}
```

删除节点:

```c
struct student *delNode(struct student *head, int num)
{
    printf("delNode.\n");
    struct student *p1, *p2;
    if(head == NULL)
    {
        printf("The List is NULL.\n");
    }
    else
    {
        p1 = head;
        while(p1->next != NULL && p1->num != num)
        {
            p2 = p1;
            p1 = p1->next;
        }
        if(p1->num == num)
        {
            if(p1 == head)
                head = p1->next;
            else
                p2->next = p1->next;
        }
        else
            printf("Can not find list num.\n");
    }
    return head;
}
```

更新节点:

```c
struct student *update(struct student *head, int index, int num, float score)
{
    printf("update.\n");
    struct student *p;
    if(head == NULL)
    {
        printf("The List is NULL.\n");
    }
    else
    {
        p = head;
        while(p->next != NULL && p->num != index)
        {
            p = p->next;
        }
        if(p->num == index)
        {
            p->num = num;
            p->score = score;
        }
        else
            printf("Can not find list index.\n");
    }
    return head;
}
```

增加节点:

```c
struct student *add(struct student *head, int index, int num, float score)
{
    printf("add.\n");
    struct student *p1, *p2, *p3;
    if(head == NULL)
    {
        printf("The List is NULL.\n");
    }
    else
    {
        p1 = p2 = head;
        while(p1->next != NULL && p1->num != index)
        {
            p1 = p1->next;
            p2 = p1;
        }
        if(p1->num == index)
        {
            p3 = (struct student *)malloc(LEN);
            p3->num = num;
            p3->score = score;

            if(p2->next == NULL)
            {
                p2->next = p3;
                p3->next = NULL;
            }
            else
            {
                p3->next = p2->next;
                p2->next = p3;   
            }
        }
        else
            printf("Can not find list index.\n");
    }
    return head;
}
```





































































































































































