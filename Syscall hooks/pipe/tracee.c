#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void parent(int fd[2]) {
    char* eax = "3";
    char* rdi = "123";
    close(fd[0]);
    //tries to do close
    for (int i = 0; i < 500000; i++) {
        //writes registers
        write(fd[1], eax, 1);
        write(fd[1], rdi, 3);
    }
}

void child(int fd[2]) {
    dup2(fd[0], 0);
    //changed STDIN
    close(fd[0]);
    close(fd[1]);
    //exec process with stdin = pipe
    execl("tracer", NULL);
}

int main() {
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if (pid) {
        parent(fd);
    } else {
        child(fd);
    }
    return 0;
}
