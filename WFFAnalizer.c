#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// [*] Conjuncion    [+] Disyuncion    [-] Implicacion     [~] Negacion

typedef struct
{
    int top;
    char elementos[100];
} pila;

void push(pila *p, int x);
int pop(pila *p);
int empty(pila *p);
int oprpar(char *expresion);
int minval(char *expresion);
int parjpar(pila *p, char *expresion);
char *replaceRange(const char *str, int start, int end, const char *replacement);
char *substring(const char *str, int start, int end);
char *implicationFree(const char *expresion);

int main()
{
    char expresion[100];
    char expresionfree[300];
    pila s; // Pila de apoyo
    s.top = 0;
    int validation1, validation2, validation3;
    system("cls");
    printf("Ingrese la expresion a evaluar: \n");
    gets(expresion); // Lectura de la expresion a evaluar
    validation1 = oprpar(expresion);
    validation2 = minval(expresion);
    validation3 = parjpar(&s, expresion);

    printf("\n\n\nLa expresion ");
    printf("%s", expresion);
    if (validation1 == 1 && validation2 == 1 && validation3 == 1)
    {
        printf(" es valida\n");
        strcpy(expresionfree, implicationFree(expresion));
        printf("Expresion sin implicaciones:  %s", expresionfree);
    }
    else
    {
        printf(" es invalida");
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
int oprpar(char *expresion)
{
    int opr = 0;
    int par = 0;
    while (*expresion)
    {
        if ((*expresion == '+') || (*expresion == '*') || (*expresion == '-') || (*expresion == '~'))
        {
            opr++;
        }
        if ((*expresion == '(') || (*expresion == ')'))
        {
            par++;
        }
        expresion++;
    }
    if (par == opr * 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int minval(char *expresion)
{
    // 0=[Vacio] 1 = [Literal] 2=[Negacion] 3=[Operador] 4=[Parentesis] 5=[Valido]
    int valores[100];
    int cadenatemporal[100];
    for (int i = 0; i < 100; i++)
    {
        valores[i] = 0;
        cadenatemporal[i] = 0;
    }
    int i = 0;
    while (*expresion)
    {
        if ((*expresion == '(') || (*expresion == ')'))
        {
            valores[i] = 4;
        }
        if ((*expresion == '+') || (*expresion == '*') || (*expresion == '-'))
        {
            valores[i] = 3;
        }
        if (*expresion == '~')
        {
            valores[i] = 2;
        }
        if (((*expresion >= 80) && (*expresion <= 90)) || ((*expresion >= 112) && (*expresion <= 122)))
        {
            valores[i] = 1;
        }
        expresion++;
        i++;
    }
    i = 0;
    while (valores[i] != 0)
    {
        for (int k = 0; k < 100; k++)
        {
            cadenatemporal[k] = 0;
        }
        if (valores[i] == 3)
        {
            if ((valores[i + 1] == 1 || valores[i + 1] == 5) && (valores[i + 2] == 4) && (valores[i - 1] == 1 || valores[i - 1] == 5) && (valores[i - 2] == 4))
            {
                for (int j = 0; valores[j] != 0; j++)
                {
                    cadenatemporal[j] = valores[j];
                    if (j + 2 == i)
                    {
                        cadenatemporal[j] = 5;
                        j = j + 5;
                        int k;
                        k = j - 4;
                        while (valores[j] != 0)
                        {
                            cadenatemporal[k] = valores[j];
                            k++;
                            j++;
                        }
                        break;
                    }
                }

                for (int i = 0; i < 100; i++)
                {
                    valores[i] = cadenatemporal[i];
                }
                i = -1;
            }
        }
        if (valores[i] == 2)
        {
            if ((valores[i + 1] == 1 || valores[i + 1] == 5) && (valores[i + 2] == 4) && (valores[i - 1] == 4))
            {
                for (int j = 0; valores[j] != 0; j++)
                {
                    cadenatemporal[j] = valores[j];
                    if (j + 1 == i)
                    {
                        cadenatemporal[j] = 5;
                        j = j + 4;
                        int k;
                        k = j - 3;
                        while (valores[j] != 0)
                        {
                            cadenatemporal[k] = valores[j];
                            k++;
                            j++;
                        }
                        break;
                    }
                }

                for (int i = 0; i < 100; i++)
                {
                    valores[i] = cadenatemporal[i];
                }
                i = -1;
            }
        }
        if ((valores[0] == 5 || valores[0] == 1) && valores[1] == 0)
        {
            return 1;
        }
        i++;
    }
    return 0;
}
int parjpar(pila *p, char *expresion)
{
    while (*expresion)
    { // Mientras lo que este en (expresion) sea diferente de NULL
        if (*(expresion) == '(')
        {
            push(p, '(');
        }
        if ((*(expresion) == ')') && (p->elementos[p->top] == '('))
        {
            pop(p);
        }
        else if ((*(expresion) == ')') && ((p->elementos[p->top] != '(')))
        {
            push(p, ')');
        }
        expresion++;
    }

    if (p->top == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
char *replaceRange(const char *str, int start, int end, const char *replacement)
{
    int len = strlen(str);
    int newLen = len - (end - start) + strlen(replacement);
    char *result = (char *)malloc(newLen + 1);

    
    strncpy(result, str, start);
    result[start] = '\0';

    
    strcat(result, replacement);

    
    strcat(result, str + end);

    return result;
}
char *substring(const char *str, int start, int end)
{
    int len = end - start;
    char *result = (char *)malloc(len + 1);
    strncpy(result, str + start, len);
    result[len] = '\0';
    return result;
}
char *implicationFree(const char *expresion)
{
    char *expresioncopy = strdup(expresion); //strdup crea una copia de 'expresion' en 'expresioncopy'
    int indice = 0;

    while (indice < strlen(expresioncopy)) 
    {
        if (expresioncopy[indice] == '-')
        {
            if (expresioncopy[indice - 1] == ')') //Si hay una subformula
            {
                int indiceparentesiscerrado = indice - 1;
                int indiceparentesisabierto = -1;

                int balance = 1;

                // Buscar el '(' correspondiente a nuestro ')'
                for (int i = indiceparentesiscerrado - 1; i >= 0; i--)
                {
                    if (expresioncopy[i] == ')')
                    {
                        balance++;
                    }
                    else if (expresioncopy[i] == '(')
                    {
                        balance--;
                    }

                    if (balance == 0) 
                    {
                        indiceparentesisabierto = i; //asigna al indice el valor de la posicion en la que esta '('
                        break;
                    }
                }

                //Crear una subcadena llama ExpresionInterna con la expresion dentro de los parentesis
                char *ExpresionInterna = substring(expresioncopy, indiceparentesisabierto, indiceparentesiscerrado + 1);

                //Modificar la expresion 
                char *ExpresionInternaModificada = (char *)malloc(strlen(ExpresionInterna) + 5); 
                sprintf(ExpresionInternaModificada, "(~%s)+", ExpresionInterna); 
                //La funcion sprintf ayuda a insertar lo que queriamos en la expresion modificada
                // Remplaza el tamaño de la cadena
                char *nuevaexpresion = replaceRange(expresioncopy, indiceparentesisabierto, indice + 1, ExpresionInternaModificada);

                // Libera la memoria y pasa la expresion final a expresion copy
                free(expresioncopy);
                expresioncopy = nuevaexpresion;

                // Libera memoria
                free(ExpresionInterna);
                free(ExpresionInternaModificada);
            }
            else //Si hay un atomo
            { 
                char atomo = expresioncopy[indice - 1]; 

                // Modificar el atomo
                char Nuevaliteral[6]; 
                sprintf(Nuevaliteral, "(~%c)+", atomo);

                // Remplaza el tamanio de la cadena
                char *nuevaexpresion = replaceRange(expresioncopy, indice - 1, indice + 1, Nuevaliteral);

                // Libera la memoria y pasa la expresion final a expresion copy
                free(expresioncopy);
                expresioncopy = nuevaexpresion;
            }
        }
        indice++;//Sigue avanzando en expresioncopy en busca de mas implicaciones
    }

    return expresioncopy; //Devuelve la expresion modificada
}