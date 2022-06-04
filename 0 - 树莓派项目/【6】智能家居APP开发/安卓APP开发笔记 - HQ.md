# 安卓APP开发笔记 - HQ

[TOC]

------

#### 注意

- 

------

### 开发经验

安卓创建软件信息：

- 密码：12345678

  > <img src="assets/7d8faa92c00c7a9ec776e13786c911bc-21406" alt="img" style="zoom:67%;" />

- 在.xml文件中，选中内容按ctrl+shift+/将其变为注释，一般不建议在这些文件中加注释

- ctrl+1,可添加try,或者添加强制类型装换

- 可以自动调整格式

  > <img src="assets/868ef1ff1d13f7aa033aa234a09efe12-10487" alt="img" style="zoom:67%;" />

- 如果调试过程中出现修改未被执行，可以将gen中的R.java删掉，然后重新运行

- logcat位置

  > <img src="assets/655c7fa354fd6509c6b280ee844d30d6-31447" alt="img" style="zoom:67%;" />

  > <img src="assets/145a57d585e4d69db9aa3c09f20d26ec-15152" alt="img" style="zoom: 67%;" />





### 基本配置

- 新建工程，Package Name中不能含有中文

  > <img src="assets/0fe567d6a6241ee98aba44429441c725-24922" alt="img" style="zoom:67%;" />

- 运行App

  > <img src="assets/f0a0df9c800b2749e791032586fc298e-50228" alt="img" style="zoom:67%;" />

- 提示是否用自带的模拟器，选择否，使用夜神模拟器

- 选择显示提示/错误信息

  > <img src="assets/f1f942e15b2c6585f3e8223bc29c7754-10504" alt="img" style="zoom:67%;" />

#### 如何关联模拟器

- 找到Java软件安装目录里的adb.exe，复制路径如E:\Java_class_use\adt-bundle-windows-x86_64-20131030\sdk\platform-tools

- 配置电脑环境变量，在系统变量中，找到Path，然后新建，将路径粘贴进去

- 打开模拟器，然后打开cmd，输入adb connect 127.0.0.1:62001

- 注：127.0.0.1是本地网络地址，62001是夜神模拟器暴露出来的端口号，如果连接失败输入adb kill-server,adb start-server

  > ![img](assets/d7966832c769573a7186744f9beedec5-7355)



### 2.安卓工程目录文件夹介绍

- src 存放java代码的，有包，有文件

- gen 存放自动生成的文件，需要关心的是里面的R.java，存放程序页面、按键、文本等控件的ID

- Android 4.4与Android Private Libraries存放的安卓开发的库，供开发者调用

- Asserts 存放一些资源，配置文件、图片

- bin 编译后会生产的一些文件，包括我们关心得.apk，可以直接拖进模拟器

- libs 依赖库

- res 

- - drawable-* 存放app程序要用到的一些图片
  - layout 存放布局文件的文件夹，一般的一个安卓页面（activity）对应一个布局
  - values 存放一些参数，或者自定义控件的文件

- AndroidManifest.xml API的配置

- - 权限管理：网络访问权限，名片夹访问权限，相机访问权限
  - 目标机器SDK版本
  - APP的名字，图标
  - 配置第一个被加载，启动页面



### 3.布局

- res->layout->activity_main.xml 配置界面的样式，设置属性参数
- 举例：布局底下有两个控件，一个文本框，一个控件

```java
<RelativeLayout>  
    <TextView
       />
    <ToggleButton
       />
</RelativeLayout>
```



### 4.练习——显示图片

- 在MainActivity.java中ctrl+activity_main跳转

- 设置高度宽度，输入wi或hi按alt+/快速选择输入

- 在res中插入一张图片

  > <img src="assets/54cb1196670eb5e017107b5639d6e77b-23697" alt="img" style="zoom:67%;" />

- 添加android:background="@drawable/ccc"（注原来程序尽量不动）

  > <img src="assets/a7057a96525aa06040c5fd5078416e31-18521" alt="img" style="zoom:67%;" />

#### 练习——显示两张图片

```java
<RelativeLayout  xmlns:android="http://schemas.android.com/apk/res/android"
     xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
     android:paddingBottom="@dimen/activity_vertical_margin"
     android:paddingLeft="@dimen/activity_horizontal_margin"
     android:paddingRight="@dimen/activity_horizontal_margin"
     android:paddingTop="@dimen/activity_vertical_margin"
    tools:context=".MainActivity" >
    
    <RelativeLayout
        android:id="@+id/pic1"               //设置id
        android:layout_width="match_parent"  //设置与父控件相同大小
        android:layout_height="wrap_content" //图片有多大就显示多大     
        android:background="@drawable/ccc"
        ></RelativeLayout>
    
    
    
    <RelativeLayout
        android:layout_below="@id/pic1"      //设置第二张图片在第一张图片下面，用id指明图片
        android:layout_width="match_parent"
        android:layout_height="200dp"
        android:background="@drawable/bbb"
        ></RelativeLayout>
    
  
</RelativeLayout>
```



### 5.相对布局RelativeLayout常用属性

