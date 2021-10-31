#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main()
{
    int a=5;
    char buffer[20];

    for(int i = 0; i < 20; i++){ /*initialization*/
        *(buffer + i) = '#';
    }

    buffer[1] = '=';

	snprintf (buffer, sizeof(buffer), "%d",a); // print int 'a' into the char[] buffer

	for(int i = 0; i < 20; i++){ /*initialization*/
        printf("%c", *(buffer + i));
    }

    printf("\n");
    
    return 0;
}