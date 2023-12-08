#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define max 15 // 0 to 15 will be 16 bit

int str_value(char *c);

int main(void)
{
    char *c = "0010000110000100"; // 8580
    int value = str_value(c);
    printf("%i\n",value);
}

int str_value(char *c){
    int temp=0,arr[max],arr_indx=max,base=2,value=0;
    int c_len = strlen(c);
    
    if(c_len>16){
        printf("INvalid Size\n");
        return 0;
    }

    for(int i=0; *(c+i)!='\0';i++){
        temp = *(c+i);
        temp=temp-48;
        arr[i]=temp;
    }

    for(int j=0;j<max;j++){
        value = value + (arr[j]*pow(base,arr_indx));
        arr_indx--;
    }
    return value;
}