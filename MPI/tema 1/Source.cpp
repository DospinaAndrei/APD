//Tema1_numar prim

#include <iostream>
#include "mpi.h"
#include <string>
#define FirstRank 0
#define N 40

using namespace std;

bool isprime(int n)
{
	if (n <= 1) { // nu este natural
		return 0;
	}
	if (n == 2) {
		return true;
	}
	if ((n % 2)) {
		return false;  // cand gaseste nr par returneaza 0-fals
	}
	for (int i = 2; i <= n/2; i++) { 
		if (!(n % i)) {  
			return 0;
		}
	}
	return 1;
}


int main(int argc, char *argv[])
{
	int i;

	int  my_rank;       
	int  nrProcesses;   
	int  nameSize;      

	int  parte = 0;      
	int count = 0;    

	int SendData = 0;   
	int ReceiveData = 0;  

	char computerName[MPI_MAX_PROCESSOR_NAME];       

	MPI_Init(&argc, &argv); 

	
	MPI_Comm_size(MPI_COMM_WORLD, &nrProcesses);

	
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	
	MPI_Get_processor_name(computerName, &nameSize);

	if (my_rank == FirstRank) { 
		
		parte = N / nrProcesses;

		cout << "Hello from process " << my_rank << " of " << nrProcesses << " processor on " << computerName << "\n\n";

		for (count = parte*FirstRank;count < parte*(FirstRank + 1);count++) 
		{
			if (isprime(count)) {
				cout << count << "  ";
			}
		}

		SendData = parte;
		for (i = 1; i < nrProcesses; i++)
		{
		
			MPI_Send(&SendData, 1, MPI_INT, i, 1, MPI_COMM_WORLD);   //trimite date
		}

	}

	MPI_Status status;
	if (my_rank > FirstRank) {   
		MPI_Recv(&ReceiveData, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);  								   //int MPI_Send(void *buf -Datele care trebuie trimise / primite (tampon aplicație). 
		cout << "Hello from process " << my_rank << " of " << nrProcesses << " processor on " << computerName << "\n\n";
		for (count = ReceiveData*my_rank;count < ReceiveData*(my_rank + 1);count++)
		{
			if (isprime(count)) {
				cout << count << "  ";
			}
		}
	}

	MPI_Finalize(); /* EXIT MPI */

	return 0;
}
