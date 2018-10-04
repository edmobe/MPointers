//
// Created by maria on 21/09/18.
//

#ifndef UNTITLED_CLIENT_H
#define UNTITLED_CLIENT_H


#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include "json.hpp"

#define PORT 8080

using json = nlohmann::json;

class Client{
public:
    static bool gcrunning; //indica si ya inició el garbage collector
    Client (){
        struct sockaddr_in address;
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char *hello = "Hello from client";
        char buffer[1024] = {0};
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            //return -1;
        }

        memset(&serv_addr, '0', sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, "192.168.0.10", &serv_addr.sin_addr)<=0)
        {
            printf("\nInvalid address/ Address not supported \n");
            //return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            //return -1;
        }
        json msent;
        msent["hello world"] = "Hello World";
        // a String .dump() y a Char con c_str();
        send(sock , msent.dump().c_str() , strlen(msent.dump().c_str()) , 0 );
        std::cout<<msent.dump().c_str()<<std::endl;
        printf("Hello message sent\n");
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
        //return 0;
    }

};



#endif //UNTITLED_CLIENT_H
