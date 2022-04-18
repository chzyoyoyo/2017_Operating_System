#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/time.h>
#include<sys/stat.h>

#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#define PARM IPC_CREAT | 0666

using namespace std;

int main()
{
	int proces;
	int pronum;
	int dim;

	cout << "Input the matrix dimension: ";
	cin >> dim;


    int shm_id1, shm_id2, shm_id3;
 	key_t key;


	size_t shm_size = dim*dim*sizeof(unsigned int);

 	//key = 5679;


	for (proces = 1; proces <= 16; proces++)
	{
		unsigned int checksum = 0;
			
		if ((shm_id1 = shmget(IPC_PRIVATE, shm_size, PARM)) < 0) 
			{
		        perror("shmget");
		        return 0;
    		}



		if ((shm_id2 = shmget(IPC_PRIVATE, shm_size, PARM)) < 0) 
			{
		        perror("shmget");
		        return 0;
    		} 


		if ((shm_id3 = shmget(IPC_PRIVATE, shm_size, PARM)) < 0) 
			{
		        perror("shmget");
		        return 0;
    		}


		unsigned int *shm_addr1, *shm_addr2, *shm_addr3;
		unsigned int *addr1, *addr2, *addr3;

		shm_addr1 = (unsigned int *)shmat(shm_id1, NULL, 0);
    	if (shm_addr1 == (unsigned int *) -1) 
    		{
		        perror("shmat");
		        return 1;
    		}
    	shm_addr2 = (unsigned int *)shmat(shm_id2, NULL, 0);
    	if (shm_addr2 == (unsigned int *) -1) 
    		{
		        perror("shmat");
		        return 1;
    		}
    	shm_addr3 = (unsigned int *)shmat(shm_id3, NULL, 0); 
    	if (shm_addr3 == (unsigned int *) -1) 
    		{
		        perror("shmat");
		        return 1;
    		}


		addr1 = shm_addr1;
		addr2 = shm_addr2;
		addr3 = shm_addr3;

    	for (int i = 0; i < dim*dim; i++)
    		{
    			shm_addr1[i] = i;
    			shm_addr2[i] = i;
    			shm_addr3[i] = 0;
    			// *addr1 = i;
    			// addr1++;
    			// *addr2 = i;
    			// addr2++;
    			// *addr3 = 0;
    			// addr3++;
       		}
    		

    	/*for (int i = 0; i < dim*dim; i++)
    		cout << shm_addr2[i] << endl;*/
		
       	int mat1;
       	int mat2;
       	pid_t pid;
		struct  timeval start;
        struct  timeval end;
        
        unsigned long diff;

        bool nofloat = 0;
		if ((dim%proces) != 0)
		{
			nofloat = true;
		}


		gettimeofday(&start, NULL);

		for (pronum = 1; pronum <= proces; pronum++)
		{
			pid = fork();
			if (pid == 0)
			{

				shm_addr1 = (unsigned int *)shmat(shm_id1, NULL, 0);
		    	if (shm_addr1 == (unsigned int *) -1) 
		    		{
				        perror("shmat");
				        return 1;
		    		}
		    	shm_addr2 = (unsigned int *)shmat(shm_id2, NULL, 0);
		    	if (shm_addr2 == (unsigned int *) -1) 
		    		{
				        perror("shmat");
				        return 1;
		    		}
		    	shm_addr3 = (unsigned int *)shmat(shm_id3, NULL, 0); 
		    	if (shm_addr3 == (unsigned int *) -1) 
		    		{
				        perror("shmat");
				        return 1;
		    		}

		    	//addr3 = shm_addr3;

		    	addr3 = shm_addr3 + ((pronum-1)*(dim/proces))*dim;

		    	if (nofloat == true && pronum == proces)
		    	{
		    		for(mat1 = (pronum-1)*(dim/proces); mat1 < dim; mat1++)
					{
						for(mat2 = 0; mat2 < dim; mat2++)
						{
							addr1 = shm_addr1 + mat1*dim;
							addr2 = shm_addr2 + mat2;

							for (int i = 0; i < dim; ++i)
							{
								*addr3 = (*addr3) + (*addr1)*(*addr2);
								addr1++;
								addr2 = addr2 + dim;
							}
							addr3++;
						}

					}
		    	}

		    	else
		    	{
		    		for(mat1 = (pronum-1)*(dim/proces); mat1 < (pronum-1)*(dim/proces)+dim/proces; mat1++)
					{
						for(mat2 = 0; mat2 < dim; mat2++)
						{
							addr1 = shm_addr1 + mat1*dim;
							addr2 = shm_addr2 + mat2;

							for (int i = 0; i < dim; ++i)
							{
								*addr3 = (*addr3) + (*addr1)*(*addr2);
								addr1++;
								addr2 = addr2 + dim;
							}
							addr3++;
						}

					}

		    	}

		    	
				
				//child end
				shmdt(shm_addr1);
		        shmdt(shm_addr2);
		        shmdt(shm_addr3);
				exit(0);
			}

		}
	
		for (int i = 0; i < proces; ++i)
		{
			wait(NULL);
		}
		
		gettimeofday(&end, NULL);

		shm_addr3 = (unsigned int *)shmat(shm_id3, NULL, 0); 
		if (shm_addr3 == (unsigned int *) -1) 
    		{
		        perror("shmat");
		        return 1;
    		}
		//addr3 = shm_addr3;
    	/*for (int i = 0; i < dim*dim; i++)
    		cout << shm_addr3[i] << " ";*/

		for (int i = 0; i < dim*dim; ++i)
		{
			checksum = checksum + *shm_addr3;
			shm_addr3++;
		}
        
        diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        cout << "Multiplying matrices using " << proces << " process" << endl;
        //shm_addr1++;
        cout << "Elapsed time: " << (float)diff/1000000 << " sec, Checksum: " << checksum << endl;
        

		shmdt(shm_addr1);
        shmdt(shm_addr2);
        shmdt(shm_addr3);

        shmctl(shm_id1, IPC_RMID, NULL);
        shmctl(shm_id2, IPC_RMID, NULL);
        shmctl(shm_id3, IPC_RMID, NULL);
	    
	}






}