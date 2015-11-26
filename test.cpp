#include <iostream>
#include <stdio.h>

int main () {
	float pi = 3.14;
	pi = 5.4;
	printf("%f", pi);
	
	int a = 5;
	float b = a/2.0;
	printf("b = %f \n",b);
    
    char *ptr = "Linux";
    printf("\n [%c] \n",*ptr++);
    printf("\n [%c] \n",*ptr++);
    printf("\n [%c] \n",*ptr++);
    return 0;
}
