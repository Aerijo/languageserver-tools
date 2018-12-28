#include "IOmonitor.h"

string getMessageMethod (Document &message) {
    return "";
}

void IOmonitor::handleMessage (Document &message) {
    string method = getMessageMethod(message);

    if (method.empty()) handleInvalidMessage(message);
}

void IOmonitor::handleInvalidMessage (Document &message) {

}

void IOmonitor::handleNotification (Document &message) {}

void IOmonitor::handleRequest (Document &message) {}

void IOmonitor::handleResponse (Document &message) {}

void IOmonitor::onRequestGeneric (Id &id, string &method, Value &params) {
    // respond with error "unhandled"
}

void IOmonitor::onNotifGeneric(string &method, Value &params) {}

void IOmonitor::_onRequestShutdown(Id &id, Value &params) {
    onRequestShutdown(id);
}

void IOmonitor::onRequestShutdown (Id &id) {
    shutdownRequestReceived = true;
}

void IOmonitor::_handleExitNotif (Value &params) {
    onNotifExit();
}

void IOmonitor::onNotifExit () {
    exit(shutdownRequestReceived ? 0 : 1);
}

void IOmonitor::onNotifCancelRequest (Value &params) {}

void IOmonitor::onNotifInitialized (Value &params) {}

void IOmonitor::notifShowMessage (MessageType type, string &message) {
    const string method = "window/showMessage";
}

void IOmonitor::notifLogMessage (MessageType type, string &message) {
    const string method = "window/logMessage";
}

void IOmonitor::requestShowMessage (ShowMessageRequestParams &params) {
    const string method = "window/showMessageRequest";
}

void IOmonitor::notifTelemetry(Value &params) {
    const string method = "telemetry/event";
}

void IOmonitor::requestWorkspaceFolders () {
    const string method = "workspace/workspaceFolders";
}

void IOmonitor::requestWorkspaceConfiguration (vector<ConfigurationItem> items) {
    const string method = "requestWorkspaceConfiguration";
}

void IOmonitor::onNotifDidChangeWorkspaceFolders (Value &params) {}

void IOmonitor::onNotifDidChangeConfiguration (Value &params) {}

void IOmonitor::onNotifDidChangeWatchedFiles (Value &params) {}

void IOmonitor::_onRequestWorkspaceSymbol (Id &id, Value &params) {
    string query = params["query"].GetString();
    onRequestWorkspaceSymbol(id, query);
}

void IOmonitor::requestEdit (string &label, WorkspaceEdit &edit) {}

void IOmonitor::onNotifDidOpenTextDocument (Value &params) {}

void IOmonitor::onNotifDidChangeTextDocument (Value &params) {}

void IOmonitor::onNotifWillSaveTextDocument (Value &params) {}

void IOmonitor::onNotifDidSaveTextDocument (Value &params) {}

void IOmonitor::onNotifDidCloseTextDocument (Value &params) {}

void IOmonitor::notifPublishDiagnostics (Value &params) {
    const string method = "textDocument/publishDiagnostics";
}
