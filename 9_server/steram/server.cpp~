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


int main()
{
    	int socket_;
    	socket_ = socket(AF_INET, SOCK_STREAM, 0);
    	struct sockaddr_in server, client;
    	server.sin_family = AF_INET;
    	server.sin_port = htons(53000);
    	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	if( bind(socket_,(struct sockaddr *)&server , sizeof(server)) < 0) 
	{
		puts("Bind failed!"); 
		return 1;
	} 
	else puts("Bind done!");
	int status =  listen(socket_, 5);
	if (status == -1)  
	{
		cout << "Listen error!" << endl << strerror(errno) << endl; 
		return 1;
	}
	else puts("Waiting for incoming connections...");
    	int c = sizeof(struct sockaddr_in);
    	int new_socket;
	while(new_socket = accept(socket_, (struct sockaddr *)&client, (socklen_t*)&c))
	{
		bool md = true;
    		if (new_socket < 0) 
		{
			perror("Accept failed!");
			md = false;
		} 
		else puts("Connection accepted!");    	
    		char buffer[256];
    		c = sizeof(client);
		while(md)
		{    
    			int m = true;
			while(m)
			{
				if(recv(new_socket, buffer, sizeof(buffer), 0) > 0)		
				{
		    			cout << "recieved : " << buffer;
		    			m = false;
		  		}
			}
    			int size = 0;
			string str = "";
			for (int i = 0; buffer[i] != '\n'; i++)
			{
				str += buffer[i];
				buffer[i] += 5;
				if (buffer[i] > 122)
					buffer[i] -= 10;
				size++;
			}
			if (str == "done") 
			{	
				md = false; 
				puts("Disconnected.\n");
			}
    			if(send(new_socket, buffer, size, 0) < 0) cout<<"Error while sending back!"<<endl;
		}
	}
    	return 0;
}
