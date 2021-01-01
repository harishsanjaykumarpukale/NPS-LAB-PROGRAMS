#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>



int compare_strings(char a[], char b[])
{
    int c = 0;
    while (a[c] == b[c]) 
    {
        if (a[c] == '\0' || b[c] == '\0')
        break;
        c++;
    }
    if (a[c] == '\0' && b[c] == '\0')
    return 0;
    else
    return -1;
}


int main() {

    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    int cmdEXIT = 0;


    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    addr_size = sizeof serverAddr;

 
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    printf("Client 1 : ");
    scanf(" %[^\n]s", buffer);
    send(clientSocket,buffer,sizeof buffer - 1,0);      

    while (cmdEXIT == 0)
    {

        if (compare_strings(buffer, "exit")==-1)
        {
     
            memset(&buffer[0], 0, sizeof(buffer));

            int recvValue = recv(clientSocket, buffer, sizeof buffer - 1, 0);

            if (recvValue != 1)
            {
    
                if (compare_strings(buffer, "exit")==-1)
                {
           
                    printf("Client 2 : ");
                    printf("%s\n", buffer);
        
                    memset(&buffer[0], 0, sizeof(buffer));
                }
          
                else cmdEXIT=1;
            }
   
            else
            {
           
                printf("Client 1 : ");
                scanf(" %[^\n]s", buffer);
         
                send(clientSocket,buffer,sizeof buffer - 1,0);
            }
        }
  
        else cmdEXIT=1;
    }

    return 0;
}