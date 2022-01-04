#include <stdio.h>
#include <errno.h>

int main(void) {
    char phone[11];
    int num;

    scanf("%10s", phone);
    char c;
    while(( c = getchar()) != '\n' && c != EOF)
        /* discard */;

    while(1) {
        scanf("%d", &num);

        if(num == -1) {
            printf("%s\n", phone);
        }

        else if(num < 10 && num >-1) {
            printf("%c\n", phone[num]);
        }
        else {
            printf("%s\n", "ERROR");
        }

        if(errno > 0){
            break;
        }
    }

    if(errno > 0){
        return 1;
    }
    else{ 
        return 0; 
    }
   
}