```java
<RelativeLayout  xmlns:android="http://schemas.android.com/apk/res/android"
     xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
   
    tools:context=".MainActivity" >
    
    <RelativeLayout
        android:id="@+id/pic1"
        android:layout_alignParentTop="true"                 //设置子控件与父控件的上下左右对齐
        android:layout_alignParentBottom="true"              //设置子控件与父控件的上下左右对齐
        android:layout_alignParentRight="true"               //设置子控件与父控件的上下左右对齐
        android:layout_alignParentLeft="true"                //设置子控件与父控件的上下左右对齐
        android:layout_width="match_parent"
        android:layout_height="400dp"        
        android:background="@drawable/ggg"
        ></RelativeLayout>
</RelativeLayout>
----------------------------------------------------------------------
RelativeLayout用到的一些重要的属性：


    第一类:属性值为true或false
    android:layout_centerHrizontal  水平居中
    android:layout_centerVertical 垂直居中
    android:layout_centerInparent    相对于父元素完全居中
    android:layout_alignParentBottom 贴紧父元素的下边缘
    android:layout_alignParentLeft   贴紧父元素的左边缘
    android:layout_alignParentRight  贴紧父元素的右边缘
    android:layout_alignParentTop    贴紧父元素的上边缘
    android:layout_alignWithParentIfMissing  如果对应的兄弟元素找不到的话就以父元素做参照物


    第二类：属性值必须为id的引用名“@id/id-name”
    android:layout_below      在某元素的下方
    android:layout_above      在某元素的的上方
    android:layout_toLeftOf   在某元素的左边
    android:layout_toRightOf  在某元素的右边


    android:layout_alignTop   本元素的上边缘和某元素的的上边缘对齐
    android:layout_alignLeft  本元素的左边缘和某元素的的左边缘对齐
    android:layout_alignBottom 本元素的下边缘和某元素的的下边缘对齐
    android:layout_alignRight  本元素的右边缘和某元素的的右边缘对齐


    第三类：属性值为具体的像素值，如30dip，40px
    android:layout_marginBottom              离某元素底边缘的距离
    android:layout_marginLeft                   离某元素左边缘的距离
    android:layout_marginRight                 离某元素右边缘的距离
    android:layout_marginTop                   离某元素上边缘的距离
----------------------------------------------------------------------
android:id —— 为控件指定相应的ID
android:text —— 指定控件当中显示的文字，需要注意的是，这里尽量使用strings.xml文件当中的字符串
android:textSize —— 指定控件当中字体的大小
android:background —— 指定该控件所使用的背景色,RGB命名法 #FFFFFF或@android:color/white
android:width —— 指定控件的宽度
android:height —— 指定控件的高度
android:sigleLine —— 如果设置为真的话，则将控件的内容只能在同一行当中进行显示
android:grivity —— 指定控件中的内容的基本位置，比如说居中，居右等位置
android:layout_gravity 控件本身相对于父视图的位置
//此属性值为带单位的数值 在所有视图中都可使用
android:padding —— 指定控件的四周的内部留出一定的空间
android:paddingLeft —— 指定控件的左边的内部留出一定的空间
android:paddingTop —— 指定控件的上边的内部留出一定的空间
android:paddingRight —— 指定控件的右边的内部留出一定的空间
android:paddingBottom —— 指定控件的下边的内部留出一定的空间
//此属性值为带单位的数值 在所有视图中都可使用
android:layout_margin—— 指定控件的四周的外部留出一定的空间
android:layout_marginLeft—— 指定控件的左边的外部留出一定的空间
android:layout_marginTop—— 指定控件的上边的外部留出一定的空间
android:layout_marginRight—— 指定控件的右边的外部留出一定的空间
android:layout_marginBottom—— 指定控件的下边的外部留出一定的空间
//此属性值为引用id 只能在相对布局中都可使用
android:layout_above 将该控件的底部与给定ID的控件之上部对齐
android:layout_below 将该控件的上部与给定ID的控件之下部对齐
android:layout_toLeftOf 将该控件的右与给定ID的控件之左边对齐
android:layout_toRightOf 将该控件的左边与给定ID的控件的右边对齐
//此属性值为引用id 只能在相对布局中都可使用
android:layout_alignTop 将该控件的上部与给定ID的控件之上部对齐
android:layout_alignBottom 将该控件的下部与给定ID的控件之下部对齐
android:layout_alignLeft 将该控件的左与给定ID的控件之左边对齐
android:layout_alignRight 将该控件的右边与给定ID的控件的右边对齐
android:layout_alignBaseline 该控件的baseline和给定ID的控件的baseline对齐
//此属性值为引用id 只能在相对布局中都可使用
android:alignParentBottom 如果该值为true，则将该控件的底部和父控件的底部对齐
android:layout_alignParentLeft 如果该值为true，则将该控件的左边与父控件的左边对齐
android:layout_alignParentRight 如果该值为true，则将该控件的右边与父控件的右边对齐
android:layout_alignParentTop 如果该值为true，则将空间的顶部与父控件的顶部对齐
android:layout_centerHorizontal 如果值为真，该控件将被至于水平方向的中央
android:layout_centerInParent 如果值为真，该控件将被至于父控件水平方向和垂直方向的中央
android:layout_centerVertical 如果值为真，该控件将被至于垂直方向的中央
----------------------------------------------------------------------
```

