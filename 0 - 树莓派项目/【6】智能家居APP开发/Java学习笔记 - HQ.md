# Java学习笔记 - HQ

[TOC]

------

#### 注意

- 

------

## Java知识整理

### 快捷键

- ALT+/ 显示建议    

- 按ctrl+1可生成try块



### 编译运行步骤

> <img src="assets/2daf9f151618852eb6893e31d3b862c7-31003-16515620727866" alt="img" style="zoom:50%;" />





## Java语法

**面向对象语言OOP三大特性——封装，继承，多态**

### 基础语法

- MyClass myClass=new MyClass();
- new的时候在堆中新建了一个对象。
- 这个对象是MyClass的实例。
- 其中myClass是该对象的引用。    

```java
    //输出
        System.out.println("Hello World");
        //快捷输出方式  "syso"+alt+/
        System.out.println("c="+c);
        System.out.println("a="+a + "b="+b +  "c="+c);
        System.out.println(a + "+" + b + "=" + c);
        //小数
        float f = (float)0.1;
        double d = 0.2;
        System.out.println("f="+f);
        System.out.println("d="+d);
        //if()嵌套
        if(g > 0){
            System.out.println("g是正整数");
            if(a == 1){
                System.out.println("它是正整数，就是1");
            }else{
                System.out.println("它是正整数，不是1");
            }
        }else{
            System.out.println("g是非正整数");
        }
        //switch()选择
        switch(a){
        
            case 1:
                System.out.println("这是1");
                break;
            case 110:
                System.out.println("这是110");
                break;
        }
        //for()循环 while()循环
        for(i=0;i<20;i++){
            System.out.println("1");
        }
        while(i>0){
            System.out.println("2");
            i--;
        }
        //数组
        //数组[]中不能有内容
        int[] q = {1,2,4};
        System.out.println(q[0]);
        System.out.println(q[1]);
        System.out.println(q[2]);
        //定义空数组
        int[] array = new int[3];
        int[] array2 = null;
        array2 = new int[3];
        //遍历数组，面向对象的特性，可直接输出大小
        for (w=0;w<array.length;w++){    
            array[w] = w;
            System.out.println(array[w]);
        }
        //方法
public class test2 {
    
    static void myPrintf()  //类似于C中的机构体函数指针void (*a)();
    {
        System.out.println("yanghaoqing");
    }
    void myPrintf2()    
    {
        System.out.println("yanghaoqing");
    }
    static void putAInt(int a)
    {
        System.out.println("输出了一个数："+a);
    }
    
    public static void main(String[] args) {
        myPrintf();   //函数定义类型为static,则在main中可直接调用
        putAInt(3);   
        test2 t = new test2();  //函数定义类型不是static，则需要这样（类似于C中的结构体变量）
        t.myPrintf2();  
    }
}    
        //输入类Scanner_P
        import java.util.Scanner;
public class test2 {
    
    public static void main(String[] args){
        
        Scanner sc = new Scanner(System.in);   //ctrl+shift+o  导入包
        int a;
        double f;
        String str;
        System.out.println("请输入一个整数");
        a = sc.nextInt();
        f = sc.nextFloat();
        System.out.println("请输入一个字符串：");
        str = sc.nextLine();
        str = sc.nextLine();
        System.out.println("a="+a);
        System.out.println("str="+str);
    }   
}
```



### 4.Java封装之封装类

```java
//封装类，类=模板，类不能直接访问变量，需要先实例化，即申请一个空间
class Student {
    
    int age;
    String name;
    double score;
    //方法=函数
    void introduce() {  
    //不需要传参,此方法可以访问属于自己的成员变量age,name,score
    
        System.out.println("name="+name+",age="+age+",score="+score);
    }
    void testFunc() {
        System.out.println("testFunc");
    }
}
public class Demo1 {
    public static void main(String[] args) {
        //类型            变量名         给构造方法进行传参
        Student stu1 = new Student();//通过一个类实例化一个对象
        /*等同于C中
         struct Student *p;
         p = malloc(sizeof(struct Student));
         */
        stu1.age = 18;
        stu1.name = "yanghaoqing";
        stu1.score = 98.5;
        stu1.introduce();
    }
}
```



### 5.Java封装之访问修饰符

- public 该类或非该类均可以访问
- private 只有该类可以访问
- protected 该类及其子类的成员可以访问，同一个包中的类也可以访问
- 默认 同一个包中的类可以访问

**属性（变量）/方法访问权限表**

> <img src="assets/77d732b5ba76c826a5b0627b7a8d81ca-337313" alt="img" style="zoom: 50%;" />

#### 属性封装

```java
class Student {
    
    int a;
    private int s;
    
    void SSS(int b){    //通过函数接口来输出private类型的属性
        
        s = b;
    }
}
public class Demo2 {
    
    public static void main(String[] args) {
        
        Student stu1 = new Student();
        stu1.SSS(0);
    }
}
---
class Student{
    int age;
    private int sex;  //默认为0
    
    public int getsex(){  //通过函数接口来输出private类型的属性
        return sex;
    }
}
public class test2 {
    
    public static void main(String[] args){
        
        Student stu2 = new Student();
        System.out.println("sex="+stu2.getsex());
    }   
}
```

