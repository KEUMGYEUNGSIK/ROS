#include <stdio.h>

int main(void)
{
	int num1, num2, arr[100] = {0,};
	int sum = 0, i, a;
	scanf("%d %d", &num1, &num2);
	i = 1;
	for(int x = num1 ; x <= num2 ; x++){
		i = 0;
	while(1){
		a = x;
		if(a/10 >= 1){
			arr[i] = a%10;
			a = a/10;
			i++;
			printf("%d", a);
		}
		else{
			arr[i] = a;
			break;
		}
	}
	
	for(int j = 0; arr[j] != '\0' ; j++)
		sum = arr[j]*arr[j]*arr[j];

	if(x == sum)
		printf("%d ", sum);
	}
	
	return 0;
}