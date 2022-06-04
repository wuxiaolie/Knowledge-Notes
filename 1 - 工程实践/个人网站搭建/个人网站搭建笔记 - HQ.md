## 个人网站搭建流程笔记 - HQ

[TOC]

------

#### 注意

- 

------

## 第二次网站搭建流程 2022

### 个人网站的目标效果 - 搭建在服务器上

- https://interviewguide.cn/notes/01-guide/web-guide-reading.html#%E4%B8%80%E3%80%81%E6%9C%AC%E7%AB%99%E7%9F%A5%E8%AF%86%E9%80%9F%E8%A7%88

  > ![image-20220602140906727](assets/assets.个人网站搭建笔记 - HQ/image-20220602140906727-16541501490801.png)

- https://xiaolincoding.com/network/1_base/what_happen_url.html#%E5%AD%A4%E5%8D%95%E5%B0%8F%E5%BC%9F-http

  > <img src="assets/assets.个人网站搭建笔记 - HQ/image-20220602140939939.png" alt="image-20220602140939939"  />

- https://programmercarl.com/%E5%89%8D%E5%BA%8F/%E7%A8%8B%E5%BA%8F%E5%91%98%E7%AE%80%E5%8E%86.html#%E7%AE%80%E5%8E%86%E7%AF%87%E5%B9%85

  > ![image-20220602141010355](assets/assets.个人网站搭建笔记 - HQ/image-20220602141010355.png)

- https://www.r2coding.com/#/README?id=api%e7%ae%a1%e7%90%86%e6%96%87%e6%a1%a3%e7%ae%a1%e7%90%86

  > ![image-20220602141034216](assets/assets.个人网站搭建笔记 - HQ/image-20220602141034216.png)

### 个人网站的目标效果 - 搭建在GitHub上

- http://www.openedv.com/docs/boards/arm-linux/zdyz-i.mx6ull.html

  > ![image-20220602141135207](assets/assets.个人网站搭建笔记 - HQ/image-20220602141135207.png)

- http://download.100ask.net/books/Linux/ELADCMFor4412/index.html

  > ![image-20220602141201078](assets/assets.个人网站搭建笔记 - HQ/image-20220602141201078.png)



### 搭建方案

#### 在服务器上搭建博客

第一种网站搭建方式涉及到前端后端，而且要使用自己的服务器，虽然自己有服务器，但是2021年按照教程搭建失败了，而且学习成本比较高，目前不推荐，后面维护起来可能也有难度，先尝试后面的几种方案。

#### 在GitHub上搭建博客

目标效果如上一节第二种网站效果。

可以采用多种工具实现。

##### 工具一 - SPHINX

采用工具：https://www.sphinx-doc.org/en/master/

> ![image-20220602141522575](assets/assets.个人网站搭建笔记 - HQ/image-20220602141522575.png)

参考教程：https://docs.readthedocs.io/en/stable/tutorial/

> ![image-20220602141404012](assets/assets.个人网站搭建笔记 - HQ/image-20220602141404012.png)

参考主题：https://github.com/readthedocs/sphinx_rtd_theme

> ![image-20220602141441922](assets/assets.个人网站搭建笔记 - HQ/image-20220602141441922.png)

其他教程：https://www.bilibili.com/read/cv11923872

https://www.bilibili.com/video/BV1S5411T7Qg?spm_id_from=333.337.search-card.all.click

好像还是会出现图片显示的问题，而且使用这个工具还需要安装配置，所以选择使用工具二HEXO。

> ![image-20220602145155621](assets/assets.个人网站搭建笔记 - HQ/image-20220602145155621.png)

##### 工具二 - HEXO

推荐教程

https://www.cnblogs.com/huanhao/p/hexobase.html

参考教程

https://wushishu.xyz/post/be8880ea.html

https://www.bilibili.com/video/BV1NY4y1C7Ng?spm_id_from=333.337.search-card.all.click

https://www.bilibili.com/video/BV1aV411p7Bc/?spm_id_from=333.788



### 搭建流程 - 采用HEXO+GitHub

参考教程：https://www.bilibili.com/video/BV1Xh411b7wh?p=3

1. GitHub新建仓库（仓库名称需要.github.io形式），并关联到本地文件夹

   > ![image-20220602150931036](assets/assets.个人网站搭建笔记 - HQ/image-20220602150931036.png)
   >
   > ![image-20220602150644278](assets/assets.个人网站搭建笔记 - HQ/image-20220602150644278.png)

2. 启用Page功能

   > ![image-20220602153644166](assets/assets.个人网站搭建笔记 - HQ/image-20220602153644166.png)

3. 挑选模板来建站。

   - 官方模板网站：https://hexo.io/themes/

   - 本次使用模板网址：https://github.com/kitian616/jekyll-TeXt-theme，下载后放到git文件夹中，然后push到仓库，效果如下

     该主题教程网址：https://tianqi.name/jekyll-TeXt-theme/docs/zh/quick-start

     > ![image-20220602153732501](assets/assets.个人网站搭建笔记 - HQ/image-20220602153732501.png)

4. 修改模板配置文件，来修改主题，添加自己的博客文章。配置介绍参考README文档。

   - ![image-20220602153306073](assets/assets.个人网站搭建笔记 - HQ/image-20220602153306073.png)

   - 修改蓝色字符串即为修改配置。

     > ![image-20220602153934378](assets/assets.个人网站搭建笔记 - HQ/image-20220602153934378.png)

     参考修改样式。

     > ![image-20220602154046967](assets/assets.个人网站搭建笔记 - HQ/image-20220602154046967.png)

   - 添加博客推文。所有的推文都放在_posts文件夹下。

     > ![image-20220602154336400](assets/assets.个人网站搭建笔记 - HQ/image-20220602154336400.png)

   - 撰写博客需要遵守的规范：https://tianqi.name/jekyll-TeXt-theme/docs/zh/writing-posts

     > ![image-20220602154640683](assets/assets.个人网站搭建笔记 - HQ/image-20220602154640683.png)
     >
     > ![image-20220602154655435](assets/assets.个人网站搭建笔记 - HQ/image-20220602154655435.png)