#### 相对布局综合演练——智能家居刷卡界面

```java
<RelativeLayout  xmlns:android="http://schemas.android.com/apk/res/android"
     xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:background="@drawable/fff"
    tools:context=".MainActivity" >
    <RelativeLayout
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:background="#00ff00"
        >
        
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="智能家居"
        android:layout_marginLeft="35dp"
        android:layout_marginTop="11dp"
        />
     
    <Button
        android:id="@+id/aaaas"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="注册"
        android:layout_alignParentRight="true"
        android:layout_marginRight="20dp"
        />
    
    <Button
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="查询信息"
        android:layout_toLeftOf="@id/aaaas"
        />
        
        
    </RelativeLayout>
    
    <ImageView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:src="@drawable/a1"
        android:layout_centerInParent="true"
        />
    <ImageView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:src="@drawable/a2"
        android:layout_centerInParent="true"
        android:paddingLeft="120dp"
        />
    
    <Button
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="刷卡"
        android:layout_marginBottom="30dp"
        android:layout_centerHorizontal="true"
        android:layout_alignParentBottom="true"
        
        />
    
    
</RelativeLayout>
```



### 6.美化按键

- 参考博文（https://blog.csdn.net/tracydragonlxy/article/details/88552262）

- 在drawable-mdpi下新建3个xml文件

  > <img src="assets/b58c8845031f5658e57e63b147211b88-41349" alt="img" style="zoom:67%;" />

- 更改程序

- - btn_selector.xml

```java
<?xml version="1.0" encoding="utf-8"?>
<selector  xmlns:android="http://schemas.android.com/apk/res/android">
    <!-- 正常状态 -->
    <item  android:drawable="@drawable/btn_normal"  android:state_pressed="false"/>
    <!-- 按下状态 -->
    <item  android:drawable="@drawable/btn_pressed"  android:state_pressed="true"/>
</selector>
```

- - btn_normal.xml

```java
<?xml version="1.0" encoding="utf-8"?>
<shape
     xmlns:android="http://schemas.android.com/apk/res/android"
    android:shape="rectangle">
    <!-- 圆角的半径 -->
    <corners android:radius="30dp"/>
    <!-- 填充颜色 -->
    <solid android:color="#3a8fea"/>
</shape>
```

- - btn_pressed.xml

```java
<?xml version="1.0" encoding="utf-8"?>
<shape  xmlns:android="http://schemas.android.com/apk/res/android">
    <!-- 圆角的半径 -->
    <corners android:radius="30dp"/>
    <!-- 填充颜色 -->
    <solid android:color="#00ff00"/>
</shape>
```



### 7.线性布局

- > <img src="assets/a7a98c6f02d6c628be353f27da531e70-309612" alt="img" style="zoom:67%;" />

- 实现样式

  > <img src="assets/1efb732c6fc42ab3fd762c47944a2d53-13203" alt="img" style="zoom: 33%;" />

代码

```java
<RelativeLayout  xmlns:android="http://schemas.android.com/apk/res/android"
     xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    tools:context=".MainActivity" >
    <LinearLayout
        android:layout_width="match_parent"
        android:layout_height="100dp"
        android:layout_centerInParent="true"
        android:background="#A6FFA6"
        android:orientation="horizontal" >
        <LinearLayout
            android:layout_width="0dp"
            android:layout_height="100dp"
            android:layout_weight="1"
            android:background="#00ff00"
            android:divider="@drawable/fenge"
            android:dividerPadding="4dp"
            android:orientation="vertical"
            android:showDividers="middle" >
            <TextView
                 android:layout_width="match_parent"
                android:layout_height="0dp"
                android:layout_weight="1"
                android:background="#778899"
                android:gravity="center"
                android:text="账号" />
            <TextView
                 android:layout_width="match_parent"
                android:layout_height="0dp"
                android:layout_weight="1"
                android:background="#778899"
                android:gravity="center"
                android:text="密码" />
        </LinearLayout>
        <LinearLayout
            android:layout_width="0dp"
            android:layout_height="50dp"
            android:layout_weight="5"
            android:background="#0000ff"
            android:divider="@drawable/fenge"
            android:dividerPadding="4dp"
            android:orientation="vertical"
            android:showDividers="middle" >
            <EditText
                 android:layout_width="match_parent"
                android:layout_height="0dp"
                android:layout_weight="1" />
            <EditText
                 android:layout_width="match_parent"
                android:layout_height="0dp"
                android:layout_weight="1" />
        </LinearLayout>
    </LinearLayout>
</RelativeLayout>
```

插入水平线

> ![img](assets/30d3ab36afcd7b900603f2eb6ecae35d-3841)

代码

```java
<?xml version="1.0" encoding="utf-8"?>
<shape  xmlns:android="http://schemas.android.com/apk/res/android"
    android:shape="line"
     >
    <size
        android:width="200dp"
        android:height="2dp"
        />
    <stroke android:color="#000000"
        />
</shape>
```



### 8.按键响应的第一种方式（xml中的onclick属性）

