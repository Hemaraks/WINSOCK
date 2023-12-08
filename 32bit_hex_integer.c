#include<stdio.h>
#include<math.h>

#define max 7

double str_Hex_value(char *c);

int main(void)
{
    char *c = "ABCDEF89"; // 2882400137 // each char is of 4 bit in hexa so total 32 bit 
    double value = str_Hex_value(c);
    printf("%f\n",value);
    return 0;
}

double str_Hex_value(char *c){
    int temp=0,arr[max],c_len=0;
    double value=0,base=16,arr_indx=7; 
    /* it is very very important that we take the preceding 3 values as double 
        because in line 45 where the actual value is being calculated the var value 
        tends to be very big for an int so we would have to canvert value into a double
        then due to the arthematic in c is we add any int to double with such magnitude
        it tends to break the program due to some bit problems so it kind of tries to change
        the int into a double which manupilates the value of the given int, so its better
        and best to provide the pow values a double only
    */

    // char convertion to int 
    for(int i=0; *(c+i)!='\0';i++){
        temp = *(c+i);
        arr[i]=temp;
        c_len++;
    }
    // ascii convertion to actual value int
    for(int j=0; j<c_len;j++){
        if(arr[j]>=48 && arr[j]<58){
            arr[j] = arr[j]-48;
        }
        else if(arr[j]>=65 && arr[j]<71){
            arr[j] = arr[j]-55;
        }
        else {
            printf("INvalid HEX INput ");
            return 0;
        }
    }
    // actual value 
    
    for(int e=0;e<=max;e++){
        value= value + arr[e]*(pow(base,arr_indx));
        arr_indx--;
    }
    return value;
}