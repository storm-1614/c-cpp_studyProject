// 某工地需要搬运砖块，已知男人一人搬3块，女人一人搬2块，小孩两人搬1块，有多少种搬法用45人正好搬45块砖？
#include <stdio.h>

int main(int argc, char* argv[]) {
    int men, women, child;
    for (men = 0; men <= 45; men++) {
        for (women = 0; women < 45 - men; women++) {
            child = 45 - men - women;
            if (men * 3 + women * 2 + child * 0.5 == 45) {
                printf("men=%d women=%d child=%d\n", men, women, child);
            }
        }
    }
    return 0;
}