- 在xml中设置按键的onclick绑定的函数

```java
<RelativeLayout  xmlns:android="http://schemas.android.com/apk/res/android"
     xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
     android:paddingBottom="@dimen/activity_vertical_margin"
     android:paddingLeft="@dimen/activity_horizontal_margin"
     android:paddingRight="@dimen/activity_horizontal_margin"
     android:paddingTop="@dimen/activity_vertical_margin"
    tools:context=".MainActivity" >
    <Button
        android:id="@+id/button1"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:onClick="buttonCliecked"
        android:text="按键" />
    <Button
        android:id="@+id/button2"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_alignLeft="@+id/button1"
        android:layout_below="@+id/button1"
        android:layout_marginTop="74dp"
        android:onClick="buttonCliecked"
        android:text="按键2" />
</RelativeLa
```

- 在MainActivity.java中添加程序，记得添加包（ctrl+shift+o）

```java
package com.example.yhq;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;
public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
   public void buttonCliecked(View v) {       //v是返回的数据
       
       System.out.println(v.getId());
       
       switch(v.getId()) {
       case R.id.button1:
           System.out.println("按键1被按下");
         //Toast类，this是调用者的类的指针，二是显示的内容，三是显示的时长
         //.show可在app中显示提示信息
           Toast.makeText(this, "按键1被按下",  0).show();
           break;
       case R.id.button2:
           System.out.println("按键2被按下");
         //Toast类，this是调用者的类的指针，二是显示的内容，三是显示的时长
           Toast.makeText(this, "按键2被按下",  0).show();
           break;
       }
   }
    
}
```



### 9.按键响应的第二种方式（接口类）

安卓开发中的监听器（onclicklistener）

- 自定义类实现按键监听事件的接口
- 通过findViewByld绑定局部变量button和xml中的button
- 实现接口类，在类中实现onclieck方法，写业务代码
- 为1.2两步做的准备进行绑定，使得按键被按下后执行业务代码

```java
package com.example.yhq;


import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

class MyClieckHandler implements View.OnClickListener {

    @Override
    public void onClick(View v) {
        // TODO 自动生成的方法存根
           switch(v.getId()) {
           case R.id.button1:
               System.out.println("按键1被按下");
               break;
           case R.id.button2:
               System.out.println("按键2被按下");        
               break;
           }
    }
}


public class MainActivity extends Activity {


    Button btn1;  //此时为野指针         定义局部变量
    Button btn2;
        
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //通过方法将其与按钮组件联系起来，此处需要强转换
        btn1 = (Button)findViewById(R.id.button1);                 //绑定xml
        btn2 = (Button)findViewById(R.id.button2);
        
        btn1.setOnClickListener(new MyClieckHandler());            //设置监听器
        btn2.setOnClickListener(new MyClieckHandler());
              
    }
}
```



### 9.按键响应的第三种方式（匿名内部类）

```java
package com.example.yhq;


import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;


public class MainActivity extends Activity {


    Button btn1;  //此时为野指针
    Button btn2;
        
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //通过方法将其与按钮组件联系起来，此处需要强转换
        btn1 = (Button)findViewById(R.id.button1);
        btn2 = (Button)findViewById(R.id.button2);
        //匿名内部类,由于没有名字，需要现场建类实现里面的接口
        btn1.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View arg0) {
                // TODO 自动生成的方法存根
                System.out.println("按键1被按下");


            }
        });  
        btn2.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View arg0) {
                // TODO 自动生成的方法存根
                System.out.println("按键2被按下");    
            }
        });
    }
}

```



### 10.按键响应的第四种方式（Activity_P）

```java
package com.example.yhq;


import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
//为整个页面实现一个onClick这个接口，具备点击的事件处理，也要让btn跟页面功能建立联系
public class MainActivity extends Activity implements View.OnClickListener {


    Button btn1;  //此时为野指针
    Button btn2;
        
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //通过方法将其与按钮组件联系起来，此处需要强转换
        btn1 = (Button)findViewById(R.id.button1);
        btn2 = (Button)findViewById(R.id.button2);
        
        btn1.setOnClickListener(this);
        btn2.setOnClickListener(this);
        
    }


    @Override
    public void onClick(View v) {
        // TODO 自动生成的方法存根
         switch(v.getId()) {
         case R.id.button1:
             System.out.println("按键1被按下");
             break;
         case R.id.button2:
             System.out.println("按键2被按下");        
             break;
    }
    }
}

```



### 11.安卓页面跳转

创建新页面

- 新建，右键src新建other

  > ![img](assets/1361bfbb7aaac33a2b05b93015bc7ec5-1656)

  > ![img](assets/60036f8dc41665922746ebcba15e1424-727)

  > ![img](assets/1105574f739574209db8a61a69fa353f-9980)

```java
package com.example.yhq;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    public void goSecond(View v) {
     //intent去设置要跳转的页面                       //当前页面，跳转页面的类
        Intent intent = new Intent(this,  SecondActivity.class);
        //跳转
        startActivity(intent);
    }   
}
```

```java
     <Button
        android:id="@+id/button1"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:onClick="goSecond"
        android:text="跳转到第二个页面" />
```

