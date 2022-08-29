#include <stdio.h>
#include <math.h>

// quadratic equation solution (with imaginary ones)

int main(void){
        float a,b,c,delta;
        scanf("%f %f %f", &a, &b, &c);
        printf("The equation (%.2f)x^2 + (%.2f)x + (%.2f) = 0 has a solution:\n", a, b, c);
	delta = b*b - 4*a*c;
	printf("Delta = %f\n",delta);
	if ( delta > 0){
		float x1,x2;
		x1 = (-b + sqrt(delta))/(2*a);
		x2 = (-b - sqrt(delta))/(2*a);
		printf("x1 = %f, x2 = %f\n",x1,x2);
		return 0;
	}
	if (delta == 0){
		float x0= -b/(2*a);
		printf("x0 = %f\n",x0);
		return 0;
	}
	if ( delta < 0){
		float zespo = sqrt(-delta);
		printf("x1 = %f + %fi \n",-b/(2*a),zespo/(2*a));
		printf("x2 = %f - %fi \n",-b/(2*a),zespo/(2*a));
		return 0;
	}
}
