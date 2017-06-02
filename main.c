#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char a[] = "J@RODQ";
    for (int i = 0; i < sizeof(a)-1; i++) {

            printf("%c", a[i]+!!a);
    }

    return 0;
}