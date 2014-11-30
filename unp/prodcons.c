#define MAX_SIZE 10000

int taskNo = 1;

struct {
    pthread_mutex_t mutex;
    int start;
    int end;
    int list[MAX_SIZE];
} tasklist = {
    PTHREAD_MUTEX_INITIALIZER, 0, 0
};

struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int ntask;
} pendtask = {
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, 0
};

int produce() {
    pthread_lock_mutex(&tasklist.mutex);
    if((start + 1) % MAX_SIZE == end)
        return 0;
    tasklist.start++;
    tasklist.start %= MAX_SIZE;
    tasklist[tasklist.start] = taskNo++;
    pthread_unlock_mutex(&tasklist.mutex);

    pthread_lock_mutex(&pendtask.mutex);
    pendtask.ntask++;
    pthread_cond_signal(&pendtask.cond);
    pthread_unlock_mutex(&pendtask.mutex);

    return 0;
}

int consume() {
    pthread_lock_mutex(&pendtask.mutex);
    while(pend.task == 0)
        pthread_cond_wait(&pendtask.cond);
    ntask--;
    pthread_unlock_mutex(&pendtask.mutex);

    pthread_lock_mutex(&tasklist.mutex);
    printf("%d\n", tasklist.list[tasklist.end]);
    tasklist.end++;
    tasklist.end %= MAX_SIZE; 
    pthread_unlock_mutex(&tasklist.mutex);

    return 0;
}
