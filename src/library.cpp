#include <iostream>

#include "library.h"

#define STDIN_EXPECT(e) if (getchar() != e) { gotoNextHeader(); continue; };

void handleFailedJSON () {
//    const string fpp = "Failed to parse JSON";
//    sendError(LSP_ERROR::ParseError, fpp);
}

void verifyJSON (const Document &json) {
    if (json.HasParseError()) return handleFailedJSON();

    Value::ConstMemberIterator version = json.FindMember("jsonrpc");
    if (
            version == json.MemberEnd() ||
            std::string(version->value.GetString()) != "2.0"
       ) {
        return handleFailedJSON();
    }
}

void gotoNextHeader () {
    while (true) {
        while (getchar() != '\r') {}
        if (getchar() == '\n') return;
    }
}

size_t readHeaders () {
    size_t length = 0;
    string length_str;
    int c;

    while (true) {
        STDIN_EXPECT('C');
        STDIN_EXPECT('o');
        STDIN_EXPECT('n');
        STDIN_EXPECT('t');
        STDIN_EXPECT('e');
        STDIN_EXPECT('n');
        STDIN_EXPECT('t');
        STDIN_EXPECT('-');
        STDIN_EXPECT('L');
        STDIN_EXPECT('e');
        STDIN_EXPECT('n');
        STDIN_EXPECT('g');
        STDIN_EXPECT('t');
        STDIN_EXPECT('h');
        STDIN_EXPECT(':');
        STDIN_EXPECT(' ');

        break;
    }

    while (true) {
        c = getchar();
        if (c == '\r') {
            getchar(); // '\n'
            break;
        }
        length_str += static_cast<char>(c);
    }

    length = std::strtoull(length_str.c_str(), nullptr, 10);

    while (true) {
        if (getchar() != '\r') continue;
        if (getchar() != '\n') continue;
        if (getchar() != '\r') continue;
        if (getchar() != '\n') continue;

        return length;
    }
}


bool validateMessage (Document &message) {
    /**
     * Check:
     * - If method starts with `$/`, it must be a notification (request throws error MethodNotFound)
     * - Has `jsonrpc: 2.0`
     * - Has `method`
     * -
     */

    return true;
}

// NOTE: Still need to respond
void cancelRequest (int id) {
    Document message;
    auto &allocator = message.GetAllocator();

    message.AddMember("method", "$/cancelRequest", allocator);
    message.AddMember("params", Value().SetObject().AddMember("id", id, allocator), allocator);

    sendMessage(message);
}

void cancelRequest (const string &id) {
    Document message;
//    auto &allocator = message.GetAllocator();

//    message.AddMember("method", "$/cancelRequest", allocator);
//    message.AddMember("params", Value().SetObject().AddMember("id", id, allocator), allocator);

    sendMessage(message);
}

/**
 * Extracts and returns the raw JSON from a message. Also verifies the
 * jsonrpc property is valid.
 *
 * @return The JSON message
 */
Document getMessage () {
    size_t length = readHeaders();
    char buffer[length];

    FileReadStream input (stdin, buffer, sizeof(buffer));

    Document json;
    json.ParseStream(input);

    return json;
}

void sendResponse (Value &result) {
    Document json;
    auto &allocator = json.GetAllocator();

    json.AddMember("id", Value(), allocator);
    json.AddMember("result", result, allocator);

    sendMessage(json);
}

void sendResponse (const string &id, Value &result) {
    Document json;
//    auto &allocator = json.GetAllocator();
//
//    json.AddMember("id", id, allocator);
//    json.AddMember("result", result, allocator);

    sendMessage(json);
}

void sendResponse (const int id, Value &result) {
    Document json;
    auto &allocator = json.GetAllocator();

    json.AddMember("id", id, allocator);
    json.AddMember("result", result, allocator);

    sendMessage(json);
}

void sendError (int code, const string &message) {
    Document json;
//    auto &allocator = json.GetAllocator();
//
//    json.AddMember("code", code, allocator);
//    json.AddMember("message", message, allocator);

    sendMessage(json);
}

void sendRequest (const int id, const string &method, Value &params) {
    Document json;
//    auto &allocator = json.GetAllocator();
//
//    json.AddMember("id", id, allocator);
//    json.AddMember("method", method, allocator);
//    json.AddMember("params", params, allocator);

    sendMessage(json);
}

void sendNotification (const string &method, Value &params) {
    Document json;
//    auto &allocator = json.GetAllocator();
//
//    json.AddMember("method", method, allocator);
//    json.AddMember("params", params, allocator);

    sendMessage(json);
}

//void sendMessage (Document &message) {
//    message.AddMember("jsonrpc", "2.0", message.GetAllocator());
//
//    StringBuffer buffer;
//    Writer<StringBuffer> writer (buffer);
//    message.Accept(writer);
//
//    std::cout
//            << "Content-Length: "
//            << buffer.GetLength()
//            << "\r\n\r\n"
//            << buffer.GetString();
//    std::cout.flush();
//}

void awaitInitializeRequest () {

}

void handleMessage (Document &message) {

}

void startServerListening () {
    awaitInitializeRequest();

    while (true) {
        Document message = getMessage();
        handleMessage(message);

        if (message == "foo") break;
    }
}
