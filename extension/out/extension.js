const vscode = require("vscode");
const cp = require("child_process");

function activate(context) {
    const runCommand = vscode.commands.registerCommand("delta.runFile", () => {
        const editor = vscode.window.activeTextEditor;
        if (!editor) {
            vscode.window.showErrorMessage("No active editor.");
            return;
        }

        const filePath = editor.document.fileName;

        const terminal = vscode.window.createTerminal("Delta");
        terminal.show();
        terminal.sendText(`delta run "${filePath}"`);
    });

    context.subscriptions.push(runCommand);
}

function deactivate() {}

module.exports = { activate, deactivate };