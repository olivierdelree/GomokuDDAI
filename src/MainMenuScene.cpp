//
// Created by grump on 09/09/2023.
//

#include "MainMenuScene.h"
#include <QApplication>
#include <QtGui>

#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 50

MainMenuScene::MainMenuScene(QWidget *parent)
    : QWidget(parent),
      mLayout(new QVBoxLayout(this)),
      mButtonPlay(new QPushButton("Play")),
      mButtonConsole(new QPushButton("Console")),
      mButtonQuit(new QPushButton("Quit"))
{
    mLayout->setAlignment(Qt::AlignCenter);
    mLayout->setSpacing(50);

    mButtonPlay->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    mButtonConsole->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    mButtonQuit->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);

    mLayout->addWidget(mButtonPlay, Qt::AlignHCenter);
    mLayout->addWidget(mButtonConsole, Qt::AlignHCenter);
    mLayout->addWidget(mButtonQuit, Qt::AlignHCenter);

    connect(mButtonPlay, SIGNAL(clicked()), this, SIGNAL(requestedMainGameScene()));
    connect(mButtonConsole, SIGNAL(clicked()), this, SLOT(startConsole()));
    connect(mButtonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

// Source (adapted): https://stackoverflow.com/a/20733453
void MainMenuScene::startConsole()
{
    // When working with CLion on Windows, prints to std::cout do not work.
    // Instead, launching a separate console allows for printing.
    AllocConsole();
    FILE *pFileCon = nullptr;
    pFileCon = freopen("CONOUT$", "w", stdout);
}
