#include<stdio.h>
#include<conio.h>

int x,t_last=9,u,arr=0,exec=1,deadline=2,period=3,abs_arr=4,exec_copy=5,abs_deadline=6,w_time=7;t_time=8;idle=999,ALL=1,CURRENT=0;
int stack[100],top=-1;
void push(int y)
{
	top++;
	stack[top]=y;
}
int pop()
{
	if(top==-1)
		return 0;
	top--;
	return stack[top+1];
}
//------------------------------------function definations
typedef struct
{
	int T[10];
	int instance;
	int alive;
}proccess;

void input(proccess *p1,int n)
{
	int i=0;
	while(i<n)
	{
	printf("Enter proccess %d parameters\n",i+1);
	printf("Enter Arrival time,Execution time,Deadline time,Period: ");
	scanf("%d%d%d%d",&p1->T[arr],&p1->T[exec],&p1->T[deadline],&p1->T[period]);
	p1->T[abs_arr]=0,p1->T[exec_copy]=0,p1->T[abs_deadline]=0,p1->T[w_time]=0,p1->T[t_time]=0,p1->instance =0,p1->alive = 0,p1++;
	i++;
	}
}

int totaltime(proccess *p1,int n)
{
	int i=0,k,a[10];
	while(i<n)

		{
			a[i]=p1->T[period];
			p1++;
			i++;
		}
	k=lcm(a,n);
	return k;
}
//gcd function is made for calculating the lcm(Basically used in the lcm function)
int gcd(int a,int b)
{
  if (b==0)
	  return a;
  else
  return gcd(b,a%b);
}

int lcm(int *a,int n)
{
  int res=1,i;
  for (i=0;i<n;i++)
  {
    res=res*a[i]/gcd(res,a[i]);
  }
  return res;
}

int ready(proccess *p1,int timer,int n)//timer determines the timer which means the scale in which the time is being seen
{//Bascially p2 is the copy of p1 so we are storing the value of p1 in a temporary and performing some operation to get the value of a and then again performing other operation to find the value of n1
int i=0,n1=0,a=0;
proccess *p2;
p2=p1;
	while(i<n)
	{
		if(timer==p1->T[abs_arr])
			{
				p1->alive=1;
				a++;
			}
		p1++;
		i++;
	}

	p1=p2;
	i=0;
	while(i<n)
	{
		if(p1->alive==0)
			n1++;
			p1++;
			i++;
	}
	if(n1==n || a!=0)//a!=0 means that atleast one process is there alive and n1==n means that no process is alive and all are at the begging stage with alive=0
	{
		return 1;
	}

	return 0;
}
void new_abs_deadline(proccess *p1,int n,int all)
{
int i=0;
		if(all)
		{
			while(i<n)
			{
				p1->T[abs_deadline]=p1->T[deadline]+p1->T[abs_arr];
				p1++;
				i++;
			}
		}
		else
		{
			p1+=n;
			p1->T[abs_deadline]=p1->T[deadline]+p1->T[abs_arr];
		}
}
//This arr time is the absolute one which means that the arr time after each period so if we give the arr time as 2 in input then the absolut arr time will keep in changing as in the first period it will be 2 and then in the next period it will be arrtime +n*period where n is the nummber of times the process has executed
void new_abs_arr(proccess *p1,int n,int k,int all)
{
int i=0;
		if(all)
		{
			while(i<n)
			{
				p1->T[abs_arr]=p1->T[arr]+k*(p1->T[period]);
				p1++;
				i++;
			}
		}
		else
		{
		p1+=n;
		p1->T[abs_arr]=p1->T[arr]+k*(p1->T[period]);
		}
}

void copy_exec_time(proccess *p1,int n,int all)
{
	int i=0;
	if(all)
	{
		while(i<n)
		{
			p1->T[exec_copy]=p1->T[exec];
			p1++;
			i++;
		}
	}
	else
	{
		p1+=n;
		p1->T[exec_copy]=p1->T[exec];
	}
}

//min function is to find the absolute time
int min(proccess *p1,int n,int p)//p is the deadline or the number whose min is to be calculated
{
	int i=0,min=999,proccess_id=idle;
	while(i<n)
	{
		if(min>p1->T[p] && p1->alive==1)
		{
			min=p1->T[p];
			proccess_id=i;
		}
		p1++;
		i++;
	}
	return proccess_id;
}

int timer=0;
//------------------------------------------------------------main
int main()
{
proccess *t;
int n,total_time,active_id,j;
printf("==========  Earliest Deadline First CPU Scheduling Algorithm Simulator  ==========\n\n");
printf("Enter number of Processes:\n");
scanf("%d",&n);
t=malloc(n*sizeof(proccess));
input(t,n);

total_time=totaltime(t,n);
copy_exec_time(t,n,ALL);
new_abs_arr(t,n,0,ALL);
new_abs_deadline(t,n,ALL);
printf("\n\nGant Chart\n\n");
	while(timer<=total_time)
	  {
			 if(ready(t,timer,n))
			 	active_id=min(t,n,abs_deadline);

		     if(active_id==idle )
		     {
		    	printf("Idle-->");
		    	push(timer+1);
			}
		     if(active_id!=idle)
		     {

		    	 	 {
			    	 	 t[active_id].T[exec_copy]--;//value is decrementing since it is running for 1 sec and now the excec time decreases by one and the proccess gets printed
			    	 	 printf("P[%d]-->",active_id+1);
		    	 	 }
					//if the proccess is executed then exec_copy=0 so then ......
		    	 if(t[active_id].T[exec_copy]==0)
		    	 	{
			    	 	t[active_id].instance++;
			    	 	t[active_id].alive=0;
			    	 	t[active_id].T[t_last]=timer+1;
			    	 	for(j=0;j<n;j++)
						 {
			    	 		if(j!=active_id && t[j].T[abs_arr]<timer)
							 {
			    	 			t[active_id].T[w_time]+=t[j].T[exec];
							 }
						}
						j=active_id;
						copy_exec_time(t,j,CURRENT);
			    	 	new_abs_arr(t,j,t[j].instance,CURRENT);
			    	 	new_abs_deadline(t,j,CURRENT);
			    	 	active_id=min(t,n,abs_deadline);

		    	 	}
		     }
		     ++timer;
		 }
		 x=pop();
		 while(x)
		 {
		 	for(u=0;u<n;u++)
		 	{
		 		if(t[u].T[t_last]>x)
				 {
				 	t[u].T[w_time]+=1;
				}
			}
			x=pop();
		 }
		int i=0;
		while(i<n)
		{
			t[i].T[t_time]=t[i].T[t_last]-t[i].T[arr];
			i++;
		}


		 printf("\n\nProcess number    Waiting time     TurnAround time       Deadline      Execution time        Period \n");
		 for(j=0;j<n;j++)
		 {
		 	printf("\tp[%d]     \t %d         \t%d\t\t     %d     \t\t %d     \t\t%d\n ",j,t[j].T[w_time],t[j].T[t_time],t[j].T[deadline],t[j].T[exec],t[j].T[period]);
		 }
		 printf("\n");
		 int totalWT=0,totalTT=0;
		 for(j=0;j<n;j++)
		 {
		 	totalWT+=t[j].T[w_time];
		 	totalTT+=t[j].T[t_time];
		 }
printf("The average waiting time is %d\nThe average turn around time is %d",totalWT/n,totalTT/n);
printf("\n\nPress any key to exit...");
getch();
return 0;
}

