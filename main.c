#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("Parent\n");
    printf("First fork...\n");
    int f = fork();
    if (f) {
        //Run by parent only
        printf("Second fork...\n");
        f = fork();
    }

    if (f) {
        int s, p;
        p = wait(&s);
        printf("Child with PID %d finished.\tTime to exit: %d\nParent done.\n", p, WEXITSTATUS(s));
        return 0;
    }

    else {
        srand(time(NULL) + getpid());
        printf("Child PID: %d\n", getpid());
        int ret = rand() % 9 + 2;
        sleep(ret);
        printf("Child with PID %d awaking.\n", getpid());
        return ret;
    }
    return 0;
}
