#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#define bktSize 512
using namespace std;

void bktInput(int a,int b);
int main()
{
	int op,pktSize;
	cout<<"Enter output rate:";
	cin>>op;
	for(int i=1;i<=2;i++)   //number of times
	{
		usleep(rand()%1000);
		pktSize=rand()%100;
		cout<<"\n Packet number"<<i<<"\t Packetsize="<<pktSize;
		bktInput(pktSize,op);
	}
	return 0;
}

void bktInput(int a,int b)
{

	if(a>bktSize)
	
		cout<<"\t Overflow";
	else
	{
		usleep(500);
		while(a > b)
		{
			cout<<"\n\t\t"<<b<<"bytes outputed";
			a-=b;
			usleep(500);
		}
		if(a>0)
		{
		cout<<"\n\t\t Last"<<a<<"bytes sent \n";
		cout<<"\n\t\t Bucket output successfull\n";
		}
	}
}

/*
 Enter output rate:5

 Packet number1	 Packetsize=86
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		5bytes outputed
		 Last1bytes sent 

		 Bucket output successfull

 Packet number2	 Packetsize=15
		5bytes outputed
		5bytes outputed
		 Last5bytes sent 

		 Bucket output successfull




*/
