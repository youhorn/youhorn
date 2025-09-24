#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("사용법: %s <num1> <op> <num2>\n", argv[0]);
        return 1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[3]);
    char *op = argv[2];

    if (strcmp(op, "+") == 0) {
        printf("%d\n", a + b);
    } else if (strcmp(op, "-") == 0) {
        printf("%d\n", a - b);
    } else if (strcmp(op, "x") == 0 || strcmp(op, "*") == 0) {
        printf("%d\n", a * b);
    } else if (strcmp(op, "/") == 0) {
        if (b != 0) printf("%d\n", a / b);
        else printf("0으로 나눌 수 없습니다.\n");
    } else {
        printf("지원하지 않는 연산자입니다.\n");
    }

    return 0;
}

