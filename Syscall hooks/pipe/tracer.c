#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int error_code;
    int eax = getchar();
    int rdi;
    int tmp;
    printf("\n");
    while (EOF != eax) {
        printf("SYSCALL %d\n", eax - '0');
        rdi = (getchar() - '0') * 100 + (getchar() - '0') * 10 + (getchar() - '0');
        printf("close() parameter - %d\n", rdi);
        error_code = close(rdi);
        if (0 != error_code) {
            tmp = 10;
        }
        tmp += 10;
        eax = getchar();
    }
    return 0;
}
