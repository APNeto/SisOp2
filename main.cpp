void handle_user_input()
{
    cout << endl << "$ ";

    std::string line, cmd, arg;

    while (getline(cin, line)) {
        std::istringstream iss(line);
        iss >> cmd;

        if (cmd == "download") {
            iss >> arg;

            if (arg.length() > 0) {
                download_file(arg);
            }
            else {
                cout << "Command syntax: `download <filename>`" << endl;
            }
        }

        else if (cmd == "upload") {
            iss >> arg;

            if (arg.length() > 0) {
                queue->set_message(Message::MSG_UPDT_FILE, arg);
                cout << "File `" << arg << "` added to upload queue." << endl;
            }
                        else {
                cout << "Command syntax: `upload /path/to/file`" << endl;
            }
        }

        else if (cmd == "delete") {
            iss >> arg;

            if (arg.length() > 0) {
                queue->set_message(Message::MSG_DELE_FILE, arg);
                cout << "File `" << arg << "` added to deletion queue." << endl;
            }
            else {
                cout << "Command syntax: `delete <filename>`" << endl;
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
            cout << "Unknown command." << endl;
        }

        cout << "$ ";
    }
}