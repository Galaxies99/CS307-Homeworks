    # include <iostream>
    # include <pthread.h>

    using namespace std;

    struct StackNode {
        int data;
        StackNode *nxt;             // the next data
        StackNode(int data, StackNode *nxt) : data(data), nxt(nxt) {}
    };

    StackNode *top;                 // the top of stack
    pthread_mutex_t mutex;          // lock if there is an operation in push-pop CS.
                                    // CS: critical section.
    pthread_mutex_t empty;          // lock if stack is empty.
    
    void push(int input_data) {
        pthread_mutex_lock(&mutex);
        if (top == NULL) pthread_mutex_unlock(&empty);
                                    // won't be empty after push, unlock empty lock.
        StackNode *new_top = new StackNode(input_data, top);
        top = new_top;
        pthread_mutex_unlock(&mutex);
    }

    int pop() {
        pthread_mutex_lock(&empty); // must not be empty
        pthread_mutex_lock(&mutex);
        int output_data = top -> data;
        StackNode *old_top = top;
        top = top -> nxt;
        delete old_top;
        if(top != NULL) pthread_mutex_unlock(&empty);
                                    // if not empty, unlock the empty lock;
                                    // if empty again, do not unlock and keep it lock.
        pthread_mutex_unlock(&mutex);
        return output_data;
    }

    int main() {
        pthread_mutex_init(&mutex, NULL);
        pthread_mutex_init(&empty, NULL);
        top = NULL;
        pthread_mutex_lock(&empty); // initial empty, lock the empty lock.

        /* perform push operations and pop operations */
        /* Here is an example */
        push(5);
        push(10);
        push(15);

        int value = pop();
        value = pop();
        value = pop();

        return 0;
    }
