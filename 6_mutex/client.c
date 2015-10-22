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
        //структура для передачи сообщения
	long mtype;
  	int int_num;
        int ch;
};

struct mess_t  sent, received;
//два экземпляра сообщения

void set(int a, int c)
{
    //функция для заполнения исходящего сообщения
	sent.int_num = a;
  	sent.ch = c;
	sent.mtype = 1;
}
  
void print()
{
    //вывод полученного сообщения на экран
	printf("int= %d f = %d\n",
 		received.int_num, 
		received.ch
	      );
}

void print_s()
{
    //вывод отправляемого сообщения
	printf("int= %d f = %d\n",
 		sent.int_num, 
		sent.ch
	      );
}

int get_queue(int flag)
{
    //создание или получение очереди сообщений
  //1 is creating
  //0 is getting
	  if (flag == 1)
	      return msgget(ftok("main.c", 's'), IPC_CREAT | 0660);
	  else
	      return msgget(ftok("main.c", 's'), 0660);
}

int main()
{	
  	int length;
  	length = sizeof(struct mess_t);
  	int qid = get_queue(0);
	int pid = fork();
        //создание подпотока
	if (pid != 0)
        {
                //заполнение сообщения
		set(pid, 0);
  		msgsnd(qid, &sent, length, 0);
  		printf("I'm first and i'm ready\n");
		int c = 1;
		while(c)
		{
                      //ожидание получения нужного сообщения
		      msgrcv(qid, &received, length, sent.mtype, 0);
		      if (pid == received.int_num && received.ch == 1) c = 0;
		      else msgsnd(qid, &received, length, 0);
		}
		printf("I'm first and i'm working\n");
		usleep(10000000);
		printf("I'm first and i've done\n");
		set(pid, 0);
                //сообщение о завершении работы
  		msgsnd(qid, &sent, length, 0);
		wait();
	}	
	else
	{
                //тоже самое для дочернего потока
		set(pid, 0);
  		msgsnd(qid, &sent, length, 0);
  		printf("I'm secound and i'm ready\n");
		int c = 1;
		while(c)
		{
		      msgrcv(qid, &received, length, sent.mtype, 0);
		      if (pid == received.int_num && received.ch == 1) c = 0;
		      else msgsnd(qid, &received, length, 0);
		}
		printf("I'm secound and i'm working\n");
		usleep(10000000);
		printf("I'm secound and i've done\n");
		set(pid, 0);
  		msgsnd(qid, &sent, length, 0);
	}
}

