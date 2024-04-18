#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>

int main() {
    int a = ftok("/sys", 'x');
    printf("%d\n", a);
    return 0;
}