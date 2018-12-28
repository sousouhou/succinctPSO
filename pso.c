/* 
    author: S. Song 
    email: leadingsong[at]outlook.com
    license: Apache 2.0

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rand.h"

#define MAX_POPSIZE     400  
#define MAX_DIMEN       100  


int FEs = 0;
int maxFEs = 0;

int dim = 0;
int popSize  = 0;
double w = 0;
double c1 = 0;
double c2 = 0;

double posMin = 0;
double posMax = 0;

double pos[MAX_POPSIZE][MAX_DIMEN];  // position of each particle
double vel[MAX_POPSIZE][MAX_DIMEN];  // velocity of each particle
double fit[MAX_POPSIZE];             // fitness of each particle

double pbestPos[MAX_POPSIZE][MAX_DIMEN];  //personal best position
double pbestFit[MAX_POPSIZE];             //personal best fitness

double gbestPos[MAX_DIMEN];
double gbestFit= 1e+100;



double fun_hook(double *a, int dime)
{
    double x = 0;
    int i = 0;
    
    FEs ++;
    if(FEs % 1000 == 0 && FEs!=0 )
    {
        printf("FEs = %d: %.6e\n", FEs, gbestFit);
    }
    
    for (i=0; i<dime; i++)
    {
        x += a[i]*a[i];
    }
    return x;
}


void initial( void )
{
    randomize((time(NULL)%1000)/1000.0);
    
    FEs = 0;
    maxFEs = 25000;

    dim = 20;
    popSize =100;
    w = 0.9;
    c1 = 1.5;
    c2 = 0.5;
    
    posMin = -10;
    posMax = 10;

    {
        int i = 0;
        int j = 0;
        for (i=0; i<popSize; i++) 
        {
            for(j=0; j<dim; j++)
            {
                pos[i][j] = rndreal(posMin, posMax);
                vel[i][j] = 0;
            }
            fit[i] = fun_hook(pos[i], dim);
            
            for(j=0; j<dim; j++)
            {
                pbestPos[i][j] = pos[i][j];
            } 
            pbestFit[i] = fit[i];
            
        }        
    }
    
    {
        int j =0;
        for(j=0; j<dim; j++)
        {
            gbestPos[j] =  pbestPos[0][j] ;  // set p[0] as the gbest
        } 
        gbestFit = pbestFit[0];
    }
    
}



int main(void)
{    
    initial();

    while(FEs < maxFEs ) 
    {
        int i = 0;
        int j = 0;
        
        //---- update velocity 
        for (i = 0; i < popSize; i++) 
        {
            for(j=0; j<dim; j++)
            {
                vel[i][j] =  w*vel[i][j] + c1*rndreal(0,1)*(pbestPos[i][j] - pos[i][j]) + c2*rndreal(0,1)*(gbestPos[j] - pos[i][j]);
            }
        }
        
        //---- update positions and maintain within limits 
        for (i = 0; i < popSize; i++) 
        {
            for(j=0; j<dim; j++)
            {
                pos[i][j] = pos[i][j] + vel[i][j];
                
                if( pos[i][j] > posMax )
                {
                    pos[i][j] = posMax;
                    vel[i][j] = - vel[i][j];
                }
                if( pos[i][j] < posMin )
                {
                    pos[i][j] = posMin;
                    vel[i][j] = - vel[i][j];
                }                
            }
        }
        
        //---- evaluate and update pbest, gbest.
        for (i = 0; i < popSize; i++) 
        {   
            fit[i] = fun_hook(pos[i], dim);
            
            if( fit[i]< pbestFit[i])
            {
                for(j=0; j<dim; j++)
                {
                    pbestPos[i][j] = pos[i][j];
                } 
                pbestFit[i] = fit[i];  
            }
            
            if( fit[i]< gbestFit )
            {
                for(j=0; j<dim; j++)
                {
                    gbestPos[j] =  pos[i][j] ;  
                } 
                gbestFit = fit[i]; 
            }

        } 
    }

    printf("Last, gbestFit is %.6e \n", gbestFit);            

    return 0;
}

