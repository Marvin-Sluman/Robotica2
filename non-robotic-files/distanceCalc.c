#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Ax, Ay, Bx, By, distance, distanceVert, distanceHori;

int main(){
	printf("Geef de x waarde van punt A:  ");
	scanf("%lf", &Ax);
	printf("Geef de y waarde van punt A:  ");
	scanf("%lf", &Ay);
	printf("Geef de x waarde van punt B   ");
	scanf("%lf", &Bx);
	printf("Geef de y waarde van punt B   ");
	scanf("%lf", &By);
	distanceHori = Bx - Ax;
	distanceVert = By - Ay;
	distance = distanceHori*distanceHori + distanceVert*distanceVert;
	//distance = sqrt(distance);
	printf("%lf\n", distance);
}
