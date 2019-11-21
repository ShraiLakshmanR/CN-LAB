#include <iostream>
#define MAX 10
int n;
using namespace std;

class router
{
char adj_new[MAX], adj_old[MAX];
int table_new[MAX], table_old[MAX];
public:
	router( )
	{
	for(int i=0;i<MAX;i++) 
		table_old[i]=table_new[i]=99;
	}
	void copy( )
	{
		for(int i=0;i<n;i++) 
		{
			adj_old[i] =adj_new[i];
			table_old[i]=table_new[i];
		}
	}
	int equal( ) 
	{
		for(int i=0;i<n;i++)
			if(table_old[i]!=table_new[i]||adj_new[i]!=adj_old[i])return 0;
		return 1;
	}
	void input(int j) 
	{
		cout<<"Enter 1 if the corresponding router is adjacent to router"
		<<(char)('A'+j)<<" else enter 99: "<<endl<<" ";
		for(int i=0;i<n;i++)
			if(i!=j) cout<<(char)('A'+i)<<" ";
		cout<<"\nEnter matrix:";
		for(int i=0;i<n;i++) 
		{
			if(i==j)
				table_new[i]=0;
			else
				cin>>table_new[i];
			adj_new[i]= (char)('A'+i);
		}
		cout<<endl;
	}
	void display()
	{
		cout<<"\nDestination Router: ";


		for(int i=0;i<n;i++) 
			cout<<(char)('A'+i)<<" ";
		cout<<"\nOutgoing Line: ";
		for(int i=0;i<n;i++) cout<<adj_new[i]<<" ";
		cout<<"\nHop Count: ";
		for(int i=0;i<n;i++) cout<<table_new[i]<<" ";
	}
	void build(int j) ;
	
} r[10];
void router::build(int j)
{
for(int i=0;i<n;i++)
		for(int k=0;(i!=j)&&(k<n);k++)
			if(table_old[i]!=99)
				if((table_new[i]+r[i].table_new[k])<table_new[k]) 
				{
					table_new[k]=table_new[i]+r[i].table_new[k];
					adj_new[k]=(char)('A'+i);
				}
}#include <iostream>
#define MAX 10
int n;
using namespace std;

class router
{
char adj_new[MAX], adj_old[MAX];
int table_new[MAX], table_old[MAX];
public:
	router( )
	{
	for(int i=0;i<MAX;i++) 
		table_old[i]=table_new[i]=99;
	}
	void copy( )
	{
		for(int i=0;i<n;i++) 
		{
			adj_old[i] =adj_new[i];
			table_old[i]=table_new[i];
		}
	}
	int equal( ) 
	{
		for(int i=0;i<n;i++)
			if(table_old[i]!=table_new[i]||adj_new[i]!=adj_old[i])return 0;
		return 1;
	}
	void input(int j) 
	{
		cout<<"Enter 1 if the corresponding router is adjacent to router"
		<<(char)('A'+j)<<" else enter 99: "<<endl<<" ";
		for(int i=0;i<n;i++)
			if(i!=j) cout<<(char)('A'+i)<<" ";
		cout<<"\nEnter matrix:";
		for(int i=0;i<n;i++) 
		{
			if(i==j)
				table_new[i]=0;
			else
				cin>>table_new[i];
			adj_new[i]= (char)('A'+i);
		}
		cout<<endl;
	}
	void display()
	{
		cout<<"\nDestination Router: ";


		for(int i=0;i<n;i++) 
			cout<<(char)('A'+i)<<" ";
		cout<<"\nOutgoing Line: ";
		for(int i=0;i<n;i++) cout<<adj_new[i]<<" ";
		cout<<"\nHop Count: ";
		for(int i=0;i<n;i++) cout<<table_new[i]<<" ";
	}
	void build(int j) ;
	
} r[10];
void router::build(int j)
{
for(int i=0;i<n;i++)
		for(int k=0;(i!=j)&&(k<n);k++)
			if(table_old[i]!=99)
				if((table_new[i]+r[i].table_new[k])<table_new[k]) 
				{
					table_new[k]=table_new[i]+r[i].table_new[k];
					adj_new[k]=(char)('A'+i);
				}
}
void build_table( ) {
int i=0, j=0;
while(i!=n) {
for(i=j;i<n;i++) {
r[i].copy();
r[i].build(i);
}
for(int i=0;i<n;i++)
if(!r[i].equal()) {
j=i;
break;
}
}
}
int main() {

cout<<"Enter the number of routers(<"<<MAX<<"): "; cin>>n;
for(int i=0;i<n;i++) r[i].input(i);
build_table();
for(int i=0;i<n;i++) {
cout<<"Router Table entries for router "<<(char)('A'+i)<<":-";
r[i].display();
cout<<endl<<endl;
}
return 0;
}


/*---------------OUTPUT--------------------------
Enter the number the routers(<10): 3
Enter 1 if the corresponding router is adjacent to routerA else enter 99: 
 B C 
Enter matrix:1 99

Enter 1 if the corresponding router is adjacent to routerB else enter 99: 
 A C 
Enter matrix:1 1

Enter 1 if the corresponding router is adjacent to routerC else enter 99: 
 A B 
Enter matrix:99 1

Router Table entries for router A:-
Destination Router: A B C 
Outgoing Line: A B B 
Hop Count: 0 1 2 

Router Table entries for router B:-
Destination Router: A B C 
Outgoing Line: A B C 
Hop Count: 1 0 1 

Router Table entries for router C:-
Destination Router: A B C 
Outgoing Line: B B C 
Hop Count: 2 1 0 
-------------------------------------------------------------- */


void build_table( ) {
int i=0, j=0;
while(i!=n) {
for(i=j;i<n;i++) {
r[i].copy();
r[i].build(i);
}
for(int i=0;i<n;i++)
if(!r[i].equal()) {
j=i;
break;
}
}
}
int main() {

cout<<"Enter the number of routers(<"<<MAX<<"): "; cin>>n;
for(int i=0;i<n;i++) r[i].input(i);
build_table();
for(int i=0;i<n;i++) {
cout<<"Router Table entries for router "<<(char)('A'+i)<<":-";
r[i].display();
cout<<endl<<endl;
}
return 0;
}


/*---------------OUTPUT--------------------------
Enter the number the routers(<10): 3
Enter 1 if the corresponding router is adjacent to routerA else enter 99: 
 B C 
Enter matrix:1 99

Enter 1 if the corresponding router is adjacent to routerB else enter 99: 
 A C 
Enter matrix:1 1

Enter 1 if the corresponding router is adjacent to routerC else enter 99: 
 A B 
Enter matrix:99 1

Router Table entries for router A:-
Destination Router: A B C 
Outgoing Line: A B B     //outgoin link for first will be A and B it will be B and for C also its B
Hop Count: 0 1 2      //from a to a o hops a to b directly connected 1 hop a to c is 2 hops because of intermediate b

Router Table entries for router B:-
Destination Router: A B C 
Outgoing Line: A B C 
Hop Count: 1 0 1 

Router Table entries for router C:-
Destination Router: A B C 
Outgoing Line: B B C 
Hop Count: 2 1 0 
-------------------------------------------------------------- */

