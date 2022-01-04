#include <stdio.h>

int main(void) {
    char phone[11];
    int num;
    scanf("%10s%d", phone, &num);
    if (num == -1) {
        printf("%s\n", phone);
    }
    else if (num < 10 && num >-1) {
        printf("%c\n", phone[num]);
    }
    else {
        printf("%s\n", "ERROR");
    }
    return 0;
}
    
