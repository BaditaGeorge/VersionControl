#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>

extern int errno;
int port;
char currentUser[128];
int main(int argc,char *argv[])
{
	int sd;
	bzero(currentUser,128);
	struct sockaddr_in server;
	int nr=0;
	char buf[10];
	if(argc!=3)
	{
		printf("Eroare la sintaxa!");
		return -1;
	}
	port=atoi(argv[2]);
	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(argv[1]);
	server.sin_port=htons(port);
	connect(sd,(struct sockaddr *)&server,sizeof(struct sockaddr));
	//printf("[client]Introduceti un numar\n");
	fflush(stdout);
	char S[122];
	char kebab[25];
	bzero(S,122);
	int ookl=0;
	while(strcmp(S,"exit")!=0){
	bzero(S,122);
	if(ookl==0){
	  while(ookl==0)
	    {
	      read(0,S,sizeof(S));
	      S[strlen(S)-1]=0;
	      printf("%s\n",S);
	      if(strcmp(S,"login")==0 || strcmp(S,"register")==0)
		ookl=1;
	      if(ookl==0)
		printf("Logati-va sau inregistrati-va!");
	    }
	}
	else
	  {
	    read(0,S,sizeof(S));
	    S[strlen(S)-1]=0;
	    printf("%s\n",S);
	  }
	write(sd,S,sizeof(S));
	printf("%s\n",S);
	if(strcmp(S,"save")==0)
	  {
	    char ms[126],ms2[126];
	    char repo[128];
	    char prop[128];
	    bzero(prop,128);
	    bzero(ms,126);
	    bzero(ms2,126);
	    bzero(repo,128);
	    read(0,repo,sizeof(repo));
	    read(0,prop,sizeof(prop));
	    read(0,ms2,sizeof(ms2));
	    read(0,ms,sizeof(ms));
	    //char messg[2056];
	    ms[strlen(ms)-1]=0;
	    repo[strlen(repo)-1]=0;
	    prop[strlen(prop)-1]=0;
	    //bzero(messg,2056);
	    while(ms2[0]<'a' && ms2[0]>'z')
	      {
		for(int ind=0;ind<strlen(ms2);ind++)
		  ms2[ind]=ms2[ind+1];
	      }
	    ms2[strlen(ms2)]=0;
	    printf("%s\n",ms);
	    printf("%s\n",ms2);
	    strcat(ms,"/");
	    strcat(ms,ms2);
	    if(strcmp(prop,"me")==0)
	      {
		strcat(repo,"@");
		strcat(repo,currentUser);
	      }
	    else
	      {
		strcat(repo,"@");
		strcat(repo,prop);
	      }
	    write(sd,currentUser,sizeof(currentUser));
	    write(sd,repo,sizeof(repo));
	    write(sd,ms2,sizeof(ms2));
	    printf("%s\n",ms);
	    int ix=0;
	    ms[strlen(ms)-1]=0;
	    char checker;
	    read(sd,&checker,sizeof(char));
	    int fpp;
	    if(checker==1)
	      {
		fpp=open(ms,O_WRONLY|O_CREAT,0666);
		char cic;
		while(read(sd,&cic,sizeof(char))>0)
		  {
		    if(cic==-1)
		      break;
		    write(fpp,&cic,sizeof(char));
		  }
	      }
	    close(fpp);
	  }
	else
	  if(strcmp(S,"delete")==0)
	    {
	      char ms[126];
	      char repo[128];
	      char prop[128];
	      bzero(prop,128);
	      bzero(ms,126);
	      bzero(repo,128);
	      read(0,repo,sizeof(repo));
	      read(0,prop,sizeof(prop));
	      read(0,ms,sizeof(ms));
	      ms[strlen(ms)-1]=0;
	      repo[strlen(repo)-1]=0;
	      prop[strlen(prop)-1]=0;
	      if(strcmp(prop,"me")==0)
		{
		  strcat(repo,"@");
		  strcat(repo,currentUser);
		}
	      else
		{
		  strcat(repo,"@");
		  strcat(repo,prop);
		}
	      printf("%s\n",repo);
	      write(sd,currentUser,sizeof(currentUser));
	      write(sd,repo,sizeof(repo));
	      write(sd,ms,sizeof(ms));
	    }
	  else
	    if(strcmp(S,"upload")==0)
	      {
		char ms[126],repo[128];
		char prop[128];
		bzero(prop,128);
		bzero(ms,126);
		bzero(repo,128);
		read(0,ms,sizeof(ms));
		read(0,repo,sizeof(repo));
		read(0,prop,sizeof(prop));
		prop[strlen(prop)-1]=0;
		ms[strlen(ms)-1]=0;
		repo[strlen(repo)-1]=0;
		sync();
		write(sd,currentUser,sizeof(currentUser));
		write(sd,ms,sizeof(ms));
		if(strcmp(prop,"MakeRepo")==0)
		  {
		    strcat(repo,"@");
		    strcat(repo,currentUser);
		  }
		else
		  {
		    strcat(repo,"@");
		    strcat(repo,prop);
		  }
		write(sd,repo,sizeof(repo));
		bzero(ms,126);
		read(sd,ms,sizeof(ms));
		printf("%s\n",ms);
	      }
	    else
	      if(strcmp(S,"commit")==0)
		{
		  char path0[1024],repo[128],comm[1024],prop[128];
		  bzero(path0,1024);
		  bzero(repo,128);
		  bzero(comm,1024);
		  bzero(prop,128);
		  read(0,repo,sizeof(repo));
		  read(0,prop,sizeof(prop));
		  repo[strlen(repo)-1]=0;
		  prop[strlen(prop)-1]=0;
		  if(strcmp(prop,"me")==0)
		    {
		      strcat(repo,"@");
		      strcat(repo,currentUser);
		    }
		  else
		    {
		      strcat(repo,"@");
		      strcat(repo,prop);
		    }
		  write(sd,currentUser,sizeof(currentUser));
		  write(sd,repo,sizeof(repo));
		  read(0,path0,sizeof(path0));
		  path0[strlen(path0)-1]=0;
		  write(sd,path0,sizeof(path0));
		  read(0,comm,sizeof(comm));
		  comm[strlen(comm)-1]=0;
		  write(sd,comm,sizeof(comm));
		}
	      else
		if(strcmp(S,"register")==0)
		  {
		    char ms[128];
		    bzero(ms,128);
		    read(0,ms,sizeof(ms));
		    ms[strlen(ms)-1]=0;
		    strcpy(currentUser,ms);
		    write(sd,ms,sizeof(ms));
		  }
		else
		  if(strcmp(S,"login")==0)
		    {
		      char ms[128];
		      bzero(ms,128);
		      read(0,ms,sizeof(ms));
		      ms[strlen(ms)-1]=0;
		      printf("%s\n",ms);
		      strcpy(currentUser,ms);
		      write(sd,ms,sizeof(ms));
		    }
		  else
		    if(strcmp(S,"view")==0)
		      {
			int index1=0;
			char repo[128];
			char proprietar[128];
			bzero(repo,128);
			bzero(proprietar,128);
			read(0,repo,sizeof(repo));
			read(0,proprietar,sizeof(proprietar));
			repo[strlen(repo)-1]=0;
			proprietar[strlen(proprietar)-1]=0;
			if(strcmp(proprietar,"me")==0)
			  {
			    strcat(repo,"@");
			    strcat(repo,currentUser);
			  }
			else
			  {
			    strcat(repo,"@");
			    strcat(repo,proprietar);
			  }
			sync();
			write(sd,currentUser,sizeof(currentUser));
			write(sd,repo,sizeof(repo));
			char msg[1024];
			bzero(msg,1024);
			read(sd,msg,sizeof(msg));
			while(strcmp(msg,"finito")!=0)
			  {
			    printf("%s\n",msg);
			    bzero(msg,1024);
			    read(sd,msg,sizeof(msg));
			  }
		      }
		    else
		      if(strcmp(S,"GivePermission")==0)
			{
			  char mis[128];
			  char repo[128];
			  bzero(repo,128);
			  read(0,repo,sizeof(repo));
			  repo[strlen(repo)-1]=0;
			  strcat(repo,"@");
			  strcat(repo,currentUser);
			  //write(sd,currentUser,sizeof(currentUser));
			  sync();
			  write(sd,repo,sizeof(repo));
			  bzero(mis,128);
			  read(0,mis,sizeof(mis));
			  //mis[strlen(mis)-1]=0;
			  sync();
			  write(sd,mis,sizeof(mis));
			}
		      else
			if(strcmp(S,"TakePermission")==0)
			  {
			    char mis[128];
			    char repo[128];
			    bzero(repo,128);
			    read(0,repo,sizeof(repo));
			    repo[strlen(repo)-1]=0;
			    //write(sd,currentUser,sizeof(currentUser));
			    strcat(repo,"@");
			    strcat(repo,currentUser);
			    write(sd,repo,sizeof(repo));
			    bzero(mis,128);
			    read(0,mis,sizeof(mis));
			    mis[strlen(mis)-1]=0;
			    write(sd,mis,sizeof(mis));
			  }
			else
			  if(strcmp(S,"viewRepos")==0)
			    {
			      sync();
			      write(sd,currentUser,sizeof(currentUser));
			      char path[1024];
			      bzero(path,1024);
			      read(sd,path,sizeof(path));
			      while(strcmp(path,"done")!=0)
				{
				  for(int ii=0;ii<strlen(path);ii++)
				    {
				      if(path[ii]=='@')
					{
					  break;
					}
				      printf("%c",path[ii]);
				    }
				  printf("\n");
				  bzero(path,1024);
				  read(sd,path,sizeof(path));
				}
			    }
			  else
			    if(strcmp(S,"push")==0)
			      {
				char repo[128];
				char fill[128];
				char prop[128];
				bzero(repo,128);
				bzero(fill,128);
				bzero(prop,128);
				read(0,repo,sizeof(repo));
				read(0,prop,sizeof(prop));
				read(0,fill,sizeof(fill));
				repo[strlen(repo)-1]=0;
				fill[strlen(fill)-1]=0;
				prop[strlen(prop)-1]=0;
				if(strcmp(prop,"me")==0)
				  {
				    strcat(repo,"@");
				    strcat(repo,currentUser);
				  }
				else
				  {
				    strcat(repo,"@");
				    strcat(repo,prop);
				  }
				write(sd,currentUser,sizeof(currentUser));
				write(sd,repo,sizeof(repo));
				write(sd,fill,sizeof(fill));
			      }
			    else
			      if(strcmp(S,"revert")==0)
				{
				  char repo[128],file[128],prop[128];
				  int versiune=0;
				  bzero(repo,128);
				  bzero(file,128);
				  bzero(prop,128);
				  read(0,repo,sizeof(repo));
				  read(0,prop,sizeof(prop));
				  read(0,file,sizeof(file));
				  repo[strlen(repo)-1]=0;
				  file[strlen(file)-1]=0;
				  prop[strlen(prop)-1]=0;
				  char num[128];
				  bzero(num,128);
				  read(0,num,sizeof(num));
				  num[strlen(num)-1]=0;
				  if(strcmp(prop,"me")==0)
				    {
				      strcat(repo,"@");
				      strcat(repo,currentUser);
				    }
				  else
				    {
				      strcat(repo,"@");
				      strcat(repo,prop);
				    }
				  write(sd,currentUser,sizeof(currentUser));
				  write(sd,repo,sizeof(repo));
				  write(sd,file,sizeof(file));
				  write(sd,num,sizeof(num));
				}
			      else
				if(strcmp(S,"viewCommitLogs")==0)
				  {
				    sync();
				    write(sd,currentUser,sizeof(currentUser));
				    int num;
				    read(sd,&num,sizeof(int));
				    char mssg[2048];
				    for(int ij=0;ij<num;ij++)
				      {
					bzero(mssg,2048);
					read(sd,mssg,sizeof(mssg));
					if(ij%2==0)
					  printf("%s\n",mssg);
					else
					  printf("Log pentr fisierul %s\n",mssg);
				      }
				  }
				else
				  if(strcmp(S,"viewRevertsLogs")==0)
				    {
				      
				    }
	}
	close(sd);
}
