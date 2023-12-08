#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define max 15

void method_one(int num);
void method_two(int num);
long long to_pow(int base,int pwr );

char s[max];
char s_2[max];

int main(void)
{
    int num = 8580;  // 10000110000100
    method_one(num);
    printf("%s",s);
    printf("\n");
    method_two(num);
    printf("%s",s_2);
    return 0;
}

long long to_pow(int base,int pwr ){
    long long res=1;
    for(int i=pwr;i>0;i--){
        res=res*base;
    }
    return res;
}

void method_one(int num){
    int arr[max],bit;
    int arr_index=0,base=10,s_index=0;
    long long int_bin_val=0;
    
    // int to binary arr
    for(int i=0; num>=1 ;i++){
        bit = num%2;
        num=num/2;
        arr[i]=bit;
        arr_index++;
        // printf("%i\n",bit);
    }

    arr_index = arr_index - 1;

    // binary arr to str array 
    for(int j=arr_index;j>=0;j--){
        s[s_index]=arr[j]+48; //this is a method for string concatination // the 48 is there for the ascii value 
        s_index++;
    }
    
}

void method_two(int num){
    int arr[max],bit;
    int arr_index=0,base=10,s_2_index=0;
    long long int_bin_val=0;
    
    // int to binary arr
    for(int i=0; num>=1 ;i++){
        bit = num%2;
        num=num/2;
        arr[i]=bit;
        arr_index++;
    }
    arr_index = arr_index - 1;

    
    int temp_index = arr_index;
    int t_index = arr_index;
    
    // binary arr to int
    for(int j=temp_index;j>=0;j--){
        if(arr[j]==0){
            arr_index--;
        }
        else{
            int_bin_val = int_bin_val + arr[j]*to_pow(base,arr_index);
            arr_index--;
        }
    }
    
    for(int b=t_index;b>=0;b--){
        s_2[b] = (int_bin_val%10)+48;
        int_bin_val=int_bin_val/10;
        
    }
}