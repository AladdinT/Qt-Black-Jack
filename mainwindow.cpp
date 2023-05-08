#include "mainwindow.h"
#include "ui_mainwindow.h"

std::vector <int> chosen_cards;
std::vector <int> p1_cards;
std::vector <int> p2_cards;
int p1_score = 0;
int p2_score = 0;
int p1_aces = 0;
int p2_aces = 0;
bool playAgain = false;
card myCards[52];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString mySuit;

    for(int i=0 ; i<52 ; i++)
    {
        mySuit = card::suit_str[(int)((i)/13)] ;
        myCards[i].init_card( (i%13)+1 , mySuit);
    }

    for(int i=0 ; i<52 ; i++)
    {
        qDebug() << myCards[i].whoami();
    }

    on_pushButton_playAgain_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_p1_draw_clicked()
{
    //pick a random card
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int random_card;
    do
    {
        random_card = ( std::rand() )  % 52;
        //if the card was already choosen pick another card
    }while( std::find( chosen_cards.begin(), chosen_cards.end(), random_card) != chosen_cards.end() );

    //update array of p1 drawed card
    p1_cards.push_back(random_card);
    chosen_cards.push_back(random_card);
    qDebug() << "card chosen: "<< random_card;

    //calculate p1 score
    if( myCards[random_card].getRank() < 10)
    {
        p1_score += myCards[random_card].getRank();
    }
    else
    {
        p1_score += 10;
    }

    if(myCards[random_card].getName() == "ace")
    {
        p1_aces++;
        p1_score+=10;
    }

    if(p1_aces > 0 && p1_score > 21)
    {
        p1_score-=10;
        p1_aces--;
    }
    ui->label_p1_score->setText("Score: "+QString::number(p1_score) );

    //display card
    qDebug() << myCards[random_card].whoami();
    QString path = ":/cards/"+ myCards[random_card].getSuit() + "/" + myCards[random_card].whoami() + ".png";
    QPixmap result = player1_appendCardPics(path);

    ui->label_p1->setPixmap(result);


    if(p1_score >= 21)
    {
        gameOver();
        return;
    }
    //switch to player2 turn
    ui->pushButton_p1_draw->setDisabled(1);
    ui->pushButton_p1_pass->setDisabled(1);

    ui->pushButton_p2_draw->setEnabled(1);
    ui->pushButton_p2_pass->setEnabled(1);

    ui->label_status->setText("<a style=\"color:#B22222\">Player 2 turn</a>");


}

void MainWindow::on_pushButton_p2_draw_clicked()
{
    //pick a random card
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int random_card;
    do
    {
        random_card = ( std::rand() )  % 52;
        //if the card was already choosen pick another card
    }while( std::find( chosen_cards.begin(), chosen_cards.end(), random_card) != chosen_cards.end() );

    //update array of p2 drawed card
    p2_cards.push_back(random_card);
    chosen_cards.push_back(random_card);
    qDebug() << "card chosen: "<< random_card;

    //calculate p2 score
    if( myCards[random_card].getRank() < 10)
    {
        p2_score += myCards[random_card].getRank();
    }
    else
    {
        p2_score += 10;
    }

    if(myCards[random_card].getName() == "ace")
    {
        p2_aces++;
        p2_score+=10;
    }

    if(p2_aces > 0 && p2_score > 21)
    {
        p2_score-=10;
        p2_aces--;
    }


    ui->label_p2_score->setText("Score: "+QString::number(p2_score) );


    //display card
    qDebug() << myCards[random_card].whoami();
    QString path = ":/cards/"+ myCards[random_card].getSuit() + "/" + myCards[random_card].whoami() + ".png";
    QPixmap result = player2_appendCardPics(path);

    ui->label_p2->setPixmap(result);


    if(p2_score >= 21)
    {
        gameOver();
        return;
    }
    //switch to player1 turn
    ui->pushButton_p2_draw->setDisabled(1);
    ui->pushButton_p2_pass->setDisabled(1);

    ui->pushButton_p1_draw->setEnabled(1);
    ui->pushButton_p1_pass->setEnabled(1);

    ui->label_status->setText("Player 1 turn");

}

QPixmap MainWindow::player1_appendCardPics(QString imgPath)
{
    static int indent = 0;
    QPixmap base = QPixmap::fromImage(QImage("Player1Display.png"));

    if(playAgain)
    {
        indent = 0;
        return base;
    }

    QPixmap overlay = QPixmap::fromImage(QImage(imgPath));
    QPixmap result(base.width() + 30, base.height());
    result.fill(Qt::transparent); // force alpha channel
    {
        QPainter painter(&result);
        painter.drawPixmap(0, 0, base);
        painter.drawPixmap(indent, 0, overlay);
    }

    indent += 30;

    QFile file("Player1Display.png");
    file.open(QIODevice::WriteOnly);
    result.save(&file, "png");
    return (result);
}

