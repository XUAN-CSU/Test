#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 9
#define NUM_TASKS 10

// Task structure
typedef struct {
    void (*function)(void* arg);
    void* argument;
} Task;

// Thread pool structure
typedef struct {
    pthread_t threads[NUM_THREADS];
    Task tasks[NUM_TASKS];
    int task_count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int shutdown;
} ThreadPool;

// Worker function
void* worker(void* arg) {
    ThreadPool* pool = (ThreadPool*)arg;
    while (1) {
        pthread_mutex_lock(&pool->mutex);
        while (pool->task_count == 0 && !pool->shutdown) {
            pthread_cond_wait(&pool->cond, &pool->mutex);
        }
        if (pool->shutdown) {
            pthread_mutex_unlock(&pool->mutex);
            break;
        }
        Task task = pool->tasks[--pool->task_count];
        pthread_mutex_unlock(&pool->mutex);

        task.function(task.argument);
    }
    return NULL;
}

// Initialize thread pool
void thread_pool_init(ThreadPool* pool) {
    pool->task_count = 0;
    pool->shutdown = 0;
    pthread_mutex_init(&pool->mutex, NULL);
    pthread_cond_init(&pool->cond, NULL);
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&pool->threads[i], NULL, worker, pool);
    }
}

// Add task to thread pool
void thread_pool_add_task(ThreadPool* pool, void (*function)(void*), void* argument) {
    pthread_mutex_lock(&pool->mutex);
    if (pool->task_count < NUM_TASKS) {
        pool->tasks[pool->task_count].function = function;
        pool->tasks[pool->task_count].argument = argument;
        pool->task_count++;
        pthread_cond_signal(&pool->cond);
    }
    pthread_mutex_unlock(&pool->mutex);
}

// Shutdown thread pool
void thread_pool_shutdown(ThreadPool* pool) {
    pthread_mutex_lock(&pool->mutex);
    pool->shutdown = 1;
    pthread_cond_broadcast(&pool->cond);
    pthread_mutex_unlock(&pool->mutex);
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(pool->threads[i], NULL);
    }
    pthread_mutex_destroy(&pool->mutex);
    pthread_cond_destroy(&pool->cond);
}

// Example task function
void example_task(void* arg) {
    int task_id = *(int*)arg;
    printf("Executing task %d on thread %lu\n", task_id, pthread_self());
    sleep(1); // Simulate work
}

int main() 
{
    ThreadPool pool;
    thread_pool_init(&pool);

    // Submit tasks
    for (int i = 0; i < NUM_TASKS; i++) {
        int* task_id = malloc(sizeof(int));
        *task_id = i;
        thread_pool_add_task(&pool, example_task, task_id);
    }

	sleep(10);
	printf("WLC the thread pool will shutdown ....\n");
    // Shutdown thread pool
    thread_pool_shutdown(&pool);
    return 0;
}
