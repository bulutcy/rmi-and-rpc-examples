/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Bulut Korkmaz 2012 
 * 
This is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * swe545-assignment1-client is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */




 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
   
    char buffer[256];
    portno = 9987;
	for(;;){ //drops connection after every message and waits for new input 

		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) 
		    error("ERROR opening socket");
	   
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//server ip
		serv_addr.sin_port = htons(portno);
	
		if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

		printf("Message to server: ");
		bzero(buffer,256);
		fgets(buffer,255,stdin);
		buffer[strlen(buffer) - 1] = 0;//trim the newline char
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0) 
		     error("ERROR writing to socket");
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if (n < 0) 
		     error("ERROR reading from socket");
		printf("Response from server:%s\n",buffer);
		close(sockfd);  
			
	}
    
    return 0;
}

