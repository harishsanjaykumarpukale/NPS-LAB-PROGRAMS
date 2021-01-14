#include<stdio.h>

void main() {
    int data[8],recv[8],c,c1,c2,c3,i,t;

    printf("Sender: ");
    scanf("%d %d %d %d",&data[3] ,&data[5] ,&data[6] ,&data[7]);

    //XOR of bits having 1 in first place
    data[1]=data[3]^data[5]^data[7];
    //XOR of bits having 1 in second place
    data[2]=data[3]^data[6]^data[7];
    //XOR of bits having 1 in third place
    data[4]=data[5]^data[6]^data[7];

    //XOR of whole block
    data[0] = 0;
    for(i=1;i<=7;i++) 
        data[0] ^= data[i];
    
    printf("Encoded Data: ");
    for(i=0;i<8;i++)
        printf("%d",data[i]);

    printf("\nReceiver: ");
    for(i=0;i<8;i++)
        scanf("%d",&recv[i]);

    //Calculation of errerneous bit position
    c1=recv[1]^recv[3]^recv[5]^recv[7];
    c2=recv[2]^recv[3]^recv[6]^recv[7];
    c3=recv[4]^recv[5]^recv[6]^recv[7];
    c=c3*4+c2*2+c1 ;

    //XOR of whole block
    t=0;
    for(i=0;i<8;i++)
        t^=recv[i];
    

    if(c==0 && t==0) 
        printf("\nNo error while transmission of data\n");
    else if (c!=0 && t==0)
        printf("\nERROR detected in atleast 2 bits.\n");
    else {
        printf("\nSyndrome bits:  %d %d %d", c3, c2, c1);
        printf("\nError Position: %d",c);
        printf("\nData sent: ");
        for(i=0;i<8;i++)
            printf("%d",data[i]);
        printf("\nData received: ");
        for(i=0;i<8;i++)
            printf("%d",recv[i]);
        printf("\nCorrect message is: ");
        //if errorneous bit is 0 we complement it else vice versa
        if(recv[c]==0)
            recv[c]=1;
        else
            recv[c]=0;
        for (i=0;i<8;i++)
            printf("%d",recv[i]);
        printf("\n");
    }
}

