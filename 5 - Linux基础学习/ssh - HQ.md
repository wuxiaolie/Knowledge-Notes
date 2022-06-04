## ssh学习笔记

[TOC]

------

#### 注意

- AcWing服务器账号
- User: acs_2663
  HostName: 123.57.47.211
  Password: d1b7d895

------

### ssh登录

#### 基本用法

远程登录服务器：

```
ssh user@hostname
```

- `user`: 用户名
- `hostname`: IP地址或域名

第一次登录时会提示：

```
The authenticity of host '123.57.47.211 (123.57.47.211)' can't be established.
ECDSA key fingerprint is SHA256:iy237yysfCe013/l+kpDGfEG9xxHxm0dnxnAbJTPpG8.
Are you sure you want to continue connecting (yes/no/[fingerprint])?
```

输入`yes`，然后回车即可。
这样会将该服务器的信息记录在`~/.ssh/known_hosts`文件中。

然后输入密码即可登录到远程服务器中。

------

默认登录端口号为22。如果想登录某一特定端口：

```
ssh user@hostname -p 22
```

登出：`logout`

------

#### 配置文件

创建文件 `~/.ssh/config`。

然后在文件中输入：

```
Host myserver1
    HostName IP地址或域名
    User 用户名

Host myserver2
    HostName IP地址或域名
    User 用户名
```

之后再使用服务器时，可以直接使用别名`myserver1`、`myserver2`。

------

#### 密钥登录

创建密钥：

```
ssh-keygen
```

然后一直回车即可。

执行结束后，`~/.ssh/`目录下会多两个文件：

- `id_rsa`：私钥
- `id_rsa.pub`：公钥

------

之后想免密码登录哪个服务器，就将公钥传给哪个服务器即可。

例如，想免密登录`myserver`服务器。则将公钥中的内容，复制到`myserver`中的`~/.ssh/authorized_keys`文件里即可。

也可以使用如下命令一键添加公钥：

```
ssh-copy-id myserver
```

------

#### 执行命令

命令格式：

```
ssh user@hostname command
```

例如：

```
ssh user@hostname ls -a
```

或者

```
# 单引号中的$i可以求值
ssh myserver 'for ((i = 0; i < 10; i ++ )) do echo $i; done'
```

或者

```
# 双引号中的$i不可以求值
ssh myserver "for ((i = 0; i < 10; i ++ )) do echo $i; done"
```

备注

双引号是在本地服务器进行转义了，所以传过去命令不是`echo $a`，而是`echo 1`，单引号传过去的是`echo $a`

```
a=1
ssh myserver  "echo $a"
ssh myserver  'echo $a'
```





### scp传文件

#### 一：scp常规的使用方式：

scp可以进行简单的远程复制文件的功能。它是一个在各个主机之间进行复制或文件传输的一个命令工具。它使用一种同ssh一样的安全机制来进行文件的传输。

注意：下面定义的远程计算机的主机域名是 192.168.1.104， 上传文件的路径是 /usr/local/nginx 下面的文件；且 服务器的账号是 root， 那么密码需要自己输入自己的密码即可。

1. 从本地上传文件到远程计算机或服务器的命令如下：
   先进入本地目录下，然后运行如下命令：

   ```
   scp my_local_file.zip root@192.168.1.104:/usr/local/nginx/html/webs

2. 从远程主机复制文件到本地主机(下载)的命令如下：（假如远程文件是about.zip）
   先进入本地目录下，然后运行如下命令：

   ```
   scp root@192.168.1.104:/usr/local/nginx/html/webs/about.zip .

#### 二： 多文件传输

2-1 从本地文件复制多个文件到远程主机（多个文件使用空格分隔开）
先进入本地目录下，然后运行如下命令：

```
scp index.css json.js root@192.168.1.104:/usr/local/nginx/html/webs
```

2-2 从远程主机复制多个文件到当前目录
先进入本地目录下，然后运行如下命令：

```
scp root@192.168.1.104:/usr/local/nginx/html/webs/{index.css,json.js} .
```

#### 三：复制整个文件夹(使用r switch 并且指定目录)

3-1 从本地文件复制整个文件夹到远程主机上（文件夹假如是diff）
先进入本地目录下，然后运行如下命令：

```
scp -v -r diff root@192.168.1.104:/usr/local/nginx/html/webs
```

3-2 从远程主机复制整个文件夹到本地目录下（文件夹假如是diff）
先进入本地目录下，然后运行如下命令：

```
scp -r root@192.168.1.104:/usr/local/nginx/html/webs/diff .
```

#### 四：在两个远程主机之间复制文件

scp也可以把文件从一个远程主机复制到另一个远程主机上。
如下命令：

```
scp root@192.168.1.104:/usr/local/nginx/html/webs/xx.txt root@192.168.1.105:/usr/local/nginx/html/webs/
```

#### 五：使用压缩来加快传输

在文件传输的过程中，我们可以使用压缩文件来加快文件传输，我们可以使用 C选项来启用压缩功能，该文件在传输过程中被压缩，
在目的主机上被解压缩。

如下命令：

```
scp -vrC diff root@192.168.1.104:/usr/local/nginx/html/webs
```

#### 六：基本用法

命令格式：

```
scp source destination
```

将`source`路径下的文件复制到`destination`中

------

一次复制多个文件：

```
scp source1 source2 destination
```

------

复制文件夹：

==服务器的用户目录不用加~/====，本地用户目录需要加~/==

```
scp -r ~/tmp myserver:
```

```
scp -r ~/tmp myserver:/home/acs/
```

将本地家目录中的`tmp`文件夹复制到`myserver`服务器中的`/home/acs/`目录下。

```
scp -r ~/tmp myserver:homework/
```

将本地家目录中的`tmp`文件夹复制到`myserver`服务器中的`~/homework/`目录下。

```
scp -r myserver:homework .
```

将`myserver`服务器中的`~/homework/`文件夹复制到本地的当前路径下。

------

指定服务器的端口号：

```
scp -P 22 source1 source2 destination
```

------

**注意：** `scp`的`-r -P`等参数尽量加在`source`和`destination`之前。

------

#### 案例：使用`scp`配置其他服务器的`vim`和`tmux`

```
scp ~/.vimrc ~/.tmux.conf myserver:
```





### 练习

#### 要求

```
	[3] remote_mkdir.sh和remote_rmdir.sh具有可执行权限
    [4] remote_mkdir.sh接收一个传入参数。格式为 ./remote_mkdir.sh directory_name
        该操作可以在myserver服务器上的~/homework/lesson_4/homework_4/目录下，创建一个名为directory_name的文件夹
    [5] remote_rmdir.sh接收一个传入传输。格式为 ./remote_rmdir.sh directory_name
        该操作可以将myserver服务器上的~/homework/lesson_4/homework_4/目录下的名为directory_name的文件夹删掉。
    [6] 注意：传入的文件参数可能包含空格。两个脚本均不需要判断传入参数的合法性。
```

#### 答案

ssh在执行的时候，会先将命令解析，

在服务器时也会解析一遍，加转义字符为了不让ssh解析，只让云端进行解析

```bash
remote_mkdir.sh
#! /bin/bash

ssh myserver mkdir homework/lesson_4/homework_4/\"$1\"
remote_rmdir.sh

#! /bin/bash

ssh myserver rm homework/lesson_4/homework_4/\"$1\" -r
```



























































































































































