#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <errno.h>

void parent(pid_t pid) {
    int status;
    int error_code;
    waitpid(pid, &status, 0);
    ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);
    while (!WIFEXITED(status)) {
        struct user_regs_struct state;
        ptrace(PTRACE_SYSCALL, pid, 0, 0);
        waitpid(pid, &status, 0);
        if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80) {
            ptrace(PTRACE_GETREGS, pid, 0, &state);
            if (state.orig_rax == 3) {
                int close_param = state.rdi;
                if (close_param == 123) {
                    error_code = close(close_param);
                    if (error_code != 0) {
                        printf("SYSCALL %lld at %08llx\n", state.orig_rax, state.rip);
                        printf("close() param - %lld\n", state.rdi);
                    }
                }
            }
            ptrace(PTRACE_SYSCALL, pid, 0, 0);
            waitpid(pid, &status, 0);
        }
    }
}

void child() {
    ptrace(PT_TRACE_ME, 0, 0, 0);
    execl("close", NULL);
}

int main() {
    pid_t pid = fork();
    if (pid) {
        parent(pid);
    } else {
        child();
    }
    return 0;
}
