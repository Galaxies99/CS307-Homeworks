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
    
    void push(int input_data) {
        pthread_mutex_lock(&mutex);
        StackNode *new_top = new StackNode(input_data, top);
        top = new_top;
        pthread_mutex_unlock(&mutex);
    }

    int pop() {
        pthread_mutex_lock(&mutex);
        int output_data = 0;         // default return value 0
        if(top != NULL) {
            output_data = top -> data;
            StackNode *old_top = top;
            top = top -> nxt;
            delete old_top;
        }
        pthread_mutex_unlock(&mutex);
        return output_data;
    }

    int main() {
        pthread_mutex_init(&mutex, NULL);
        top = NULL;

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
