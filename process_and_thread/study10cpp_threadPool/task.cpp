#include "task.h"

template <typename T>
TaskQueue<T>::TaskQueue() {
    pthread_mutex_init(&m_mutex, NULL);
}

template <typename T>
TaskQueue<T>::~TaskQueue() {
    pthread_mutex_destroy(&m_mutex);
}

template <typename T>
void TaskQueue<T>::addTask(Task<T>& task) {
    pthread_mutex_lock(&m_mutex);
    m_queue.push(task);
    pthread_mutex_unlock(&m_mutex);
}

template <typename T>
void TaskQueue<T>::addTask(callback func, void* arg) {
    pthread_mutex_lock(&m_mutex);
    Task<T> task;
    task.arg = arg;
    task.function = func;
    m_queue.push(task);
    pthread_mutex_unlock(&m_mutex);
}

template <typename T>
Task<T> TaskQueue<T>::takeTask() {
    Task<T> t;
    pthread_mutex_lock(&m_mutex);
    if (m_queue.size() > 0) {
        t = m_queue.front();
        m_queue.pop();
    }
    pthread_mutex_unlock(&m_mutex);
    return t;  //就是小红和小明同一个本子上个搞个的，小红这一轮写
               //"笨蛋"只写了一个"笨"字，可以在等会儿拿到本子时再写"蛋"
               //这个锁是防止小红只写了一个"笨"的上面偏旁本子就被抢走了
}