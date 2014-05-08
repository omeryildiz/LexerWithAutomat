#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

#define D_PARANTEZ 10
#define D_FLOAT 11
#define D_WHILE 12
#define D_IF 15
#define D_ASIGN 16
#define D_COMMA 17
#define D_LESS_BIG 18
#define D_INT 20
#define D_ASSIGN_MP 21
#define D_COMPARE 22
#define D_PLUS_MINUS 0

struct token_t {
  int type;                // yukarıda verilen token kodlarından biri
  union {
     char stringValue[256]; // eğer string veya tanımlayıcıysa burada lexeme'i tutar
    int intValue;          // integer ise lexeme burada tutulur
    float floatValue;    // double'sa lexeme burada tutulur
    void cleanstring(){
        for (int i = 0; i < 256; i++) {
            stringValue[i] = ' ';
        }

    }
  } val;

};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
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

    int scan(QChar grText);




private:
    Ui::MainWindow *ui;
    QString mFileName;
};

#endif // MAINWINDOW_H
