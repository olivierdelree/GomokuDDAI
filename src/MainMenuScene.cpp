//
// Created by grump on 09/09/2023.
//

#include "MainMenuScene.h"
#include <QApplication>

#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 50

MainMenuScene::MainMenuScene(QWidget* parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout(this))
    , m_button_play(new QPushButton("Play"))
    , m_button_quit(new QPushButton("Quit"))
{
    m_layout->setAlignment(Qt::AlignCenter);
    m_layout->setSpacing(50);

    m_button_play->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    m_button_quit->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);

    m_layout->addWidget(m_button_play, Qt::AlignHCenter);
    m_layout->addWidget(m_button_quit, Qt::AlignHCenter);

    connect(m_button_play, SIGNAL(clicked()), this, SIGNAL(requestedMainGameScene()));
    connect(m_button_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}
