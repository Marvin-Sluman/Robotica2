#include <stdio.h>

int input, iter_count;
unsigned int fibo_array[3]={0, 0, 0};

int main(){
    printf("Geef het aantal iteraties: ");
    scanf("%d", &input);

    for(iter_count = 0; iter_count < input; iter_count++){
        if(iter_count > 2){
            fibo_array[0] = fibo_array[1];
            fibo_array[1] = fibo_array[2];
            fibo_array[2] = (fibo_array[0] + fibo_array[1]);
        }else{
            fibo_array[iter_count] = 1;
        }
        printf("%u\n",fibo_array[2]);
    }
}