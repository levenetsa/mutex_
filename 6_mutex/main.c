#include <stdio.h>
#include <stdlib.h>
//#include <linux/msg.h>
//#include <linux/ipc.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>

struct mess_t{
	long mtype;
  	int int_num;
        int ch;
};

struct mess_t  sent, received;

void set(int a, int c)
{
	sent.int_num = a;
  	sent.ch = c;
	sent.mtype = 1;
}
  
void print()
{
	printf("int= %d f = %d\n",
 		received.int_num, 
		received.ch
	      );
}

void print_s()
{
	printf("int= %d f = %d\n",
 		sent.int_num, 
		sent.ch
	      );
}

int get_queue(int flag)
{
  //1 is creating
  //0 is getting
	  if (flag == 1)
	      return msgget(ftok("main.c", 's'), IPC_CREAT | 0660);
	  else
	      return msgget(ftok("main.c", 's'), 0660);
}

int main()
{	//
  	int length;
  	length = sizeof(struct mess_t);
	int qid = get_queue(0);
	msgctl(qid, IPC_RMID, 0);
  	qid = get_queue(1);
	while(1){
                int c = 1;
                //ожидание сообщения
		while(c)
		{
		      msgrcv(qid, &received, length, sent.mtype, 0);
		      if (received.ch == 0) c = 0;
		      else msgsnd(qid, &received, length, 0);
		}

		set(received.int_num, 1);
  		msgsnd(qid, &sent, length, 0);
	  	printf("locked\n");
                 //ожидане пока не получим ответ о завершении
		int ident = received.int_num;
		c = 1;
		while(c)
		{
		      msgrcv(qid, &received, length, sent.mtype, 0);
		      if (received.int_num == ident) c = 0;
		      else msgsnd(qid, &received, length, 0);
		}
		printf("unlocked\n");
	}
}

