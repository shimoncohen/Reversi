// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_THREADPOOL_H
#define ADVANCEDPROGRAMMING1_THREADPOOL_H

#include "Task.h"
#include <queue>
#include <pthread.h>
using namespace std;

class ThreadPool {
public:
    ThreadPool(int threadsNum);
    void addTask(Task *task);
    void terminate();
    virtual ~ThreadPool();

private:
    queue<Task *> tasksQueue;
    pthread_t* threads;
    void executeTasks();
    bool stopped;
    pthread_mutex_t lock;

    static void *execute(void *arg);
};


#endif //ADVANCEDPROGRAMMING1_THREADPOOL_H