#### 页面跳转传参方式一

- 修改第一个页面的程序，使其传递数据

```java
package com.example.yhq;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    public void goSecond(View v) {
     //intent去设置要跳转的页面                       //当前页面，跳转页面的类
        Intent intent = new Intent(this,  SecondActivity.class);
                     //键                           值
        intent.putExtra("MyData", "皓清很帅");
        
        //跳转
        startActivity(intent);
    }   
}
```

- 修改第二个页面的程序，使其接收数据

```java
package com.example.yhq;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;
public class SecondActivity extends Activity {
    private String data;
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);
        
        Intent i = this.getIntent();
        data = i.getStringExtra("MyData");
        System.out.println("收到数据, "+data);
        Toast.makeText(this, "收到数据"+data,  0).show();
    }
    public void goThird(View v) {
     //intent去设置要跳转的页面                       //当前页面，跳转页面的类
        Intent intent = new Intent(this,  ThirdActivity.class);
        //跳转
        startActivity(intent);
    }   
}
```

#### 页面跳转传参方式二

- 修改第一个页面的程序，使其传递数据

```java
package com.example.yhq;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    public void goSecond(View v) {
     //intent去设置要跳转的页面                       //当前页面，跳转页面的类
        Intent intent = new Intent(this,  SecondActivity.class);
        Bundle bundle = new Bundle();
        bundle.putString("MyData", "皓清很帅");
        bundle.putInt("ID", 100);
        intent.putExtras(bundle);
        //跳转
        startActivity(intent);
    }   
}
```

- 修改第二个页面的程序，使其接收数据

```java
package com.example.yhq;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;
public class SecondActivity extends Activity {
    private String data;
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);
        
        Intent i = this.getIntent();
        Bundle b = i.getExtras();
        String data = b.getString("MyData");
        int data2 = b.getInt("ID");
        Toast.makeText(this, "收到数据"+data,  0).show();
    }
    public void goThird(View v) {
     //intent去设置要跳转的页面                       //当前页面，跳转页面的类
        Intent intent = new Intent(this,  ThirdActivity.class);
        //跳转
        startActivity(intent);
    }   
}
```



### 12.安卓线程实现页面的自动跳转

```java
package com.example.yhq;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
      //实例化一个线程，使用构造方法来初始化，即通过接口Runnable设置新线程要执行的任务
        Thread t = new Thread(new Runnable() {
            
            @Override
            public void run() {
                // TODO 自动生成的方法存根
                 try {   //sleep会睡眠UI线程的刷新，所以要在新线程中使用sleep
                        Thread.sleep(3000);
                    } catch  (InterruptedException e) {
                        // TODO 自动生成的 catch  块
                        e.printStackTrace();
                    }
                 //intent去设置要跳转的页面                       //当前页面，跳转页面的类
                    Intent intent = new  Intent(MainActivity.this, SecondActivity.class);
                    //跳转
                    startActivity(intent);
            }
        }); //实例化一个线程
        t.start(); //启动线程
    }  
}
```



### 13.Activity(页面)的生命周期

> <img src="assets/f03b81f9a6e64def4578f9071b8034d1-78704" alt="img" style="zoom:67%;" />

- 1.启动Activity：系统会先调用onCreate方法，然后调用onStart方法，最后调用onResume，Activity进入运行状态。
- 2.当前Activity被其他Activity覆盖其上或被锁屏：系统会调用onPause方法，暂停当前Activity的执行。
- 3.当前Activity由被覆盖状态回到前台或解锁屏：系统会调用onResume方法，再次进入运行状态。
- 4.当前Activity转到新的Activity界面或按Home键回到主屏，自身退居后台：系统会先调用onPause方法，然后调用onStop方法，进入停滞状态。
- 5.用户后退回到此Activity：系统会先调用onRestart方法，然后调用onStart方法，最后调用onResume方法，再次进入运行状态。
- 6.当前Activity处于被覆盖状态或者后台不可见状态，即第2步和第4步，系统内存不足，杀死当前Activity，而后用户退回当前Activity：再次调用onCreate方法、onStart方法、onResume方法，进入运行状态。
- 7.用户退出当前Activity：系统先调用onPause方法，然后调用onStop方法，最后调用onDestory方法，结束当前Activity。



### 14.安卓Socket客户端开发

> ![img](assets/0adc9407f34c2c5a76ad46355711b587-3955)

- activity_main.xml

```java
<RelativeLayout  xmlns:android="http://schemas.android.com/apk/res/android"
     xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
     android:paddingBottom="@dimen/activity_vertical_margin"
     android:paddingLeft="@dimen/activity_horizontal_margin"
     android:paddingRight="@dimen/activity_horizontal_margin"
     android:paddingTop="@dimen/activity_vertical_margin"
    tools:context=".MainActivity" >
    <Button
        android:id="@+id/fh"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_above="@+id/left"
        android:layout_alignLeft="@+id/back"
        android:layout_marginBottom="20dp"
        android:onClick="sendMessage"
        android:text="前进" />
    <Button
        android:id="@+id/right"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_above="@+id/back"
        android:layout_alignParentRight="true"
        android:layout_marginRight="31dp"
        android:onClick="sendMessage"
        android:text="右转" />
    <Button
        android:id="@+id/left"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_alignParentLeft="true"
        android:layout_centerVertical="true"
        android:layout_marginLeft="32dp"
        android:onClick="sendMessage"
        android:text="左转" />
    <Button
        android:id="@+id/back"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_below="@+id/left"
        android:layout_centerHorizontal="true"
        android:layout_marginTop="27dp"
        android:onClick="sendMessage"
        android:text="后退" />
</RelativeLayout>
```

