#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100000

char *arr; // Temporary variable to use in all functions

// Function for printing until 0
bool Print0(char *res) {
    for (int i=0; res[i]!='\0'; i++) {
        if (res[i]>'0' && res[i]<='9') return true;
    }
    return false;
}

// Function for identifying number while reading string
long double IdentifyNum(void) {
    int i=0,j;
    long double num = 0.0;
    for (; arr[i]>='0' && arr[i]<='9'; i++) {
        num = num*10 + (arr[i]-'0');
    }
    if (arr[i]=='.') {
        for (i++,j=-1; arr[i]>='0' && arr[i]<='9'; i++,j--) {
            num += (arr[i]-'0') * pow(10,j);
        }
    }
    arr = arr + i;
    return num;
}

// Funcction for calculating an expression without parentheses
long double NumCalc(char op[],long double val[],int size) {
    long double result=val[0];
    for (int i=1; i<=size; i++) {
        if (op[i-1]=='*') {
            result *= val[i];
        } else if (op[i-1]=='/') {
            result /= val[i];
        } else if (op[i-1]=='+') {
            result += NumCalc(op+i,val+i,size-i);
            break;
        } else if (op[i-1]=='-') {
            op[i-1]='+';
            val[i] = -val[i];
            result += NumCalc(op+i,val+i,size-i);
            break;
        }
    }
    return result;
}

// Funcction for calculating an expression without parentheses
long double Calculator(int size) {
    // Calculating the expression with specific conditions
    long double value[size],temp[size];
    char operator[size],temp_op[size];
    int i=0,j=0,k=0,n=0;
    if (*arr=='+') arr++;
    else if (*arr=='-') {
        if (*(arr+1)>='0' && *(arr+1)<='9') {
            arr++;
            value[j] = -IdentifyNum();
            j++;
        } else if (*(arr+1)>='(') {
            arr += 2;
            value[j] = -Calculator(size);
            j++;
        }
    }
    // Calculating first parenthese
    if (*arr=='(') {
        arr++;
        while (1) {
            // Calling functions in different conditions
            if (*arr==')') {
                arr++;
                break;
            } else if (*arr=='\0') {
                break;
            }
            else if (*arr=='(') {
                if ((*(arr-1)>='0' && *(arr-1)<='9') || (*(arr-1)==')')) {
                    arr++;
                    temp[i] = Calculator(size);
                    i++;
                    temp_op[n] = '*';
                    n++;
                } else {
                    arr++;
                    temp[i] = Calculator(size);
                    i++;
                }
            } else if (*arr<='9' && *arr>='0') {
                temp[i] = IdentifyNum();
                i++;
            } else if ((*arr=='-' || *arr=='+') && *(arr-1)=='(' && *(arr+1)>='0' && *(arr+1)<='9') {
                if (*arr=='-') {
                    arr++;
                    temp[i] = -IdentifyNum();
                    i++;
                } else {
                    arr++;
                    temp[i] = IdentifyNum();
                    i++;
                }
            } else if ((*arr=='-' || *arr=='+') && *(arr-1)=='(' && *(arr+1)=='(') {
                if (*arr=='-') {
                    arr += 2;
                    temp[i] = -Calculator(size);
                    i++;
                } else {
                    arr += 2;
                    temp[i] = Calculator(size);
                    i++;
                }
            } else if ((*arr=='-' || *arr=='+') && *(arr-1)!=')' && (*(arr-1)<'0' || *(arr-1)>'9')) {
                if (*arr=='-') {
                    arr++;
                    temp[i] = -IdentifyNum();
                    i++;
                } else {
                    arr++;
                    temp[i] = IdentifyNum();
                    i++;
                }
            } else {
                temp_op[n] = *arr;
                arr++;
                n++;
            }
        }
        // Calculating the expression with values and operands
        int temp_len = (int)strlen(temp_op);
        value[j] = NumCalc(temp_op,temp,temp_len);
        j++;
    }
    // Calculating all of the expression
    while (*arr!='\0') {
        // Calling functions in different conditions
        if (*arr==')') {
            arr++;
            break;
        } else if (*arr=='(') {
            if ((*(arr-1)>='0' && *(arr-1)<='9') || (*(arr-1)==')')) {
                arr++;
                value[j] = Calculator(size);
                j++;
                operator[k] = '*';
                k++;
            } else {
                arr++;
                value[j] = Calculator(size);
                j++;
            }
        } else if (*arr<='9' && *arr>='0') {
            value[j] = IdentifyNum();
            j++;
        } else if ((*arr=='-' || *arr=='+') && *(arr-1)=='(' && *(arr+1)>='0' && *(arr+1)<='9') {
            if (*arr=='-') {
                arr++;
                value[j] = -IdentifyNum();
                j++;
            } else {
                arr++;
                value[j] = IdentifyNum();
                j++;
            }
        } else if ((*arr=='-' || *arr=='+') && *(arr-1)=='(' && *(arr+1)=='(') {
            if (*arr=='-') {
                arr += 2;
                value[j] = -Calculator(size);
                j++;
            } else {
                arr += 2;
                value[j] = Calculator(size);
                j++;
            }
        } else if ((*arr=='-' || *arr=='+') && *(arr-1)!=')' && (*(arr-1)<'0' || *(arr-1)>'9')) {
            if (*arr=='-') {
                arr++;
                value[j] = -IdentifyNum();
                j++;
            } else {
                arr++;
                value[j] = IdentifyNum();
                j++;
            }
        } else {
            operator[k] = *arr;
            arr++;
            k++;
        }
    }
    // Calculating the expression with values and operands
    int len = (int)strlen(operator);
    return NumCalc(operator,value,len);
}

int main() {
    // Reading input
    int i=0;
    char calc_arr[MAX];
    char res_arr[MAX];
    char temp = getchar();
    while (temp!=EOF && temp!='\n') {
        if (temp!=' ') {
            calc_arr[i] = temp;
            i++;
        }
        temp = getchar();
    }
    calc_arr[i]='\0';
    int size = (int)strlen(calc_arr);
    arr = calc_arr;
    long double result = Calculator(size);
    // Printing result
    if (result==0.0) {
        printf("0\n");
        return 0;
    }
    sprintf(res_arr,"%.8Lf",result);
    for (i=0; res_arr[i]!='.'; i++) {
        printf("%c",res_arr[i]);
    }
    for (; res_arr[i]!='\0' && Print0(&res_arr[i]); i++) {
        printf("%c",res_arr[i]);
    }
    printf("\n");
    return 0;
}