5. 根据主题教程网址：https://tianqi.name/jekyll-TeXt-theme/docs/zh/quick-start，来定制自己的博客。

   > ![image-20220602162508273](assets/assets.个人网站搭建笔记 - HQ/image-20220602162508273.png)


6. 搞了半天，弄完了，效果如下。

   https://wuxiaolie.github.io/hq.github.io/

   > ![image-20220602201511115](assets/assets.个人网站搭建笔记 - HQ/image-20220602201511115.png)

   https://wuxiaolie.github.io/hq.github.io/archive.html

   > ![image-20220602201655701](assets/assets.个人网站搭建笔记 - HQ/image-20220602201655701.png)

   https://wuxiaolie.github.io/hq.github.io/about.html

   > ![image-20220602201820188](assets/assets.个人网站搭建笔记 - HQ/image-20220602201820188.png)

   https://wuxiaolie.github.io/hq.github.io/2022/06/01/Welcome-to-my-blog.html

   > ![image-20220602201544495](assets/assets.个人网站搭建笔记 - HQ/image-20220602201544495.png)
   >
   > ![image-20220602201558872](assets/assets.个人网站搭建笔记 - HQ/image-20220602201558872.png)

   https://wuxiaolie.github.io/hq.github.io/2022/06/01/VisitorMS.html

   > ![image-20220602201613250](assets/assets.个人网站搭建笔记 - HQ/image-20220602201613250.png)
   >
   > ![image-20220602201642751](assets/assets.个人网站搭建笔记 - HQ/image-20220602201642751.png)

7. 但是文章中无法链接图片，排查来了好久也没解决，未来再解决吧。





## 第一次网站搭建流程 2021

### 根据视频教程进行操作[b站教程](https://www.bilibili.com/video/BV113411s7sM?from=search&seid=7437796492034320907&spm_id_from=333.337.0.0)

1. 终端内安装宝塔软件
   - [宝塔Linux安装网址](https://www.bt.cn/bbs/thread-19376-1-1.html)
   - 注意：不能安装在docker中，只能安装在本地
   - Ubuntu安装脚本 `wget -O install.sh http://download.bt.cn/install/install-ubuntu_6.0.sh && sudo bash install.sh 6dca892c`
   - 安装成功![image-20211225171020400](assets/image-20211225171020400.png)
   
2. 设置安全组，开放服务器8888端口
   - [教程网址](https://www.bt.cn/bbs/thread-2897-1-1.html)
   
3. 登录外网面板地址，按照视频教程进行操作
   - 如果提示不能添加站点，则在面板软件商城中卸载重新安装Nginx
   
   - ![image-20211225175458375](assets/image-20211225175458375.png)
   
   - 修改/www/wwwroot/你的网站域名里面index.html
   
   - ```html
     <!doctype html>
     <html>
     <head>
         <meta charset="utf-8">
         <title>圣诞快乐</title>
         <style>
             .container {
                 width: 60%;
                 margin: 10% auto 0;
                 background-color: #f0f0f0;
                 padding: 2% 5%;
                 border-radius: 10px
             }
     
             ul {
                 padding-left: 20px;
             }
     
                 ul li {
                     line-height: 2.3
                 }
     
             a {
                 color: #20a53a
             }
         </style>
     </head>
     <body>
         <div class="container">
             <h1>老婆，圣诞节快乐！</h1>
             <h3>来自皓清的祝福</h3>
             <ul>
                 <li>如果可以，我只要一杯清水，一片面包，一枝花。</li>
                 <li>如果再奢侈一些，我希望水是你倒的，面包是你切的，花是你送的。</li>
                 <li>最后，我想说，你是我的，爱你呦！</li>
             </ul>
         </div>
     </body>
     </html>
   
   - ![image-20211225191828452](assets/image-20211225191828452.png)
   
   - 最终还是因为配置问题宣告网站搭建失败，搞了一晚上，没找到原因，先放弃了
     - Nginx可以读取index.html文件，但是替换成index.php后提示403拒绝，导致wordpress无法安装
     - 怀疑是php配置或者未正常运行，不能执行.php的问题，由于重装了Nginx，也可能Nginx的问题
     - 回忆当时按照宝塔的一键安装，同时安装了Nginx，php等5个软件，但是后面新建站点时提示Nginx错误，然后自己就重新安装了Nginx，问题可能出现在这里，自己没有重新配置（但确实不懂）
     - 由于自己不走后端这条路，且个人网站也非必需品，所以先搁置。
     - 再附几个图
     - 在Nginx路径中![image-20211225215024974](assets/image-20211225215024974.png)
     - 错误日志为
       - ![image-20211225215339692](assets/image-20211225215339692.png)
     - 可能是这里的配置问题
       - ![image-20211225215040594](assets/image-20211225215040594.png)
     - 其中nginx.conf中的一段内容有嫌疑
       - ![image-20211225215257498](assets/image-20211225215257498.png)


### 附

1. [宝塔命令](https://www.bt.cn/btcode.html)
  
   - 执行命令要加`sudo`权限
   
2. 个人网址

   - ```
      tp573ln.cn
      www.tp573ln.cn
      47.98.147.248
      ```

      



























































































































































