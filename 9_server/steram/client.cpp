#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include <signal.h>

using namespace std;

int main(int argc, char* argv[])
{
	signal(SIGINT, SIG_IGN);
	int B_SIZE = 256;
 	int socket_ = socket(AF_INET, SOCK_STREAM, 0);
 	struct sockaddr_in server;
	char buffer[B_SIZE];
	char* s = argv[1];
	server.sin_family = AF_INET;
 	server.sin_port = htons(53000);
	server.sin_addr.s_addr = inet_addr(s);			
	if (connect(socket_, (struct sockaddr *)&server, sizeof(server)) < 0) cout << "Cann't connect!" << endl << strerror(errno) << endl;
	else cout << "Connected!" << endl<<"You cann't end with CTRL+C, please type 'done' to disconnect."<<endl;
	while(1)
	{	
		cout << "your message : ";
 		fgets(buffer, B_SIZE, stdin);
		if (buffer[0] == '\n') 
		{
		  cout << "You cann't send empty message!" << endl;
		  continue;
		}
		string ans = "";
		for (int i = 0; i < B_SIZE && buffer[i] != '\n'; i++)
		  ans += buffer[i];
 		if (send(socket_, buffer, sizeof(buffer), 0) == -1)  printf ("Error opening file (errno): %s\n", strerror(errno));
		if (ans == "done") 	
		{
			close(socket_);
			break;		
		} 
	 	int m = true;
		while(m){
			int rc = recv(socket_, buffer, sizeof(buffer), 0);
			if(rc != -1)
			{
		  		cout << "      answer : " << buffer;
		   		m=false;
		  	}
		}
	}
}
