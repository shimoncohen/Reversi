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
    /*
	 * function name: ThreadPool.
	 * input: number of threads.
	 * output: none.
     * operation: constructor.
    */
    ThreadPool(int threadsNum);
    /*
	 * function name: addTask.
	 * input: the require command as a task.
	 * output: none.
     * operation: adds a task to the tasks queue.
    */
    void addTask(Task *task);
    /*
	 * function name: terminate.
	 * input: none.
	 * output: none.
     * operation: Stops the pool's activity.
    */
    void terminate();
    /*
	 * function name: ~ThreadPool.
	 * input: none.
	 * output: none.
     * operation: destructor.
    */
    virtual ~ThreadPool();

private:
    queue<Task *> tasksQueue;
    pthread_t* threads;
    /*
	 * function name: executeTasks.
	 * input: none.
	 * output: none.
     * operation: gets the first task from the queue and activate it.
    */
    void executeTasks();
    bool stopped;
    pthread_mutex_t lock;
    /*
	 * function name: execute.
	 * input: the current threads pool.
	 * output: none.
     * operation: calls execute the task.
    */
    static void *execute(void *arg);
};


#endif //ADVANCEDPROGRAMMING1_THREADPOOL_H
