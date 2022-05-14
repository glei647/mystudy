#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void test1() {
    pid_t pid = fork();
    if (pid > 0) {
        cout << "这是父进程，进程id是 " << getpid << endl; 
        sleep(1);
    }
    else if (pid == 0) {
        cout << "这个是子进程，进程id是" << getpid << endl;
        cout << "他的父进程id是" << getppid << endl;  
    }
    else //pid == -1
        cout << "出错辣" << endl;              //perror(fork);
}

void test2() {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid > 0) sleep(3);
        cout << "我的id是：" << getpid() << "  i = " << i << "  我老爸是：" << getppid() << endl;
    }
}

int main() {
   
    test2();
    return 0;
}

