#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    thread_func_args->thread_complete_success = true;
    //return thread_param;
    usleep(thread_func_args->wait_to_obtain_ms * 1000); // usleep takes microseconds

    // Obtain the mutex using pthread_mutex_lock(mutex).
    if (pthread_mutex_lock(thread_func_args->mutex) != 0) {
        ERROR_LOG("Failed to lock mutex");
        thread_func_args->thread_complete_success = false; // Set error status
        return thread_param;
    }

    // Sleep/wait for wait_to_release_ms milliseconds.
    usleep(thread_func_args->wait_to_release_ms * 1000);

    // Release the mutex using pthread_mutex_unlock(mutex).
    if (pthread_mutex_unlock(thread_func_args->mutex) != 0) {
        ERROR_LOG("Failed to unlock mutex");
        thread_func_args->thread_complete_success = false; // Set error status
        return thread_param;
    }

    thread_func_args->thread_complete_success = true; // Update success status
    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
    struct thread_data *thread_data_ptr = (struct thread_data *)malloc(sizeof(struct thread_data));
    if (thread_data_ptr == NULL) {
        ERROR_LOG("Failed to allocate memory for thread_data");
        return false;
    }
    
    thread_data_ptr->thread = thread; // Store the thread ID
    thread_data_ptr->mutex = mutex;   // Store the mutex
    thread_data_ptr->wait_to_obtain_ms = wait_to_obtain_ms; // Store the wait times
    thread_data_ptr->wait_to_release_ms = wait_to_release_ms;
    thread_data_ptr->thread_complete_success = false; // Initialize the completion status
    
    int thread_create_result = pthread_create(thread, NULL, threadfunc, thread_data_ptr);
    if (thread_create_result != 0) {
        ERROR_LOG("Failed to create thread");
        free(thread_data_ptr);
        return false;
    }
    
    return true;
}

