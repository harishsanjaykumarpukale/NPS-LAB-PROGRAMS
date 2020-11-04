#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>


#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#include<netinet/in.h>
#include<arpa/inet.h>

void str_echo(int connfd){
	int n,bufsize = 1024,len;
	char *buff = malloc(bufsize);
	struct sockaddr_in addr;

again: while((n=recv(connfd,buff,bufsize,0))>0)  
	       send(connfd,buff,n,0);

       if(n<0)
	       goto again;
}
int main(){
	int listenfd,connfd,addrlen,pid;
	struct sockaddr_in address;
	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) > 0)
		printf("The socket was created\n");
	else
		printf("Error in Socket creation\n");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port= htons(15001);

	if( bind( listenfd,(struct sockaddr *)& address,sizeof(address)) ==0)
		printf("Binding Socket\n");
	else
		printf("ERROR in binding\n");

	if ((listen(listenfd, 3)) != 0){
	      printf("Listen failed\n");
	      exit(0);
	}
	else{
		getsockname(listenfd,(struct sockaddr *) &address,&addrlen);
		printf("Server listening on port  %d\n",address.sin_port);
	}


	for(;;){
		addrlen = sizeof(struct sockaddr_in);
		connfd = accept(listenfd,(struct sockaddr *)& address,&addrlen);
		printf(" connfd is %d ",connfd);
		if(connfd>0)
			printf("The client %s is connected \n", inet_ntoa(address.sin_addr));
		else
			printf("Not accepted\n");

		str_echo(connfd);
		close(connfd);
	}

	return 0;
}
