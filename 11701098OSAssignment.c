
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>

int NumCats,NumBowl,NumMice,total_Cats,total_Bowl,total_Mice;

sem_t CatsEat,MiceEat;

void *CatsEating()	//threads for Cat eating from the bowl
{
        if(NumCats<=total_Cats && NumBowl<=total_Bowl)
        {
                sem_wait(&CatsEat);
                NumBowl--;
                NumCats--;
                printf("\n Cat %d has eaten the bowl \n",total_Cats-NumCats);
                sem_post(&CatsEat);
        }
}

void *MiceEating()	//thread for mice eating from the bowl
{
        if(NumMice!=0 && NumBowl!=0)
        {
                sem_wait(&MiceEat);
                NumBowl--;
                NumMice--;
                printf("\n Mice %d has eaten the bowl \n", total_Mice-NumMice);
                sem_post(&MiceEat);
        }
}

int main()
{
        int count,i,bl,b1,c1,cl,ml,tl;	//declaring variables used in the program
 
        pthread_t th, th1;		//thread declaration 
        printf("\n Enter the number of cats:");
        scanf("%d",&NumCats);
        printf("\n Enter the number of mice:");
        scanf("%d", &NumMice);
        printf("\n Enter the number of bowls:");
        scanf("%d",&NumBowl);

        total_Cats = NumCats;
        total_Mice = NumMice;
        total_Bowl = NumBowl;


        sem_init(&CatsEat,1,1);
        sem_init(&MiceEat,1,1);

        while((NumBowl!=0) && (NumCats!=0 || NumMice!=0) && NumCats>=0 && NumMice>=0 && NumBow$        
	{

                pthread_create(&th,NULL,CatsEating,NULL);
                pthread_create(&th1, NULL, MiceEating, NULL);
                pthread_join(th,NULL);
                pthread_join(th1, NULL);

                count=count+2;

        }
      //Code when there are bowls left and all the animals have eaten once.

        if((NumBowl!=0) && (NumCats==0 || NumMice==0))
        {

                NumBowl = total_Bowl;
                NumCats = total_Cats;
                NumMice = total_Mice;

                b1=total_Cats;
                c1=total_Mice;
                bl=NumBowl-count;
                NumBowl = bl;

                printf("\n THe number of bowls left are  %d %d",bl,count);

                for(;NumBowl!=0;)
                {
                        pthread_create(&th,NULL,CatsEating,NULL);
                        pthread_create(&th1,NULL,MiceEating,NULL);
                        pthread_join(th,NULL);
                        pthread_join(th1,NULL);
                }

                printf("All the bowls are consumed");
        }

        //code when all the bowls have finished but animals have still not eaten

        if((NumCats!=0 || NumMice!=0))
        {
                printf("\n The number of mice and cats left for eating are");
                printf("%d and %d",NumMice,NumCats);

                tl=NumMice+NumCats;

                for(;tl>0;tl--)
                {
                        pthread_create(&th,NULL,CatsEating,NULL);
                        pthread_create(&th1,NULL, MiceEating, NULL);
                        pthread_join(th,NULL);
                        pthread_join(th1,NULL);

                        tl=tl-1;
                }
        }


        return 0;
}