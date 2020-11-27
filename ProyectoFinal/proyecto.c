
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matricesLib.h"
#include <math.h>
#define MAX 100
#define DATA_SIZE 1000

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
    printf("The probability of going to [%i][%i] in %i steps is %f\n", cord1, cord2, perSteps, prob);
}

Matrix *createRandMatrix()
{
    int rows = 3;
    int cols = 3;
    double x, y, z;
    Matrix *m;
    srand(time(NULL));

    x = (rand() % 100);
    y = (rand() % 100);
    z = (rand() % 100);
    x = x / 100.0;
    y = y / 100.0;
    z = z / 100.0;
    m = constructor(rows, cols);

    printf("x %f , y %f , z %f \n", x, y, z);
    //print(m);
}

Matrix *ranMatrix(int a)
{
    Matrix *temp;
    int i, j;
    int b = a;
    double x, y, z = 0;
    double upper, lower;
    double acum;
    int num;
    int limite;

    // (rand() % (upper – lower + 1)) + lower
    upper = 5;
    lower = 100;
    temp = constructor(a, a);
    limite = 100;

    for (j = 0; j < temp->rows; j++)
    {
        acum = 0;
        limite = 100;
        for (i = 0; i < temp->columns; i++)
        {

            if (i == j)
                temp->numbers[i][j] = 0;
            else
            {
                if (i + 1 == temp->columns)
                {
                    temp->numbers[i][j] = limite / 100.0;
                }
                else
                {
                    num = rand() % limite;
                    limite = limite - num;
                    //printf("Numero es %i %i\n", num, i);
                    //printf("limite es %i %i\n", limite, i);
                    temp->numbers[i][j] = num / 100.0;
                    //printf("celda es %f\n", temp->numbers[i][j]);
                }
            }

            //la ultima fila requiere tratamiento especial
            //la i es igual a las columnas -1
            //max 5

            if (j == a - 1)
            {
                num = 0;
                limite = 100;
                i = a - 1;
                temp->numbers[i][j] = 0;
                for (i = a - 2; i > 0; i--)
                {
                    num = rand() % limite;
                    limite = limite - num;
                    temp->numbers[i][j] = num / 100.0;
                }
                temp->numbers[0][j] = limite / 100.0;
                break;
            }
        }
    }

    //print(temp);
    return temp;
}

void startMatrix()
{

}

void printData(Matrix *m, int killCount, int warriorsFaction, int nameFile){
  FILE *fp;
  char buffer[100];
  char Faction;
  Faction = nameFile;
  strcpy(buffer, "faction_stats_");
  strcat(buffer, Faction);
  strcat(buffer, ".txt");
  fp = fopen(buffer, "a");// "w" means that we are going to write on this file
  fprintf(fp, "Stage \n Faction: %i \n KillCount %i", nameFile,killCount);
  fclose(fp); //Don't forget to close the file when finished
}

//usage ./a.out [#Factions][#Turns][#warriors]
int main(int argc, char *argv[])
{
    int noFactions, noTurns, noWarriors;
    Matrix *m1;
    Matrix *m2;
    Matrix *res;
    int i;
    int estocastico, regular, steady;
    srand(time(NULL));
    int turno, turnoActual, gameOn, quienAtaca;
    double probAtaque;
    double x;
    int atackedF;
    int factionRes;
    int killsFaction[6];
    gameOn = 1;

    if (argc == 4)
    {
        noFactions = atoi(argv[1]);
        noTurns = atoi(argv[2]);
        noWarriors = atoi(argv[3]);
    }

    else
    {
        noFactions = 3;
        noTurns = 100;
        noWarriors = 100;
    }

    // printf("quienAtaca %i probAtaque %f",quienAtaca,probAtaque);
    //Simulate a turn
    factionRes=noFactions;
    m1 = ranMatrix(noFactions);
    int warriorsFactions[6];
    //print(m1);

    for (i = 0; i < noFactions; i++)
    {
        warriorsFactions[i] = noWarriors;
        //printf("%i\n",warriorsFactions[i]);
    }

    for(int j=0;j<1000;j++)
    {
        quienAtaca = rand() % noFactions;
        probAtaque = (rand() % 100);
        probAtaque = probAtaque / 100.0;
        //printf("quien Ataca %i probAtaque %f\n",quienAtaca,probAtaque);

        //realizar el ataque y matar un guerrero
        for (i = 0; i < noFactions; i++)
        {
            x = m1->numbers[i][quienAtaca];
            //printf("x %f \n",x);

            if (probAtaque <= x)
            {
                atackedF = i;
                warriorsFactions[atackedF] -= 1;
                killsFaction[quienAtaca]+=1;

                //printf("Faction %i has %i warriors left\n",i,warriorsFactions[atackedF]);
                if(warriorsFactions[atackedF] <= 0){

                    printf("The faction %i died\n",i);
                    for(int w=0;w<noFactions;w++){
                    printf("The faction %i has %i warriors left\n", w, warriorsFactions[w]);
                    }
                    int winer = 0;
                    int acumWiner = 0;
                    winer = warriorsFactions[0];
                    for(int ww=1;ww<noFactions;ww++){
                      if(winer < warriorsFactions[ww])
                        winer = warriorsFactions[ww];
                        acumWiner++;
                    }  printf("The winner is %i\n",acumWiner);

                    factionRes--;
                    //printf("FactionRES %i\n",factionRes);
                    printData(m1,killsFaction[0],warriorsFactions[0],0);
                    return 0;


                }
            }

        }


    }




}