#### 方法封装

```java
/*隐藏方法实现细节（方法体），向外部提供公开接口（方法头），以供安全调用简化调用，方便修改维护*/
class Student{
    private int age;
    
    private void myage(int myage){  //私有方法
        age = myage;
    }
    public int getage(){  //公有方法调用私有方法
        myage(18);
        return age;
    }
    public void setage(int realage){
        age = realage;
    }
}
public class test2 {
    
    public static void main(String[] args){
        
        Student stu2 = new Student();
        stu2.setage(36);
        System.out.println("age="+stu2.getage());
    }   
}
```



### 6.构造方法

#### 类的构造方法的概念和作用

- 构造方法负责对象初始化工作，为对象的属性赋合适的初始值
- 创建对象时，其类的构造方法确保在用户操作对象之前，系统保证初始化的进行
- 补充：UML类图，统一建模语言或标准建模语言
- 补充：Java系统保证每个类都有构造方法
- 补充：Java语言中，方法是可重载的，函数名一样，参数列表不同，在C中不允许

#### 构造方法的语法规则

- 构造方法名与类名一致
- 没有返回类型
- 方式实现主要为字段赋初值

#### 构造方法的调用

- 构造方法的调用很特别:new操作符（实例化对象的时候，自动被调用）

```java
class Student{
    
    private int age;
    String name;
    double score;
    //构造方法1
    Student(int newage, String newname, double  newscore){
        
        System.out.println("构造方法被调用");
        age = newage;
        name = newname;
        score = newscore;
    }
    //构造方法2
    Student(int newage, String newname){
    
        System.out.println("构造方法2被调用");
        age = newage;
        name = newname;
}
}
public class Demo1 {
    public static void main(String[] args) {
        //使用类创建新对象，调用构造方法来初始化成员
        //会根据传参的不同，调用不同的构造方法
        Student stu1 = new Student(18,  "yanghaoqing", 98.9);
        Student stu2 = new Student(18,  "yanghaoqing");
    }
}
```



### 7.this关键字

- 在类的方法中，使用this关键字代表的是调用此方法的对象的引用。
- this可以看做是一个变量，它的值是当前对象的引用
- 使用this可以处理方法中的成员变量和形参同名的问题
- 当在方法内需要用到调用到该方法的对象时，就可以用this
- 在类的构造方法中可以调用this([参数列表])来调用该类的指定构造方法

```java
class Student{
    
    private int age;
    String name;
    double score;
    
    void testThis(){
        //this代表的是调用此方法的对象的引用，此处为stu1
        Student stutmp = null;
        stutmp = this;  //this可以看做是一个变量，它的值是当前对象的引用，此处为stu1
        System.out.println(stutmp.age);
        System.out.println(this.name);
        System.out.println(this.score);
    }
    
    //构造方法1
    Student(int age, String name, double score){
        //this可以处理方法中的成员变量和形参同名的问题
        System.out.println("构造方法被调用");
        this.age = age;
        this.name = name;
        this.score = score;
    }
    Student(int age, String name){
        //this构造方法的调用只能放在第一句
        //在类的构造方法中可以调用this（[参数列表]）来调用该类的指定构造方法
        this(12, "jjj", 98.1);
        System.out.println("构造方法2被调用");
        this.age = age;
        this.name = name;
    }
}
public class Demo1 {
    public static void main(String[] args) {
    
        Student stu1 = new Student(18,  "yanghaoqing");
        
        stu1.testThis();
    }
}
```



### 8.static关键字

- 用来修饰类的成员——修饰的成员变量成为类变量（静态变量）
- 修饰成员方法称之为类方法（静态方法）
- 当类被加载的时候就会被加载，优先于对象的存在
- 用来修饰语句块——称之为静态代码块，先于构造方法之前执行，只会执行一次，用来对静态成员做初始化。
- 调用的时候可以直接通过类名，成员来进行访问

#### static关键字的注意事项

- 静态方法中只能访问外部的静态成员
- 静态方法中不能出现this关键字



### 9.方法重载

- 方法重载使得在一个类中，方法名相同而参数列表不同的方法可同时存在，代表相似的行为或功能
- 在同一个类中，同名不同参的方法称为重载方法，仅有返回值不同的方法不能称为重载



### 10.包

- 一个类可以使用同一个包中的所有类
- 一个类可以使用其他包中的所有公开类
- - 怎么使用其他包中的公开类：
  - 在每个类签名加上完整包名，例如
    - java.util.Data today = new java.util.Date();

```java
java.util.Scanner bc = new  java.util.Scanner(System.in);
```

- -  更简洁更通用的方式，使用import语句包来导包（eclipse ctrl+shift+o）

  - - import java.util.Date;
    - ...
    - Date today = new Date();

```java
import java.util.Scanner;
Scanner sc = new Scanner(System.in);
```

- - 可以import特定类，也可以导入整个包，通过在源代码文件的顶部（在打包语句后）使用import语句来实现import java.util.*

> ![img](assets/ad1542887e1208d02e1bd8fd9c34c3c7-30471)