- MainActivity.java

```java
package com.example.hq;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import com.example.hq.nets.NetUtils;
public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    public void sendMessage(View v) {
        switch (v.getId()) {
        case R.id.fh:
            NetUtils.sendMessageHandler("goforward");
            break;
        case R.id.back:
            NetUtils.sendMessageHandler("goback");
            break;
        case R.id.right:
            NetUtils.sendMessageHandler("goright");
            break;
        case R.id.left:
            NetUtils.sendMessageHandler("goleft");
            break;
        }
    }
}
```

- NetUtils.java

```java
package com.example.hq.nets;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
public class NetUtils {
    public static void sendMessageHandler(final  String command) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                // TODO 自动生成的方法存根
                try {
                    Socket client = new  Socket("192.168.3.5", 8806);// 创建套接字
                    OutputStream out =  client.getOutputStream(); // 获得数据发送通道
                    out.write(command.getBytes()); // 发送数据
                    InputStream in =  client.getInputStream(); // 获得数据接收通道
                    int len;
                    byte[] data = new byte[128];
                    len = in.read(data);// 接收通道接收数据
                    System.out.println("获得服务器端返回数据是："
                            + new String(data,  0, len));
                } catch (IOException e) {
                    // TODO 自动生成的 catch 块
                    e.printStackTrace();
                }
            }
        }).start();
    }
}
```



### 15.实现倒计时10s——非UI控件想要修改线程，使用Handler类解决

- MainActivity.java

```java
package com.example.hq;
import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.TextView;
public class MainActivity extends Activity {
    
    public TextView textView;
    
    public Handler h;
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        //关联UI控件，需要类型强制转换
        textView = (TextView)  findViewById(R.id.textView);
        
        h = new Handler() {  //UI主线程的家里的电话，处理一些其他进程无法处理的事件
         @Override
         public void handleMessage(Message msg) {   //区分事件的类型
             // TODO 自动生成的方法存根
             super.handleMessage(msg);
             textView.setText(msg.what+"s");   //接到电话则会修改控件
         }
        };    
    }
    public void testFunc(View v) {
     
     new Thread(new Runnable() {
            
            @Override
            public void run() {
                // TODO 自动生成的方法存根
                for (int i = 10; i >= 0; i--) {
                    System.out.println("yhq"+i);
                    Message msg = new Message();
                    msg.what = i;
                    //打电话，去把UI要显示、处理的事件交给UI线程的Handler去做
                    h.sendMessage(msg);
                    try {
                        Thread.sleep(1000);
                    } catch  (InterruptedException e) {
                        // TODO 自动生成的 catch  块
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }
    
}
```

- 注，导Handler包时，选第一个

> <img src="assets/b0374501f651187a3fb8ed966ddf475b-8368" alt="img" style="zoom:67%;" />

- activity_main.xml

```java
<RelativeLayout  xmlns:android="http://schemas.android.com/apk/res/android"
     xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:background="#000000"
    tools:context=".MainActivity" >
    <TextView
        android:id="@+id/textView"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_centerInParent="true"
        android:textSize="40dp"
        android:textColor="#ffffff"
        android:textStyle="bold"
        android:text="倒计时10s" />
    <Button
        android:id="@+id/button1"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
         
        android:onClick="testFunc"
        android:text="开始" />
</RelativeLayout>
```



### 16.安卓客户端可收发并刷新UI控件显示

- activity_main.xml

```java
<RelativeLayout  xmlns:android="http://schemas.android.com/apk/res/android"
     xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:background="#000000"
    tools:context=".MainActivity" >
    <Button
        android:id="@+id/fh"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
         android:textColor="#ffffff"
         
        android:onClick="sendMessage"
        android:text="发起网络请求" />
    <TextView
        android:id="@+id/tx"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:textColor="#ffffff"
        android:textSize="35dp"
        android:layout_centerInParent="true"
        android:text="接收内容显示"
        />
</RelativeLayout>
```

- MainActivity.java

```java
package com.example.hq;
import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.TextView;
import com.example.hq.nets.NetUtils;
public class MainActivity extends Activity {
    Handler handler;
    TextView tx;
    
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        tx = (TextView)findViewById(R.id.tx);
        
        handler = new Handler() {
            private CharSequence String;
            public void handleMessage(Message  msg) {
                super.handleMessage(msg);
                Bundle b = msg.getData();
                String string =  b.getString("msg");
                
                tx.setText(string);
            }
        
        };
    }
    public void sendMessage(View v) {
        switch (v.getId()) {
        case R.id.fh:
            NetUtils.sendMessageHandler("goforward",  handler);
            break;
        }
    }
}
```

