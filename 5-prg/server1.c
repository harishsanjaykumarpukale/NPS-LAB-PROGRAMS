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

    int welcomeSocket, Client1, Client2;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    char buffer[1024];


    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));


    if (listen(welcomeSocket,5)==0)
        printf("Listening\n");
    else
        printf("Error\n");


    addr_size = sizeof serverStorage;
    Client1 = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
    Client2 = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

    int cmdEXIT = 0;
 
    while (cmdEXIT == 0)
    {
        //recevoir le message de Client1
        recv(Client1, buffer, 1024, 0);
        printf ("%s\n", buffer);
        send(Client2,buffer,1024,0);
        if (compare_strings(buffer, "exit")==0)
        {   
            cmdEXIT = 1;
        }
        //sinon
        else 
        {

            memset(&buffer[0], 0, sizeof(buffer));
   
            recv(Client2, buffer, 1024, 0);

            printf ("%s\n", buffer);
            send(Client1,buffer,1024,0);

            if (compare_strings(buffer, "exit")==0)
            {
                cmdEXIT = 1;
            }
        }
    }

    return 0;
}