```java
package com.yanhaoqing.learn;
public class Demo6 {
    public static void main(String[] args) {
        
        Demo3 dm = new Demo3();
        dm.age = 10;
        dm.printfdata();
        
        //定义其他包内的实例，调用其他包内的类，前提是其他包内的类中属性/方法为public类型
        com.yanhaoqing.use.Demo3 dm2 = new  com.yanhaoqing.use.Demo3();
        dm2.name = "aaaa";
        dm2.printinfo();
    }
}
```



### 11.Java继承的概念

- 父类更通用更抽象，子类更特殊更具体
- 基于已存在的类来构建新类
- 当从已存在的类继承时，就重用了它的方法和属性，还可以添加新的方法和属性来定制新类以应对需求
- 在Java中，除了Object类外，所有类都是子类，都只有唯一的父类（默认）

#### extends关键字

- 用extends关键字来表示一个类继承了另外一个类

```java
class Person{
    
    String name;
    String address;
    
    public void eat(){
        System.out.println("人吃饭");
    }
    public void drink(){
        System.out.println("人喝水");
    }
}
class Student extends Person{
    
    int score;
    public void study(){
        System.out.println("去上学");
    }
}
```



### 12.继承之super关键字

- super和this（该类对象的引用）关键字类似，super代表的是父类对象的引用
- 当子父类的成员出现同名时，可通过super来区分
- 子类的构造方法中，通过super关键字调用父类的构造方法
- 注意：当构造一个子类对象时一定会先调用父类的构造方法来构造父类的对象，调用父类构造方法的语句必须是子类构造方法中的第一条指令。
- 父类private的属性子类不可继承

```java
class Person{
    
    String name;
    String address;
    
    public Person(){}   
    //第一种方法解决子类构造方法报错问题，是在父类中定义一种无参的构造方法，则子类无需定义任何构造方法
    //第二种方法是在子类中调用父类的构造方法，super(name, address);
    public Person(String name, String address){
        
        this.name = name;
        this.address = address;
    }
    
    public void eat(){
        System.out.println("人吃饭");
    }
    public void drink(){
        System.out.println("人喝水");
    }
}
class Student extends Person{
    
    public Student(String name, String address){
        
        super(name, address);  //调用父类的构造方法的语句必须放在第一条
    }
    int score;
    public void study(){
        super.eat();   //子类方法中也可通过super调用父类的属性方法
        System.out.println("去上学");
    }
}
public class Test {
    public static void main(String[] args) {
        
        Person p = new Person();
        p.name = "人";
        p.eat();
        
        Student s = new Student("yanghaoqing",  "shandong");
        System.out.println("name="+s.name);
        System.out.println("address="+s.address);
        s.study();
    }
}
```



### 13.继承之方法重写

- 方法重写是指子类可以根据需要对从父类继承来的方法进行改写，是多态机制的前奏
- 重写方法必须和被重写方法具有相同的方法名称、参数列表和返回值（重载只需要有相同的方法名称）
- 重写方法不能比被重写方法有更严格的访问权限
- 父类中的私有方法，不能被重写
- 在子类重写的方法中继续调用父类被重写的方法可以通过super.函数名获取

```java
class Person{

    public void eat(){
        System.out.println("人吃饭");
    }
}
class Student extends Person{
    
    public void eat(){
        super.eat();
        System.out.println("子类打印-人吃饭");
    }   
}
```



```java
class Wapon{
    
    String name;
    void waponAttack(){
        System.out.println("武器攻击");
    }
}
class K98 extends Wapon{  //继承
    void waponAttack(){   //重写父类中方法
        System.out.println("98K攻击");
    }
}
class Gou extends Wapon{   //继承
    void waponAttack(){    //重写父类中方法
        System.out.println("锅盖攻击");
    }
}
class Play{
        
    String name;
    String duanwei;
    Wapon wapon;  //类中包含其他类
    int id;
    
    void attack(){      
        wapon.waponAttack();
    }
}
public class Test {
    public static void main(String[] args) {
        
        Play p1 = new Play();
        p1.wapon = new Wapon();  //由于Play中调用了Wapon类，所以需要提前定义
        p1.attack();
        p1.wapon = new K98();    //多态
        p1.attack();
        p1.wapon = new Gou();    //多态
        p1.attack();
    }
}
```



### 14.继承之Object类

- java中，所有类都直接过间接继承自java.lang.Object类，可以说Object是java中所有类的祖先即根类

- java中任何类都继承了Object类中的方法，主要有

- - toString()
  - equals()
  - hashcode()
  - clone()
  - getClass()
  - finalize()



### 15.继承之简单工厂模式

```java
class Fruit{
    
    String name;
    void Print(){
        System.out.println("野蛮生长的水果");
    }
    public Fruit(String name){   //构造方法
        this.name = name;
    }
}
class Apple extends Fruit{
    void Print(){
        System.out.println("野蛮生长的苹果");
    }
    public Apple(String name){
        super(name);   //调用父类构造方法
    }
}
class Peach extends Fruit{
    void Print(){
        System.out.println("野蛮生长的桃子");
    }
    public Peach(String name){
        super(name);   //调用父类构造方法
    }
}
class Factory{
    
    public static Fruit getFruit(String name){
        if(name == "苹果")
            return new Apple("苹果1");  //返回一个新建的对象
        if(name == "桃子")
            return new Peach("桃子1");  //返回一个新建的对象
        else
            return null;
    }
}
public class Test {
    public static void main(String[] args) {
        
        Factory.getFruit("苹果").Print();
        System.out.println(Factory.getFruit("苹果").name);
        Factory.getFruit("桃子").Print();
    }
}
```



