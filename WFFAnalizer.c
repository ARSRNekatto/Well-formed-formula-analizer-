#include <stdio.h>
#include <unistd.h>
 
// [*] Conjuncion    [+] Disyuncion    [-] Implicacion     [~] Negacion

typedef struct
{
    int top;
    char elementos[100];
} pila;

void push(pila *p, int x);
int pop(pila *p);
int empty(pila *p);
int value(pila *p, char *expresion);
int valueopr(char * expresion);


int main(){
    char expresion[100];
    pila s; //Pila de apoyo
    s.top=0;
    int validation, validation2;
    system("cls"); 
    printf("Ingrese la expresion a evaluar: \n");
    gets(expresion); //Lectura de la expresion a evaluar
    validation = value(&s,expresion); //Funcion para validar los parentesis
    validation2 = valueopr(expresion); //Funcion para validar los atomos y operaciones
    if (validation==1&&validation2==1){
        printf("\nExpresion valida");
    }else{
        printf("\nExpresion invalida");
    }

}

void push(pila *p, int x)
{
    if (p->top == 100)
    {
        printf("\nDesbordamiento");
        {
            exit(1);
        }
    }
    else
    {
        p->elementos[++(p->top)] = x;
    }
}
int pop(pila *p)
{
    if (empty(p) == 1)
    {
        printf("\nDesbordamiento");
        exit(1);
    }
    else
    {
        return (p->elementos[p->top--]);
    }
}
int empty(pila *p)
{
    if (p->top == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int value(pila *p, char *expresion){
    while(*expresion){ //Mientras lo que este en (expresion) sea diferente de NULL
        if(*(expresion) == '('){ 
            push(p,'(');
        }
        if(*(expresion) == '['){
            push(p,'[');
        }
        if(*(expresion) == '{'){
            push(p,'{');
        }
        if((*(expresion) == ')')&&(p->elementos[p->top]=='(')){
            pop(p);
        }else if((*(expresion) == ')')&&((p->elementos[p->top]!='('))){
            push(p,')');
        }
        if((*(expresion) == ']')&&(p->elementos[p->top]=='[')){
            pop(p);
        }else if((*(expresion) == ']')&&((p->elementos[p->top]!='['))){
            push(p,']');
        }
        if((*(expresion) == '}')&&(p->elementos[p->top]=='{')){
            pop(p);
        }else if((*(expresion) == '}')&&((p->elementos[p->top]!='{'))){
            push(p,'}');
        }
        expresion++; 
    }

    if(p->top==0){
        printf("\nParentesis OK\n"); 
        return 1;
    } else {
        return 0;
    }
}
int valueopr(char * expresion){
    int val = 0; //val0 = operando        val1 = literal          val2= negacion
    int tam = 0; //tamaño de la expresion
    int following = 0; //variable para darle un seguimiento al tamaño "valido" de la expresion
    while(*expresion){
        if(((*expresion == '*')||(*expresion == '+')||(*expresion == '-'))&&(val==1)){
            val = 0;
            following++;
        }
        if((*expresion == ')')||(*expresion == ']')||(*expresion == '}')||(*expresion == '(')||(*expresion == '[')||(*expresion == '{')){
            following++;
        }
        if((*expresion == '~')&&(val==0||val==2)){
            val = 2;
            following++;
        }
        if((((*expresion >= 80)&&(*expresion <= 90))||((*expresion >= 112)&&(*expresion <= 122)))&&(val==0||val==2)){
            val = 1;
            following++;
        }
        expresion++;
        tam++;
    }
    if (tam == following){
    printf("Operadores y atomos OK\n");
    return 1;
    }
}