#include <stdio.h>

char gender;
float length, weight;
float bmi;

int main(){
    printf("Bent U een man of een vrouw? (Voer in M of V) ");
    scanf("%c", &gender);
    printf("Wat is uw lengte in cm?  ");
    scanf("%f", &length);
    printf("Wat is uw gewicht in kg?  ");
    scanf("%f", &weight);

    bmi = weight / (length*2) *100;
    printf("Uw BMI is: %f \n", bmi);

    if(gender == 'V'){
        if(bmi < 19){
            printf("U bent te licht voor uw lengte \n");
        }else if(bmi > 24){
            printf("U bent te zwaar voor uw lengte \n");
        }else{
            printf("Uw lengte en gewicht zijn in balans \n");
        }
    }else if(bmi < 20){
            printf("U bent te licht voor uw lengte \n");
        }else if(bmi > 25){
            printf("U bent te zwaar voor uw lengte \n");
        }else {
            printf("Uw lengte en gewicht zijn in balans \n");
        }
}