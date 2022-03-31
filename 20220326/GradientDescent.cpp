#include <stdio.h>
#include <math.h>

float datax[99] = {};
float datay[99] = {};

float er(float a, float b, float x0, float y0)
{
	return abs(a*x0 - y0 + b)/sqrt(a*a+b*b);
}

float  f(float a, float b) {
	float sum = 0.0;
	for (int i = 0; i < 20; i++) {
		sum += er(datax[i], datay[i], a, b) / 20;
	}
	return sum;
}

float dfabda(float a, float b, float da) {
	return (f(a + da, b) - f(a, b)) / da;
}
float dfabdb(float a, float b, float db) {
	return (f(a, b + db) - f(a, b)) / db;
}

float EE(float x0, float x1, float y0, float y1) {
	return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}

int main() {
	
    for (int i = 0; i < 20; i++)
    {
        datax[i] = i+0.5;
        datay[i] = i;
        printf("%f %f\n", datax[i], datay[i]);
	}

	float a0, b0;
	int iteration = 0;
	float da = 0.01;
	float db = 0.01;
	float a1 = 1, b1 = 0;
	while (EE(a0, b0, a1, b1) > 0.0001 && iteration <100000) {
		a0 = a1;
		b0 = b1;
		a1 -= 0.005 * dfabda(a0, b0, da);
		b1 -= 0.005 * dfabdb(a0, b0, db);
		iteration ++;
	}
	/*
	cout << " y  = " << a1 << "x + " << b1 << endl;
	cout << iteration << "-th  E = " << EE(a0, b0, a1, b1) << endl;
	*/
	
	printf("y = %fx + %f, E = %f", -a1, b1, EE(a0, b0, a1, b1));
	
	return 0;
}
