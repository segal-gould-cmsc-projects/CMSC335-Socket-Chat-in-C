//Noah Segal-Gould
//Prof. K. Salehin
//Computer Networks
//9 April 2017

//Lab 5: Socket Server
//To compile, run: gcc -o Segal-Gould_Lab5_SocketServer Segal-Gould_Lab5_SocketServer.c
//To run, type: ./Segal-Gould_Lab5_SocketServer 1234

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define QUIT "QUIT\n"


int main(int argc, char **argv) {

    if (argc != 2) {
        printf("\n*****INVALID ARGUMENTS*****\n");
        return 0;
    }

    printf("Starting socket Server with port %s.\n", argv[1]);

    int port = atoi(argv[1]); // Convert the port input to an integer.
    char sendline[100]; // The String being sent to the Client.
    char recvline[100]; // The String being received by the Server.
    char buff[100]; // The String used to represent time.
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port); // Set the port to be the user input.
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listen_fd, 10);
    comm_fd = accept(listen_fd, (struct sockaddr *) NULL, NULL);

    while (strcmp(sendline, QUIT) != 0) { // Check if the message sent from the Server is "QUIT," and if so, do.
        bzero(recvline, 100);
        read(comm_fd, recvline, 100);
        time_t first = time(0); // Calculate the system time following the response.
        strftime(buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&first)); // Format the time as a String.
        printf("Client [%s]: %s\n", buff, recvline); // Print the Client's response along with the time.
        bzero(sendline, 100);
        time_t second = time(0); // Calculate the time prior to user input.
        strftime(buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&second)); // Format the time as a String.
        printf("Server [%s]: ", buff); // Print the initial time for the message sent from the Server to the Client.
        fgets(sendline, 100, stdin); // Get user input to send message from Server to Client.
        time_t third = time(0); // Calculate the time following user input.
        strftime(buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&third)); // Format the time as a String.
        printf("\nMessage sent at %s\n", buff); // Print the corrected time the message was input.
        write(comm_fd, sendline, strlen(sendline) + 1);
    }
    printf("\n*****QUITTING PROGRAM*****\n");
    return 0;
}
