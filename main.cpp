#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

void handle_user_input()
{
    std::cout << std::endl << "$ ";

    std::string line, cmd, arg;

    while (getline(std::cin, line)) {
        std::istringstream iss(line);
        iss >> cmd;

        if (cmd == "download") {
            iss >> arg;

            if (arg.length() > 0) {
                download_file(arg);
            }
            else {
                std::cout << "Command syntax: `download <filename>`" << std::endl;
            }
        }
        else if (cmd == "upload") {
            iss >> arg;

            if (arg.length() > 0) {
                queue->set_message(Message::MSG_UPDT_FILE, arg);
                std::cout << "File `" << arg << "` added to upload queue." << std::endl;
            }
                        else {
                std::cout << "Command syntax: `upload /path/to/file`" << std::endl;
            }
        }
        else if (cmd == "delete") {
            iss >> arg;

            if (arg.length() > 0) {
                queue->set_message(Message::MSG_DELE_FILE, arg);
                std::cout << "File `" << arg << "` added to deletion queue." << std::endl;
            }
            else {
                std::cout << "Command syntax: `delete <filename>`" << std::endl;
            }
        }
        else if (cmd == "list_client") {
            list_client();
        }
        else if (cmd == "list_server") {
            list_server();
        }
        else if (cmd == "exit") {
            close_connection();
            exit(EXIT_SUCCESS);
        }
        else {
            std::cout << "Unknown command." << std::endl;
        }
        std::cout << "$ ";
    }
}