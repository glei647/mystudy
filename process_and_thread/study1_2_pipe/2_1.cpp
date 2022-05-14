#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>  //包含perror的头文件
#include <cstdlib>   //c++中使用exit的头文件
//#include <string>
//using namespace std;

int main()
{
    // 1. 创建有名管道文件
    int ret = mkfifo("./testfifo", 0664);
    if(ret == -1)
    {
        perror("mkfifo");
        exit(0);
    }
    printf("管道文件创建成功...\n");

    // 2. 打开管道文件
    // 因为要写管道, 所有打开方式, 应该指定为 O_WRONLY
    // 如果先打开写端, 读端还没有打开, open函数会阻塞, 当读端也打开之后, open解除阻塞
    int wfd = open("./testfifo", O_WRONLY);
    if(wfd == -1)
    {
        perror("open");
        exit(0);
    }
    printf("以只写的方式打开文件成功...\n");

    // 3. 循环写管道
    int i = 0;
    while(i<100)
    {
        char buf[1024];
        sprintf(buf, "hello, fifo, 我在写管道...%d\n", i);
        write(wfd, buf, sizeof(buf));
        i++;
        sleep(1);
    }
    close(wfd);

    return 0;
}
