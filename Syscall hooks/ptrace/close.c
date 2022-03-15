#include <stdio.h>
#include <unistd.h>

int main() {
    int tmp;
    for (int i = 0; i < 50000; i++) {
        tmp = close(123);
        if (0 == tmp) {
           tmp = 10;
        }
        tmp += 10;
    }
}
