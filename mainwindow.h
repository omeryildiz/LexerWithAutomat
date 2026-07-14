#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "lexer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QCloseEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_actionNew_triggered();
    void on_actionA_triggered();
    void on_actionKaydet_triggered();
    void on_actionFarkl_Kaydet_triggered();
    void on_actionYap_t_r_triggered();
    void on_actionKopyala_triggered();
    void on_actionGeri_Al_triggered();
    void on_action_leri_Al_triggered();
    void on_actionLexical_Analiz_Yap_triggered();
    void on_actionGeli_tirici_triggered();
    void on_actionKes_triggered();
    void on_actionYazd_r_triggered();
    void on_action_kt_Penceresini_Temizle_triggered();

private:
    bool maybeSaveChanges();
    bool save();
    bool saveAs();
    bool loadFile(const QString &filePath);
    bool saveFile(const QString &filePath);
    void resetDocument();
    void updateWindowTitle();
    void showAnalysis(const Lexer::Result &result);

    Ui::MainWindow *ui;
    QString mFileName;
    Lexer mLexer;
};

#endif // MAINWINDOW_H
