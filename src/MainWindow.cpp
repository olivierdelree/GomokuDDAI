//
// Created by grump on 09/09/2023.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 800);
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(".MainMenuScene, .MainGameScene {background-image: url(../assets/wood_texture.jpeg);}");

    activateMainMenuScene();
}

void MainWindow::activateMainMenuScene()
{
    delete this->centralWidget(); // Make sure to delete the previous scene

    setCentralWidget(new MainMenuScene(this));
    connect(centralWidget(), SIGNAL(requestedMainGameScene()), this, SLOT(activateMainGameScene()));

    centralWidget()->setAttribute(Qt::WA_StyledBackground, true); // Allow the scene to have a background
    centralWidget()->show();
}

void MainWindow::activateMainGameScene()
{
    delete centralWidget(); // Make sure to delete the previous scene

    setCentralWidget(new MainGameScene(this));
    connect(centralWidget(), SIGNAL(requestedMainMenuScene()), this, SLOT(activateMainMenuScene()));

    centralWidget()->setAttribute(Qt::WA_StyledBackground, true); // Allow the scene to have a background
    centralWidget()->setFocus();                                  // Ensure the focus is on the game to handle events through it
    centralWidget()->show();
}
