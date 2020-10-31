
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matricesLib.h"
#include <math.h>
#define MAX 100

//Se debe compilar como gcc proyect.c -lm
//O marcara un error relacionado con la libreria de math
//Para ingresar los numeros se deben poner de arriba hacia abajo, presionando enter
// j - > numero de fila
// i - > numero de columna
/*
           i=0 i=1 i=2
            __  __  __
   j = 0 |
   j = 1 |
   j = 2 |
    

*/
//usage: -r random 3x3 matrix
//usage: -p personalized matrix
//usage: ./a.out -p -r Steps
// (size -1)^2 +1 , is regular

//m[fila][columna]
//n steps

int checkEst(Matrix *m)
{
    unsigned int i, j;
    float acum;
    int flag = 0;

    for (j = 0; j < m->rows; j++)
    {
        acum = 0;
        //suma cada fila
        for (i = 0; i < m->columns; i++)
        {
            acum = acum + m->numbers[i][j];
        }

        //printf("row %i %f \n", j, acum);
        //si no es estocastico prender la bandera
        if (acum != 1.0)
            flag = 1;
    }
    //printf("flag is %i\n",flag);
    return flag;
}

Matrix *multiplySTEPS(Matrix *m)
{
    Matrix *a, *c;
    int i, j;
    int FlagSteady;
    a = clonemx(m);
    c = clonemx(m);
    for (i = 1; i < MAX; i++)
    {
        FlagSteady = 0;
        c = multiply(c, m);
        print(c);
        printf("\n");
        FlagSteady = equals(a, c);
        //printf("\n");
        printf("Flag %i", FlagSteady);
        a = clonemx(c);
        if (FlagSteady == 1)
        {
            break;
        }
    }
    if (FlagSteady == 1)
    {
        printf("The matrix values doesnt change in steps %i", i);
    }
    else
    {
        printf("The matrix values are still changing");
    }
    return c;
}

int CheckByColumn(Matrix *m)
{
    int a,b;
    int i,j;
    int flag = 0;

    for (i = 0; i < m->rows; i++)
    {
        acum = 0;
        //suma cada fila
        for (j = 1; j < m->columns; j++)
        {   
            a = m->numbers[i][j];
            b = m->numbers[i][j];
        }

    }
    //printf("flag is %i\n",flag);
    return flag;
}
//Checar si hay algun 0 en la matriz
int isRegular(Matrix *m)
{
    int i, j;
    int flag = 0;
    float num = 0;

    for (j = 0; j < m->rows; j++)
    {
        for (i = 0; i < m->columns; i++)
        {
            num = m->numbers[i][j];
            if (num == 0)
            {
                return -1;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{

    Matrix *m1;
    Matrix *m2;
    Matrix *res;
    int i;
    int estocastico, regular;

    manual_entry(&m1);
    printf("initial matrix is:\n");
    print(m1);
    printf("\n");

    estocastico = checkEst(m1);
    if (estocastico != 1)
    {
        printf("La matriz es estocastica\n");
    }
    else
    {
        printf("La matriz no es estocastica\n");
    }

    res = multiplySTEPS(m1);

    regular = isRegular(res);
    if (regular != 0)
    {
        printf("La matriz no es regular");
    }
    else
    {
        printf("La matriz es regular");
    }
}
