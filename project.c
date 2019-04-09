#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>

int NumCats,NumBowl,NumMice,total_Cats,total_Bowl,total_Mice;

sem_t CatsEat,MiceEat;

void *CatsEating()
{
        if(NumCats<=total_Cats && NumBowl<=total_Bowl)
        {
                sem_wait(&CatsEat);
                NumBowl--;
                NumCats--;
                printf("\n Cat %d has eaten the bowl %d",total_Cats-NumCats,total_Bowl-NumBowl);
                sem_post(&CatsEat);
        }
}

void *MiceEating()
{
        if(NumMice!=0 && NumBowl!=0)
        {
                sem_wait(&MiceEat);
                NumBowl--;
                NumMice--;
                printf("\n Mice %d has eaten the bowl %d", total_Mice-NumMice,total_Bowl-NumBowl);
                sem_post(&MiceEat);
        }
}
int main()
{
        pthread_t th, th1;
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

        while((NumBowl!=0) && (NumCats!=0 || NumMice!=0) && NumCats>=0 && NumMice>=0 && NumBowl>=0)
        {

                pthread_create(&th,NULL,CatsEating,NULL);
                pthread_create(&th1, NULL, MiceEating, NULL);
                pthread_join(th,NULL);
                pthread_join(th1, NULL);
        }
        return 0;
}