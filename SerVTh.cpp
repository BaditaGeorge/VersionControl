#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <dirent.h>
#include <sqlite3.h>
#include <string>
#include <sys/wait.h>

#define PORT 2908

extern int errno;

typedef struct thData{
	int idThread;
	int cl;
}thData;
typedef struct clienti{
	unsigned short port;
	unsigned long adr;
}clienti;
typedef struct fisiere{
  char path[1024];
  char proprietar[128];
}fisiere;
fisiere fils[256];
fisiere file[256];
int alls=0;
clienti clnts[256];
char currentUser[128];
int allClnts=0,allfils=0;
static void* treat(void *);
void generatePaths(char repo[128],fisiere file[256],int &allfile);
void generatePaths2();
void raspund(void *);
void raspund1(void *);
void raspund2(void *);
void raspund3(void *);
void raspund4(void *);
void raspund5(void *);
void raspund6(void *);
void raspund7(void *);
void raspund8(void *);
void raspund9(void *);
void raspund10(void *);
void raspund11(void *);
void raspund12(void *);
void raspund13(void *);
pthread_mutex_t mlock=PTHREAD_MUTEX_INITIALIZER;
int chkforpermission(char repo[128],char user[128]);
int poss;
int main()
{
	struct sockaddr_in server;
	struct sockaddr_in from;
	int nr,sd,pid,i=0;
	pthread_t th[100];
	generatePaths2();
	sd=socket(AF_INET,SOCK_STREAM,0);
	int on=1;
	setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	bzero(&server,sizeof(server));
	bzero(&from,sizeof(from));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=htons(PORT);
	bind(sd,(struct sockaddr *)&server,sizeof(struct sockaddr));
	listen(sd,5);
	while(1)
	{
		int client;
		thData* td;
		unsigned int length=sizeof(from);
		printf("ASteptam la %d..",PORT);
		fflush(stdout);
		client=accept(sd,(struct sockaddr *)&from,&length);
		int i=0,ok=1;
		while(i<allClnts)
		{
			if(clnts[i].port==from.sin_port && clnts[i].adr==from.sin_addr.s_addr)
			{
				ok=0;
				break;
			}
			i++;
		}
		if(ok==1)
		{
			clnts[allClnts].port=from.sin_port;
			clnts[allClnts].adr=from.sin_addr.s_addr;
			poss=allClnts;
			allClnts++;
		}
		else
		{
			poss=i;
		}
		printf("Here!");
		int idThread,cl;
		td=(struct thData*)malloc(sizeof(struct thData));
		td->idThread=i++;
		td->cl=client;
		pthread_create(&th[i],NULL,&treat,td);
	}
}
bool isdir(const char* dname)
{
  struct stat Bf;
  stat(dname,&Bf);
  return S_ISDIR(Bf.st_mode);
}
void generatePaths2()
{
  DIR *dir;
  struct dirent *ddl;
  char pth[512];
  bzero(pth,512);
  strcpy(pth,"container");
  printf("HERE!");
  if((dir=opendir(pth))!=NULL)
  {
    ddl=readdir(dir);
    while(ddl!=NULL)
      {
	if(ddl->d_name[0]!='.')
	    {
	      bzero(fils[allfils].path,1024);
	      strcpy(fils[allfils].path,ddl->d_name);
	      int index1=0,lg=0,okk=0;
	      char user[128];
	      bzero(user,128);
	      while(ddl->d_name[index1]!=0)
		{
		  if(okk==1)
		    {
		      user[lg]=ddl->d_name[index1];
		      lg++;
		    }
		  if(ddl->d_name[index1]=='@')
		    okk=1;
		  index1++;
		}
	      strcpy(fils[allfils].proprietar,user);
	      allfils++;
	    }
	ddl=readdir(dir);
      }
    closedir(dir);
  }
  else
  {
     perror("Eroare");
     return;
  }
  printf("HEREEE!");
}
void generatePaths(char repo[128],fisiere fille[256],int &allfile)
{
  DIR *dir;
  struct dirent *ddl;
  char pth[512];
  bzero(pth,512);
  strcpy(pth,"container/");
  strcat(pth,repo);
  printf("%s\n",pth);
  if((dir=opendir(pth))!=NULL)
   {
      ddl=readdir(dir);
      while(ddl!=NULL)
	{
	  if(ddl->d_name[0]!='.')
	    {
	      bzero(fille[allfile].path,1024);
	      strcpy(fille[allfile].path,ddl->d_name);
	      printf("%s\n",fille[allfile].path);
	      allfile++;
	    }
	  ddl=readdir(dir);
	}
      closedir(dir);
    }
    else
    {
       perror("Eroare");
       return;
    }
}
static void* treat(void *arg)
{
	printf("[thread]-%d - Asteptam.. \n",((struct thData*)arg)->idThread);
	fflush(stdout);
	char opt[126];
	bzero(opt,126);
	int ookkl=0;
	while(strcmp(opt,"exit")!=0){
	bzero(opt,126);
	read(((struct thData*)arg)->cl,opt,sizeof(opt));
	printf("%s\n",opt);
	if(strcmp(opt,"save")==0)
	  {
	    raspund1((void*)arg);
	  }
	if(strcmp(opt,"upload")==0)
	  {
	    raspund((void*)arg);
	  }
	if(strcmp(opt,"delete")==0)
	  {
	    raspund2((void*)arg);
	  }
	if(strcmp(opt,"commit")==0)
	  {
	    raspund9((void*)arg);
	  }
	if(strcmp(opt,"register")==0)
	  {
	    raspund3((void*)arg);
	  }
	if(strcmp(opt,"login")==0)
	  {
	    raspund4((void*)arg);
	  }
	if(strcmp(opt,"view")==0)
	  {
	    raspund5((void*)arg);
	  }
	if(strcmp(opt,"GivePermission")==0)
	  {
	    raspund6((void*)arg);
	  }
	if(strcmp(opt,"TakePermission")==0)
	  {
	    raspund7((void*)arg);
	  }
	if(strcmp(opt,"viewRepos")==0)
	  {
	    raspund8((void*)arg);
	  }
	if(strcmp(opt,"push")==0)
	  {
	    raspund10((void*)arg);
	  }
	if(strcmp(opt,"revert")==0)
	  {
	    raspund11((void*)arg);
	  }
	if(strcmp(opt,"viewCommitLogs")==0)
	  {
	    raspund12((void*)arg);
	  }
	if(strcmp(opt,"viewRevertsLogs")==0)
	  {
	    raspund13((void*)arg);
	  }
	}
	close((intptr_t)arg);
	return(NULL);
}
char fm[286];
int FindFile(char ms[126])
{
  int ind=0;
  int okk=1;
  for(ind=0;ind<allfils;ind++)
  {
      okk=1;
      for(int j=0;ms[j]!='.';j++)
      {
	 if(fils[ind].path[j]!=ms[j]){
	   okk=0;
	   break;
	 }
      }
      if(okk==1)
      {
	break;
      }
  }
  return ind;
}
static int callback(void *NU,int nrArg,char **Arrg,char **Col)
{
  int i;
  for(i=0;i<nrArg;i++){
    printf("%s=$s\n",Col[i],Arrg[i]?Arrg[i]:"NULL");
  }
  printf("\n");
  return 0;
}
char diferenta[4096];
static int callback2(void *data,int nrArg,char **Arrg,char **Col)
{
  int i;
  printf("%s:\n",(const char*)data);
  for(i=0;i<nrArg;i++){
    strcpy(diferenta,Arrg[i]);
  }
  printf("\n");
  return 0;
}
char diferenta2[24][2048];
int nr=0;
static int callback3(void *data,int nrArg,char **Arrg,char **Col)
{
  int i;
  printf("%s\n",(const char*)data);
  for(i=0;i<nrArg;i++){
    //printf("%s\n",Arrg[i]);
    strcpy(diferenta2[nr],Arrg[i]);
    nr++;
  }
  return 0;
}
int chkforpermission(char repo[128],char user[128])
{
  char userforcheck[128];
  bzero(userforcheck,128);
  printf("%s %s\n",repo,user);
  int OK=0;
  int lnn=0;
  for(int ij=0;ij<strlen(repo);ij++)
    {
      if(OK==1){
	userforcheck[lnn]=repo[ij];
	lnn++;
      }
      if(repo[ij]=='@')
	OK=1;
    }
  OK=0;
  if(strcmp(userforcheck,user)==0)
    OK=1;
  else
    {
      char loc2[128];
      bzero(loc2,128);
      strcpy(loc2,repo);
      strcat(loc2,"@permisiuni.txt");
      int pf=open(loc2,O_RDONLY);
      char temp[128];
      int ltmp=0;
      char cartemp;
      bzero(temp,128);
      while(read(pf,&cartemp,sizeof(char))>0)
	{
	  if(cartemp=='\n')
	    {
	      if(strcmp(temp,user)==0)
		{
		  printf("Match!");
		  OK=1;
		  break;
		}
	      ltmp=0;
	      printf("%s\n",temp);
	      bzero(temp,128);
	    }
	  else
	    {
	      temp[ltmp]=cartemp;
	      ltmp++;
	    }
	}
      close(pf);
    }
  return OK;
}
void raspund13(void *arg)
{
  return;
}
void raspund12(void *arg)
{
  struct thData tdL;
  tdL=*((struct thData*)arg);
  char user[128];
  read(tdL.cl,user,sizeof(user));
  printf("%s\n",user);
  char *sql;
  sqlite3 *db;
  int conn;
  char *err;
  const char* data="Log-urile sunt";
  conn=sqlite3_open("commdefs.db",&db);
  char instr[2048];
  bzero(instr,2048);
  strcpy(instr,"select diff,file from difs where user=");
  strcat(instr,"'");
  strcat(instr,user);
  strcat(instr,"'");
  strcat(instr,";");
  sql=instr;
  printf("Am ajuns aici!");
  conn=sqlite3_exec(db,sql,callback3,(void*)data,&err);
  if(conn!=SQLITE_OK)
    {
      printf("%s\n",err);
      sqlite3_free(err);
    }
  printf("%i\n",nr);
  write(tdL.cl,&nr,sizeof(int));
  for(int ii=0;ii<nr;ii++)
    write(tdL.cl,diferenta2[ii],sizeof(diferenta2[ii]));
  sqlite3_close(db);
}
void raspund11(void *arg)
{
  struct thData tdL;
  tdL=*((struct thData*)arg);
  char repo[128];
  char user[128];
  char file[128];
  char vers[128];
  bzero(repo,128);
  bzero(user,128);
  bzero(file,128);
  bzero(vers,128);
  read(tdL.cl,user,sizeof(user));
  read(tdL.cl,repo,sizeof(repo));
  read(tdL.cl,file,sizeof(file));
  read(tdL.cl,vers,sizeof(vers));
  if(chkforpermission(repo,user)==0)
    {
      return;
    }
  int nrV1=0,nrV2=0,nrV3;
  char locci[1024];
  bzero(locci,1024);
  strcpy(locci,"container/");
  strcat(locci,repo);
  strcat(locci,"/");
  char dden[128];
  int llung=0;
  for(int iij=0;iij<strlen(file);iij++)
    {
      if(file[iij]=='.')
	break;
      dden[llung]=file[iij];
      llung++;
    }
  strcat(locci,dden);
  strcat(locci,"@");
  strcat(locci,"versiuni.txt");
  int fipo=open(locci,O_RDONLY);
  for(int ind=0;ind<strlen(vers);ind++)
    nrV1=nrV1*10+(vers[ind]-'0');
  char ck;
  while(read(fipo,&ck,sizeof(char))>0){
    if(ck>='0' && ck<='9')
      nrV2=nrV2*10+(ck-'0');
  }
  close(fipo);
  remove(locci);
  fipo=open(locci,O_WRONLY|O_CREAT,0666);
  for(int ind=0;ind<strlen(vers);ind++)
    write(fipo,&vers[ind],sizeof(char));
  close(fipo);
  if(nrV2>nrV1)
    {
      nrV2++;
    }
  else
    {
      nrV2--;
      nrV1--;
    }
  printf("%i %i \n",nrV1,nrV2);
  while(nrV1!=nrV2){
  char inst[2048];
  char *sql;
  int conn;
  sqlite3 *db;
  char *err=0;
  char vers1[128];
  int verlln=0;
  bzero(vers1,128);
  bzero(inst,2048);
  int x;
  if(nrV1>nrV2)
    x=nrV2+1;
  else
    x=nrV2-1;
  int y=0;
  while(x!=0){
    y=y*10+x%10;
    x=x/10;
  }
  while(y!=0)
    {
      vers1[verlln]=(y%10)+'0';
      y=y/10;
      verlln++;
    }
  printf("%s\n",vers1);
  const char* data="Callback function called!";
  strcpy(inst,"select diff from reverts where repo=");
  strcat(inst,"'");
  strcat(inst,repo);
  strcat(inst,"'");
  strcat(inst," and file=");
  strcat(inst,"'");
  strcat(inst,file);
  strcat(inst,"'");
  strcat(inst," and versiune=");
  strcat(inst,vers1);
  strcat(inst,";");
  bzero(diferenta,4096);
  conn=sqlite3_open("commdefs.db",&db);
  sql=inst;
  printf("%s\n",sql);
  conn=sqlite3_exec(db,sql,callback2,(void*)data,&err);
  if(conn!=SQLITE_OK){
    printf("%s\n",err);
    sqlite3_free(err);
  }
  printf("%s\n",diferenta);
  sqlite3_close(db);
  char loc[1024],loc2[1024];
  bzero(loc,1024);
  bzero(loc2,1024);
  strcpy(loc,"container/");
  strcpy(loc2,"container/");
  strcat(loc,repo);
  strcat(loc2,repo);
  strcat(loc,"/");
  strcat(loc2,"/");
  strcat(loc,file);
  strcat(loc2,"myfile.patch");
  int fip=open(loc2,O_WRONLY|O_CREAT,0666);
  for(int ii=0;ii<strlen(diferenta);ii++)
    write(fip,&diferenta[ii],sizeof(char));
  if(fork()==0)
    {
      if(nrV2>nrV1){
	execlp("patch","patch","-R",loc,loc2,NULL);
      }
      else
	if(nrV2<nrV1){
	  execlp("patch","patch",loc,loc2,NULL);
	}
    }
  if(nrV2>nrV1)
    nrV2--;
  else
    if(nrV2<nrV1)
      nrV2++;
  wait(NULL);
  close(fip);
  remove(loc2);
  }
}
void raspund10(void *arg)
{
  struct thData tdL;
  tdL=*((struct thData*)arg);
  char user[128];
  char repo[128];
  char file[128];
  bzero(user,128);
  bzero(repo,128);
  bzero(file,128);
  read(tdL.cl,user,sizeof(user));
  read(tdL.cl,repo,sizeof(repo));
  read(tdL.cl,file,sizeof(file));
  if(chkforpermission(repo,user)==0)
    {
      return;
    }
  int conn;
  sqlite3 *db;
  char *err=0;
  char *sql;
  const char* data="Callback function called!";
  conn=sqlite3_open("commdefs.db",&db);
  char inst[2048];
  bzero(inst,2048);
  strcpy(inst,"select diff from difs where file=");
  strcat(inst,"'");
  strcat(inst,file);
  strcat(inst,"'");
  strcat(inst," and user=");
  strcat(inst,"'");
  strcat(inst,user);
  strcat(inst,"'");
  strcat(inst,";");
  sql=inst;
  bzero(diferenta,4096);
  conn=sqlite3_exec(db,sql,callback2,(void*)data,&err);
  if(conn!=SQLITE_OK){
    printf("Error is %s\n",err);
    sqlite3_free(err);
  }else{
    printf("Operation succesful!");
  }
  sqlite3_close(db);
  printf("%s\n",diferenta);
  char loc[1024],loc2[1024];
  bzero(loc,1024);
  bzero(loc2,1024);
  strcpy(loc2,"container/");
  strcpy(loc,"container/");
  strcat(loc,repo);
  strcat(loc2,repo);
  strcat(loc,"/myfile.patch");
  strcat(loc2,"/");
  strcat(loc2,file);
  int fp=open(loc,O_WRONLY|O_CREAT,0666);
  printf("%s\n",loc);
  for(int ii=0;ii<strlen(diferenta);ii++)
    {
      write(fp,&diferenta[ii],sizeof(char));
    }
  close(fp);
  if(fork()==0)
    {
      execlp("patch","patch",loc2,loc,NULL);
    }
  wait(NULL);
  remove(loc);
  conn=sqlite3_open("commdefs.db",&db);
  bzero(inst,2048);
  int nr=0;
  char loc3[1024];
  bzero(loc3,1024);
  strcpy(loc3,"container/");
  strcat(loc3,repo);
  strcat(loc3,"/");
  char file2[128];
  bzero(file2,128);
  for(int ij=0;ij<strlen(file);ij++)
    {
      if(file[ij]=='.')
	break;
      file2[ij]=file[ij];
    }
  strcat(loc3,file2);
  strcat(loc3,"@versiuni.txt");
  fp=open(loc3,O_RDONLY|O_CREAT,0666);
  char car;
  char den[128];
  int lln=0;
  int p=1;
  bzero(den,128);
  while(read(fp,&car,sizeof(char))>0){
    if(car>='0' && car<='9')
      {
	nr=nr+(car-'0')*p;
	p=p*10;
      }
  }
  nr++;
  close(fp);
  fp=open(loc3,O_WRONLY);
  printf("%i\n",nr);
  int nraux=0;
  while(nr!=0)
    {
      car=(nr%10)+'0';
      write(fp,&car,sizeof(char));
      nraux=nraux*10+(nr%10);
      nr=nr/10;
    }
  lln=0;
  while(nraux!=0)
    {
      den[lln]=((nraux%10)+'0');
      lln++;
      nraux=nraux/10;
    }
  close(fp);
  strcpy(inst,"insert into reverts(diff,repo,file,versiune) values(");
  strcat(inst,"'");
  strcat(inst,diferenta);
  strcat(inst,"'");
  strcat(inst,",");
  strcat(inst,"'");
  strcat(inst,repo);
  strcat(inst,"'");
  strcat(inst,",");
  strcat(inst,"'");
  strcat(inst,file);
  strcat(inst,"'");
  strcat(inst,",");
  strcat(inst,den);
  strcat(inst,");");
  sql=inst;
  char *err2=0;
  conn=sqlite3_exec(db,sql,callback,0,&err2);
  if(conn!=SQLITE_OK)
    {
      printf("%s\n",err2);
      sqlite3_free(err2);
    }
  sqlite3_close(db);
  return;
}
void raspund9(void *arg)
{
  struct thData tdL;
  tdL=*((struct thData*)arg);
  char ph1[1024],ph2[1024];
  char repo[128];
  bzero(ph1,1024);
  bzero(ph2,1024);
  char comm[1024];
  bzero(repo,128);
  bzero(comm,1024);
  char user[128];
  bzero(user,128);
  read(tdL.cl,user,sizeof(user));
  read(tdL.cl,repo,sizeof(repo));
  read(tdL.cl,ph1,sizeof(ph1));
  read(tdL.cl,comm,sizeof(comm));
  if(chkforpermission(repo,user)==0)
    {
      return;
    }
  char ph3[128];
  bzero(ph3,128);
  int lg=0,i;
  for(i=strlen(ph1)-1;ph1[i]!='/';i--);
  for(int ii=i+1;ii<strlen(ph1);ii++)
    {
      ph3[lg]=ph1[ii];
      lg++;
    }
  char loc[1024];
  strcpy(loc,"container/");
  strcat(loc,repo);
  char loc2[1024];
  bzero(loc2,1024);
  strcpy(loc2,loc);
  strcat(loc2,"/");
  strcat(loc2,"diff.txt");
  int fpi=open(loc2,O_WRONLY|O_CREAT,0666);
  strcat(loc,"/");
  strcat(loc,ph3);
  printf("%s\n",repo);
  printf("%s\n",loc);
  printf("%s\n",ph1);
  if(fork()==0)
    {
      close(1);
      dup(fpi);
      execlp("diff","diff",loc,ph1,NULL);
    }
  wait(NULL);
  close(fpi);
  fpi=open(loc2,O_RDONLY);
  sqlite3 *db;
  char *err=0;
  int conn;
  char *sql;
  char dffile[4096];
  bzero(dffile,4096);
  int lung=0;
  char car;
  while(read(fpi,&car,sizeof(char))>0)
    {
      dffile[lung]=car;
      lung++;
    }
  conn=sqlite3_open("commdefs.db",&db);
  char inst2[2048];
  bzero(inst2,2048);
  strcat(inst2,"delete from difs where user=");
  strcat(inst2,"'");
  strcat(inst2,user);
  strcat(inst2,"'");
  strcat(inst2," and");
  strcat(inst2," file=");
  strcat(inst2,"'");
  strcat(inst2,ph3);
  strcat(inst2,"'");
  strcat(inst2,";");
  sql=inst2;
  conn=sqlite3_exec(db,sql,callback,0,&err);
  char inst[2048];
  bzero(inst,2048);
  strcpy(inst,"insert into difs (diff,comm,user,file) values(");
  strcat(inst,"'");
  strcat(inst,dffile);
  strcat(inst,"'");
  strcat(inst,",");
  strcat(inst,"'");
  strcat(inst,comm);
  strcat(inst,"'");
  strcat(inst,",");
  strcat(inst,"'");
  strcat(inst,user);
  //strcat(inst,"goguletz");
  strcat(inst,"'");
  strcat(inst,",");
  strcat(inst,"'");
  strcat(inst,ph3);
  strcat(inst,"'");
  strcat(inst,");");
  sql=inst;
  printf("%s\n",sql);
  close(fpi);
  remove(loc2);
  conn=sqlite3_exec(db,sql,callback,0,&err);
  if(conn!=SQLITE_OK){
    printf("EROARE ESTE %s\n",err);
    sqlite3_free(err);
  }
  else
    {
      printf("Records created!");
    }
  sqlite3_close(db);
  printf("AICI!");
  return;
}
void raspund8(void *arg)
{
  struct thData tdL;
  tdL=*((struct thData*)arg);
  char user[128];
  bzero(user,128);
  read(tdL.cl,user,sizeof(user));
  for(int i=0;i<allfils;i++){
    printf("%s %s \n",fils[i].path,fils[i].proprietar);
    if(strcmp(fils[i].proprietar,user)==0)
      {
	write(tdL.cl,fils[i].path,sizeof(fils[i].path));
      }
  }
  write(tdL.cl,"done",8);
}
void raspund7(void *arg)
{
  struct thData tdL;
  tdL=*((struct thData*)arg);
  char user[128];
  char repo[128];
  bzero(user,128);
  bzero(repo,128);
  read(tdL.cl,repo,sizeof(repo));
  read(tdL.cl,user,sizeof(user));
  //read(tdL.cl,ms1,sizeof(ms1));
  strcat(repo,"@");
  strcat(repo,"permisiuni.txt");
  printf("%s\n",repo);
  int ff=open(repo,O_RDWR);
  char A[256][128];
  for(int i=0;i<256;i++)
    bzero(A[i],128);
  char cc;
  int i=0,j=0;
  char bg=0;
  while(read(ff,&cc,sizeof(char))>0)
    {
      if(cc=='\n')
	{
	  i++;
	  j=0;
	}
      else
	{
	  A[i][j]=cc;
	  j++;
	}
    }
  i++;
  close(ff);
  remove(repo);
  ff=open(repo,O_WRONLY|O_CREAT,0666);
  int i1=0,j1=0;
  printf("AICI!");
  while(i1<i)
    {
      j1=0;
      printf("%s\n",A[i1]);
      if(strcmp(A[i1],user)!=0)
	{
	  while(j1<strlen(A[i1]))
	    {
	      write(ff,&A[i1][j1],sizeof(char));
	      j1++;
	    }
	  char cici='\n';
	  if(i1!=i-1)
	    write(ff,&cici,sizeof(char));
	}
      i1++;
    }
}
void raspund6(void *arg)
{
  struct thData tdL;
  tdL=*((struct thData*)arg);
  char user[128];
  bzero(user,128);
  char ms1[128],repo[128];
  bzero(ms1,128);
  bzero(repo,128);
  int dim=0;
  //read(tdL.cl,user,sizeof(user));
  //read(tdL.cl,ms1,sizeof(ms1));
  read(tdL.cl,repo,sizeof(repo));
  read(tdL.cl,user,sizeof(user));
  strcat(repo,"@permisiuni.txt");
  int fp=open(repo,O_RDWR|O_CREAT,0666);
  char c;
  while(read(fp,&c,sizeof(char))>0);
  int i=0;
  while(i<strlen(user)){
      write(fp,&user[i],sizeof(char));
      i++;
  }
  //c='\n';
  //write(fp,&c,sizeof(char));
  close(fp);
}
void raspund5(void *arg)
{
  struct thData tdL;
  tdL=*((struct thData*)arg);
  char user[128];
  char repo[128];
  bzero(user,128);
  bzero(repo,128);
  int dim=0;
  //read(tdL.cl,&dim,sizeof(int));
  //printf("%i\n",dim);
  //printf("%c\n",c);
  read(tdL.cl,user,sizeof(user));
  read(tdL.cl,repo,sizeof(repo));
  fisiere fiss[256];
  int allfis=0;
  //strcat(repo,"@");
  //strcat(repo,user);
  printf("%s\n",repo);
  if(chkforpermission(repo,user)==0)
    {
      write(tdL.cl,"finito",36);
      return;
    }
  generatePaths(repo,fiss,allfis);
  for(int i=0;i<allfis;i++)
    {
      printf("%s\n",fiss[i].path);
      write(tdL.cl,fiss[i].path,sizeof(fiss[i].path));
    }
  char mes[1024];
  bzero(mes,1024);
  strcpy(mes,"finito");
  write(tdL.cl,mes,sizeof(mes));
}
void raspund4(void *arg)
{
  struct thData tdL;
  tdL=*((struct thData*)arg);
  char locc[256];
  bzero(locc,256);
  char user[128],user1[128];
  bzero(user,128);
  bzero(user1,128);
  strcpy(locc,"users.txt");
  read(tdL.cl,user,sizeof(user));
  int fp=open(locc,O_RDONLY);
  int lg=0;
  char cc;
  while(read(fp,&cc,sizeof(char))>0)
    {
      if(cc=='\n' || cc=='\t')
	{
	  //printf("%s\n",user);
	  //printf("%s\n",user1);
	  printf("%s\n",user1);
	  if(strcmp(user1,user)==0)
	    {
	      printf("Gasit!\n");
	      break;
	    }
	  bzero(user1,128);
	  lg=0;
	}
      else
	{
	  user1[lg]=cc;
	  lg++;
	}
    }
  close(fp);
}
void raspund3(void *arg)
{
  struct thData tdL;
  tdL=*((struct thData*)arg);
  char locc[256];
  bzero(locc,256);
  char user[128];
  bzero(user,128);
  strcpy(locc,"users.txt");
  read(tdL.cl,user,sizeof(user));
  user[strlen(user)]=0;
  int fp=open(locc,O_RDWR,0666);
  int ix=0;
  char ci=-1;
  while(read(fp,&ci,sizeof(char))>0);
  /*if(ci!=-1){
    ci='\n';
    write(fp,&ci,sizeof(char));
  }*/
  while(ix<strlen(user))
    {
      write(fp,&user[ix],sizeof(char));
      ix++;
    }
  ci='\n';
  write(fp,&ci,sizeof(char));
}
void raspund2(void *arg)
{
  struct thData tdL;
  tdL=*((struct thData*)arg);
  char loc[256];
  char ms[126];
  char user[128];
  bzero(user,128);
  bzero(ms,126);
  bzero(loc,256);
  char repo[128];
  bzero(repo,128);
  read(tdL.cl,user,sizeof(user));
  read(tdL.cl,repo,sizeof(repo));
  read(tdL.cl,ms,sizeof(ms));
  printf("%s\n",repo);
  printf("%s\n",ms);
  if(chkforpermission(repo,user)==0)
    {
      return;
    }
  strcpy(loc,"container/");
  strcat(loc,repo);
  strcat(loc,"/");
  ms[strlen(ms)]=0;
  strcat(loc,ms);
  printf("%s\n",loc);
  remove(loc);
  sqlite3 *db;
  char* err=0;
  int conn;
  char *sql;
  conn=sqlite3_open("commdefs.db",&db);
  char inst[2048];
  bzero(inst,2048);
  strcpy(inst,"delete from difs where user=");
  strcat(inst,"'");
  strcat(inst,user);
  strcat(inst,"'");
  strcat(inst," and file=");
  strcat(inst,"'");
  strcat(inst,ms);
  strcat(inst,"'");
  strcat(inst,";");
  sql=inst;
  sqlite3_exec(db,sql,callback,0,&err);
  bzero(inst,2048);
  strcpy(inst,"delete from reverts where repo=");
  strcat(inst,"'");
  strcat(inst,repo);
  strcat(inst,"'");
  strcat(inst," and file=");
  strcat(inst,"'");
  strcat(inst,ms);
  strcat(inst,"'");
  strcat(inst,";");
  sqlite3_close(db);
}
void raspund1(void *arg)
{
  struct thData tdL;
  tdL=*((struct thData*)arg);
  char ms[126];
  char repo[128];
  bzero(repo,128);
  bzero(ms,126);
  char messg[2056];
  char cc;
  char user[128];
  bzero(user,128);
  read(tdL.cl,user,sizeof(user));
  read(tdL.cl,repo,sizeof(repo));
  read(tdL.cl,ms,sizeof(ms));
  ms[strlen(ms)-1]=0;
  printf("%s\n",ms);
  char loc[126];
  if(chkforpermission(repo,user)==0)
    {
      char dec=0;
      write(tdL.cl,&dec,sizeof(char));
      return;
    }
  char dec=1;
  write(tdL.cl,&dec,sizeof(char));
  strcpy(loc,"container/");
  strcat(loc,repo);
  strcat(loc,"/");
  strcat(loc,ms);
  printf("%s\n",loc);
  //int ind=FindFile(ms);
  //strcat(loc,fils[ind].path);
  int fp=open(loc,O_RDONLY);
  bzero(ms,126);
  int ix=0,lg=0;
  while(read(fp,&cc,sizeof(char))>0)
  {
    //messg[lg]=cc;
    //lg++;
    write(tdL.cl,&cc,sizeof(char));
  }
  cc=-1;
  write(tdL.cl,&cc,sizeof(char));
  //write(tdL.cl,messg,sizeof(messg));
  close(fp);
  
}
void raspund(void *arg)
{
	int nr,i=0;
	char repo[128];
	int okd=0;
	char user[128];
	struct thData tdL;
	tdL=*((struct thData*)arg);
	char ms[126];
	bzero(ms,126);
	bzero(repo,128);
	bzero(user,128);
	printf("AICI!");
	sync();
	read(tdL.cl,user,sizeof(user));
	read(tdL.cl,ms,sizeof(ms));
	read(tdL.cl,repo,sizeof(repo));
	printf("%s %s %s\n ",user,ms,repo);
	printf("HEYA!");
	//DIR* dir=opendir(repo);
	char locc[256];
	bzero(locc,256);
	strcpy(locc,"container/");
	strcat(locc,repo);
	printf("Inainte de DIR!");
	DIR* dir=opendir(locc);
	printf("DUPA DIR!");
	printf("Iainte de Check!");
	if(chkforpermission(repo,user)==0)
	  {
	    printf("Nu ai permisiuni!");
	    write(tdL.cl,"U shall not pass!",36);
	    return;
	  }
	printf("Dupa Check!");
	if(dir){
	  closedir(dir);
	}
	else{
	  mkdir(locc,0777);
	}
	printf("Dupa Check!");
	printf("[Thread %d]Mesajul a fost receptionat..%d\n",tdL.idThread,nr);
	printf("[Thread %d]Trimitem mesajul inapoi..%d\n",tdL.idThread,++nr);
	char c;
	int fp,fp2;
	ms[strlen(ms)]=0;
	printf("%s %d\n",ms,strlen(ms));
	fp=open(ms,O_RDONLY);
	char str[256];
	bzero(str,256);
	int ix=0;
	int lg=0;
	while(ix<strlen(ms))
	{
		if(ms[ix]=='.')
		{
		        okd=1;
			while(ms[ix]!='/')
				ix--;
			ix++;
			while(ix<strlen(ms))
			{
				str[lg]=ms[ix];
				lg++;
				ix++;
			}
			str[lg]=0;
			break;
		}
		ix++;
	}
	char cale[1024];
	bzero(cale,1024);
	//strcpy(cale,"/home/goguspoder/Desktop/proiectRetele/container/");
	strcpy(fils[allfils].path,repo);
	//strcat(repo,"/");
	//strcat(cale,repo);
	//strcat(cale,str);
	strcat(locc,"/");
	//strcpy(fils[allfils].path,str);
	strcpy(fils[allfils].proprietar,user);
	allfils++;
	strcat(locc,str);
	fp2=open(locc,O_WRONLY|O_CREAT,0666);
	printf("%s\n",locc);
	while(read(fp,&c,sizeof(char))>0)
	{
	        printf("%c",c);
		write(fp2,&c,sizeof(char));
	}
	close(fp);
	close(fp2);
	write(tdL.cl,"UploadReusit!",36);
	printf("Succes\n");
}