- NetUtils.java

```java
package com.example.hq.nets;


import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;


import android.os.Bundle;
import android.os.Handler;
import android.os.Message;


public class NetUtils {


    public static void sendMessageHandler(final String command,final Handler h) {


        new Thread(new Runnable() {


            @Override
            public void run() {
                // TODO 自动生成的方法存根
                try {
                    Socket client = new Socket("192.168.3.5", 8806);// 创建套接字
                    OutputStream out = client.getOutputStream(); // 获得数据发送通道
                    out.write(command.getBytes()); // 发送通道发送数据
                    
                    InputStream in = client.getInputStream(); // 获得数据接收通道
                    int len;
                    byte[] data = new byte[128];
                    len = in.read(data);// 接收通道接收数据
                    String str = new String(data, 0, len);
                    Message msg = new Message();
                    
                    Bundle b = new Bundle();
                    b.putString("msg", str);
                    msg.setData(b);
                    
                    h.sendMessage(msg);
                    
                    
                } catch (IOException e) {
                    // TODO 自动生成的 catch 块
                    e.printStackTrace();
                }
            }
        }).start();


    }
}

```



### 17.WebView控件的使用

- https://blog.csdn.net/weixin_40438421/article/details/85700109

- 增加访问权限

  > ![img](assets/dd870f393d8e2b8d6fc787263da5a24a-2767)

  > <img src="assets/482508c727ebb35918cf9d53e2b0e136-21046" alt="img" style="zoom:50%;" />

  > <img src="assets/f142b074b84a9061dc9bbfd3f5c57af6-6291" alt="img" style="zoom: 67%;" />

或者直接在.xml文件中输入

```
<uses-permission  android:name="android.permission.INTERNET"/>
```

保存

MainActivity.java

```java
package com.example.hq;
import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.EditText;
import android.widget.TextView;
public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    
    final WebView wb =  (WebView)findViewById(R.id.webView1);
    wb.setWebViewClient(new WebViewClient());//使用自带浏览器
    
    final EditText ed = (EditText)  findViewById(R.id.ed);
    ed.setOnEditorActionListener(new  TextView.OnEditorActionListener() {
        
        @Override
        public boolean onEditorAction(TextView  arg0, int arg1, KeyEvent event) {
            // TODO 自动生成的方法存根
            String str =  ed.getText().toString();
            wb.loadUrl(str);
            return (event.getKeyCode() ==  KeyEvent.KEYCODE_ENTER);
        }
    });   
    }
}
```

activity_main.xml

```java
<RelativeLayout  xmlns:android="http://schemas.android.com/apk/res/android"
     xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    tools:context=".MainActivity" >
    <LinearLayout
        android:id="@+id/ll"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        >
        <EditText
            android:id="@+id/ed"
            android:layout_width="match_parent"
            android:layout_height="match_parent"
            android:hint="请输入网址"
            />
        
        
        
    </LinearLayout>
    
    <WebView
        android:id="@+id/webView1"
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:layout_below="@+id/ll" >
    </WebView>
</RelativeLayout>
```



### 18.智能家居项目APP开发

- activity_main.xml（主页面布局设置）

```java
<RelativeLayout  xmlns:android="http://schemas.android.com/apk/res/android"
     xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:background="@drawable/bg5"
    tools:context=".MainActivity" >
    <WebView
        android:id="@+id/webView1"
        android:layout_width="match_parent"
        android:layout_height="388dp"
        android:layout_marginTop="0dp"
        android:layout_centerHorizontal="true"/>
    
    <LinearLayout
        android:id="@+id/ll1"
        android:layout_marginTop="140dp"
        android:layout_below="@id/webView1"
        android:layout_width="300dp"
        android:layout_height="130dp"
        android:orientation="horizontal"  
        android:layout_centerHorizontal="true"
        
        >
        <LinearLayout
            android:layout_weight="1"
            android:layout_width="0dp"
            android:layout_height="130dp"
            android:orientation="vertical"
            >
           <TextView
                android:layout_height="wrap_content"
               android:layout_width="wrap_content"
               android:text="温度 ："
               android:textSize="25sp"
               android:textStyle="bold"
               android:textColor="#ffffff"
               android:layout_weight="1" />
           <TextView
                android:layout_height="wrap_content"
               android:layout_width="wrap_content"
               android:text="湿度："
               android:textSize="25sp"
               android:textStyle="bold"
               android:textColor="#ffffff"
               android:layout_weight="1" />
           <TextView
                android:layout_height="wrap_content"
               android:layout_width="wrap_content"
               android:text="火警："
               android:textSize="25sp"
               android:textStyle="bold"
               android:textColor="#ffffff"
               android:layout_weight="1" />
        </LinearLayout>
        
        <LinearLayout
            android:layout_weight="1"
            android:layout_width="0dp"
            android:layout_height="130dp"
            android:orientation="vertical"
            >
            <TextView
                android:layout_height="wrap_content"
               android:layout_width="wrap_content"
               android:text="26摄氏度"
               android:textSize="24sp"
               android:textStyle="bold"
               android:textColor="#ffffff"
               android:layout_weight="1" />
           <TextView
                android:layout_height="wrap_content"
               android:layout_width="wrap_content"
               android:text="68%湿度"
               android:textSize="24sp"
               android:textStyle="bold"
               android:textColor="#ffffff"
               android:layout_weight="1" />
           <TextView
                android:layout_height="wrap_content"
               android:layout_width="wrap_content"
               android:text="正常运行中"
               android:textSize="24sp"
               android:textStyle="bold"
               android:textColor="#ffffff"
               android:layout_weight="1" />
                               
        </LinearLayout>
        
    </LinearLayout>
    
    <LinearLayout
        android:layout_marginTop="40dp"
        android:layout_below="@id/ll1"
        android:layout_width="500dp"
        android:layout_height="76dp"
        android:orientation="horizontal"  
        android:layout_centerHorizontal="true"
        
        >
        <Button
            android:layout_weight="1"
            android:layout_margin="20dp"
            android:layout_width="0dp"
            android:background="@drawable/z1"
            android:layout_height="wrap_content"
            />
        <Button
            android:layout_weight="1"
            android:layout_width="0dp"
            android:layout_margin="20dp"
            android:background="@drawable/z2"
            android:layout_height="wrap_content"
            />
        <Button
            android:layout_weight="1"
            android:layout_width="0dp"
            android:layout_margin="20dp"
            android:background="@drawable/z3"
            android:layout_height="wrap_content"
            />
        <Button
            android:layout_weight="1"
            android:layout_width="0dp"
            android:layout_margin="20dp"
            android:background="@drawable/z4"
            android:layout_height="wrap_content"
            />
        <Button
            android:layout_weight="1"
            android:layout_width="0dp"
            android:layout_margin="20dp"
            android:background="@drawable/z5"
            android:layout_height="wrap_content"
            />
    </LinearLayout>
    
</RelativeLayout>
```

