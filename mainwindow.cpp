#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrinter>
#include <QSaveFile>
#include <QStringList>
#include <QStatusBar>
#include <QTextDocument>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->setAcceptRichText(false);
    ui->textBrowser->setOpenExternalLinks(false);

    connect(ui->textEdit->document(), &QTextDocument::modificationChanged, this, [this](bool) {
        updateWindowTitle();
    });

    resetDocument();
    resize(960, 720);
    statusBar()->showMessage(tr("Ready"), 3000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSaveChanges()) {
        event->accept();
        return;
    }

    event->ignore();
}

void MainWindow::on_actionNew_triggered()
{
    if (!maybeSaveChanges()) {
        return;
    }

    resetDocument();
    statusBar()->showMessage(tr("New document created."), 3000);
}

void MainWindow::on_actionA_triggered()
{
    if (!maybeSaveChanges()) {
        return;
    }

    const QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Open source file"),
        QString(),
        tr("Source files (*.txt *.c *.cc *.cpp *.h *.hpp);;All files (*)"));

    if (!filePath.isEmpty()) {
        loadFile(filePath);
    }
}

void MainWindow::on_actionKaydet_triggered()
{
    save();
}

void MainWindow::on_actionFarkl_Kaydet_triggered()
{
    saveAs();
}

void MainWindow::on_actionYap_t_r_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionKopyala_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionGeri_Al_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_action_leri_Al_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionLexical_Analiz_Yap_triggered()
{
    const Lexer::Result result = mLexer.tokenize(ui->textEdit->toPlainText());
    showAnalysis(result);
    statusBar()->showMessage(
        tr("Analysis completed: %1 tokens, %2 errors.")
            .arg(result.tokens.size())
            .arg(result.errors.size()),
        5000);
}

void MainWindow::on_actionGeli_tirici_triggered()
{
    QMessageBox::about(
        this,
        tr("About"),
        tr("LexerWithAutomat is an educational lexer workbench for tokenizing a small language.\n"
           "Original concept by Omer Yildiz, modernized for current Qt toolchains."));
}

void MainWindow::on_actionKes_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionYazd_r_triggered()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(tr("Print document"));

    if (ui->textEdit->textCursor().hasSelection()) {
        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    }

    if (dialog.exec() == QDialog::Accepted) {
        ui->textEdit->print(&printer);
    }
}

void MainWindow::on_action_kt_Penceresini_Temizle_triggered()
{
    ui->textBrowser->clear();
    statusBar()->showMessage(tr("Analysis output cleared."), 3000);
}

bool MainWindow::maybeSaveChanges()
{
    if (!ui->textEdit->document()->isModified()) {
        return true;
    }

    const QMessageBox::StandardButton choice = QMessageBox::warning(
        this,
        tr("Unsaved changes"),
        tr("The current document has unsaved changes. Do you want to save them?"),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    switch (choice) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Discard:
        return true;
    case QMessageBox::Cancel:
    default:
        return false;
    }
}

bool MainWindow::save()
{
    if (mFileName.isEmpty()) {
        return saveAs();
    }

    return saveFile(mFileName);
}

bool MainWindow::saveAs()
{
    const QString filePath = QFileDialog::getSaveFileName(
        this,
        tr("Save document as"),
        mFileName.isEmpty() ? QStringLiteral("source.txt") : mFileName,
        tr("Source files (*.txt *.c *.cc *.cpp *.h *.hpp);;All files (*)"));

    if (filePath.isEmpty()) {
        return false;
    }

    return saveFile(filePath);
}

bool MainWindow::loadFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::critical(
            this,
            tr("Open failed"),
            tr("The file could not be opened:\n%1").arg(file.errorString()));
        return false;
    }

    QTextStream input(&file);
    ui->textEdit->setPlainText(input.readAll());
    ui->textEdit->document()->setModified(false);
    ui->textBrowser->clear();
    mFileName = filePath;
    updateWindowTitle();
    statusBar()->showMessage(tr("Loaded %1").arg(QFileInfo(filePath).fileName()), 3000);
    return true;
}

bool MainWindow::saveFile(const QString &filePath)
{
    QSaveFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::critical(
            this,
            tr("Save failed"),
            tr("The file could not be written:\n%1").arg(file.errorString()));
        return false;
    }

    QTextStream output(&file);
    output << ui->textEdit->toPlainText();

    if (!file.commit()) {
        QMessageBox::critical(
            this,
            tr("Save failed"),
            tr("The file could not be finalized:\n%1").arg(file.errorString()));
        return false;
    }

    mFileName = filePath;
    ui->textEdit->document()->setModified(false);
    updateWindowTitle();
    statusBar()->showMessage(tr("Saved %1").arg(QFileInfo(filePath).fileName()), 3000);
    return true;
}

void MainWindow::resetDocument()
{
    mFileName.clear();
    ui->textEdit->clear();
    ui->textBrowser->clear();
    ui->textEdit->document()->setModified(false);
    updateWindowTitle();
}

void MainWindow::updateWindowTitle()
{
    const QString fileLabel = mFileName.isEmpty()
        ? tr("Untitled")
        : QFileInfo(mFileName).fileName();
    const QString modifiedSuffix = ui->textEdit->document()->isModified()
        ? QStringLiteral("*")
        : QString();

    setWindowTitle(tr("%1%2 - LexerWithAutomat").arg(fileLabel, modifiedSuffix));
}

void MainWindow::showAnalysis(const Lexer::Result &result)
{
    QStringList lines;
    lines.reserve(result.tokens.size() + result.errors.size() + 4);
    lines << tr("Tokens: %1").arg(result.tokens.size());

    if (result.tokens.isEmpty()) {
        lines << tr("No tokens found.");
    } else {
        for (const Lexer::Token &token : result.tokens) {
            lines << tr("[%1:%2] %3 -> %4")
                         .arg(token.line)
                         .arg(token.column)
                         .arg(Lexer::tokenTypeToString(token.type), token.lexeme);
        }
    }

    lines << QString();
    lines << tr("Errors: %1").arg(result.errors.size());

    if (result.errors.isEmpty()) {
        lines << tr("No lexical errors.");
    } else {
        for (const Lexer::Error &error : result.errors) {
            lines << tr("[%1:%2] %3")
                         .arg(error.line)
                         .arg(error.column)
                         .arg(error.message);
        }
    }

    ui->textBrowser->setPlainText(lines.join(QChar('\n')));
}
