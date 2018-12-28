#ifndef LANGUAGESERVER_TOOLS_IOMONITOR_H
#define LANGUAGESERVER_TOOLS_IOMONITOR_H

#include <functional>
#include <unordered_map>

#include "library.h"

/*  LSP Message protocol:
 *
 * Message:
 *  - jsonrpc: "2.0"
 *
 * Request <- Message:
 *  - id: number | string
 *  - method: string
 *  - params: Value
 *
 * ResponseMessage <- Message:
 *  - id: number | string | null
 *  - result?: Value | null
 *  - error?: { code: number, message: string, data?: Value }
 *
 * Notification <- Message:
 *  - method: string
 *  - params: Value
 */

// Method naming conventions:
// "onRequest" from client, needs response
// "onNotif" from client, no response
// "notif" sent from server, no response
// "request" sent from server, will get response

class IOmonitor {
    typedef void (IOmonitor::*IOrequest)(Id &id, Value &params);
    typedef void (IOmonitor::*IOnotif)(Value &params);

private:
    bool shutdownRequestReceived { false };
    void _onRequestShutdown(Id &id, Value &params);
    void _handleExitNotif (Value &params);

public:
    // Generic handlers, can be overridden but don't need to be
    virtual void handleMessage (Document &message);
    virtual void handleInvalidMessage (Document &message);

    virtual void handleNotification (Document &message);
    virtual void handleRequest (Document &message);
    virtual void handleResponse (Document &message);

    // "Core" events. All must be defined.
    virtual void onRequestGeneric (Id &id, string &method, Value &params) = 0;
    virtual void onNotifGeneric (string &method, Value &params) = 0;

    virtual void onRequestShutdown (Id &id);
    virtual void onRequestWorkspaceSymbol (Id &id, Value &params) = 0;
    virtual void onRequestExecuteCommand (Id &id, Value &params) = 0;
    virtual void onRequestWillSaveWaitUntil (Id &id, Value &params) = 0;
    virtual void onRequestCompletion (Id &id, Value &params) = 0;
    virtual void onRequestCompletionItemResolve (Id &id, Value &params) = 0;
    virtual void onRequestHover (Id &id, Value &params) = 0;
    virtual void onRequestSignature (Id &id, Value &params) = 0;
    virtual void onRequestGotoDeclaration (Id &id, Value &params) = 0;
    virtual void onRequestGotoDefinition (Id &id, Value &params) = 0;
    virtual void onRequestGotoTypeDefinition (Id &id, Value &params) = 0;
    virtual void onRequestGotoImplementation (Id &id, Value &params) = 0;
    virtual void onRequestFindReferences (Id &id, Value &params) = 0;
    virtual void onRequestDocumentHighlight (Id &id, Value &params) = 0;
    virtual void onRequestDocumentSymbol (Id &id, Value &params) = 0;
    virtual void onRequestCodeAction (Id &id, Value &params) = 0;
    virtual void onRequestCodeLens (Id &id, Value &params) = 0;
    virtual void onRequestCodeLensResolve (Id &id, Value &params) = 0;
    virtual void onRequestDocumentLink (Id &id, Value &params) = 0;
    virtual void onRequestDocumentLinkResolve (Id &id, Value &params) = 0;
    virtual void onRequestDocumentColor (Id &id, Value &params) = 0;
    virtual void onRequestColorPresentation (Id &id, Value &params) = 0;
    virtual void onRequestFormatting (Id &id, Value &params) = 0;
    virtual void onRequestOnTypeFormatting (Id &id, Value &params) = 0;
    virtual void onRequestRename (Id &id, Value &params) = 0;
    virtual void onRequestPrepareRename (Id &id, Value &params) = 0;
    virtual void onRequestFoldingRange (Id &id, Value &params) = 0;

    // Notifications need no response, so don't need to redefine
    virtual void onNotifExit ();
    virtual void onNotifInitialized (Value &params);
    virtual void onNotifCancelRequest (Value &params);
    virtual void onNotifDidChangeWorkspaceFolders (Value &params);
    virtual void onNotifDidChangeConfiguration (Value &params);
    virtual void onNotifDidChangeWatchedFiles (Value &params);
    virtual void onNotifDidOpenTextDocument (Value &params);
    virtual void onNotifDidChangeTextDocument (Value &params);
    virtual void onNotifWillSaveTextDocument (Value &params);
    virtual void onNotifDidSaveTextDocument (Value &params);
    virtual void onNotifDidCloseTextDocument (Value &params);

