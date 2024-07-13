
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_K 1000
#define MAX_M 1000
#define MAX_N 1000
#define MAX_THREADS 100

int K, M, N;
long A[MAX_M][MAX_K];
long B[MAX_K][MAX_N];
long C[MAX_M][MAX_N];
int threadPoolSize;

typedef struct {
    int row;
    int col;
} Task;
typedef struct {
    int thread_id;
} ThreadArgs;

Task taskQueue[MAX_M * MAX_N];
int taskCount = 0;
int ProgramStarted = 0;
int ProgramTerminated = 0;

pthread_mutex_t taskMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t taskCond = PTHREAD_COND_INITIALIZER;


void get_inputs();
void *startThread(void *args);

void addTask(Task task);

void executeTask(Task task);

void print_output();


int main() {
    clock_t begin = clock();
    pthread_t threads[MAX_THREADS];

    get_inputs();
    ThreadArgs threadArgsArray[threadPoolSize];

    for (int i = 0; i < threadPoolSize; ++i) {
        threadArgsArray[i].thread_id = i;
        pthread_create(&threads[i], NULL, startThread, (void *) &threadArgsArray[i]);
    }


    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            Task newTask;
            newTask.row = i;
            newTask.col = j;
            taskQueue[taskCount] = newTask;
            taskCount++;
        }
    }
    ProgramStarted = 1;


    for (int i = 0; i < threadPoolSize; ++i) {
        pthread_join(threads[i], 0);
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTotal time consumming: %ft \n", time_spent);

    print_output();
    return 0;
}

void print_output() {
    printf("Resultant matrix C (%d x %d):\n", N, M);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%ld ", C[i][j]);
        }
        printf("\n");
    }
}

void get_inputs() {
    printf("Enter the number of rows (M) and columns (K) for matrix A: ");
    scanf("%d %d", &M, &K);

    printf("Enter matrix A (%d x %d):\n", M, K);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < K; ++j) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter the number of rows (K) and columns (N) for matrix B: ");
    scanf("%d %d", &K, &N);

    printf("Enter matrix B (%d x %d):\n", K, N);
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", &B[i][j]);
        }
    }

    printf("Enter the size of the thread pool: ");
    scanf("%d", &threadPoolSize);
}

void *startThread(void *args) {
    ThreadArgs *threadArgs = (ThreadArgs *) args;
    int threadNumber = threadArgs->thread_id;
    int everyThreadShare = ((N * M) / threadPoolSize) + 1;
    while (1) {
        if (ProgramStarted) {
            for (int i = threadNumber * everyThreadShare; (i < ((threadNumber + 1) * everyThreadShare)) && (i < taskCount); ++i) {
                Task task;
                task = taskQueue[i];
                executeTask(task);
            }
            return NULL;
        }
    }
}


void executeTask(Task task) {
    long result = 0;
    for (int k = 0; k < K; ++k) {
        result += A[task.row][k] * B[k][task.col];
    }
    C[task.row][task.col] = result;
}