### 16.抽象方法和抽象类

- Java中可以定义没有方法体的方法，该方法由子类来具体实现
- 没有方法体的方法称为抽象方法，含有抽象方法的类称为抽象类

#### 抽象方法的特点

- 只有方法头没有方法体的方法称为抽象方法
- 抽象方法用abstract来修饰
- 抽象方法代表一种不确定性的操作或行为
- 抽象方法不能被调用

#### 抽象类的特点

- 定义中含有抽象方法的类叫抽象类
- 抽象类用abstract来修饰
- 抽象类代表一种抽象的对象类型
- 抽象类不能实例化
- 抽象类中可以有具体方法，可以没有抽象方法

```java
abstract class Demo2{   //抽象类
    
    abstract public void printInfo(); //抽象方法
}
//抽象类不能被实例化
class Demo3 extends Demo2{
        public void printInfo(){
            System.out.println("被实现的方法");
        }
}
public class Demo1 {
    public static void main(String[] args) {
        
        Demo3 d = new Demo3();
        d.printInfo();
    }
}
```

#### 模板方法模式

- 一个模板方法用一些抽象的操作定义一个算法，而子类将重定义这些操作以提供具体行为
- 意义：定义了一个操作中的一个算法框架，把一些步骤推迟到子类去实现，模板方法模式让子类不需要改变算法结构

```java
abstract class Control{
    
    abstract void initUart();
    abstract void getCommand();
    abstract void openCurse();
    
    public void work(){
        
        initUart();
        getCommand();
        openCurse();
    }
}
class C51Control extends Control{   //在此类中按alt+/可快速生产函数模板
    void getCommand() {
        // TODO 自动生成的方法存根
        System.out.println("C51 getCommand");
    }
    void initUart() {
        // TODO 自动生成的方法存根
        System.out.println("C51 initUart");
    }
    void openCurse() {
        // TODO 自动生成的方法存根
        System.out.println("C51 openCurse");
    }
}
class Stm32Control extends Control{
    void getCommand() {
        // TODO 自动生成的方法存根
        System.out.println("Stm32 getCommand");
    }
    void initUart() {
        // TODO 自动生成的方法存根
        System.out.println("Stm32 initUart");
    }
    void openCurse() {
        // TODO 自动生成的方法存根
        System.out.println("Stm32 openCurse");
    }
}
public class Demo1 {
    public static void main(String[] args) {
        
    C51Control c = new C51Control();
    c.work();    //直接使用父类中的work()函数
    Stm32Control s = new Stm32Control();
    s.work();    //直接使用父类中的work()函数
    }
}
```



### 17.Java接口及应用

#### 接口语法