    virtual void requestShowMessage (ShowMessageRequestParams &params);
    virtual void requestWorkspaceFolders ();
    virtual void requestWorkspaceConfiguration (vector<ConfigurationItem> items);
    virtual void requestEdit (string &label, WorkspaceEdit &edit);

    virtual void notifShowMessage (MessageType type, string &message);
    virtual void notifLogMessage (MessageType type, string &message);
    virtual void notifTelemetry (Value &params);
    virtual void notifPublishDiagnostics (Value &params);

    std::unordered_map<string, IOrequest> requestHandlers {
            {"shutdown",                        &IOmonitor::_onRequestShutdown},
            {"workspace/symbol",                &IOmonitor::onRequestWorkspaceSymbol},
            {"workspace/executeCommand",        &IOmonitor::onRequestExecuteCommand},
            {"textDocument/willSaveWaitUntil",  &IOmonitor::onRequestWillSaveWaitUntil},
            {"textDocument/willSaveWaitUntil",  &IOmonitor::onRequestWillSaveWaitUntil},
            {"textDocument/completion",         &IOmonitor::onRequestCompletion},
            {"completionItem/resolve",          &IOmonitor::onRequestCompletionItemResolve},
            {"textDocument/hover",              &IOmonitor::onRequestHover},
            {"textDocument/signatureHelp",      &IOmonitor::onRequestSignature},
            {"textDocument/declaration",        &IOmonitor::onRequestGotoDeclaration},
            {"textDocument/definition",         &IOmonitor::onRequestGotoDefinition},
            {"textDocument/typeDefinition",     &IOmonitor::onRequestGotoTypeDefinition},
            {"textDocument/implementation",     &IOmonitor::onRequestGotoImplementation},
            {"textDocument/references",         &IOmonitor::onRequestFindReferences},
            {"textDocument/documentHighlight",  &IOmonitor::onRequestDocumentHighlight},
            {"textDocument/documentSymbol",     &IOmonitor::onRequestDocumentSymbol},
            {"textDocument/codeAction",         &IOmonitor::onRequestCodeAction},
            {"textDocument/codeLens",           &IOmonitor::onRequestCodeLens},
            {"codeLens/resolve",                &IOmonitor::onRequestCodeLensResolve},
            {"textDocument/documentLink",       &IOmonitor::onRequestDocumentLink},
            {"documentLink/resolve",            &IOmonitor::onRequestDocumentLinkResolve},
            {"textDocument/documentColor",      &IOmonitor::onRequestDocumentColor},
            {"textDocument/colorPresentation",  &IOmonitor::onRequestColorPresentation},
            {"textDocument/formatting",         &IOmonitor::onRequestFormatting},
            {"textDocument/onTypeFormatting",   &IOmonitor::onRequestOnTypeFormatting},
            {"textDocument/rename",             &IOmonitor::onRequestRename},
            {"textDocument/prepareRename",      &IOmonitor::onRequestPrepareRename},
            {"textDocument/foldingRange",       &IOmonitor::onRequestFoldingRange},
    };

    std::unordered_map<string, IOnotif> notifHandlers {
            {"exit",                                &IOmonitor::_handleExitNotif},
            {"$/cancelRequest",                     &IOmonitor::onNotifCancelRequest},
            {"initialized",                         &IOmonitor::onNotifInitialized},
            {"workspace/didChangeWorkspaceFolders", &IOmonitor::onNotifDidChangeWorkspaceFolders},
            {"workspace/didChangeConfiguration",    &IOmonitor::onNotifDidChangeConfiguration},
            {"workspace/didChangeWatchedFiles",     &IOmonitor::onNotifDidChangeWatchedFiles},
            {"textDocument/didOpen",                &IOmonitor::onNotifDidOpenTextDocument},
            {"textDocument/didChange",              &IOmonitor::onNotifDidChangeTextDocument},
            {"textDocument/willSave",               &IOmonitor::onNotifWillSaveTextDocument},
            {"textDocument/didSave",                &IOmonitor::onNotifDidSaveTextDocument},
            {"textDocument/didClose",               &IOmonitor::onNotifDidCloseTextDocument},
    };

    std::unordered_map<string, std::function<void(Value &message)>> responseHandlers {

    };
};

#endif //LANGUAGESERVER_TOOLS_IOMONITOR_H
