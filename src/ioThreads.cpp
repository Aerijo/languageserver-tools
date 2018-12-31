#include <iostream>
#include <thread>
#include <string>

#include <rapidjson/document.h>

#include "QueueManager.h"
#include "library.h"

bool isExitNotif (const Document &message) {
    return std::strcmp(message["method"].GetString(), "exit") == 0;
}

std::thread launchStdinLoop () {
    std::cin.tie(nullptr);

    return std::thread([]{
       while (true) {
            Document message = getMessage();

            if (message.HasParseError() || isExitNotif(message)) {
                break;
            }

            QueueManager::pushMessage(message);
       }
    });
}

void sendMessage (Document &message) {
    message.AddMember("jsonrpc", "2.0", message.GetAllocator());

    StringBuffer buffer;
    Writer<StringBuffer> writer (buffer);
    message.Accept(writer);

    std::cout
            << "Content-Length: "
            << buffer.GetLength()
            << "\r\n\r\n"
            << buffer.GetString();
    std::cout.flush();
}

std::thread launchStdoutLoop () {
    return std::thread([]{
        auto *queue = QueueManager::getInstance();

        while (true) {
            Document message = queue->for_stdout.dequeue();
            sendMessage(message);
        }
    });
}