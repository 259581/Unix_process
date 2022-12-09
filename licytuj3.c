#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>



#define N_AGENTS 20 /* liczba uczestników */
#define N_ITEMS 20 /* liczba przedmiotów */
#define OPENING_BID 100 /* początkowa cena każdego przedmiotu */
#define MAX_RAISE 10 /* maksymalna wartość podbicia */
#define BIDDING_ROUNDS 1000000 /* liczba podbić wykonana przez każdego uczestnika */

//int Bids [N_ITEMS];
//int Nbids [N_ITEMS];
int a = 0;
int b = 0;

long int Bids_sum = 0;
long int Nbids_sum = 0;

struct memory{
    int Bids [N_ITEMS];
    int Nbids [N_ITEMS];
    int client_write;
}* s1;

/*****************************************************************************************************************/
int main(int argc, char *argv[]){


int shmid;
char *data;


if (argc > 2) {
	fprintf(stderr, "usage: shmdemo [data_to_write]\n");
	exit(1);
}

/* connect to (and possibly create) the segment: */
if ((shmid = shmget(259581, sizeof(struct memory), 0666 | IPC_CREAT)) == -1) {
	perror("shmget");
	exit(1);
}

if ((s1 = shmat(shmid, (void *)0,0)) ==(void *)-1){
    perror("failure shmat");
    exit(errno);
}


// set starting value
for (int i=0;i<N_ITEMS;i++){
    s1->Bids[i]=OPENING_BID;
    s1->Nbids[i]=0;
}

for (int i=0;i<N_AGENTS;i++){
//starting subprocess
switch(fork()){
    case -1:
    fprintf(stderr, "Error in fork, errno=%d\n", errno);
    exit(-1);
    break;

    case 0:
    srand(getpid());
    //increasing value
    for (int i=0;i<BIDDING_ROUNDS;i++){
        a = rand()%N_ITEMS;
        b = rand()%(MAX_RAISE+1);
        s1->Bids[a]+=b;
        s1->Nbids[a]+=1;
    }
        exit(0);
        break;
    }
}

// waiting for children come from school
for (int i=0;i<N_AGENTS;i++){
    wait(NULL);
}

//printing item's value
for (int i=0;i<N_ITEMS;i++){
    printf("Item's value, %d element:%d\n",i,s1->Bids[i]);
}
printf("\n");

//printing bids amount
for (int i=0;i<N_ITEMS;i++){
    printf("Bids amount, %d element:%d\n",i,s1->Nbids[i]);
}

//summary
for(int i=0;i<N_ITEMS;i++){
    Bids_sum+=s1->Bids[i];
    Nbids_sum+=s1->Nbids[i];
}
printf("\n");
printf("Total sum of bids:%ld\n",Bids_sum);
printf("Total sum of Nbids:%ld\n",Nbids_sum);

//realising reserved memory - destroying it
shmctl(shmid, IPC_RMID, 0);
return 0;
}