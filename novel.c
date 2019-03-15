#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include "novel.h"

int main(){

    //Initialize required variables

    int i,n,preemptive,totalWT=0,totalTT=0,t=0;
    float avgWT, avgTT;
    process *p;

    //First input is number of processes to be scheduled

    printf("==========  Novel CPU Scheduling Algorithm Simulator  ==========\n\n");
    printf("Enter the number of processes: ");
    scanf("%d",&n);

    //Allocate space for the process structure array of given number of processes

    p = (process *) malloc((size_t) n*sizeof(process));
    if(!p){printf("Error while allocating memory."); exit(0);}

    //Ask mode of scheduling: Either Non-Preemptive or Preemptive

    printf("Enter 0 for non-preemptive simulation, 1 for preemptive: ");
    scanf("%d",&preemptive);
    getTasks(p,n);

    if(!preemptive){

        //Code for Simulating the Non-Preemptive Algorithm

        sortTasks(p,n,0);
        int j, swapped=0;
        for(i=0;i<n;i++){

            /*If p[i], the next process with least cf, has
            not arrived, find next in the sorted list that's arrived
            and swap the two*/

            if(p[i].arrt>t){

                /*Safety net for the following case:
                Process may not have actually arrived but
                calculation of cf shows it is the most preferable for execution*/

                swapped=0;
                for(j=i;j<n;j++){
                    if(p[j].arrt<=t){
                        swapProcess(p,i,j);
                        swapped=1;
                        i--;
                        break;
                    }
                }

                /*If a suitable swap has occurred, we can re-enter the loop immediately
                Value of i has been taken care of for decrementation to bring it as it was before
                in the foor loop above...*/

                if(swapped) continue;
                else{
                    printf("\nIdle for Process P%d",p[i].id);
                    t=p[i].arrt;
                }
            }

            /*Because this is non-preemptive, a process once dispatched,
            gets completely executed and its remaining burst time becomes zero at
            once, and time is assumed to have passed as equal to required burst time
            of the process p[i]*/

            p[i].wt = t-p[i].arrt;
            t += p[i].bt;
            p[i].tt=t - p[i].arrt;
            totalWT+=p[i].wt;
            totalTT+=p[i].tt;

            /*Process once scheduled gets completely executed. So now display its stats*/

            printf("\nExecuted Process P%d: BT=%d AT=%d WT=%d TT=%d",p[i].id,p[i].bt,p[i].arrt,p[i].wt,p[i].tt);
        }

        //Calculate overall stats

        avgWT=(float)totalWT/(float)n;
        avgTT=(float)totalTT/(float)n;

        //Show overall stats and finish

        printf("\nTotal WT: %d, Avg WT:%f",totalWT,avgWT);
        printf("\nTotal TT: %d, Avg TT:%f",totalTT,avgTT);
    }

    else{

        //Code for simulating the Preemptive algorithm
        /*bt is the total burst time of all the processes combined,
        current is the currently executing process's offset wrt the array p(not id!!!)
        swapped is the flag if a swap between not-yet-arrived-but-most-suitable
        and arrived-but-second-most-suitable process has occured
        */

        int bt=sum(p,n)[1],current=0,swapped=0,j;
        sortTasks(p,n,current);

        /*Within the loop the time increases by 1 ticks per iteration or 0 ticks per iteration,
        depending on whether the system is in IDLE state (no runnable process available)
        Also, for every loop iteration total burst time is decreased by 1 for the p[current] process.
        Note: current is an offset NOT id, id is stored within p[x].id where x is an offset*/

        while(bt){

                /*Check if nominated process has arrived or not at time t
                If not arrived then find the new nominee for current execution
                Set swapped to 1 if a new nominee has been found and swap has been performed
                Otherwise set swapped to 0
                Depending on swap has occurred or not, decide whether the system will remain idle
                or move on to execute next nominee
                */

                if(p[current].arrt>t){
                    swapped=0;
                    for(j=current;j<n;j++){
                        if(p[j].arrt<=t){
                            swapProcess(p,i,j);
                            swapped=1;
                            current--;
                            break;
                        }
                    }
                    if(!swapped){
                        printf("\nIdle for Process P%d",p[current].id);
                        t=p[i].arrt;
                    }
                }
                //Increment timer
                t++;
                //Decrement total remaining burst time counter
                bt--;

                //Decrement remaining burst time from the process's data block.
                p[current].bt--;
                //This is to reduce starvation, my addition to the algorithm. Moreover, the text was unclear around this step.
                p[current].cf++;

                /*
                All others who were not currently executed are waiting, so increase their
                waiting time by 1.
                */

                for(i=0;i<n;i++){
                    if(i!=current && p[i].arrt<t){
                        p[i].wt++;
                    }
                }

                //Print current status
                printf("\nRun P%d: BT Remaining=%d, T=%d, ConditionFactor=%d",p[current].id,p[current].bt,t,p[current].cf);

                /*If process under current execution is completed, then its bt will be zero
                Now we need to update its turnaround time.
                Waiting time for the current process was being updated while it was not under execution
                Total turnaround time is incremented with newly completed process's turnaround time.
                Total Waiting time is incremented with the newly completed process's waiting time.
                */

                if(p[current].bt==0){
                    p[current].tt = t-p[current].arrt;
                    totalWT+=p[current].wt;
                    totalTT+=p[current].tt;
                    printf("\nFinished Process P%d: AT=%d WT=%d TT=%d",p[current].id,p[current].arrt,p[current].wt,p[current].tt);
                    current++;
                    if(current>=n) break;
                }
                //Because it is preemptive, we need to sort at every timer tick...
                sortTasks(p,n,current);
        }

        //Calculate and Show algorithm stats, averages calculated as totals divided by number of processes...
        avgWT=(float)totalWT/(float)n;
        avgTT=(float)totalTT/(float)n;

        printf("\nTotal WT: %d, Avg WT:%f",totalWT,avgWT);
        printf("\nTotal TT: %d, Avg TT:%f",totalTT,avgTT);
    }
    //Wait for user input for exitting.
    printf("\n\nPress any key to exit...");
    getch();
}
