#include "mainview.h"
#include "ui_mainview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QFile>

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);

    loadPhrases();

    auto vlmain= new QVBoxLayout(ui->centralWidget);


    auto hlmain= new QHBoxLayout();

    vlmain->addLayout(hlmain);

    auto newPhraseBtn= new QPushButton();

    newPhraseBtn->setText("New Phrase");

    connect(newPhraseBtn,
            &QPushButton::clicked,
            this,
            &MainView::onClick);

    hlmain->addWidget(newPhraseBtn);

    displayPhrase = new QLabel();
    vlmain->addWidget(displayPhrase);

    displayPhrase->setText("LOOK");



}

MainView::~MainView()
{
    delete ui;
}

void MainView::onClick()
{
    displayPhrase->setText(phrases[qrand() % phrases.size()]);
}

void MainView::loadPhrases()
{
    QFile iFile(":/text/hangman.txt");

    if(!iFile.open(QIODevice::ReadOnly | QIODevice::Text)){

        qWarning() << "Error opening file e\n";
        exit(EXIT_FAILURE);
    }

    QTextStream in(&iFile);
    QString line = in.readLine();

    while(!in.atEnd()){

        phrases.push_back(line);
        line=in.readLine();
    }

    iFile.close();
}
