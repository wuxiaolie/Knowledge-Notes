/* 通过man指令查询调用函数所在头文件 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* 通过宏定义将模拟指令简化为整形数，便于处理 */
#define LS   0
#define GET  1
#define PWD  2
#define IFGO 3
#define LCD  4
#define LLS  5
#define CD   6
#define PUT  7
#define QUIT 8
#define DOFILE  9

/* 定义用来存储信息块的结构体 */
struct Msg {
        int type;
        char data[1024];
        char secondBuf[128];
};

/* 判断模拟指令类型 */
int get_cmd_type(char *cmd)
{
	if (!strcmp("ls", cmd))			return LS;
	if (!strcmp("quit", cmd))		return QUIT;
	if (!strcmp("pwd", cmd))		return PWD;
	if (strstr(cmd, "cd") != NULL)	return CD;
	if (strstr(cmd, "get") != NULL)	return GET;
	if (strstr(cmd, "put") != NULL)	return PUT;
	//其他指令未定义，返回100表示未找到
	return 100; 
}

/* 分割字符串 */
char *get_dir(char *cmsg)
{
	char *p;
	p = strtok(cmsg, " ");
    //再次调用时，cmsg应设置为NULL
	p = strtok(NULL, " ");
	return p;
}

/* 信息处理函数 */
void msg_handler(struct Msg msg, int fd)
{
	char dataBuf[1024] = {0};
	char *file = NULL;
	int fdfile;  //文件描述符
	
	//msg.data为字符数组
	printf("The command requested by the client is:  %s\n", msg.data);
	//将模拟指令字符串转换为整型数
	int ret = get_cmd_type(msg.data);

	switch(ret)
	{
        /* 输出当前文件列表 */
		case LS:
        	msg.type = 0;
            FILE *r1 = popen(msg.data, "r");
            fread(msg.data, sizeof(msg.data), 1, r1);
            write(fd, &msg, sizeof(msg));
            break;
            
		/* 输出当前路径 */
		case PWD:
			msg.type = 0;
            //调用fork()生成子进程，在子进程中调用/bin/sh -c来执行参数msg.data的指令，是以创建管道的方式创建子进程并连接到子进程的标准输出设备或标准输入设备，功能是执行指令将输出放入文件中，返回文件指针
			FILE *r2 = popen(msg.data, "r");
            //从文件读取1个数据项，每个数据项大小为sizeof(msg.data),将读取到的数据存放在参数 ptr指向的缓冲区中
			fread(msg.data, sizeof(msg.data), 1, r2);
            //将数据写入套接字描述符中
			write(fd, &msg, sizeof(msg));
			break;
		
        /* 切换目录 */
		case CD:
			msg.type = 1;
			//分割字符串，得到待切换的目录字符串
			char *dir = get_dir(msg.data);
			printf("Switched to directory:  %s\n", dir);
            //调用函数切换目录
			chdir(dir);
			break;
            
       	/* 打印文件内容 */
		case GET:
            msg.type = DOFILE;  //作为服务器信息处理函数GET/PUT的判断标志
			//分割字符串，得到文件名字符串
			file = get_dir(msg.data);  //获取第二个参数
			//系统调用函数，查看file文件是否存在
			if (access(file, F_OK) == -1) {
				strcpy(msg.data, "The requested file does not exist!");
				write(fd, &msg, sizeof(msg));
			} else {
				fdfile = open(file, O_RDWR);  //打开文件，获得文件描述符
				read(fdfile, dataBuf, sizeof(dataBuf));  //将文件内容读取到dataBuf
				close(fdfile);  //关闭文件描述符，释放占用的资源
				//将内容拷贝到masg.data然后写入到套接字描述符中
                strcpy(msg.data, dataBuf);
				write(fd, &msg, sizeof(msg));
			}
			break;
            
        /* 上传文件内容 */
		case PUT:
            //以可读可写打开文件，如果pathname参数指向的文件不存在则创建权限为0666的文件
			fdfile = open(get_dir(msg.data), O_RDWR | O_CREAT, 0666);
			write(fdfile, msg.secondBuf, strlen(msg.secondBuf));
			close(fdfile);
			break;
            
        /* 退出 */
		case QUIT:
			printf("The client has exited.\n");
			printf("--------------------------------------\n");
			exit(-1);	
	}
}

/* 主程序，建立socket连接，*/
int main(int argc, char **argv)
{
	int s_fd;
	int c_fd;
	int n_read;
	char readBuf[128];

	struct sockaddr_in s_addr;  //定义服务器的套接字
	struct sockaddr_in c_addr;  //定义与执行connect的客户端建立连接的套接字
	struct Msg msg;  

    //传入参数不符合要求
	if(argc != 3) {
		printf("Unqualified parameters!\n");
		exit(-1);
	}
    
	//初始化，将两个结构体的内容全部初始化为0
	memset(&s_addr, 0, sizeof(struct sockaddr_in));
	memset(&c_addr, 0, sizeof(struct sockaddr_in));

	/* 1.socket，申请socket描述符 */
    //选择TCP/IP协议；提供有序的、可靠的、双向的、基于连接的字节流；为给定的通信域和套接字类型选择默认协议
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd == -1) {
		perror("Ask for socket error!");
		exit(-1);
	}
    
    /* 2.bind，将服务器IP地址和端口号与一个套接字进行绑定（将套接字与地址关联） */
	s_addr.sin_family = AF_INET;  //设置为TCP/IP协议族
	s_addr.sin_port = htons(atoi(argv[2]));  //设置端口号，由于传入的参数为字符串类型，要转换为int类型，htons为宏定义，用于避免出现大小端问题
	inet_aton(argv[1], &s_addr.sin_addr);  //将IP地址在点分十进制和二进制表示形式之间进行转化

	bind(s_fd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr_in));

	/* 3.listen，让服务器进入监听状态，等待客户端连接请求 */
	listen(s_fd, 15);  //s_fd等待连接队列最大为15

    int clen = sizeof(struct sockaddr_in);
	/* 放在死循环中，一直监听客户端连接，并fork子进程去处理 */

	printf("Waiting for client connection ...\n");
	printf("--------------------------------------\n");
	while(1) {
        
        /* 4.accept，进入阻塞状态，获取客户端的连接请求，并建立连接 */
		c_fd = accept(s_fd, (struct sockaddr *)&c_addr, &clen);
        //输出错误信息
		if(c_fd == -1)
			perror("Failed to establish connection!");
        //打印客户端IP地址
        printf("Client connection succeeded.\n");
		printf("The IP address of the client is:  %s\n",inet_ntoa(c_addr.sin_addr));
		printf("--------------------------------------\n");
		/* 当新的客户端接入的时候才创建子进程，一个子进程负责一条连接通道 */
        //fork()调用成功，将会在父进程中返回子进程的PID，而在子进程中返回值是0
        //fork()调用失败，父进程返回值-1，不创建子进程，并设置errno
        //if进行区分，子进程进入while循环中，父进程又返回4处
		if(fork() == 0)	{
			while(1) {
                //清空msg结构体
				memset(msg.data, 0, sizeof(msg.data));
				//等待客户端输入，将所有数据都传到msg结构体中，返回值是读到的字节数
				n_read = read(c_fd, &msg, sizeof(msg));
               
				if(n_read == 0)	{
					printf("The client has exited.\n");
					printf("--------------------------------------\n");
					break;	
				}
				else if(n_read > 0)	{
					msg_handler(msg, c_fd);	 //执行处理函数
				}				
			}
		}
	}
    
    /* 关闭套接字，释放相应资源 */
	close(c_fd);  
	close(s_fd);
	return 0;
}
