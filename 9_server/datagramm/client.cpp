#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

using namespace std;

int main(int argc, char* argv[])
{
	int B_SIZE = 256;
 	int sockfd;
        //получение сокета
 	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
 	struct sockaddr_in serv, client;
	serv.sin_family = AF_INET;
 	serv.sin_port = htons(53000);
        //настройка адреса
	char* s = argv[1];
	serv.sin_addr.s_addr = inet_addr(s);		
	char buffer[B_SIZE]; 
 	cout << "\ngoing to send\n";	
	while(1)
	{	
		cout << "your message : ";
 		fgets(buffer, B_SIZE, stdin);
                //считывание сообщения из консоли
		if (buffer[0]=='\n') 
		{
		  cout<<"You cann't send empty message!"<<endl;
		  continue;
		}
		string ans="";
		for (int i = 0; i < B_SIZE && buffer[i] != '\n'; i++)
		  ans += buffer[i];
		if (ans=="done") break; 
                //отправка сообщения
 		int z = sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv, sizeof(serv));
 		if ( z == -1)  printf ("Error opening file (errno): %s\n", strerror(errno));
                //получение ответа
                z = recvfrom(sockfd, buffer, B_SIZE, 0, (struct sockaddr *)&client, (socklen_t*)sizeof(client));
		cout << "answer : " << buffer;
	}
}
