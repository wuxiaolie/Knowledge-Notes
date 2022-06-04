# libcurl库介绍 - 详细 - HQ

[TOC]

------

#### 注意

- 摘自文章 https://www.cnblogs.com/heluan/p/10177475.html
- [http协议之详解（点我）](https://www.cnblogs.com/xietianjiao/p/13255099.html)
- [http协议之https（点我）](https://www.cnblogs.com/xietianjiao/p/13255408.html)
- [http协议之libcurl（点我）](https://www.cnblogs.com/xietianjiao/p/13260021.html)

------

### 一、libcurl库介绍

libcurl库是一个**多协议的便于客户端使用的URL传输库**，基于C语言，提供C语言的API接口

- 支持DICT, FILE, FTP, FTPS, Gopher, HTTP, HTTPS, IMAP, IMAPS, LDAP, LDAPS, POP3, POP3S, RTMP, RTSP, SCP, SFTP, SMTP, SMTPS, Telnet and TFTP这些协议

- 同时支持使用SSL证书的安全文件传输：HTTP POST, HTTP PUT, FTP 上传

- 基于HTTP形式的上传、代理、Cookies、用户加密码的认证等多种应用场景

- 另外，libcurl是一个高移植性的库，能在绝大多数系统上运行，包括Solaris, NetBSD, FreeBSD, OpenBSD, Darwin, HPUX, IRIX, AIX, Tru64, Linux, UnixWare, HURD, Windows, Amiga, OS/2, BeOs, Mac OS X, Ultrix, QNX, OpenVMS, RISC OS, Novell NetWare, DOS等。



### 二、使用步骤

1. 调用curl_global_init()初始化libcurl
2. 调用curl_easy_init()函数得到 easy interface型指针
3. 调用curl_easy_setopt()设置传输选项
4. 根据curl_easy_setopt()设置的传输选项，实现回调函数以完成用户特定任务
5. 调用curl_easy_perform()函数完成传输任务
6. 调用curl_easy_cleanup()释放内存
7. 调用curl_global_cleanup()析构libcurl

**在整过过程中设置curl_easy_setopt()参数是最关键的**，几乎所有的libcurl程序都要使用它。

在基于LibCurl的程序里，**主要采用callback function （回调函数）的形式完成传输任务**，用户在启动传输前设置好各类参数和回调函数，当满足条件时libcurl将调用用户的回调函数实现特定功能。



### 三、函数说明

#### 1 CURLcode curl_global_init(long flags);

描述：
这个函数只能用一次。(其实在调用curl_global_cleanup 函数后仍然可再用)
如果这个函数在curl_easy_init函数调用时还没调用，它讲由libcurl库自动调用，所以多线程下最好主动调用该函数以防止在线程中curl_easy_init时多次调用。

注意：虽然libcurl是线程安全的，但curl_global_init是不能保证线程安全的，所以不要在每个线程中都调用curl_global_init，应该将该函数的调用放在主线程中。
参数：flags
CURL_GLOBAL_ALL              //初始化所有的可能的调用。
CURL_GLOBAL_SSL              //初始化支持 安全套接字层。
CURL_GLOBAL_WIN32        //初始化win32套接字库。
CURL_GLOBAL_NOTHING      //没有额外的初始化。

#### 2 void curl_global_cleanup(void);

描述：在结束libcurl使用的时候，用来对curl_global_init做的工作清理。类似于close的函数。

注意：虽然libcurl是线程安全的，但curl_global_cleanup是不能保证线程安全的，所以不要在每个线程中都调用curl_global_init，应该将该函数的调用放在主线程中。

#### 3 char *curl_version( );

描述: 打印当前libcurl库的版本。

#### 4 CURL *curl_easy_init( );

描述:
curl_easy_init用来初始化一个CURL的指针(有些像返回FILE类型的指针一样). 相应的在调用结束时要用curl_easy_cleanup函数清理.
一般curl_easy_init意味着一个会话的开始. 它会返回一个easy_handle(CURL*对象), 一般都用在easy系列的函数中.

#### 5 void curl_easy_cleanup(CURL *handle);

描述:
这个调用用来结束一个会话.与curl_easy_init配合着用. 
参数:
CURL类型的指针.

#### 6 CURLcode curl_easy_setopt(CURL *handle, CURLoption option, parameter);

描述: 这个函数最重要了.几乎所有的curl 程序都要频繁的使用它.它告诉curl库.程序将有如何的行为. 比如要查看一个网页的html代码等.(这个函数有些像ioctl函数)参数:
1 CURL类型的指针
2 各种CURLoption类型的选项.(都在curl.h库里有定义,man 也可以查看到)
3 parameter 这个参数 既可以是个函数的指针,也可以是某个对象的指针,也可以是个long型的变量.它用什么这取决于第二个参数.
CURLoption 这个参数的取值很多.具体的可以查看man手册.

#### 7 CURLcode curl_easy_perform(CURL *handle);

描述:这个函数在初始化CURL类型的指针 以及curl_easy_setopt完成后调用. 就像字面的意思所说perform就像是个舞台.让我们设置的
option 运作起来.参数:
CURL类型的指针.

#### 8 void curl_global_cleanup(void);

释放libcurl

 

### 四、curl_easy_setopt函数部分选项介绍

本节主要介绍curl_easy_setopt中跟http相关的参数。该函数是curl中非常重要的函数，curl所有设置都是在该函数中完成的，该函数的设置选项众多，注意本节的阐述的只是部分常见选项。

#### CURLOPT_URL 

设置访问URL

#### CURLOPT_WRITEFUNCTION，CURLOPT_WRITEDATA

回调函数原型为：size_t function( void *ptr, size_t size, size_t nmemb, void *stream); 函数将在libcurl接收到数据后被调用，因此函数多做数据保存的功能，如处理下载文件。CURLOPT_WRITEDATA 用于表明CURLOPT_WRITEFUNCTION函数中的stream指针的来源。
如果你没有通过CURLOPT_WRITEFUNCTION属性给easy handle设置回调函数，libcurl会提供一个默认的回调函数，它只是简单的将接收到的数据打印到标准输出。你也可以通过 CURLOPT_WRITEDATA属性给默认回调函数传递一个已经打开的文件指针，用于将数据输出到文件里。

#### CURLOPT_HEADERFUNCTION，CURLOPT_HEADERDATA

回调函数原型为 size_t function( void *ptr, size_t size,size_t nmemb, void *stream); libcurl一旦接收到http 头部数据后将调用该函数。CURLOPT_WRITEDATA 传递指针给libcurl，该指针表明CURLOPT_HEADERFUNCTION 函数的stream指针的来源。

#### CURLOPT_READFUNCTION CURLOPT_READDATA

libCurl需要读取数据传递给远程主机时将调用CURLOPT_READFUNCTION指定的函数，函数原型是：size_t function(void *ptr, size_t size, size_t nmemb,void *stream). CURLOPT_READDATA 表明CURLOPT_READFUNCTION函数原型中的stream指针来源。

#### CURLOPT_NOPROGRESS，CURLOPT_PROGRESSFUNCTION，CURLOPT_PROGRESSDATA

跟数据传输进度相关的参数。CURLOPT_PROGRESSFUNCTION 指定的函数正常情况下每秒被libcurl调用一次，为了使CURLOPT_PROGRESSFUNCTION被调用，CURLOPT_NOPROGRESS必须被设置为false，CURLOPT_PROGRESSDATA指定的参数将作为CURLOPT_PROGRESSFUNCTION指定函数的第一个参数

#### CURLOPT_TIMEOUT，CURLOPT_CONNECTIONTIMEOUT

CURLOPT_TIMEOUT 由于设置传输时间，CURLOPT_CONNECTIONTIMEOUT 设置连接等待时间

#### CURLOPT_FOLLOWLOCATION

设置重定位URL

#### CURLOPT_RANGE: CURLOPT_RESUME_FROM

断点续传相关设置。CURLOPT_RANGE 指定char *参数传递给libcurl，用于指明http域的RANGE头域，例如：
表示头500个字节：bytes=0-499
表示第二个500字节：bytes=500-999
表示最后500个字节：bytes=-500
表示500字节以后的范围：bytes=500-
第一个和最后一个字节：bytes=0-0,-1
同时指定几个范围：bytes=500-600,601-999
CURLOPT_RESUME_FROM 传递一个long参数给libcurl，指定你希望开始传递的 偏移量。



### 五、libcurl使用的HTTP消息头

当使用libcurl发送http请求时，它会自动添加一些http头。我们可以通过CURLOPT_HTTPHEADER属性手动替换、添加或删除相应 的HTTP消息头。

  **Host**
  http1.1（大部分http1.0)版本都要求客户端请求提供这个信息头。
  **Pragma**
  "no-cache"。表示不要缓冲数据。
  **Accept**
  "*/*"。表示允许接收任何类型的数据。
  **Expect**
  以POST的方式向HTTP服务器提交请求时，libcurl会设置该消息头为"100-continue"，它要求服务器在正式处理该请求之前，返回一 个"OK"消息。如果POST的数据很小，libcurl可能不会设置该消息头。

#### 自定义选项

  当前越来越多的协议都构建在HTTP协议之上（如：soap），这主要归功于HTTP的可靠性，以及被广泛使用的代理支持（可以穿透大部分防火墙）。 这些协议的使用方式与传统HTTP可能有很大的不同。对此，libcurl作了很好的支持。

#### 自定义请求方式(CustomRequest)

  HTTP支持GET, HEAD或者POST提交请求。可以设置CURLOPT_CUSTOMREQUEST来设置自定义的请求方式，libcurl默认以GET方式提交请求：
  curl_easy_setopt(easy_handle, CURLOPT_CUSTOMREQUEST, "MYOWNREQUEST"); 

```
struct curl_slist *headers=NULL; /* init to NULL is important */ headers = curl_slist_append(headers, "Hey-server-hey: how are you?"); headers = curl_slist_append(headers, "X-silly-content: yes"); /* pass our list of custom made headers */ curl_easy_setopt(easyhandle, CURLOPT_HTTPHEADER, headers); curl_easy_perform(easyhandle); /* transfer http */ curl_slist_free_all(headers); /* free the header list */
```

 

### 六、获取http应答头信息

发出http请求后，服务器会返回应答头信息和应答数据，如果仅仅是打印应答头的所有内容，则直接可以通过curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, 打印函数)的方式来完成，这里需要获取的是应答头中特定的信息，比如应答码、cookies列表等，则需要通过下面这个函数：
  CURLcode curl_easy_getinfo(CURL *curl, CURLINFO info, ... ); 

**info参数就是我们需要获取的内容，下面是一些参数值:**

1. CURLINFO_RESPONSE_CODE
     获取应答码
2. CURLINFO_HEADER_SIZE
     头大小
3. CURLINFO_COOKIELIST
     cookies列表

除了获取应答信息外，这个函数还能获取curl的一些内部信息，如请求时间、连接时间等等。

 

### 七、多线程问题

首先一个基本原则就是：绝对不应该在线程之间共享同一个libcurl handle(CURL *对象)，不管是easy handle还是multi handle（本文只介绍easy_handle）。一个线程每次只能使用一个handle。
libcurl是线程安全的，但有两点例外：信号(signals)和SSL/TLS handler。 信号用于超时失效名字解析(timing out name resolves)。libcurl依赖其他的库来支持SSL/STL，所以用多线程的方式访问HTTPS或FTPS的URL时，应该满足这些库对多线程 操作的一些要求。

详细可以参考：
  OpenSSL: http://www.openssl.org/docs/crypto/threads.html#DESCRIPTION

  GnuTLS: http://www.gnu.org/software/gnutls/manual/html_node/Multi_002dthreaded-applications.html



### 八、HTTP验证

在使用HTTP协议时，客户端有很多种方式向服务器提供验证信息。默认的 HTTP验证方法是"Basic”，它将用户名与密码以明文的方式、经Base64编码后保存在HTTP请求头中，发往服务器。当然这不太安全。
  当前版本的libcurl支持的验证方法有：basic, Digest, NTLM, Negotiate, GSS-Negotiate and SPNEGO。

可以通过CURLOPT_HTTPAUTH属性来设置具体 的验证方式：
  curl_easy_setopt(easy_handle, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);

向代理服务器发送验证信息时，可以通过CURLOPT_PROXYAUTH设置验证方式：
  curl_easy_setopt(easy_handle, CURLOPT_PROXYAUTH, CURLAUTH_NTLM);

也可以同时设置多种验证方式（通过按位与）， 使用‘CURLAUTH_ANY‘将允许libcurl可以选择任何它所支持的验证方式。通过CURLOPT_HTTPAUTH或 CURLOPT_PROXYAUTH属性设置的多种验证方式，libcurl会在运行时选择一种它认为是最好的方式与服务器通信：
  curl_easy_setopt(easy_handle, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST|CURLAUTH_BASIC); 
  // curl_easy_setopt(easy_handle, CURLOPT_HTTPAUTH, CURLAUTH_ANY);

 

### 九、编译libcurl库

从网站https://curl.haxx.se/download找到源码包，官网最新版为7.56.0，但是这个压缩包的curl-7.56.0\projects\Windows路径下VC6-VC14各个版本的VS解决方案。

### 9.1 如果需要libcur支持https，需要openssl库支持。

libcurl主要功能就是用不同的协议连接和沟通不同的服务器，如果使用HTTPS，需要OpenSSL

libcurl https://curl.haxx.se/download.html 下载Source Archives即可

ActiveState https://www.activestate.com/activeperl/downloads 下载perl解析器，编译openssl需要用到。

openssl https://www.openssl.org/source/ 下载openssl-1.0.2k，1.1.0以后的文件和安装方法都换了。

zlib http://zlib.net/ 下载1.2.7以外的版本，比如1.2.11。

#### 支持https的libcurl库编译方法

##### 1）解压

为了方便安装，在D盘根目录下新建一个名为libcurl-ssl的文件夹，将下载的三个压缩包解压到该文件夹。
在 curl-7.54.0 -> lib 下新建文件夹openssl用来存放openssl的头文件。

##### \2) zlib编译：

zlib-1.2.11\contrib\vstudio\vc14\zlibvc.sln，编译release版本。

在生成的x86\ZlibDllRelease文件夹中有zlibwapi.dll和zlibwapi.lib文件

##### 3) ActiveState安装：

打开安装包，选择Modify默认安装或Repair修改安装路径都可以

##### 4) openssl编译：

这是最麻烦、最容易出错的一环了，因为他没有项目文件，只能通过命令行来编译。

在开始菜单中找到vs自带的 VS2015 x86 本机工具命令提示符

使用cd命令进入到openssl-1.0.2k文件夹中

命令行键入 perl Configure VC-WIN32 no-asm

命令行键入 ms\do_ms.bat

命令行键入 nmake -f ms/ntdll.mak

等待差不多五分钟，只要不出现“stop”，安全地执行到结束，就算成功。
一旦中间出了差错，最好是把文件夹也删了，重新解压、配置编译，如果你留有编译失败的半成品，它可能会告诉你“无法解析XXX”。

##### 5) 将 openssl-1.0.2k -> inc32 -> openssl 所有的.h 和 openssl-1.0.2k -> out32dll 的 libeay32.lib、libeay32.dll、ssleay32.lib、ssleay32.dll 一起复制到 curl-7.54.0 -> lib -> openssl 中

#### libcurl编译：

编译平台选择 DLL Debug - DLL OpenSSL

curl-7.54.0 ->projects -> Windows -> VC14 -> curl-all.sln，可能会提示升级工程，确定即可。

将 libcurl 设为启动项目，选择 libcurl -> Resource Files -> libcurl.rc，右键“移出”，它记录着版本信息，只会增大文件，可以移出掉。

选择 属性 -> C/C++ -> 预处理器 -> 预处理器定义，将"BUILDING_LIBCURL"改成"CURL_STATICLIB"。这样那些接口函数就不会被声明为导出函数了。

选择 属性 -> 链接器 -> 常规 -> 附加库目录 添加 ..\..\..\..\lib\openssl，指向curl-7.54.0 -> lib -> openssl

选择 属性 -> 链接器 -> 输入 -> 附加依赖项 添加 libeay32.lib;ssleay32.lib;ws2_32.lib;wldap32.lib; 前两个是为了OpenSSL，后两个是CURL必须依赖的。

在编译成功后 curl-7.54.0 -> build -> Win32 -> VC14 -> DLL Debug - DLL OpenSSL 文件夹中会生成有 libcurld.dll 和 libcurld.lib（注意名字不是libcurl）。

 

### 9.2不支持https的libcurl库编译方法：

使用curl-7.32.0版本中vs工程，vc自动编译。从网站https://curl.haxx.se/download 中下载curl-7.32.0版本。解压curl-7.32.0，找到vs工程目录，比如：curl-7.32.0\vs\vc8\lib\vc8libcurl.vcproj

1） 打开curl-7.32.0\vs\vc8\lib\vc8libcurl.vcproj文件，VS2010会提示升级工程，下一步即可。
VC工程里有些设置问题导致不能直接编译，需要稍作修改

2） 打开工程属性 > C\C++ > 常规 > 附加包含目录。这里的包含目录是"..\include"，而这个目录根本就不存在，它应该指向"curl-7.32.0\include"才对，所以把这里改成"..\..\..\include"。(或者直接完整路径也可以）

3） 打开工程属性 > C\C++ > 预处理器 > 预处理器定义。这里有个默认宏"BUILDING_LIBCURL"，如果要编译生成静态库，则要把它改成"CURL_STATICLIB"。这样，那些接口函数就不会被声明为导出函数了。

4） 打开工程属性 > C\C++ > 库管理器 > 常规 > 附加依赖项。添加ws2_32.lib和wldap32.lib，这是CURL必须依赖的。或者在代码中使用#pragma comment预编译指令，手动引入这两个lib库。

 

### 9.3 libcurld.lib/libcurl.lib引用方法

将 curl-7.54.0 -> include 目录下的curl文件夹，复制过去。

将libcurl编译的 libcurld.dll 和 libcurld.lib 复制到debug。

将libcurld.dll和之前OpenSSL生成的 libeay32.dll、ssleay32.dll 各复制一份到项目文件夹下，否则会报错。

选择 配置属性 -> C\C++ -> 预处理器 -> 预处理器定义，添加CURL_STATICLIB。

属性中的 附加包含目录、附加库目录和附加依赖项就在代码中实现。



### 十、实例代码

```c
  1 #define CURL_STATICLIB                //如果是静态库方式，需要包含这句
  2  
  3 #include "curl\curl.h"
  4 #include <iostream>
  5 #include <list>
  6 #include <string>
  7  
  8 #ifdef _DEBUG
  9 #pragma comment(lib,"libcurld.lib")
 10 #else
 11 #pragma comment(lib,"libcurl.lib")
 12 #endif
 13  
 14 #pragma comment ( lib, "ws2_32.lib" )
 15 #pragma comment ( lib, "winmm.lib" )
 16 #pragma comment ( lib, "wldap32.lib" )
 17 #pragma comment(lib, "Advapi32.lib")
 18  
 19  
 20 std::wstring AsciiToUnicode(const std::string& str)
 21 {
 22     // 预算-缓冲区中宽字节的长度  
 23     int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
 24     // 给指向缓冲区的指针变量分配内存  
 25     wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
 26     // 开始向缓冲区转换字节  
 27     MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);
 28     std::wstring ret_str = pUnicode;
 29     free(pUnicode);
 30     return ret_str;
 31 }
 32  
 33 std::string UnicodeToUtf8(const std::wstring& wstr)
 34 {
 35     // 预算-缓冲区中多字节的长度  
 36     int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
 37     // 给指向缓冲区的指针变量分配内存  
 38     char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
 39     // 开始向缓冲区转换字节  
 40     WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
 41     std::string ret_str = pAssii;
 42     free(pAssii);
 43     return ret_str;
 44 }
 45  
 46 //ANSI转UTF8
 47 std::string AsciiToUtf8(const std::string& str)
 48 {
 49     return UnicodeToUtf8(AsciiToUnicode(str));
 50 }
 51  
 52 //UTF8转ANSI
 53 std::string Utf8toAscii(const std::string strUTF8)
 54 {
 55     std::string  strAnsi = "";
 56     //获取转换为多字节后需要的缓冲区大小，创建多字节缓冲区
 57     UINT nLen = MultiByteToWideChar(CP_UTF8, NULL, strUTF8.c_str(), -1, NULL, NULL);
 58     WCHAR *wszBuffer = new WCHAR[nLen + 1];
 59     nLen = MultiByteToWideChar(CP_UTF8, NULL, strUTF8.c_str(), -1, wszBuffer, nLen);
 60     wszBuffer[nLen] = 0;
 61     nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
 62     CHAR *szBuffer = new CHAR[nLen + 1];
 63     nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
 64     szBuffer[nLen] = 0;
 65     strAnsi = szBuffer;
 66     //清理内存
 67     delete[]szBuffer;
 68     delete[]wszBuffer;
 69     return strAnsi;
 70 }
 71  
 72 // reply of the requery  
 73 size_t req_reply(void *ptr, size_t size, size_t nmemb, void *stream)
 74 {
 75     if (stream == NULL || ptr == NULL || size == 0)
 76         return 0;
 77  
 78     size_t realsize = size * nmemb;
 79     std::string *buffer = (std::string*)stream;
 80     if (buffer != NULL)
 81     {
 82         buffer->append((const char *)ptr, realsize);
 83     }
 84     return realsize;
 85     /*
 86     std::string *str = (std::string*)stream;
 87     (*str).append((char*)ptr, size*nmemb);
 88     return size * nmemb;
 89     */
 90 }
 91  
 92 /*
 93 功能：get http数据
 94 参数：url：请求字符串。如果请求带参数数据，直接拼凑到url后面；比如：http://127.0.0.1:8080/api/Accounts/Login?uername=admin&password=123
 95 listRequestHeader：请求头数据列表。
 96 bResponseIsWithHeaderData：bool类型，表示响应体中是否包含应答头数据。true，包含，false，不包含。如果包含的话，应答数据中包含Content-Type，Server等信息。
 97 nConnectTimeout：连接超时时间，单位为秒；
 98 nTimeout：读写数据超时时间，单位为秒
 99 返回值：CURLcode
100 */
101 CURLcode curl_get_req(const std::string &url, std::string &response, std::list<std::string> listRequestHeader, bool bResponseIsWithHeaderData = false, int nConnectTimeout = 10, int nTimeout = 10)
102 {
103     // init curl  
104     CURL *curl = curl_easy_init();
105     // res code  
106     CURLcode res;
107     if (curl)
108     {
109         // set params  
110         curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  
111         //curl_easy_setopt(m_curl, CURLOPT_PORT, 8089);    //port
112         curl_easy_setopt(curl, CURLOPT_POST, 0); // get reqest 
113         //构建HTTP报文头
114         struct curl_slist* headers = NULL;
115         if (listRequestHeader.size() > 0)
116         {
117             std::list<std::string>::iterator iter, iterEnd;
118             iter = listRequestHeader.begin();
119             iterEnd = listRequestHeader.end();
120             for (iter; iter != iterEnd; iter++)
121             {
122                 headers = curl_slist_append(headers, iter->c_str());
123             }
124             //headers = curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
125             //headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded");
126             if (headers != NULL)
127             {
128                 curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);//设置http请求头信息
129             }
130         }
131         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https  
132         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  
133         curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
134         curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
135         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
136         curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
137         curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
138         if (bResponseIsWithHeaderData)
139         {
140             curl_easy_setopt(curl, CURLOPT_HEADER, 1);//响应体中是否包含了头信息，比如Content-Type:application/json;charset=UTF-8
141         }
142         curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, nConnectTimeout); // set transport and time out time  
143         curl_easy_setopt(curl, CURLOPT_TIMEOUT, nTimeout);
144         // start request  
145         res = curl_easy_perform(curl);
146         if (headers != NULL)
147         {
148             curl_slist_free_all(headers); //free the list again
149         }
150     }
151     // release curl  
152     curl_easy_cleanup(curl);
153     return res;
154 }
155  
156 CURLcode curl_get_req_ex(CURL *curl, const std::string &url, std::string &response, std::list<std::string> listRequestHeader, bool bResponseIsWithHeaderData = false, int nConnectTimeout = 10, int nTimeout = 10)
157 {
158     // res code  
159     CURLcode res;
160     if (curl)
161     {
162         // set params 
163                 curl_easy_reset(curl);
164         /* enable TCP keep-alive for this transfer */
165         curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
166         /* keep-alive idle time to 120 seconds */
167         curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 120L);
168         /* interval time between keep-alive probes: 30 seconds */
169         curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 30L);
170  
171         curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  
172         //curl_easy_setopt(m_curl, CURLOPT_PORT, 8089);    //port
173         curl_easy_setopt(curl, CURLOPT_POST, 0); // get reqest 
174         //构建HTTP报文头
175         struct curl_slist* headers = NULL;
176         if (listRequestHeader.size() > 0)
177         {
178             std::list<std::string>::iterator iter, iterEnd;
179             iter = listRequestHeader.begin();
180             iterEnd = listRequestHeader.end();
181             for (iter; iter != iterEnd; iter++)
182             {
183                 headers = curl_slist_append(headers, iter->c_str());
184             }
185             //headers = curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
186             //headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded");
187             if (headers != NULL)
188             {
189                 curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);//设置http请求头信息
190             }
191         }
192         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https  
193         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  
194         curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
195         curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
196         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
197         curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
198         curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
199         if (bResponseIsWithHeaderData)
200         {
201             curl_easy_setopt(curl, CURLOPT_HEADER, 1);//响应体中是否包含了头信息，比如Content-Type:application/json;charset=UTF-8
202         }
203         curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, nConnectTimeout); // set transport and time out time  
204         curl_easy_setopt(curl, CURLOPT_TIMEOUT, nTimeout);
205         // start request  
206         res = curl_easy_perform(curl);
207         if (headers != NULL)
208         {
209             curl_slist_free_all(headers); //free the list again
210         }
211     }
212     return res;
213 }
214  
215 /*
216 功能：post http数据
217 参数：url：请求字符串，比如：http://127.0.0.1:8080/api/Accounts/Login
218 postParams：请求附带的参数，比如uername=admin&password=123
219 listRequestHeader：请求头数据列表。
220 bResponseIsWithHeaderData：bool类型，表示响应体中是否包含应答头数据。true，包含，false，不包含。如果包含的话，应答数据中包含Content-Type，Server等信息。
221 nConnectTimeout：连接超时时间，单位为秒；
222 nTimeout：读写数据超时时间，单位为秒
223 返回值：CURLcode
224 */
225 CURLcode curl_post_req(const std::string &url, const std::string &postParams, std::string &response, std::list<std::string> listRequestHeader, bool bResponseIsWithHeaderData = false, int nConnectTimeout = 10, int nTimeout = 10)
226 {
227     // init curl  
228     CURL *curl = curl_easy_init();
229     // res code  
230     CURLcode res;
231     if (curl)
232     {
233         // set params  
234         curl_easy_setopt(curl, CURLOPT_POST, 1); // post req  
235         curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  
236         //curl_easy_setopt(m_curl, CURLOPT_PORT, 8089);    //port
237         curl_easy_setopt(curl, CURLOPT_POST, 1); // post reqest 
238         //构建HTTP报文头
239         struct curl_slist* headers = NULL;
240         if (listRequestHeader.size() > 0)
241         {
242             std::list<std::string>::iterator iter, iterEnd;
243             iter = listRequestHeader.begin();
244             iterEnd = listRequestHeader.end();
245             for (iter; iter != iterEnd; iter++)
246             {
247                 headers = curl_slist_append(headers, iter->c_str());
248             }
249             //headers = curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
250             //headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded");
251             if (headers != NULL)
252             {
253                 curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);//设置http请求头信息
254             }
255         }
256         else
257         {
258             headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded");
259             if (headers != NULL)
260             {
261                 curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);//设置http请求头信息
262             }
263         }
264         curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postParams.c_str()); // params  
265         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https  
266         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  
267         curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
268         curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1); //返回的头部中有Location(一般直接请求的url没找到)，则继续请求Location对应的数据 
269         curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
270         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
271         curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
272         curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
273         if (bResponseIsWithHeaderData)
274         {
275             curl_easy_setopt(curl, CURLOPT_HEADER, 1);//响应体中是否包含了头信息，比如Content-Type:application/json;charset=UTF-8
276         }
277         curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, nConnectTimeout);
278         curl_easy_setopt(curl, CURLOPT_TIMEOUT, nTimeout);
279         // start request  
280         res = curl_easy_perform(curl);
281         if (headers != NULL)
282         {
283             curl_slist_free_all(headers); //free the list again
284         }
285     }
286     // release curl  
287     curl_easy_cleanup(curl);
288     return res;
289 }
290  
291 CURLcode curl_post_req_ex(CURL *curl, const std::string &url, const std::string &postParams, std::string &response, std::list<std::string> listRequestHeader, bool bResponseIsWithHeaderData = false, int nConnectTimeout = 10, int nTimeout = 10)
292 {
293     // res code  
294     CURLcode res;
295     if (curl)
296     {
297         // set params
298                 curl_easy_reset(curl);
299         /* enable TCP keep-alive for this transfer */
300         curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
301         /* keep-alive idle time to 120 seconds */
302         curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 120L);
303         /* interval time between keep-alive probes: 30 seconds */
304         curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 30L);
305  
306         curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  
307         //curl_easy_setopt(m_curl, CURLOPT_PORT, 8089);    //port
308         curl_easy_setopt(curl, CURLOPT_POST, 1); // post reqest 
309         //构建HTTP报文头
310         struct curl_slist* headers = NULL;
311         if (listRequestHeader.size() > 0)
312         {
313             std::list<std::string>::iterator iter, iterEnd;
314             iter = listRequestHeader.begin();
315             iterEnd = listRequestHeader.end();
316             for (iter; iter != iterEnd; iter++)
317             {
318                 headers = curl_slist_append(headers, iter->c_str());
319             }
320             //headers = curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
321             //headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded;charset=UTF-8");
322             if (headers != NULL)
323             {
324                 curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);//设置http请求头信息
325             }
326         }
327         else
328         {
329             headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded");
330             if (headers != NULL)
331             {
332                 curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);//设置http请求头信息
333             }
334         }
335         curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postParams.c_str()); // params  
336         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https  
337         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  
338         curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
339         curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1); //返回的头部中有Location(一般直接请求的url没找到)，则继续请求Location对应的数据 
340         curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
341         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
342         curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
343         curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
344         if (bResponseIsWithHeaderData)
345         {
346             curl_easy_setopt(curl, CURLOPT_HEADER, 1);//响应体中是否包含了头信息，比如Content-Type:application/json;charset=UTF-8
347         }
348         curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, nConnectTimeout);
349         curl_easy_setopt(curl, CURLOPT_TIMEOUT, nTimeout);
350         // start request  
351         res = curl_easy_perform(curl);
352         if (headers != NULL)
353         {
354             curl_slist_free_all(headers); //free the list again
355         }
356     }
357     return res;
358 }
359  
360 //实例1
361     curl_global_init(CURL_GLOBAL_ALL);
362     
363     //post获取数据
364     std::string strResponse = "",strResponseAnsi = "";
365         strResponse.clear();
366     CURLcode res = curl_post_req("http://127.0.0.1:8080/api/Accounts/Login", "username=admin&password=123", strResponse);
367     if (res == CURLE_OK)
368     {
369         std::string strToken = "";
370         strResponseAnsi = Utf8toAscii(strResponse);
371     }
372  
373     //get获取数据
374         strResponse.clear();
375     res = curl_get_req("http://127.0.0.1:8080/api/Accounts/Login?username=admin&password=123", strResponse);
376     if (res == CURLE_OK)
377     {
378         int jj = 0;
379     }
380  
381     curl_global_cleanup();
382 //实例2    
383     //post json数据
384     CURL * curl = curl_easy_init();
385     std::string strResponse = "", strResponseAnsi = "";
386     char szRequestUrl[256] = { 0 };
387     CURLcode res = CURLE_OK;
388     sprintf_s(szRequestUrl, "%s/api/GPS/AddOne", "http://127.0.0.1:8080");
389     std::string strPostParams = "";
390     try
391     {
392         boost::property_tree::ptree ptroot;
393         ptroot.put("deviceid", "12345678");
394         ptroot.put<unsigned int>("deviceStatus", 0);
395         ptroot.put<unsigned int>("alarmFlag", 0);
396         ptroot.put("lng", fLongitude);
397         ptroot.put("lat", fLatitude);
398         ptroot.put("speed", 0);
399         ptroot.put("direction", 0);
400         ptroot.put<int>("altitude", 10);
401         ptroot.put("gpsTime", "2018-10-10 12:00:01");
402         std::stringstream sstream;
403         boost::property_tree::write_json(sstream, ptroot);
404         strPostParams = sstream.str();
405         bSuccess = true;
406     }
407     catch (boost::property_tree::ptree_error pt)
408     {
409         pt.what();
410     }
411     if (bSuccess)
412     {
413       std::string strAuthorization = "admin---";
414         std::string strRequestHeaders = strAuthorization;
415         std::list<std::string> listRequestHeader;
416         listRequestHeader.push_back(strRequestHeaders);
417         listRequestHeader.push_back("Content-Type:application/json;charset=UTF-8");
418         res = curl_post_req_ex(curl, szRequestUrl, strPostParams, strResponse, listRequestHeader);
419         if (res == CURLE_OK)
420         {
421             bSuccess = true;
422         }
423     }
424 
425 curl_easy_cleanup(curl);
```



### 注意事项：

1、http模式测试，使用Postman插件或模拟测试网站 https://www.sojson.com/httpRequest/

2、保持长连接，设置选项。

```
 /* enable TCP keep-alive for this transfer */
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
    /* keep-alive idle time to 120 seconds */
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 120L);
    /* interval time between keep-alive probes: 60 seconds */
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 60L);
```

3、调用libcurl下载，然后使用netstat查看发现有大量的TCP连接保持在CLOSE_WAIT状态
查看libcurl的文档说明，有这样一个选项：
CURLOPT_FORBID_REUSE
Pass a long. Set to 1 to make the next transfer explicitly close the connection when done. Normally, libcurl keeps all connections alive when done with one transfer in case a succeeding one follows that can re-use them. This option should be used with caution and only if you understand what it does. Set to 0 to have libcurl keep the connection open for possible later re-use (default behavior).
也就是说，默认情况下libcurl完成一个任务以后，出于重用连接的考虑不会马上关闭
如果没有新的TCP请求来重用这个连接，那么只能等到CLOSE_WAIT超时，这个时间默认在7200秒甚至更高，太多的CLOSE_WAIT连接会导致性能问题
解决方法：
curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);
最好再修改一下TCP参数调低CLOSE_WAIT和TIME_WAIT的超时时间

4、libcurl进行异步并发
使用multi接口，multi接口的使用会比easy 接口稍微复杂点，毕竟multi接口是依赖easy接口的，首先粗略的讲下其使用流程：curl_multi _init初始化一个multi curl对象，为了同时进行多个curl的并发访问，我们需要初始化多个easy curl对象，使用curl_easy_setopt进行相关设置，然后调用curl_multi _add_handle把easy curl对象添加到multi curl对象中，添加完毕后执行curl_multi_perform方法进行并发的访问，访问结束后curl_multi_remove_handle移除相关easy curl对象，curl_easy_cleanup清除easy curl对象，最后curl_multi_cleanup清除multi curl对象。multi接口具体使用方法参考下面链接

https://blog.csdn.net/whui19890911/article/details/79320408

5、请求头、响应头多个参数设置。使用curl_slist_append函数一个个参数插入。

### 参考资料：

libcurl官网：https://curl.haxx.se/libcurl/

vc编译libcurl：https://www.cnblogs.com/findumars/p/7496122.html



### curl_errno错误码说明

CURLE_UNSUPPORTED_PROTOCOL (1) – 您传送给 libcurl 的网址使用了此 libcurl 不支持的协议。 可能是您没有使用的编译时选项造成了这种情况（可能是协议字符串拼写有误，或没有指定协议 libcurl 代码）。

CURLE_FAILED_INIT (2) – 非常早期的初始化代码失败。 可能是内部错误或问题。

CURLE_URL_MALFORMAT (3) – 网址格式不正确。

CURLE_COULDNT_RESOLVE_PROXY (5) – 无法解析代理服务器。 指定的代理服务器主机无法解析。

CURLE_COULDNT_RESOLVE_HOST (6) – 无法解析主机。 指定的远程主机无法解析。

CURLE_COULDNT_CONNECT (7) – 无法通过 connect() 连接至主机或代理服务器。

CURLE_FTP_WEIRD_SERVER_REPLY (8) – 在连接到 FTP 服务器后，libcurl 需要收到特定的回复。 此错误代码表示收到了不正常或不正确的回复。 指定的远程服务器可能不是正确的 FTP 服务器。

CURLE_REMOTE_ACCESS_DENIED (9) – 我们无法访问网址中指定的资源。 对于 FTP，如果尝试更改为远程目录，就会发生这种情况。

CURLE_FTP_WEIRD_PASS_REPLY (11) – 在将 FTP 密码发送到服务器后，libcurl 需要收到正确的回复。 此错误代码表示返回的是意外的代码。

CURLE_FTP_WEIRD_PASV_REPLY (13) – libcurl 无法从服务器端收到有用的结果，作为对 PASV 或 EPSV 命令的响应。 服务器有问题。

CURLE_FTP_WEIRD_227_FORMAT (14) – FTP 服务器返回 227 行作为对 PASV 命令的响应。如果 libcurl 无法解析此行，就会返回此代码。

CURLE_FTP_CANT_GET_HOST (15) – 在查找用于新连接的主机时出现内部错误。

CURLE_FTP_COULDNT_SET_TYPE (17) – 在尝试将传输模式设置为二进制或 ascii 时发生错误。

CURLE_PARTIAL_FILE (18) – 文件传输尺寸小于或大于预期。当服务器先报告了一个预期的传输尺寸，然后所传送的数据与先前指定尺寸不相符时，就会发生此错误。

CURLE_FTP_COULDNT_RETR_FILE (19) – ‘RETR’ 命令收到了不正常的回复，或完成的传输尺寸为零字节。

CURLE_QUOTE_ERROR (21) – 在向远程服务器发送自定义 “QUOTE” 命令时，其中一个命令返回的错误代码为 400 或更大的数字（对于 FTP），或以其他方式表明命令无法成功完成。

CURLE_HTTP_RETURNED_ERROR (22) – 如 果 CURLOPT_FAILONERROR 设置为 TRUE，且 HTTP 服务器返回 >= 400 的错误代码，就会返回此代码。 （此错 误代码以前又称为 CURLE_HTTP_NOT_FOUND。）

CURLE_WRITE_ERROR (23) – 在向本地文件写入所收到的数据时发生错误，或由写入回调 (write callback) 向 libcurl 返回了一个错误。

CURLE_UPLOAD_FAILED (25) – 无法开始上传。 对于 FTP，服务器通常会拒绝执行 STOR 命令。错误缓冲区通常会提供服务器对此问题的说明。 （此错误代码以前又称为 CURLE_FTP_COULDNT_STOR_FILE。）

CURLE_READ_ERROR (26) – 读取本地文件时遇到问题，或由读取回调 (read callback) 返回了一个错误。

CURLE_OUT_OF_MEMORY (27) – 内存分配请求失败。此错误比较严重，若发生此错误，则表明出现了非常严重的问题。

CURLE_OPERATION_TIMEDOUT (28) – 操 作超时。 已达到根据相应情况指定的超时时间。 请注意： 自 Urchin 6.6.0.2 开始，超时时间可以自行更改。 要指定远程日志下载超时， 请打开 urchin.conf 文件，取消以下行的注释标记：

\#DownloadTimeout: 30 

CURLE_FTP_PORT_FAILED (30) – FTP PORT 命令返回错误。 在没有为 libcurl 指定适当的地址使用时，最有可能发生此问题。 请参阅 CURLOPT_FTPPORT。

CURLE_FTP_COULDNT_USE_REST (31) – FTP REST 命令返回错误。如果服务器正常，则应当不会发生这种情况。

CURLE_RANGE_ERROR (33) – 服务器不支持或不接受范围请求。

CURLE_HTTP_POST_ERROR (34) – 此问题比较少见，主要由内部混乱引发。

CURLE_SSL_CONNECT_ERROR (35) – 同时使用 SSL/TLS 时可能会发生此错误。您可以访问错误缓冲区查看相应信息，其中会对此问题进行更详细的介绍。可能是证书（文件格式、路径、许可）、密码及其他因素导致了此问题。

CURLE_FTP_BAD_DOWNLOAD_RESUME (36) – 尝试恢复超过文件大小限制的 FTP 连接。

CURLE_FILE_COULDNT_READ_FILE (37) – 无法打开 FILE:// 路径下的文件。原因很可能是文件路径无法识别现有文件。 建议您检查文件的访问权限。

CURLE_LDAP_CANNOT_BIND (38) – LDAP 无法绑定。LDAP 绑定操作失败。

CURLE_LDAP_SEARCH_FAILED (39) – LDAP 搜索无法进行。

CURLE_FUNCTION_NOT_FOUND (41) – 找不到函数。 找不到必要的 zlib 函数。

CURLE_ABORTED_BY_CALLBACK (42) – 由回调中止。 回调向 libcurl 返回了 “abort”。

CURLE_BAD_FUNCTION_ARGUMENT (43) – 内部错误。 使用了不正确的参数调用函数。

CURLE_INTERFACE_FAILED (45) – 界 面错误。 指定的外部界面无法使用。 请通过 CURLOPT_INTERFACE 设置要使用哪个界面来处理外部连接的来源 IP 地址。 （此错误代 码以前又称为 CURLE_HTTP_PORT_FAILED。）

CURLE_TOO_MANY_REDIRECTS (47) – 重定向过多。 进行重定向时，libcurl 达到了网页点击上限。请使用 CURLOPT_MAXREDIRS 设置上限。

CURLE_UNKNOWN_TELNET_OPTION (48) – 无法识别以 CURLOPT_TELNETOPTIONS 设置的选项。 请参阅相关文档。

CURLE_TELNET_OPTION_SYNTAX (49) – telnet 选项字符串的格式不正确。

CURLE_PEER_FAILED_VERIFICATION (51) – 远程服务器的 SSL 证书或 SSH md5 指纹不正确。

CURLE_GOT_NOTHING (52) – 服务器未返回任何数据，在相应情况下，未返回任何数据就属于出现错误。

CURLE_SSL_ENGINE_NOTFOUND (53) – 找不到指定的加密引擎。

CURLE_SSL_ENGINE_SETFAILED (54) – 无法将选定的 SSL 加密引擎设为默认选项。

CURLE_SEND_ERROR (55) – 无法发送网络数据。

CURLE_RECV_ERROR (56) – 接收网络数据失败。

CURLE_SSL_CERTPROBLEM (58) – 本地客户端证书有问题

CURLE_SSL_CIPHER (59) – 无法使用指定的密钥

CURLE_SSL_CACERT (60) – 无法使用已知的 CA 证书验证对等证书

CURLE_BAD_CONTENT_ENCODING (61) – 无法识别传输编码

CURLE_LDAP_INVALID_URL (62) – LDAP 网址无效

CURLE_FILESIZE_EXCEEDED (63) – 超过了文件大小上限

CURLE_USE_SSL_FAILED (64) – 请求的 FTP SSL 级别失败

CURLE_SEND_FAIL_REWIND (65) – 进行发送操作时，curl 必须回转数据以便重新传输，但回转操作未能成功

CURLE_SSL_ENGINE_INITFAILED (66) – SSL 引擎初始化失败

CURLE_LOGIN_DENIED (67) – 远程服务器拒绝 curl 登录（7.13.1 新增功能）

CURLE_TFTP_NOTFOUND (68) – 在 TFTP 服务器上找不到文件

CURLE_TFTP_PERM (69) – 在 TFTP 服务器上遇到权限问题

CURLE_REMOTE_DISK_FULL (70) – 服务器磁盘空间不足

CURLE_TFTP_ILLEGAL (71) – TFTP 操作非法

CURLE_TFTP_UNKNOWNID (72) – TFTP 传输 ID 未知

CURLE_REMOTE_FILE_EXISTS (73) – 文件已存在，无法覆盖

CURLE_TFTP_NOSUCHUSER (74) – 运行正常的 TFTP 服务器不会返回此错误

CURLE_CONV_FAILED (75) – 字符转换失败

CURLE_CONV_REQD (76) – 调用方必须注册转换回调

CURLE_SSL_CACERT_BADFILE (77) – 读取 SSL CA 证书时遇到问题（可能是路径错误或访问权限问题）

CURLE_REMOTE_FILE_NOT_FOUND (78) – 网址中引用的资源不存在

CURLE_SSH (79) – SSH 会话中发生无法识别的错误

CURLE_SSL_SHUTDOWN_FAILED (80) – 无法终止 SSL 连接





































































































































































