// Copyright (c) 2011-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include <config/bitcoin-config.h>
#endif

#include <qt/utilitydialog.h>

#include <qt/forms/ui_helpmessagedialog.h>

#include <qt/guiutil.h>

#include <clientversion.h>
#include <util/system.h>
#include <util/strencodings.h>

#include <cassert>
#include <stdio.h>

#include <QCloseEvent>
#include <QLabel>
#include <QMainWindow>
#include <QTextCursor>
#include <QVBoxLayout>

/** "Help message" or "About" dialog box */
HelpMessageDialog::HelpMessageDialog(QWidget* parent, bool about) :
    QDialog(parent),
    ui(new Ui::HelpMessageDialog)
{
    ui->setupUi(this);

    // Simple full version string from the core
    const QString version = QString::fromStdString(FormatFullVersion());

    if (about) {
        setWindowTitle(tr("About %1").arg(PACKAGE_NAME));

        ui->aboutMessage->setTextFormat(Qt::RichText);
        ui->aboutMessage->setOpenExternalLinks(true);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        // Keep this as the "text" used by other parts of the dialog
        text = version;

        ui->aboutMessage->setText(
            version + "<br><br>" + QStringLiteral(
                "Copyright (C) 2025 The Altcoin Core developers<br>"
                "Copyright (C) 2009-2024 The Bitcoin Core developers<br><br>"
                "Please contribute if you find Altcoin Core useful. "
                "Visit <a style=\"color:#e36a6a;\" href=\"https://altoshi.org\">https://altoshi.org</a> for further information about the software.<br>"
                "The source code is available from <a style=\"color:#e36a6a;\" href=\"https://github.com/altoshicoin/altcoin\">https://github.com/altoshicoin/altcoin</a>"
            )
        );

        QPalette pal = ui->aboutMessage->palette();
        pal.setColor(QPalette::Link, QColor("#e36a6a"));
        pal.setColor(QPalette::LinkVisited, QColor("#e36a6a"));
        ui->aboutMessage->setPalette(pal);
        ui->aboutMessage->setWordWrap(true);

        ui->helpMessage->setVisible(false);
    } else {
        setWindowTitle(tr("Altcoin Core - Command-line options"));

        const QString header = QStringLiteral("Usage:  altcoin-qt [command-line options]\n");

        // Build a simple plain-text help message instead of the old table layout
        const std::string strUsage = gArgs.GetHelpMessage();
        const QString coreOptions = QString::fromStdString(strUsage);

        text = version + "\n\n" + header + "\n" + coreOptions;

        ui->helpMessage->setPlainText(text);

        ui->scrollArea->setVisible(false);
        ui->aboutLogo->setVisible(false);
    }

    GUIUtil::handleCloseWindowShortcut(this);
}

HelpMessageDialog::~HelpMessageDialog()
{
    delete ui;
}

void HelpMessageDialog::showOrPrint()
{
    // In the Qt GUI build, just show the dialog.
    exec();
}

void HelpMessageDialog::on_okButton_accepted()
{
    close();
}

// Simple shutdown window shown while the node is shutting down.
ShutdownWindow::ShutdownWindow(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f)
{
    setWindowTitle(tr("Altcoin Core is shutting down"));

    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel(
        tr("Altcoin Core is shutting down...\n"
           "Do not shut down the computer until this window disappears."),
        this);
    label->setWordWrap(true);
    layout->addWidget(label);

    GUIUtil::handleCloseWindowShortcut(this);
}

QWidget* ShutdownWindow::showShutdownWindow(QMainWindow* window)
{
    assert(window != nullptr);

    // Show a simple window indicating shutdown status
    QWidget* shutdownWindow = new ShutdownWindow(window, Qt::Window);
    shutdownWindow->setWindowTitle(window->windowTitle());

    // Center shutdown window at where main window was
    const QPoint global = window->mapToGlobal(window->rect().center());
    shutdownWindow->move(global.x() - shutdownWindow->width() / 2,
                         global.y() - shutdownWindow->height() / 2);
    shutdownWindow->show();
    return shutdownWindow;
}

void ShutdownWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();
}

