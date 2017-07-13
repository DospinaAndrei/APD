#include <iostream>
#include <mpi.h>
#include <math.h>

using namespace std;

#define MAXSIZE 10  

int main(int argc, char *argv[])
{
	int  my_rank;       
	int  nrProcesses;  

	int arr[MAXSIZE], i, parte, low, high, myresult = 0, result;
	int pozitie = 0;
	int nrcautat = 3;


	MPI_Init(&argc, &argv); 
	MPI_Comm_size(MPI_COMM_WORLD, &nrProcesses);

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


	if (0 == my_rank) {  
		cout << "Enter Array Elements : ";
		for (i = 0; i<MAXSIZE; i++) {
			cin >> arr[i];
		}
	}

	
	MPI_Bcast(arr, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD);
	
	parte = MAXSIZE / nrProcesses; 
	low = my_rank * parte;
	high = low + parte;
	for (i = low; i<high; i++) {   
		if (nrcautat == arr[i]) {
			pozitie = i;
		}
	}
	cout << "I got position " << pozitie << " from " << my_rank << "\n";

	MPI_Reduce(&pozitie, &result, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (0 == my_rank) {
		if (result == 0)
		{
			cout << "Number NOT found..!!\n";
		}
		else {
			cout << "Number FOUND at MAX position " << result << "\n";
		}
	}


	MPI_Finalize(); /* EXIT MPI */

	return 0;
}