- MainActivity.java（主页面程序）

```java
package com.example.hq;
import android.app.Activity;
import android.os.Bundle;
import android.webkit.WebView;
import android.webkit.WebViewClient;
public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    
        WebView wb = (WebView)  findViewById(R.id.webView1);
        wb.loadUrl("https://tianqi.2345.com/");
        wb.setWebViewClient(new WebViewClient());
    
    
    }
}
```

- activity_main.xml（启动页面布局设置）

```java
<RelativeLayout  xmlns:android="http://schemas.android.com/apk/res/android"
     xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:background="@drawable/bg"
    tools:context=".WelcomeActivity" >
     
    <TextView
        android:id="@+id/textView"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:textColor="#ffffff"
        android:layout_alignParentRight="true"
        android:layout_margin="30dp"
        
        
        />
</RelativeLayout>
```

- WelcomeActivity.java（启动页面程序）

```java
package com.example.hq;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.TextView;
public class WelcomeActivity extends Activity {
    TextView textview;  
    Handler h;
    @Override
    protected void onCreate(Bundle  savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_welcome);
    
    
        textview = (TextView)  findViewById(R.id.textView);
        h = new Handler() {
            @Override
            public void handleMessage(Message  msg) {
                // TODO 自动生成的方法存根
                super.handleMessage(msg);
                textview.setText(msg.what+"s");
                
            }
        };
        
        new Thread(new Runnable() {
            
            @Override
            public void run() {
                // TODO 自动生成的方法存根
                for (int i = 3; i > 0; i--) {
                    Message msg = new Message();
                    msg.what = i;
                    h.sendMessage(msg);
                    try {
                        Thread.sleep(1000);
                    } catch  (InterruptedException e) {
                        // TODO 自动生成的 catch  块
                        e.printStackTrace();
                    }
                }
                Intent intent = new  Intent(WelcomeActivity.this,  MainActivity.class);
                startActivity(intent);  //启动页面
            }
        }).start();
    
    
    
    }
}
```

- AndroidMainifest.xml

```java
<?xml version="1.0" encoding="utf-8"?>
<manifest  xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.example.hq"
    android:versionCode="1"
    android:versionName="1.0" >
    <uses-sdk
        android:minSdkVersion="8"
        android:targetSdkVersion="18" />
    <uses-permission  android:name="android.permission.INTERNET"/>
    <application
        android:allowBackup="true"
        android:icon="@drawable/ic_launcher"
        android:label="@string/app_name"
        android:theme="@style/AppTheme" >
        <activity
             android:name="com.example.hq.MainActivity"
            android:label="@string/app_name" >
          
        </activity>
       
        <activity
             android:name="com.example.hq.WelcomeActivity"
             android:label="@string/title_activity_welcome" >
               <intent-filter>
                <action  android:name="android.intent.action.MAIN" />
                <category  android:name="android.intent.category.LAUNCHER"  />
            </intent-filter>
        </activity>
    </application>
</manifest>
```

- 包资源管理

  > <img src="assets/a5deda695e89c7867afe71a67fa4b010-18699" alt="img" style="zoom:67%;" />

- 实际界面展示

  > <img src="assets/98ef99a09c274805f576ca2c1f40a1bf-2289777" alt="img" style="zoom:50%;" />





































































































































































