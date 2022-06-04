## curl网络工具 -  HQ

[TOC]

------

#### 注意

- 

------

## curl 的用法指南

[阮一峰博文](https://mp.weixin.qq.com/s?__biz=MzkzMDE4MDM2NQ==&mid=2247484003&idx=2&sn=df176d8c86ad82dfcc448da854b0610e&scene=19#wechat_redirect)

#### 简介

curl 是常用的命令行工具，用来请求 Web 服务器。它的名字就是客户端（client）的 URL 工具的意思。

它的功能非常强大，命令行参数多达几十种。如果熟练的话，完全可以取代 Postman 这一类的图形界面工具。

本文介绍它的主要命令行参数，作为日常的参考，方便查阅。内容主要翻译自《curl cookbook》。为了节约篇幅，下面的例子不包括运行时的输出，初学者可以先看我以前写的《curl 初学者教程》。

不带有任何参数时，curl 就是发出 GET 请求。

```
1$ curl https://www.example.com
```

上面命令向www.example.com发出 GET 请求，服务器返回的内容会在命令行输出。

#### -A

-A参数指定客户端的用户代理标头，即User-Agent。curl 的默认用户代理字符串是curl/[version]。

```
1$ curl -A 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/76.0.3809.100 Safari/537.36' https://google.com
```

上面命令将User-Agent改成 Chrome 浏览器。

```
1$ curl -A '' https://google.com
```

上面命令会移除User-Agent标头。

也可以通过-H参数直接指定标头，更改User-Agent。

```
1$ curl -H 'User-Agent: php/1.0' https://google.com
```

#### -b

-b参数用来向服务器发送 Cookie。

```
1$ curl -b 'foo=bar' https://google.com
```

上面命令会生成一个标头Cookie: foo=bar，向服务器发送一个名为foo、值为bar的 Cookie。

```
1$ curl -b 'foo1=bar;foo2=bar2' https://google.com
```

上面命令发送两个 Cookie。

```
1$ curl -b cookies.txt https://www.google.com
```

上面命令读取本地文件cookies.txt，里面是服务器设置的 Cookie（参见-c参数），将其发送到服务器。

#### -c

-c参数将服务器设置的 Cookie 写入一个文件。

```
1$ curl -c cookies.txt https://www.google.com
```

上面命令将服务器的 HTTP 回应所设置 Cookie 写入文本文件cookies.txt。

#### -d

-d参数用于发送 POST 请求的数据体。

```
1$ curl -d'login=emma＆password=123'-X POST https://google.com/login
```

或者

```
1$ curl -d 'login=emma' -d 'password=123' -X POST  https://google.com/login
```

使用-d参数以后，HTTP 请求会自动加上标头Content-Type : application/x-www-form-urlencoded。并且会自动将请求转为 POST 方法，因此可以省略-X POST。

-d参数可以读取本地文本文件的数据，向服务器发送。

```
1$ curl -d '@data.txt' https://google.com/login
```

上面命令读取data.txt文件的内容，作为数据体向服务器发送。

#### --data-urlencode

--data-urlencode参数等同于-d，发送 POST 请求的数据体，区别在于会自动将发送的数据进行 URL 编码。

```
1$ curl --data-urlencode 'comment=hello world' https://google.com/login
```

上面代码中，发送的数据hello world之间有一个空格，需要进行 URL 编码。

#### -e

-e参数用来设置 HTTP 的标头Referer，表示请求的来源。

```
1curl -e 'https://google.com?q=example' https://www.example.com
```

上面命令将Referer标头设为https://google.com?q=example。

#### -H

-H参数可以通过直接添加标头Referer，达到同样效果。

```
1curl -H 'Referer: https://google.com?q=example' https://www.example.com
```

-F
-F参数用来向服务器上传二进制文件。

```
1$ curl -F 'file=@photo.png' https://google.com/profile
```

上面命令会给 HTTP 请求加上标头Content-Type: multipart/form-data，然后将文件photo.png作为file字段上传。

-F参数可以指定 MIME 类型。

```
1$ curl -F 'file=@photo.png;type=image/png' https://google.com/profile
```

上面命令指定 MIME 类型为image/png，否则 curl 会把 MIME 类型设为application/octet-stream。

#### -F

-F参数也可以指定文件名。

```
1$ curl -F 'file=@photo.png;filename=me.png' https://google.com/profile
```

上面命令中，原始文件名为photo.png，但是服务器接收到的文件名为me.png。

#### -G

-G参数用来构造 URL 的查询字符串。

```
1$ curl -G -d 'q=kitties' -d 'count=20' https://google.com/search
```

上面命令会发出一个 GET 请求，实际请求的 URL 为https://google.com/search?q=kitties&count=20。如果省略--G，会发出一个 POST 请求。

如果数据需要 URL 编码，可以结合--data--urlencode参数。

```
1$ curl -G --data-urlencode 'comment=hello world' https://www.example.com
```

#### -H

-H参数添加 HTTP 请求的标头。

```
1$ curl -H 'Accept-Language: en-US' https://google.com
```

上面命令添加 HTTP 标头Accept-Language: en-US。

```
1$ curl -H 'Accept-Language: en-US' -H 'Secret-Message: xyzzy' https://google.com
```

上面命令添加两个 HTTP 标头。

```
1$ curl -d '{"login": "emma", "pass": "123"}' -H 'Content-Type: application/json' https://google.com/login
```

上面命令添加 HTTP 请求的标头是Content-Type: application/json，然后用-d参数发送 JSON 数据。

#### -i

-i参数打印出服务器回应的 HTTP 标头。

```
1$ curl -i https://www.example.com
```

上面命令收到服务器回应后，先输出服务器回应的标头，然后空一行，再输出网页的源码。

#### -I

-I参数向服务器发出 HEAD 请求，然会将服务器返回的 HTTP 标头打印出来。

```
1$ curl -I https://www.example.com
```

上面命令输出服务器对 HEAD 请求的回应。

--head参数等同于-I。

```
1$ curl --head https://www.example.com
```

#### -k

-k参数指定跳过 SSL 检测。

```
1$ curl -k https://www.example.com
```

上面命令不会检查服务器的 SSL 证书是否正确。

#### -L

-L参数会让 HTTP 请求跟随服务器的重定向。curl 默认不跟随重定向。

```
1$ curl -L -d 'tweet=hi' https://api.twitter.com/tweet
```

#### --limit-rate

--limit-rate用来限制 HTTP 请求和回应的带宽，模拟慢网速的环境。

```
1$ curl --limit-rate 200k https://google.com
```

上面命令将带宽限制在每秒 200K 字节。

#### -o

-o参数将服务器的回应保存成文件，等同于wget命令。

```
1$ curl -o example.html https://www.example.com
```

上面命令将www.example.com保存成example.html。

#### -O

-O参数将服务器回应保存成文件，并将 URL 的最后部分当作文件名。

```
1$ curl -O https://www.example.com/foo/bar.html
```

上面命令将服务器回应保存成文件，文件名为bar.html。

#### -s

-s参数将不输出错误和进度信息。

```
1$ curl -s https://www.example.com
```

上面命令一旦发生错误，不会显示错误信息。不发生错误的话，会正常显示运行结果。

如果想让 curl 不产生任何输出，可以使用下面的命令。

```
1$ curl -s -o /dev/null https://google.com
```

#### -S

-S参数指定只输出错误信息，通常与-s一起使用。

```
1$ curl -s -o /dev/null https://google.com
```

上面命令没有任何输出，除非发生错误。

#### -u

-u参数用来设置服务器认证的用户名和密码。

```
1$ curl -u 'bob:12345' https://google.com/login
```

上面命令设置用户名为bob，密码为12345，然后将其转为 HTTP 标头Authorization: Basic Ym9iOjEyMzQ1。

curl 能够识别 URL 里面的用户名和密码。

```
1$ curl https://bob:12345@google.com/login
```

上面命令能够识别 URL 里面的用户名和密码，将其转为上个例子里面的 HTTP 标头。

```
1$ curl -u 'bob' https://google.com/login
```

上面命令只设置了用户名，执行后，curl 会提示用户输入密码。

#### -v

-v参数输出通信的整个过程，用于调试。

```
1$ curl -v https://www.example.com
```

#### --trace

--trace参数也可以用于调试，还会输出原始的二进制数据。

```
1$ curl --trace - https://www.example.com
```

#### -x

-x参数指定 HTTP 请求的代理。

```
1$ curl -x socks5://james:cats@myproxy.com:8080 https://www.example.com
```

上面命令指定 HTTP 请求通过myproxy.com:8080的 socks5 代理发出。

如果没有指定代理协议，默认为 HTTP。

```
1$ curl -x james:cats@myproxy.com:8080 https://www.example.com
```

上面命令中，请求的代理使用 HTTP 协议。

#### -X

-X参数指定 HTTP 请求的方法。

```
1$ curl -X POST https://www.example.com
```

上面命令对https://www.example.com发出 POST 请求。

































































































































































