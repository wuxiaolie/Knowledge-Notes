/* 通过man指令查询调用函数所在头文件 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/* 通过宏定义将模拟指令简化为整形数，便于处理 */
#define LS   0
#define GET  1
#define PWD  2
#define IFGO 3  //大于IFGO的不需要执行handler_server_message函数
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
	if (!strcmp("quit", cmd))   return QUIT;
	if (!strcmp("ls", cmd))		return LS;
	if (!strcmp("lls", cmd))	return LLS;
	if (!strcmp("pwd", cmd))	return PWD;
	
    if (strstr(cmd, "lcd"))		return LCD;
	if (strstr(cmd, "cd"))		return CD;
	if (strstr(cmd, "get"))		return GET;
	if (strstr(cmd, "put"))		return PUT;
	//其他指令未定义，返回-1表示未找到
	return -1;
}

/* 分割字符串 */
char *get_dir(char *cmd)
{
	char *p;
	p = strtok(cmd, " ");
    //再次调用时，cmsg应设置为NULL
	p = strtok(NULL, " ");
	return p;
}

/* 指令处理函数 */
int cmd_handler(struct Msg msg, int fd)
{
	char *dir = NULL;
	char buf[32] = {0};
	int ret;
	int filefd;  //文件描述符

	//将模拟指令字符串转换为整型数
	ret = get_cmd_type(msg.data);

	switch(ret)
	{
        /* 输出当前文件列表 */
		case LS:
            msg.type = 0;
			//将数据写入套接字描述符中
			write(fd, &msg, sizeof(msg));
			break;
			
        /* 切换目录 */
		case CD:
            msg.type = 0;
			//将数据写入套接字描述符中
			write(fd, &msg, sizeof(msg));
			break;
			
        /* 输出当前路径 */
		case PWD:
			msg.type = 0;
			//将数据写入套接字描述符中
			write(fd, &msg, sizeof(msg));
			break;
            
        /* 打印文件内容 */
		case GET:
			msg.type = 0;  //此处设置无效，这里的msg是局部变量
			write(fd, &msg, sizeof(msg));
			break;
            
        /* 上传文件内容 */
		case PUT:
			strcpy(buf, msg.data);
            //分割字符串，得到文件名字符串
			dir = get_dir(buf);
            //系统调用函数，查看file文件是否存在
			if (access(dir, F_OK) == -1)	{
				printf("%s is not exsit.\n",dir);
			} else {
				filefd = open(dir, O_RDWR);
				read(filefd, msg.secondBuf, sizeof(msg.secondBuf));
				close(filefd);  //关闭文件描述符
				write(fd, &msg, sizeof(msg));
			}
			break;
        
        /* 输出当前文件列表 */
		case LLS:
			printf("--------------------------------------\n\n");
			system("ls");
			printf("\n--------------------------------------\n");
			break;
         
        /* 切换目录 */
		case LCD:
			dir = get_dir(msg.data);
            //调用函数切换目录
			chdir(dir);
			break;
            
        /* 退出 */
		case QUIT:
			strcpy(msg.data, "quit");
			write(fd, &msg, sizeof(msg));
			close(fd);
			exit(-1);
	}
	return ret;
}

/* 服务器信息处理函数，从服务器返回的信息，在这里进行处理 */
void handler_server_message(int c_fd, struct Msg msg)
{
	int n_read;
	struct Msg msgget;
	int newfilefd;

	//读取服务器数据，将数据读取到msgget结构体中
	n_read = read(c_fd, &msgget, sizeof(msgget));

	//对msgget结构体中的内容进行解析，如果是普通指令则直接输出，如果是get指令则将数据写入文件(创建并写入)中
	if(n_read == 0) {  //套接字描述符中没有任何数据，退出
		printf("Server disconnected, quit!\n");
		exit(-1);
	} else if (msgget.type == DOFILE) {  //GET指令，打印文件内容
		newfilefd = open(get_dir(msg.data), O_RDWR | O_CREAT, 0600);
		write(newfilefd, msgget.data, strlen(msgget.data));
		
        //将输出到stdio缓冲区中的数据写入到内核缓冲区
		fflush(stdout);
		close(newfilefd);

		//将下载的文件内容打印部分
		printf("--------------------------------------\n");
		printf("\n%s\n", msgget.data);
		printf("--------------------------------------\n");
		
		printf("> ");
	} else {
		printf("--------------------------------------\n");
		printf("\n%s\n", msgget.data);
		printf("--------------------------------------\n");
		printf("> ");
		fflush(stdout);
	}
}

/* 主程序，建立socket连接，*/
int main(int argc, char **argv)
{
	int c_fd;
	struct sockaddr_in c_addr;  //定义客户端的套接字
	struct Msg msg;
	
    //传入参数不符合要求
	if(argc != 3) {
		printf("param is not good\n");
		exit(-1);
	}
    
    //初始化，将结构体的内容全部初始化为0
	memset(&c_addr, 0, sizeof(struct sockaddr_in));
	    	
	/* 1.socket，申请socket描述符 */
    //选择TCP/IP协议；提供有序的、可靠的、双向的、基于连接的字节流；为给定的通信域和套接字类型选择默认协议
	c_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(c_fd == -1) {
		perror("Ask for socket error!");
		exit(-1);
	}

	/* 2.配置客户端IP地址和端口号 */
    c_addr.sin_family = AF_INET;  //设置为TCP/IP协议族
	c_addr.sin_port = htons(atoi(argv[2]));   //设置端口号，由于传入的参数为字符串类型，要转换为int类型，htons为宏定义，用于避免出现大小端问题
	inet_aton(argv[1], &c_addr.sin_addr);  //将IP地址在点分十进制和二进制表示形式之间进行转化
    
    /* 3.客户端调用connect()函数将套接字与远程服务器进行连接 */
	if(connect(c_fd, (struct sockaddr *)&c_addr, sizeof(struct sockaddr)) == -1) {
		perror("Connection failed ");
		exit(-1);
	}
    
   	//连接成功
	printf("Successfully connected to server.\n");
    printf("--------------------------------------\n");
	int mark = 0;
    
    /* 不断输出指令并处理指令 */
	while(1) {
		memset(msg.data, 0, sizeof(msg.data));  //每次循环都重新初始化
		if(mark == 0) printf("> ");
		
		//接收用户输入，gets函数已经被弃用，这里替换成fgets函数，由于fgets函数会读入回车，这里将回车去掉
		fgets(msg.data, sizeof(msg.data), stdin);
		//printf("%s", msg.data);
		msg.data[strlen(msg.data) - 1] = '\0';
		//printf("-------------\n");
		//printf("%s", msg.data);
		
		//判断输入信息是否符合要求，否则重新循环
		if(strlen(msg.data) == 0) {
			if(mark == 1) printf("> "); 
			continue;
		}
		mark = 1;
        
		//调用命令处理函数
		int ret = cmd_handler(msg, c_fd);
		if(ret > IFGO) {   //IFGO = 3，使后几个命令跳过handler_server_message函数
			printf("> ");
			fflush(stdout);  //刷新输出缓冲区
			continue;
		}
		if(ret == -1) {    //ret出现错误
			printf("Sorry, the command you entered does not exist.\n");
			printf("> ");
			fflush(stdout);
			continue;
		}

        // 调用服务器信息处理函数  
		handler_server_message(c_fd, msg);
	}
	/* 关闭套接字，释放相应资源 */
	close(c_fd);  
	return 0;
}
