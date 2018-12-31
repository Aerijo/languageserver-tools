# languageserver-tools
Provides a clean interface between a C++ language server and it's client

## TODO

- Support https://github.com/Microsoft/language-server-protocol-inspector

## Design
The IO is entirely handled by the IOmonitor class. It will take a JSON message, add the `jsonrpc` property and header, and send it on stdout. Likewise, it will monitor stdin and receive all messages, removing the header and processing them into a RapidJSON Document before adding them to the input queue.

The input queue is a cross thread