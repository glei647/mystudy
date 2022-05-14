#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>  //包含perror的头文件
#include <cstdlib>   //c++中使用exit的头文件

//#include<string.h>  //C语言
#include<cstring>  //c++    memset的

int main()
{
    // 1. 打开管道文件
    // 因为要read管道, so打开方式, 应该指定为 O_RDONLY
    // 如果只打开了读端, 写端还没有打开, open阻塞, 当写端被打开, 阻塞就解除了
    int rfd = open("./testfifo", O_RDONLY);
    if(rfd == -1)
    {
        perror("open");
        exit(0);
    }
    printf("以只读的方式打开文件成功...\n");

    // 2. 循环读管道
    while(1)
    {
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        // 读是阻塞的, 如果管道中没有数据, read自动阻塞
        // 有数据解除阻塞, 继续读数据
        int len = read(rfd, buf, sizeof(buf));
        printf("读出的数据: %s\n", buf);
        if(len == 0)
        {
            // 写端关闭了, read解除阻塞返回0
            printf("管道的写端已经关闭, 拜拜...\n");
            break;
        }

    }
    close(rfd);

    return 0;
}
