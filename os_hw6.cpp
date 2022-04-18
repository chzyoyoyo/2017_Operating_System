#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


using namespace std;

struct targets
{
	bool fi_ino;
	bool fi_name;
	bool fi_min;
	bool fi_max;
	int tarino;
	double min;
	double max;
	string name;
}target;


void recur(const char *path)
{

	string nowpos = path;
    if(nowpos[nowpos.length()-1] != '/')
    {
        nowpos = nowpos + '/';
    }

	DIR *dir;
    DIR *dir2;
    struct dirent *ptr;
    struct stat buf;
    //int i;
    dir = opendir(path);
    if (dir != NULL)
    {
	    while((ptr = readdir(dir))!=NULL) 
	    {
	        //printf(“d_name: %s\n”,ptr->d_name);
	    	if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
	            continue;
	        if (stat((nowpos+ptr->d_name).c_str(), &buf) == -1)
                continue;

            // if ((dir2 = opendir(nowpos + d->d_name)) == NULL)
            // {
        	if (target.fi_ino == false || target.tarino == ptr->d_ino)
        	{
        		if (target.fi_name == false || target.name == ptr->d_name)
        		{
        			if (target.fi_max == false || target.max > buf.st_size/1024.0/1024.0)
        			{
        				if (target.fi_min == false || target.min < buf.st_size/1024.0/1024.0)
            			{
            				printf("%s %lu %lf MB\n",(nowpos + ptr->d_name).c_str(), ptr->d_ino, buf.st_size/1024.0/1024.0);
            			}
        			}
        		}
        	}
            //}
            if ((dir2 = opendir((nowpos + ptr->d_name).c_str())) != NULL)
            {
            	recur((nowpos + ptr->d_name).c_str());
            	closedir(dir2);
            }
	    }
    	closedir(dir);
	}	
}


int main(int argc, char **argv)
{
	target.fi_ino = false;
	target.fi_name = false;
	target.fi_min = false;
	target.fi_max = false;
	for (int i = 2; i < argc; ++i)
	{	
		string argue = argv[i];
		if (argue == "-inode")
		{
			target.fi_ino = true;
			target.tarino = atoi(argv[i+1]);
			i++;
		}
		if (argue == "-name")
		{
			target.fi_name = true;
			target.name = argv[i+1];
			i++;
		}
		if (argue == "-size_min")
		{
			target.fi_min = true;
			target.min = atof(argv[i+1]);
			i++;
		}
		if (argue == "-size_max")
		{
			target.fi_max = true;
			target.max = atof(argv[i+1]);
			i++;
		}

	}
	cout << target.fi_ino << " " << target.fi_name << " "<< target.fi_min << " "<< target.fi_max << " "<< endl;
	recur(argv[1]);


}

