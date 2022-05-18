#include "threadPool.h"
//#include "threadPool.cpp"

void taskFunc(void* arg) {
    //cout <<  "arg的地址是：" << arg << "然后 ";
    int num = *(int*)arg;
    cout << "thread " << pthread_self() << " is working, number = ";
    cout << num << endl;
    sleep(1);
}

int main() {
    ThreadPool pool(3, 10);
    for (int i = 0; i < 100; i++) {
        int* num = new int(i + 100);
        //Task task(taskFunc, num);
        pool.addTask(Task (taskFunc, num));
    } 
}