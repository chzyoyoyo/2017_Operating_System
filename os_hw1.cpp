#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <string.h>

using namespace std;

/*void ign_handler()
{
    while(waitpid(-1,NULL,WNOHANG)>0);
}*/

int main ()
{


	signal(SIGCHLD, SIG_IGN);

	stringstream ss;

	int i;

	
	string arg;
	//char argv_execv[600][600];
	//vector<string> v;


	while(1)
	{
		char *argList[500];
		
		for(int i=0; i<500; i++)
			argList[i] = new char[600];


		ss.clear();
		int andflag = 0;

		//arg[0] = "Yi";
		cout << ">";
		//cin.getline(arg, 6000);
		getline(cin, arg);

		int len = arg.length();




		if(arg[len-1] == '&')
		{
			andflag = 1;
			arg[len-1] = '\0';
		}
		//cout << andflag;

		ss << arg;

		int nullpos = 0;
		while (ss >> argList[nullpos])
		{
		    
		    nullpos++;

		}

		if(andflag == 1)
			argList[nullpos-1] = NULL;

		else
			argList[nullpos] = NULL;

		
		pid_t  pid = fork(); /* fork another process */  

		

		if (pid < 0) 
		{ 
			cout << "Fork Failed";
			//exit(-1);  
		}  
		else if (pid == 0) 
		{
		 	/* child process */  
		 	execvp(argList[0], argList);

			//cout << "flag";

		 	
		}  
		else 
		{ 	/* parent process */   
			/* parent will wait for the child to complete */   
			if(andflag == 0)
			{
				wait (NULL);  
			}

						
			
			//exit(0);  
		}  
		//argList[nullpos] = temp;
	}
}


