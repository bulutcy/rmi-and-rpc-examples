/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Bulut Korkmaz 2012 <bulutkorkmaz@gmail.com>
 * 
This is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * swe545-assigment1-server is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//common libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//network communication libs
#include <sys/types.h> 
#include <sys/socket.h>
//helper libs for port bind
#include <netinet/in.h>
//error signals
#include <signal.h>

int sockfd;

//error raiser
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
void leave(int sig) {//port closer
        printf("Server closing..");
		close(sockfd);
        exit(sig);
}
int main(int argc, char *argv[])
{
	(void) signal(SIGINT,leave);
     int newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;//server and client socketaddress objects
     int n;
	 char IP[256] = "IP";
 	 char TCP[256] = "TCP";
	
     sockfd = socket(AF_INET, SOCK_STREAM, 0);//since we are using tcp we set family INET,type STREAM , and 0 for auto choice.
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));//make serv_addr socket null
     portno = 9987; //listening port
     serv_addr.sin_family = AF_INET; //make adress object family the same
     serv_addr.sin_addr.s_addr = INADDR_ANY;//  we already included netinet/in.h class so we can easily bind the ip for listening using INADDR_ANY
     serv_addr.sin_port = htons(portno);// using htons for network byte order standarts

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) //socket bind to system, returns -1 for any errors
              error("ERROR on binding");
	
     listen(sockfd,5); //starts server for listening(currently 5 max clients)
     clilen = sizeof(cli_addr);
	for(;;){ // it will listen forever
		 newsockfd = accept(sockfd,  (struct sockaddr *) &cli_addr, &clilen);//wait connection
		//at this point, someone is connected 
		if (newsockfd < 0) //if error occurs
		      error("ERROR on accept");

		 bzero(buffer,256); //create empty buffer
		 n = read(newsockfd,buffer,255);//write the incoming message
		 if (n < 0) error("ERROR reading from socket");//error 
		
		 printf("Message from client: %s\n",buffer);
		 char OK[256] = "OK ";
		 if(strcmp(buffer,IP)==0){ //if message is = "IP"
			  struct sockaddr_in ss;
			  socklen_t len = sizeof(ss);
			  char buf[INET_ADDRSTRLEN] = "";
			  getpeername(newsockfd,(struct sockaddr*)&ss,&len);// we have created a structure for getting peer's information
			  inet_ntop(AF_INET, &ss.sin_addr, buf, sizeof buf);//convert ip address to readable format
			  strcat(OK,buf); //add OK message
			  n = write(newsockfd,OK,sizeof(OK));// give response
		 }else if(strcmp(buffer,TCP)==0){//if message is = "TCP"
			  struct sockaddr_in ss;
			  socklen_t len = sizeof(ss);
			  getpeername(newsockfd,(struct sockaddr*)&ss,&len);
			  sprintf (OK, "%s%d", OK, ntohs(ss.sin_port));//format the port number and add it to message
		
			  n = write(newsockfd,OK,sizeof(OK));//response
		 }else
		  n = write(newsockfd,"NO",2);//else, NO response
		
		if (n < 0) 
		error("ERROR writing to socket"); //response error
		 close(newsockfd);
	}
     close(sockfd);
     return 0; 
}
