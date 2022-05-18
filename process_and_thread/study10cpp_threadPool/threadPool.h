#pragma once
#include <pthread.h>
#include "task.h"
#include "task.cpp"
#include <iostream>
#include <cstring>   //memset的头文件
#include <unistd.h>
using namespace std;

template <typename T>
class ThreadPool {
public:
    ThreadPool(int min, int max);
    ~ThreadPool();

    //添加任务
    void addTask(Task<T> task);
    //获取忙线程得个数
    int getBusyNumber();
    //获取还活着线程得个数
    int getAliveNumber();
    //线程退出
    void threadExit();

//类内调用得函数和变量用private
private:
    //工作线程任务函数
    static void* worker(void* arg);  //两个星号
    //管理者线程任务函数
    static void* manager(void* arg);

private:
    pthread_mutex_t m_lock;   //互斥锁
    pthread_cond_t m_notEmpty;   //条件阻塞,判断任务队列是不是空
    pthread_t* m_threadIDs;  //工作的线程ID
    pthread_t* m_managerID;   //管理者的线程ID
    TaskQueue<T>* m_taskQ;
    int m_minNum;
    int m_maxNum;
    int m_busyNum;
    int m_aliveNum;   //用于析构的时候用for来唤醒活着的线程
    int m_exitNum;
    bool m_shutdown = false;
};
