#ifndef LANGUAGESERVER_TOOLS_IOTHREADS_H
#define LANGUAGESERVER_TOOLS_IOTHREADS_H

#include <thread>

std::thread launchStdinLoop ();

std::thread launchStdoutLoop ();

#endif //LANGUAGESERVER_TOOLS_IOTHREADS_H