QPixmap MainWindow::player2_appendCardPics(QString imgPath)
{
    static int indent = 0;
    QPixmap base = QPixmap::fromImage(QImage("Player2Display.png"));
    if(playAgain)
    {
        indent = 0;
        return base;
    }
    QPixmap overlay = QPixmap::fromImage(QImage(imgPath));
    QPixmap result(base.width() + indent, base.height());
    result.fill(Qt::transparent); // force alpha channel
    {
        QPainter painter(&result);
        painter.drawPixmap(0, 0, base);
        painter.drawPixmap(indent, 0, overlay);
    }

    indent += 35;

    QFile file("Player2Display.png");
    file.open(QIODevice::WriteOnly);
    result.save(&file, "png");
    base.load("Player2Display.png");
    return (result);
}



void MainWindow::on_pushButton_p1_pass_clicked()
{
    //switch to player2 turn
    ui->pushButton_p1_draw->setDisabled(1);
    ui->pushButton_p1_pass->setDisabled(1);

    ui->pushButton_p2_draw->setEnabled(1);
    ui->pushButton_p2_pass->setEnabled(1);

    ui->label_status->setText("<a style=\"color:#B22222\">Player 2 turn</a>");
}


void MainWindow::on_pushButton_p2_pass_clicked()
{
    //switch to player1 turn
    ui->pushButton_p2_draw->setDisabled(1);
    ui->pushButton_p2_pass->setDisabled(1);

    ui->pushButton_p1_draw->setEnabled(1);
    ui->pushButton_p1_pass->setEnabled(1);

    ui->label_status->setText("Player 1 turn");
}


void MainWindow::on_pushButton_play_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
    on_pushButton_playAgain_clicked();
}

void MainWindow::gameOver(void)
{
    if(p1_score == 21 || p2_score > 21)
    {
        ui->label_status->setText("<a align=\"center\">PLAYER 1 is THE WINNER </a>");
        ui->label_p1->setStyleSheet("border-style: dashed;\
                                    border-width: 5px;\
                                    border-color: blue;\
                                    ");
    }
    else if(p2_score == 21 || p1_score > 21)
    {
        ui->label_status->setText("<a align=\"center\" style=\"color:#B22222\">PLAYER 2 is THE WINNER</a>");
        ui->label_p2->setStyleSheet("border-style: dashed;\
                                    border-width: 5px;\
                                    border-color: red;\
                                    ");
    }

    ui->pushButton_p2_draw->setDisabled(1);
    ui->pushButton_p2_pass->setDisabled(1);

    ui->pushButton_p1_draw->setDisabled(1);
    ui->pushButton_p1_pass->setDisabled(1);

    ui->pushButton_playAgain->setEnabled(1);
}


void MainWindow::on_pushButton_playAgain_clicked()
{
    playAgain = true;
    chosen_cards.clear();
    p1_cards.clear();
    p2_cards.clear();
    p1_score = 0;
    p1_aces = 0;
    p2_score = 0;
    p2_aces = 0;

    ui->pushButton_p2_draw->setEnabled(1);
    ui->pushButton_p2_pass->setEnabled(1);

    ui->pushButton_p1_draw->setEnabled(1);
    ui->pushButton_p1_pass->setEnabled(1);

    ui->label_p1_score->setText("Score: ");
    ui->label_p2_score->setText("Score: ");

    QPixmap myPix = QPixmap::fromImage(QImage(":/icons/card.png"));
    QFile file("Player1Display.png");
    file.open(QIODevice::WriteOnly);
    myPix.save(&file, "png");

    QFile file2("Player2Display.png");
    file2.open(QIODevice::WriteOnly);
    myPix.save(&file2, "png");

    ui->label_p1->setPixmap(player1_appendCardPics(""));
    ui->label_p2->setPixmap(player2_appendCardPics(""));

    ui->label_p1->setStyleSheet("");
    ui->label_p2->setStyleSheet("");

    ui->label_status->setText("Draw a Card");
    playAgain = false;
}


void MainWindow::on_pushButton_help_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(" In Blackjack, each card has a value that remains constant throughout the game.<br>\
 The goal is to beat the other player and also not bust with a 22 or more. <br>\
 Here are the cards values: <br>\
Number cards: The number is the value of the card. <br>\
Face cards: The value of face cards is 10. <br>\
Ace: Either 1 or 11. It is counted as 11 (...generally) unless it would put you over 21, in which case it counts as 1. <br>\
Therefore, an ace and a ten card are 21 in two cards, which is Blackjack/Natural. <br>\
A hand containing an ace is called soft hand ");
                     msgBox.exec();

}


void MainWindow::on_pushButton_Logo_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Projcet made by : Ahmad Alaa <br>\
                    Email: tuhami.10.8@gmail.com <br>\
                    Presented to: Dr. Mina Dawood <br>\
                    Eng. Suzan Al Garhy <br>\
                    Eng. Ramez Hosny");
    msgBox.exec();

}
