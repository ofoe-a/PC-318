
#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	int numberProcess, processID;
	MPI_Comm_rank(MPI_COMM_WORLD, &processID);
	MPI_Comm_size(MPI_COMM_WORLD, &numberProcess);
	int message;
	if(processID != 0){
		MPI_Recv(&message,1,MPI_INT,processID-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		cout<<"Process "<<processID<<" received $ "<< message<<" from process "<<processID-1<<endl;
	}
	else{
		message = 1000;
	}
	MPI_Send(&message,1, MPI_INT,(processID+1)%numberProcess,0,MPI_COMM_WORLD);
	if(processID == 0){
		MPI_Recv(&message,1,MPI_INT,numberProcess-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		cout<<"Process "<<processID<<" received $ "<< message<<" from process "<<numberProcess-1<<endl;
	}
	MPI_Finalize();
	return 0;
}
