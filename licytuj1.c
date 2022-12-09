#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define N_AGENTS 20 /* liczba uczestników */
#define N_ITEMS 20 /* liczba przedmiotów */
#define OPENING_BID 100 /* początkowa cena każdego przedmiotu */
#define MAX_RAISE 10 /* maksymalna wartość podbicia */
#define BIDDING_ROUNDS 1000000 /* liczba podbić wykonana przez każdego uczestnika */
//try this git
long int Bids [N_ITEMS];
long int Nbids [N_ITEMS];
int a = 0;
int b = 0;
long int Bids_sum = 0;
long int Nbids_sum = 0;
int main(){
srand(time(NULL));

// set starting value
for (int i=0;i<N_ITEMS;i++){
    Bids[i]=OPENING_BID;
    Nbids[i]=0;
}

//increasing value
for (int i=0;i<BIDDING_ROUNDS;i++){
    a = rand()%N_ITEMS;
    b = rand()%(MAX_RAISE+1);

    Bids[a]+=b;
    Nbids[a]+=1;
}

//printing item's value
for (int i=0;i<N_ITEMS;i++){
    printf("Item's value, %d element:%ld\n",i,Bids[i]);
}
printf("\n");
//printing bids amount
for (int i=0;i<N_ITEMS;i++){
    printf("Bids amount, %d element:%ld\n",i,Nbids[i]);
}

//summary
for(int i=0;i<N_ITEMS;i++){
    Bids_sum+=Bids[i];
    Nbids_sum+=Nbids[i];
}
printf("\n");
printf("Total sum of bids:%ld\n",Bids_sum);
printf("Total sum of Nbids:%ld\n",Nbids_sum);
return 0;
}