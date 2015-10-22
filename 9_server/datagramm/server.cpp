#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;


int main()
{
    	int sockfd;
    	sockfd = socket(AF_INET,SOCK_DGRAM,0);
    	struct sockaddr_in serv,client;
    	serv.sin_family = AF_INET;
    	serv.sin_port = htons(53000);
    	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    	bind(sockfd,(struct sockaddr*)&serv,sizeof(serv));
    	char buffer[256];
    	socklen_t l = sizeof(client);
	cout<<"running\n";	
        while(1){
                //получение сообщений от клиентов
    		int rc= recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&l);
    		if(rc<0)
    		{
        		cout<<"Error while reading"<<endl;
    		}
    		cout<<"recieved : "<<buffer;
		int size = 0;
                //создание ответа
		for (int i = 0; buffer[i]!='\n'; i++)
		{
			buffer[i] += 5;
			if (buffer[i] > 122)
				buffer[i] -=10;
			size++;
                }
                //отправка ответа
    		int rp= sendto(sockfd, buffer, size, 0, (struct sockaddr *)&client, l);
    		if(rp<0)
    		{
        		cout<<"Error while sending back"<<endl;
    		}
	}
    	return 0;
}
