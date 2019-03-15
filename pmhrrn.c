#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct{
    int id,bt,btc,at,wt,tt;
    float pr, prc;
}process;

void PrSort(process *,int,int,int);

int* sum(process *,int);

int main(){
    printf("==========  Preemptive Highest Response Ratio Next CPU Scheduling Algorithm Simulator  ==========\n\n");
    int i,n,totalWT=0,totalTT=0,t=0;
    float avgWT, avgTT;
    process *p;

    //Taking Inputs
    printf("Number of processes: ");
    scanf("%d",&n);

    //Allocating Memory
    p = (process *) malloc((size_t) n*sizeof(process));
    if(!p){printf("Error while allocating memory."); exit(0);}


    printf("Enter arrival time followed by burst time and priority for each process %d:\n",n);
    for(i=0;i<n;i++){
        scanf("%d",&(p[i].at));
        scanf("%d",&(p[i].bt));
        scanf("%f",&(p[i].pr));
        p[i].prc=p[i].pr;
        p[i].btc=p[i].bt;
        p[i].wt=0;
        p[i].tt=0;
        p[i].id=i;
    }
    //Task Scheduler
    int bt=sum(p,n)[1],current_process=0, res=0;;
    printf("\nTotal BT: %d\n",bt);
    PrSort(p,n,0,0);
    while(bt){
        //sort the tasks according to priority and arrival time
        PrSort(p,n,current_process,t);

        if(p[current_process].at>t){
            printf("\nNo Process In Ready Queue\n");
            continue;
        }

        printf("\n");
        p[current_process].pr = ((p[current_process].prc)/2) + (((float)(p[current_process].btc+p[current_process].wt)/(float)p[current_process].btc)/2);

        printf("Run P%d: BT=%d, BT Remaining=%d, T=%d, WT=%d, Priority=%f\n",p[current_process].id,p[current_process].btc,p[current_process].bt,t,p[current_process].wt,p[current_process].pr);

        for(i=current_process;i<n;i++){
            if(p[i].at<=t && p[i].bt>0  ){
                printf("i:%d, prc: %f, bt: %d, wt: %d, res: %f, pr: %f\n",p[i].id,p[i].prc,p[i].btc,p[i].wt,(float)(p[i].btc+p[i].wt)/p[i].btc, ((p[i].prc)/2) + (((float)(p[i].btc+p[i].wt)/(float)p[i].btc)/2));
            }
        }


        //Updating Hybrid Priority
        for(i=0;i<n;i++){
            if(i!=current_process && p[i].at<t && p[i].bt>0){
                p[i].wt++;
                p[i].pr = ((p[i].prc)/2) + (((float)(p[i].btc+p[i].wt)/(float)p[i].btc)/2);
            }
        }
        bt--;
        p[current_process].bt--;

        //If process ends
        if(p[current_process].bt==0){
            p[current_process].tt = t-p[current_process].at;
            totalWT+=p[current_process].wt;
            totalTT+=p[current_process].tt;
            printf("\n**********Finished Process P%d: AT=%d WT=%d TT=%d**********\n",p[current_process].id,p[current_process].at,p[current_process].wt,p[current_process].tt);
            current_process++;
            if(current_process>=n) break;
        }
        t++;
    }
    //Computing averageWT and averageTT
    avgWT=(float)totalWT/(float)n;
    avgTT=(float)totalTT/(float)n;
    printf("\nAverage Waiting Time: %f",avgWT);
    printf("\nAverage Turnaround Time: %f\n\n",avgTT);
    printf("\n\nPress any key to exit...");
    getch();
}

void PrSort(process *p,int n,int current_process, int t){
    int i,j;
    process *ptemp;
    ptemp = (process *) malloc((size_t) 1*sizeof(process));
    for(i=current_process;i<n;i++){
        for(j=i;j<n;j++){
            if(p[i].pr<p[j].pr && p[i].at<=t && p[j].at<=t){
                ptemp[0]=p[j];
                p[j]=p[i];
                p[i]=ptemp[0];
            }
        }
    }
}
int* sum(process *p, int n){
    int i;
    int *out;
    out = (int*) calloc(4,sizeof(int));

    for(i=0;i<n;i++){
        out[0]+=p[i].at;
        out[1]+=p[i].bt;
        out[2]+=p[i].wt;
        out[3]+=p[i].tt;
    }
    return out;
}
