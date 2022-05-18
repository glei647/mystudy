#pragma once
#include <pthread.h>
#include <queue>

using namespace std;
using callback = void(*)(void* arg);

template <typename T>
struct Task {
    Task<T>() {
        function = nullptr;
        arg = nullptr;
    }
    Task<T>(callback f, void* arg) {
        function = f;
        this->arg = (T*)arg;
    }

    T* arg;
    callback function;
};

template <typename T>
class TaskQueue {
public:
    TaskQueue();
    ~TaskQueue();

    void addTask(Task<T>& task);
    void addTask(callback func, void* arg);

    Task<T> takeTask();  //取出其中一个任务

    //获取当前的任务个数
    inline size_t taskNumber() {
        return m_queue.size();
    }

private:
    pthread_mutex_t m_mutex;
    queue<Task<T>> m_queue;
};