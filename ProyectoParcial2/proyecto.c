
#include <time.h>
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
        printf("Multypling matrix, step #%i\n", i + 1);
        print(c);
        printf("\n");
        FlagSteady = equals(a, c);
        //printf("\n");
        //printf("Flag %i", FlagSteady);
        a = clonemx(c);
        if (FlagSteady == 1)
        {
            break;
        }
    }
    if (FlagSteady == 1)
    {
        printf("The matrix values doesnt change in steps %i\n", i + 1);
    }
    else
    {
        printf("The matrix values are still changing after 100 steps\n");
    }
    return c;
}

int CheckByColumn(Matrix *m)
{
    double a, b;
    int i, j;
    int flag = 0;
    int acumC, acumR = 0;

    for (i = 0; i < m->rows; i++)
    {

        //suma cada fila
        for (j = 0; j + 1 < m->columns; j++)
        {

            a = m->numbers[i][j];
            b = m->numbers[i][j + 1];

            if ((a - b) < DIF)
            {
                acumC++;
            }
            //printf("a %f b %f acumC %i\n", a, b, acumC);
        }
        if (acumC == (m->columns - 1))
        {
            acumR++;
        }
        acumC = 0;
    }
    //printf("acumR %i\n", acumR);
    if (acumR == (m->rows - 1))
    {
        flag = 1;
    }

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

void persoSteps(Matrix *m, int cord1, int cord2, int perSteps)
{
    Matrix *c;
    int i, j;
    double prob;

    c = clonemx(m);
    for (i = 1; i < perSteps; i++)
    {
        c = multiply(c, m);
        printf("Multypling matrix, step #%i\n", i + 1);
        print(c);
        printf("\n");       
    }
    prob = c->numbers[cord2][cord1];
    printf("The probability of going to [%i][%i] in %i steps is %f\n", cord1, cord2, perSteps,prob);
}

Matrix* createRandMatrix(){
    int rows = 3;
    int cols = 3;
    double x,y,z;
    Matrix *m;
    srand(time(NULL));


    x =  (rand() % 100);
    y =  (rand() % 100);
    z =  (rand() % 100);
    x = x / 100.0;
    y = y / 100.0;
    z = z / 100.0;
    m = constructor(rows,cols);
    
    printf("x %f , y %f , z %f \n",x,y,z);
    //print(m);


}

int main(int argc, char *argv[])
{
    int cord1, cord2, perSteps;
    Matrix *m1;
    Matrix *m2;
    Matrix *res;
    int i;
    int estocastico, regular, steady;

    printf("Pls write the matrix to calculate, write  1 character by lane, when you finish press control + d\n");
    manual_entry(&m1);
    printf("initial matrix is:\n");
    print(m1);

    if (argc == 4)
    {
        cord1 = atoi(argv[1]);
        cord2 = atoi(argv[2]);
        perSteps = atoi(argv[3]);
        printf("You choose to calculate [%i][%i] in %i steps\n", cord1, cord2, perSteps);
        persoSteps(m1,cord1,cord2,perSteps);
    }
    
    printf("\n");

    estocastico = checkEst(m1);
    res = multiplySTEPS(m1);
    steady = CheckByColumn(res);
    regular = isRegular(res);

    if (estocastico != 1)
    {
        printf("La matriz es estocastica\n");
    }
    else
    {
        printf("La matriz no es estocastica\n");
    }

    if (steady == 1)
    {
        printf("The matrix has steady state\n");
    }
    else
    {
        printf("The matrix doesnt have steady state\n");
    }

    if (regular != 0)
    {
        printf("La matriz no es regular\n");
    }
    else
    {
        printf("La matriz es regular\n");
    }

    createRandMatrix();
}
