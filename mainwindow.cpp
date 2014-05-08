#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setCentralWidget(ui->textBrowser);
    //this->setCentralWidget(ui->textEdit);
    this->setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{

    mFileName = "";
    ui->textEdit->setPlainText("");

}

void MainWindow::on_actionA_triggered()
{
    QString file = QFileDialog::getOpenFileName(this,trUtf8("Dosya Seç..."));

    if(!file.isEmpty())
    {
        QFile sFile(file);

        if(sFile.open(QFile::ReadOnly | QFile::Text))
        {

            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();
            ui->textEdit->setPlainText(text);
        }


    }

}

void MainWindow::on_actionKaydet_triggered()
{

    if(mFileName.isEmpty()){
        on_actionFarkl_Kaydet_triggered();


    }

    QFile sFile(mFileName);

        if(sFile.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&sFile);
            out << ui->textEdit->toPlainText();
            sFile.flush();
            sFile.close();


        }






}

void MainWindow::on_actionFarkl_Kaydet_triggered()
{
    QString file = QFileDialog::getSaveFileName(this,trUtf8("Dosya Seç||İsim Belirle"));

    if(!file.isEmpty())
    {
        mFileName = file;
        on_actionKaydet_triggered();


    }


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
int MainWindow::scan(QChar grText)
{
    if(grText.isDigit())
        return 6;


    char tempChar = grText.toAscii();
    printf("Gönderilen karakter %c\n",tempChar);


            switch (tempChar) {
        case '(':
            return 0;
            break;
        case ')':
            return 1;
            break;
        case '{':
            return 2;
            break;
        case '}':
            return 3;
            break;
        case '+':
            return 4;
            break;
        case '-':
            return 5;
            break;
        case 'i':
            return 7;
            break;
        case 'f':
            return 8;
            break;
        case 'w':
            return 10;
            break;
        case 'h':
            return 11;
            break;

            case 'l':
                return 12;
                break;
            case 'e':
                return 13;
                break;

            case 's':
                return 14;
                break;
            case '.':
                return 15;
                break;
            case '=':
                return 16;
                break;
            case ';':
                return 17;
                break;
            case '<':
                return 18;
                break;
            case '>':
                return 19;
                break;
            case 'n':
                return 20;
                break;
            case 't':
                return 21;
                break;
            case ' ': case '\n': case '\t':
                return 22;
                break;

        default:
            break;
    }
            if(grText.isLetter())
                return 9;

}


void MainWindow::on_actionLexical_Analiz_Yap_triggered()
{
    struct token_t token;

    //todo: ktransition tablosunu dışardan al!
    //Elle yazmak mantıklı değil
                                //1 2 3 4   5  6    7   8   9   10 11  12  13  14  15  16  17 18 19 20 21 22 23
                                //(	) {	}	+	-	dg	i	f	lt	w	h	l	e	s	.  =   ;  <  >  n  t bos
int kTransitionTable[23][23] = { {0,0,0,0,	0,	0,	14,	0,	0,	0,	0,	0,	0,	0,	0,	0, 21, 0 ,0 ,0 ,0 ,0,9},//0
                                 {1,1,1,1,	1,	1,	1,	1,	1,	1,	1,	2,	1,	1,	1,	1, 1 , 1 ,1 ,1 ,1 ,1,9},//1
                                 {2,2,2,2,	2,	2,	2,	4,	2,	2,	2,	2,	2,	2,	2,	2, 2 ,2 ,2 ,2 ,2 ,2,9},//2
                                 {3,3,3,3,	3,	3,	3,	3,	3,	3,	3,	3,	5,	3,	3,	3, 3 ,3 ,3 ,3 ,3 ,3,9},//3
                                 {4,4,4,4,	4,	4,	4,	4,	4,	4,	4,	4,	6,	4,	4,	4, 4 ,4 ,4 ,4 ,4 ,4,9},//4
                                 {5,5,5,5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	7,	5, 5 ,5 ,5 ,5 ,5 ,5,9},//5
                                 {6,6,6,6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	12,	6,	6, 6 ,6 ,6 ,6 ,6 ,6,9},//6
                                 {7,7,7,7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	13,	7,	7, 7 ,7 ,7 ,7 ,7 ,7,9},//7
                                 {8,8,8,8,	8,	8,	8,	8,	15,	8,	8,	8,	8,	8,	8,	8, 8 ,8 ,8 ,8 ,19,8,9},//8
                              {10,10,10,10, 0,  0,	14,	8,	9,	13,	1,	9,	9,	1,	9,  9, 16,17,18,18,13,13,9},//9
                                 {9,9,9,9,	 9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,  9, 10,10,10,10,10,10,9},//10
                                {11,11,11,11,11,11,	11,	11,	11,	11,	11,	11,	11,	11,	11,11, 11,11,11,11,11,11,9},//11
                                {12,12,12,12,12,12,	12,	12,	12,	13,	12,	12,	12,	12,	12,12, 12,12,12,12,12,12,9},//12
                                 {9,9,9,	9,	9,	9,	9,	9,	13,	9,	9,	13,	9,	9,	9 ,9 ,13,13,13,13,13,13,9},//13
                                 {14,14,14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,11,14,14,14,14,14,14,9},//14
                                 {15,15,15, 15, 15, 15, 13, 15, 15, 13, 15, 15, 15, 15, 15,15,15,15,15,15,15,15,9},//15
                                 {16,16,16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,22,16,16,16,16,16,16,9},//16
                                 {17,17,17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,17,17,17,17,17,17,17,9},//17
                                 {18,18,18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,18,18,18,18,18,18,18,9},//18
                                 {19,19,19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,19,19,19,19,19,19,20,9},//19
                                 {20,20,20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,20,20,20,20,20,20,20,9},//20
                                 {21,21,21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,21,21,21,21,21,21,21,9},//21
                                 {22,22,22,	22,	22,	22,	22, 22,22 ,	22,	22,	22,	22,	22,	22,22,22,22,22,22,22,22,9} //22
                                //1  2  3    4  5    6   7   8  9   10  11  12  13  14  15 16 17 18 19 20 21 22

                               };
                           //     0      1    2    3   4     5    6       7    8    9             10           11                12          13             14        15             16                17                18            19      20                21              22
QString kAcceptTable[23] = {"TOKEN_+-","ID","ID","ID","ID","ID","ID",	"ID","ID","ID","TOKEN_BRACE_PAREN","TOKEN_FLOAT","TOKEN_WHILE","TOKEN_IDENTIFIER","DIGIT","TOKEN_IF","TOKEN_ASSIGN_MARK","TOKEN_COMMA","TOKEN_LESS_OR_BIGGER","ID","TOKEN_INT","TOKEN_MINUS_OR_PLUS","EMPTY_STRING"};

    QString str = ui->textEdit->toPlainText();
    QByteArray ba = str.toLatin1();
    char *symbol = ba.data();//Tüm metin dinamik char değişkene dönüştürülüyor.
    //QChar *inputText = ui->textEdit->toPlainText().data();
    printf("symbol = %s\n",symbol);
    QChar tempText;
    int state = 9;//başlangıç durumu ayarlamaları
    ui->textBrowser->setText("");//textbrowser ayarı
    int j = 0;
    token.val.cleanstring();

    printf("string boyutu %d\n",str.size());
    for (int i = 0; i < str.size(); i++) {

        //printf("symbol typeu\n",symbol[i]);
        printf("i=%d  j=%d\n",i,j);
        tempText = symbol[i];
        if (state == 9) {
            j = 0;
        }
        token.val.stringValue[j] = symbol[i];
        int result = scan(tempText);
        printf("scan(tempText) type = %d\n",result);
        printf("kTransitionTable[%d][%d]",state,result);
        state = kTransitionTable[state][result];
        printf("= %d\n\n",state);
        QString type = kAcceptTable[state];
        //QString qStr = QString::number(state);
        QString t_value = token.val.stringValue;


        switch (state) {
        case D_PARANTEZ:
            ui->textBrowser->insertHtml(t_value.append("-"));
            ui->textBrowser->insertHtml(type.append("<br />"));
            j=0;
            token.val.cleanstring();
            state=9;
            break;
        case D_FLOAT:
            ui->textBrowser->insertHtml(t_value.append("-"));
            ui->textBrowser->insertHtml(type.append("<br />"));
            j=0;
            token.val.cleanstring();
            state=9;
            i--;
            break;
        case D_WHILE:
            ui->textBrowser->insertHtml(t_value.append("-"));
            ui->textBrowser->insertHtml(type.append("<br />"));
            j=0;
            token.val.cleanstring();
            state=9;
            break;
        case D_IF:
            ui->textBrowser->insertHtml(t_value.append("-"));
            ui->textBrowser->insertHtml(type.append("<br />"));
            j = 0;
            token.val.cleanstring();
            state=9;
            break;
        case D_ASIGN:
            ui->textBrowser->insertHtml(t_value.append("-"));
            ui->textBrowser->insertHtml(type.append("<br />"));
            j = 0;
            token.val.cleanstring();
            state=9;
            break;
        case D_COMMA:
            ui->textBrowser->insertHtml(t_value.append("-"));
            ui->textBrowser->insertHtml(type.append("<br />"));
            j = 0;
            token.val.cleanstring();
            state=9;
            break;
        case D_ASSIGN_MP:
            ui->textBrowser->insertHtml(t_value.append("-"));
            ui->textBrowser->insertHtml(type.append("<br />"));
            j = 0;
            token.val.cleanstring();
            state=9;
            break;
        case D_LESS_BIG:
            ui->textBrowser->insertHtml(t_value.append("-"));
            ui->textBrowser->insertHtml(type.append("<br />"));
            j = 0;
            token.val.cleanstring();
            state=9;
            break;
        case D_INT:
            ui->textBrowser->insertHtml(t_value.append("-"));
            ui->textBrowser->insertHtml(type.append("<br />"));
            j = 0;
            token.val.cleanstring();
            state=9;
            break;
        case D_COMPARE:
            ui->textBrowser->insertHtml(t_value.append("-"));
            ui->textBrowser->insertHtml(type.append("<br />"));
            j = 0;
            token.val.cleanstring();
            state=9;
            break;
        case D_PLUS_MINUS:
            ui->textBrowser->insertHtml(t_value.append("-"));
            ui->textBrowser->insertHtml(type.append("<br />"));
            j = 0;
            token.val.cleanstring();
            state=9;
            break;


        case 13:
            ui->textBrowser->insertHtml(t_value.append("-"));
            ui->textBrowser->insertHtml(type.append("<br />"));
            j = 0;
            token.val.cleanstring();
            state=9;
            break;
        default:
            j++;


            break;
        }




    }


    //ui->textBrowser->setText(type.append("<br />"));
    //QMessageBox::about(this,"",type);
}






void MainWindow::on_actionGeli_tirici_triggered()
{
    QMessageBox::about(this, trUtf8("Geliştirici Hakkında"),
              trUtf8("Bu editör Ömer Yıldız tarafından eğlence için yazılmıştır." \
                     "http://www.omeryildiz.org.\n"
                     "Mail: nomeryildiz@gmail.com"));
}

void MainWindow::on_actionKes_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionYazd_r_triggered()
{
    QPrinter printer(QPrinter::HighResolution);
       QPrintDialog *dlg = new QPrintDialog(&printer, this);
       if (ui->textEdit->textCursor().hasSelection())
           dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
       dlg->setWindowTitle(trUtf8("Dökümanı Yazdır"));
       if (dlg->exec() == QDialog::Accepted) {
           ui->textEdit->print(&printer);
       }
       delete dlg;

}

void MainWindow::on_action_kt_Penceresini_Temizle_triggered()
{
    ui->textBrowser->clear();

}