- interface 接口名{ //公有静态常量，抽象方法}

#### 接口特点

- 接口中只能存放静态常量和抽象方法
- 接口是对功能的扩展，通过实现接口，java类可以多实现
- 一个类可以同时继承(extends)一个父类并且实现（implements）多个接口
- 接口与接口间可以使用extends实现继承

#### 接口与抽象类区别

- 抽象类和具体实现之间是一个继承关系，也就是如果采用抽象类的方式，则父类和子类在概念上应该是相同的
- 接口和实现类在概念上不要求相同，接口只是抽取相互之间没有关系的类的共同特征，而不去关注类之间的关系，它可以使没有层次关系的类具有相同的行为
- 抽象类是对一组具有相同属性和行为的逻辑上有关系的事物的一种抽象，而接口则是对一组具有相同属性和行为的逻辑上不相关的事物的一种抽象

```java
interface XingWei{
        
    abstract void eat();
    abstract void drink();
}
class Man implements XingWei{
    
    public void drink() {
        // TODO 自动生成的方法存根
        System.out.println("男人喝");
    }
    public void eat() {
        // TODO 自动生成的方法存根
        System.out.println("男人吃");
    }
}
class Dog implements XingWei{
    
    public void drink() {
        // TODO 自动生成的方法存根
        System.out.println("狗喝");
    }
    public void eat() {
        // TODO 自动生成的方法存根
        System.out.println("狗喝");
    }
}
public class Demo1 {
    public static void main(String[] args) {
        
        new Man().drink();
        new Dog().eat();
    }
}
```



### 18.Java内部类

#### 内部类特点

- 内部类（Inner Class），即将一个类定义在另一个类的内部
- 内部类可以很好的实现隐藏，可以使用protected private修饰符
- 内部类可以直接访问外部类的所有成员，包括私有的成员
- 外部类不能直接访问内部类的成员，必须首先建立内部类的对象才能访问

#### 成员内部类

- 成员内部类属于外部类的实例成员，成员内部类可以有public private default protected权限修饰符，在成员内部类中访问外部类的成员方法和属性，要使用“外部类名.this.成员方法”和“外部类名.this.成员属性”的形式
- 创建成员内部类的实例使用“外部类名.内部类名 实例 = 外部类实例名.new 内部类构造方法（参数）”的形式

#### 成员内部类有以下限制

- 成员内部类不能与外部类重名
- 不能在成员内部类中定义static属性，方法和类（static final形式的常量定义除外），因为一个成员内部类实例必然与一个外部类实例关联，static成员完全可以移到其外部类中去

```java
class Outer{
    
    int data;
    void printData(){
        System.out.println("外部类打印");
    }
    //外部类不能直接访问内部类的成员，必须首先建立内部类的对象才能访问
    void visitInner(){
        Inner i = new Inner();
        i.data = 90;
        System.out.println("内部类的data="+i.data);
    }
    class Inner{
        int data;
        void InnerPrint(){
            System.out.println("内部类打印");
            //在成员内部类中访问外部类的成员方法和属性，
            //要使用“外部类名.this.成员方法”和“外部类名.this.成员属性”的形式
            Outer.this.printData();
            System.out.println("外部类data="+Outer.this.data);
        
        }
    }
}
public class Demo1 {
    public static void main(String[] args) {
        
        
        Outer o = new Outer();  //首先实例化一个外部类
        //外部类名.内部类名 实例 = 外部类实例名.new  内部类构造方法（参数）
        Outer.Inner test = o.new Inner(); //实例化一个内部类
        test.InnerPrint();
        o.visitInner();
        
    }
}
```



### 19.Java匿名内部类

#### 匿名内部类的特点

- 匿名内部类是没有名称的内部类，没办法引用它们。必须在创建时，作为new语句的一部分来声明并创建它们的实例
- 匿名内部类必须继承一个类（抽象的，非抽象的都可以）或者实现一个接口，所有父类（或者父接口）是抽象类，则匿名内部类必须实现其所有抽象方法

#### 语法：实例

- new interface/superclass(){类体}
- 这种形式的new语句声明一个新的匿名类，它对一个给定的类进行扩展，或者实现一个给定的接口，并同时创建该匿名类的一个新实例。

```java
abstract class Demo2{  //声明一个抽象类
    
    abstract void printInfo();  //声明一个抽象方法
}
interface Demo3{     //声明一个接口
    abstract void interprint();
}
public class Demo1 {
    public static void main(String[] args) {
        
        //不能实例化抽象类，但可以创建一个匿名内部类，并实现其方法，同时会实例化一个匿名内部类
        new Demo2(){    
            void printInfo() {
                // TODO 自动生成的方法存根
                System.out.println("这不是Demo1，而是匿名内部类的方法");
            }
        }.printInfo();
        
        //匿名内部类，属于抽象类的子类
        Demo2 d = new Demo2(){  
            void printInfo() {
                // TODO 自动生成的方法存根
                System.out.println("这不是Demo1，而是匿名内部类的方法");
            }
        };
        d.printInfo();
    
        //不能实例化接口，但可以创建一个匿名内部类，并实现其方法，同时会实例化一个匿名内部类
        new Demo3(){
            public void interprint() {
                // TODO 自动生成的方法存根
                System.out.println("这不是接口的实例，而是匿名内部类的方法");
            }
        }.interprint();
    }
}
```



### 20.多态

多态性是指同一个操作作用于某一类对象，可以有不同的解释，产生不同的执行结果

#### 多态存在的三个必要条件

- 需要存在继承或实现关系
- 同样的方法调用而执行不同操作、运行不同代码（重写）
- 在运行时父类或者接口的引用变量可以引用其子类的对象

#### 多态的作用

- 多态通过分离做什么和怎么做，从一个角度将接口和实现进行分离
- 多态消除了类型之间的耦合关系
- 多态的存在提高了程序的拓展性和后期的可维护性

```java
class Animal{           //定义一个父类
    
    public String name;
    public void eat(){};
}
//上下两种方法都可行
abstract class Animal{    //定义一个抽象类
    
    public String name;
    abstract public void eat();  //抽象方法
}
class Dog extends Animal{
    
    public void eat() {
        // TODO 自动生成的方法存根
        System.out.println("狗啃骨头");
    }
}
class Cat extends Animal{
    
    public void eat() {
        // TODO 自动生成的方法存根
        System.out.println("猫吃鱼");
    }
}
public class Demo1 {
    public static void main(String[] args) {
    
        Animal an3 = new Dog();
        Animal an2 = new Cat();
        an3.eat();
        an2.eat();
    }
}
```



### 21.多态中上下转型

#### 对象的上下转型

- 由子类转型成父类，在继承图上是向上移动的，一般称为向上转型

```java
public class Demo1 {
    public static void main(String[] args) {
    
        Animal an3 = new Dog();   //由子类转型成父类
        Animal an2 = new Cat();
        an3.eat();
        an2.eat();
    }
}
```

- 向上转型是从一个较专用类型向通用类型转换，所以总是安全的，也就是说，子类是父类的超集
- 向上转型过程中，类接口中唯一可能反生的事情是丢失方法，而不是获取方法
- 与之相反的操作是向下转型，不安全（可能需要instanceof操作符协助）

instanceof运算符用来在运行时通过返回值来指出对象是否是特定类或者是它的子类的一个实例

- 用法：

- result = object instanceof class

- - result: 布尔类型
  - object: 必选项，任意对象表达式
  - class: 必选项，任意已定义的对象类

- 说明：如果object是class或其子类的一个实例，则instanceof运算符返回true,如果不是或者object是null,则返回false。

- 典型的使用场合：在对对象做下转型之前，没有其他有关对象信息时务必使用instanceof来判断一下，以避免抛出ClassCastException异常。

```java
public class Demo1 {
    public static void main(String[] args) {
    
        Animal an3 = new Dog();
        Animal an2 = new Cat();
        //向下转型是危险的，需要判断一下
        if(an2 instanceof Cat){
            System.out.println("是子类");
            Cat cat = (Cat) an2;
            cat.eat();
        }
        
        an3.eat();
        an2.eat();
    }
}
```



### 22.多态案例——打印机

简单来说，多态是具有表现多种形式能力的特征

同一个实现接口，使用不同的实例而执行不同操作

```java
class School{
    public Dayin dayinji;
    public void anZhuang(Dayin dayinji){  //要求方法参数为Dayin父类的子类
        this.dayinji = dayinji;
    }
    public void print(String contex){
        dayinji.print(contex);
    }
}
class Dayin{    //父类
    public String pinpai;
    public void print(String contex){}
}
class CaiSeDayin extends Dayin{      //子类
    public void print(String contex) {
        // TODO 自动生成的方法存根
        System.out.println("彩色打印机"+contex);
    }
}
class HeiBaiDayin extends Dayin{     //子类
    public void print(String contex) {
        // TODO 自动生成的方法存根
        System.out.println("黑白打印机"+contex);
    }
}
public class printor {
    public static void main(String[] args) {
    
        School s = new School();
        CaiSeDayin c = new CaiSeDayin();
        s.anZhuang(c);    //将子类传递回去
        s.print("yanghaoqing");
        HeiBaiDayin h = new HeiBaiDayin();
        s.anZhuang(h);    //将子类传递回去
        s.print("重中之重做做做做");
    }
}
```



### 23.异常

Java异常处理机制  Try-catch-finally

- try{}     监控区域，执行可能产生异常的代码
- catch(异常类型){} 捕获、处理异常
- finally{}    善后处理，无论是否发生异常，代码总能执行，一般用来释放资源，除了在之前执行了System.exit(0)

```java
import java.util.Scanner;
public class printor {
    public static void main(String[] args) {
    
        Person p = null;
        int a = 10;
        int b = 0;
        double c = 0;
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入除数：");
        b = sc.nextInt();
                
        try {
            c = (double)a/b;
        //catch(Exception e) 为捕获所有异常
        } catch(java.lang.NullPointerException  e) {
            System.out.println("空指针错误");
        } catch(java.lang.ArithmeticException e)  {
            System.out.println("你输入了0，请重新输入");
            b = sc.nextInt();
            c = a/b;
            System.out.println("c="+c);
        } finally {
            System.out.println("c="+(double)a/b);
        }
    }
}
```

#### throw和throws

- throw用于手动抛出异常

- throws用于在方法上标识要暴露的异常，抛出的异常交由调用者处理

- 区别：

- - throw用在方法内，后面跟上要抛出的异常类对象，手动抛出异常
  - throws修饰在方法上，告诉调用者此方法可能会抛出异常，后面跟上可能要抛出的异常类名

```java
class Bar {
    int age;
    public Bar(int age) {   //构造方法
        this.age = age;
    }
    void check() throws IllegalArgumentException {
        if(age < 18) {
            throw new  IllegalArgumentException("年级太小");  //抛出异常
        }
    }
}
public class printor {
    public static void main(String[] args) {
    
        Bar b = new Bar(15);
        try {
            b.check();  //throw抛出异常，catch捕获异常
        } catch (IllegalArgumentException e) {          
            System.out.println(e.getMessage());  //获取异常
            e.printStackTrace(); //将抛出异常输出
        }
    }
}
```

#### 自定义异常

- 自定义异常类必须从已有的异常类继承
- 建立新的异常类型最简单的方法就是让编译器产生默认构造方法
- 对异常来说，最重要的部分就是它的类名
- 可以为异常类定义一个接受字符串参数的构造方法，字符串参数描述异常信息

```java
class Bar {
    int age;
    public Bar(int age) {   //构造方法
        this.age = age;
    }
    void check() throws  AgeLessThanEighteenException {
        if(age < 18) {
            throw new  AgeLessThanEighteenException("年级太小");  //抛出异常
        }
    }
}
//自定义异常类必须从已有的异常类继承
class AgeLessThanEighteenException extends  Exception {
    private String message;
    public AgeLessThanEighteenException(String  message) { //构造方法
        this.message = message;
    }
}
public class printor {
    public static void main(String[] args) {
    
        Bar b = new Bar(15);
        try {
            b.check();  //throw抛出异常，catch捕获异常
        } catch (AgeLessThanEighteenException e)  {           
            System.out.println(e.getMessage());  //获取异常
            e.printStackTrace(); //将抛出异常输出
        }
    }
}
```



### 24.泛型

- 泛型可以在编译的时候检查类型安全，并且所有的强制转换都是自动和隐式的
- 泛型的原理就是“类型的参数化”，即把类型看做参数，也就是说把所要操作的数据类型看做参数，就像方法的形式参数是运行时传递的值的占位符一样。
- 简单的说，类型变量扮演的角色就如同一个参数，它提供给编译器用来类型检测的信息。
- 泛型可以提高代码的扩展性和重用性

```java
class Class1<T> {
    
    T a;
    
    public Class1(T a) {
        this.a = a;
    }
    public T getData() {
        return a;
    }
}
public class printor {
    public static void main(String[] args) {
        Class1<Integer> class1 = new  Class1<Integer>(10);
        System.out.println(class1.getData());
        Class1<String> class2 = new  Class1<String>("sasd");
        System.out.println(class2.getData());
    }
}
```

#### 泛型类及特点

- 泛型的类型参数可以是泛型类

```java
Class1<Class1<Integer>> class1 = new  Class1<Class1<Integer>>(new  Class1<Integer>(10));
        System.out.println(class1.getData().getData());
```

- 泛型类可以同时设置多个类型参数

```java
class Class2<T, T2> {
    
    T a;
    T2 b;
    public Class2(T a, T2 b) {
        this.a = a;
        this.b = b;
    }
    public T getData() {
        return a;
    }
    public T2 getData2() {
        return b;
    }
}
public class printor {
    public static void main(String[] args) {
        Class2<Integer, String> class3 = new  Class2<Integer, String>(100, "帅");
        System.out.println(class3.getData()+class3.getData2());
    }
}
```

- 泛型类可以继承泛型类
- 泛型类可以实现泛型接口

```java
abstract class Class1<T> {
    
    T a;
    
    public Class1(T a) {
        this.a = a;
    }
    public T getData() {
        return a;
    }
    abstract void printInfo();
}
interface Class3<T> {
    abstract void printInfoClass3(T t);
}
class Class2<T, T2> extends Class1<T> implements  Class3<T> {   //泛型类可以继承泛型类
    
    T a;
    T2 b;
    public Class2(T a, T2 b) {
        super(a);
        this.b = b;
    }
    public T2 getData2() {
        return b;
    }
     @Override
    void printInfo() {  //方法重写
        // TODO 自动生成的方法存根
         System.out.println("输出");
    }
     public void printInfoClass3(T t) {
        // TODO 自动生成的方法存根
         System.out.println(t);
    }
}
public class printor {
    public static void main(String[] args) {
        
        Class2<Integer, String> class2 = new  Class2<Integer, String>(10, "aaa");
        class2.printInfo();
        class2.printInfoClass3(100);
    }
}
```



### 25.限制泛型可用类型

- 在定义类型时，使用extends关键字指定这个类型必须是继承某个类，或者实现某个接口，可用限制使用泛型的类型
- 当没有指定泛型继承的类型或接口时，默认使用extends Object,所以默认情况下任何类型都可以作为参数传入

```java
class Animal {
}
class Dog extends Animal {
    
}
abstract class Class1<T extends Animal> {
    
    T a;
    
    public Class1(T a) {
        this.a = a;
    }
    public T getData() {
        return a;
    }
    abstract void printInfo();
}
interface Class3<T3> {
    abstract void printInfoClass3(T3 t);
}
class Class2<T extends Animal, T2, T3> extends  Class1<T> implements Class3<T3> {   //泛型类可以继承泛型类
    
    T a;
    T2 b;
    public Class2(T a, T2 b) {
        super(a);
        this.b = b;
    }
    public T2 getData2() {
        return b;
    }
     @Override
    void printInfo() {  //方法重写
        // TODO 自动生成的方法存根
         System.out.println("输出");
    }
     public void printInfoClass3(T3 t) {
        // TODO 自动生成的方法存根
         System.out.println(t);
    }
}
public class printor {
    public static void main(String[] args) {
        
        Class2<Dog,String, String> class2 = new  Class2<Dog, String, String>(new Dog(), "aaa");
        class2.printInfo();
        class2.printInfoClass3("111");
    }
}
```



### 26.类型通配声明

- 同一泛型类，如果实例化时给定的实际类型不同，则这些实例的类型时不兼容的，不能相互赋值。
- 泛型类实例之间的不兼容性会带来使用的不便，我们可以使用泛型通配符（？）声明泛型类的变量就可以解决这个问题。

```java
class Class1<T> {
    
    T a;
    
    public Class1(T a) {
        this.a = a;
    }
    public T getData() {
        return a;
    }
}
public class printor {
    public static void main(String[] args) {
        
        Class1<Integer> c1 = new  Class1<Integer>(10);
        Class1<Double> c2 = new  Class1<Double>(10.0);
        Class1<?> c3;
        
        c3 = c1;
        System.out.println(c3.getData());
        c3 = c2;
        System.out.println(c3.getData());
    
    }
}
```

- 和限制泛型的上限相似，可以使用extends关键字限定通配类型上限

```java
Class1<? extends Animal> c3;
```

- 可以使用super关键词将通配符匹配类型限定为某个类型

```java
Class1<? super Dog> c3;
```



### 27.泛型方法

- 不仅类可以声明泛型，类中的方法也可以声明仅用于自身的泛型，这种方法叫做泛型方法

- - 访问修饰符<泛型列表> 返回类型 方法名（参数列表） {实现代码}

- 在泛型列表中声明的泛型，可用于该方法的返回类型声明、参数类型声明和方法代码中的局部变量的类型声明

- 类中其他方法不能使用当前方法声明的泛型

- 注：是否拥有泛型方法，与其所在的类是否泛型没有关系，要定义泛型方法，只需将泛型参数列表置于返回值前。

```java
class A<T> {     //泛型类
    public void printInfo(T t){
        System.out.println(t);
    }
}
class B {
    public<T> void printInfo(T t){   //泛型方法更加灵活，可以不受泛型类的限制
        System.out.println(t);
    }
    public<T, T2> void printInfo(T t, T2 t2){    //泛型方法的重载
        System.out.println(t);
        System.out.println(t2);
    }
}
public class printor {
    public static void main(String[] args) {
        
        A<String> a = new A<String>();
        a.printInfo("hh");
        B b = new B();
        b.printInfo("hhhhh");
        b.printInfo(1234);
        b.printInfo(0.3);
    
    }
}
```

- 什么时候用泛型方法，而不是泛型类

- - 添加类型约束只作用于一个方法的多个参数之间，而不涉及到类中的其他方法
  - 施加类型约束的方法为静态方法，只能将其定义为泛型方法，因为静态方法不能使用其所在类的类型参数

```java
class Animal {
    public void eat() {
        System.out.println("动物吃");
    }
}
class Dog extends Animal {
    public void eat() {
        System.out.println("狗吃肉");
    }
}
class Cat extends Animal {
    public void eat() {
        System.out.println("吃鱼肉");
    }
}
class A<T> {     //泛型类
    public void printInfo(T t){
        System.out.println(t);
    }
}
class B {
    public<T> void printInfo(T t){   //泛型方法更加灵活，可以不受泛型类的限制
        System.out.println(t);
    }
    public<T, T2> T printInfo(T t, T2 t2){    //泛型方法的重载
        System.out.println(t);
        System.out.println(t2);
        return t;
    }
    public <T extends Animal> void printInfo1(T  t) {  //设置上限，类型约束
        t.eat();
    }
    public static <T extends Animal> void  printInfo2(T t) {  //静态方法
        t.eat();
    }
}
public class printor {
    public static void main(String[] args) {
        
        A<String> a = new A<String>();
        a.printInfo("hh");
        B b = new B();
        b.printInfo("hhhhh");
        b.printInfo(1234);
        b.printInfo(0.3);
    
        b.printInfo1(new Dog());
        b.printInfo1(new Cat());
        b.printInfo1(new Animal());
        
        B.printInfo2(new Dog());  //静态调用
    }
}
```



### 28.Java之Socket服务端

```java
import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
public class Test {
    public static void main(String[] args) {
        byte[] data = new byte[128];
        int len = 0;
        
        //创建套接字，ip,端口号
        try {                             //按ctrl+1可生成try块
            ServerSocket socket = new  ServerSocket(8801);
            System.out.println("socket套接字创建成功，等待连接");
            Socket con = socket.accept();
            System.out.println("有客户端接入");
            
            InputStream in =  con.getInputStream(); //获取输入流，用来读取数据
            len = in.read(data);
            //输出字符串data从第0个开始到len
            System.out.println("读到消息："+new  String(data, 0, len));
            
        } catch (IOException e) {
            // TODO 自动生成的 catch 块
            e.printStackTrace();
        }
    }
}
```

#### Socket服务端支持多连接

```java
import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Test {
    public static void main(String[] args) {


        //创建套接字，ip,端口号
        try {
            ServerSocket socket = new ServerSocket(8801);
            System.out.println("socket套接字创建成功，等待连接");
            
            while(true) {
                final Socket con = socket.accept();
                System.out.println("有客户端接入");
                //创建一个新线程
                new Thread(new Runnable() {
                    
                    public void run() {
                        // TODO 自动生成的方法存根
                        InputStream in;
                        try {
                            in = con.getInputStream();
                            int len = 0;
                            byte[] data = new byte[128];
                            len = in.read(data);
                            //输出字符串data从第0个开始到len
                            System.out.println("读到消息："+new String(data, 0, len));
                        } catch (IOException e) {
                            // TODO 自动生成的 catch 块
                            e.printStackTrace();
                        } //获取输入流，用来读取数据
                        
                    }
                }).start();
                
                
            }
            
            
        } catch (IOException e) {
            // TODO 自动生成的 catch 块
            e.printStackTrace();
        }
    }
}


```

#### Socket客户端

```java
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Scanner;
public class Test2 {
    public static void main(String[] args) {
        
        try {
            Socket client = new  Socket("192.168.3.5", 8800);//创建套接字
            OutputStream out =  client.getOutputStream(); //获得数据发送通道
            
            Scanner sc = new Scanner(System.in);
            String message = sc.next();
            
            out.write(message.getBytes());//发送通道，发送数据
            
            InputStream in =  client.getInputStream(); //获得数据接收通道
            int len;
            byte[] data = new byte[128];
            len = in.read(data);//接收通道接收数据
            System.out.println("获得服务器端返回数据是："+new String(data,0,len));
        } catch (IOException e) {
            // TODO 自动生成的 catch 块
            e.printStackTrace();
        }
    }
}
```





















































































































































