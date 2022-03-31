#include <stdio.h>
#include <math.h>

float average(float arr_1[]);
float divisor(float arr_2[]);
float dividend(float arr_3[], float arr_4[]);

int main(void)
{
	float a, b;
	
	float x[] = {2, 4, 6, 8};
	float y[] = {81, 93, 91, 97};
	
	float avg_x = average(x);
	float avg_y = average(y);
	
	float div = divisor(x);		//분모
	float top = dividend(x, y);		//분자
	
	printf("분자, 분모 : %lf %lf\n", top, div);
	
	a = top / div;				//기울기
	b = avg_y - (avg_x * a);	//y절편
	
	printf("기울기 a = %lf\n", a);
	printf("y 절편 b =%lf\n", b);

	return 0;	
}

float average(float arr_1[])
{
	float avg, sum = 0;
	
	for(int i = 0; i < 4 ; i++)
	{
		sum += arr_1[i];
	}
	avg = sum/4;
	
	return avg;
}

float divisor(float arr_2[])
{
	float sum = 0, avg_x;
	
	for(int i = 0; i < 4 ; i++)
	{
		sum += (arr_2[i] - avg_x)*(arr_2[i] - avg_x);
	}
	
	return sum;
}

float dividend(float arr_3[], float arr_4[])
{
	float sum = 0, top_x, top_y, avg_x, avg_y;
	
	for(int i = 0; i < 4 ; i++)
	{
		top_x = arr_3[i] - avg_x;
		top_y = arr_4[i] - avg_y;
		
		sum += top_x * top_y;
	}
	
	return sum;
}
