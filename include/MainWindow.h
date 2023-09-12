//
// Created by grump on 09/09/2023.
//

#ifndef GOMOKUDDAI_MAINWINDOW_H
#define GOMOKUDDAI_MAINWINDOW_H

#include "MainGameScene.h"
#include "MainMenuScene.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void activateMainMenuScene();
    void activateMainGameScene();
};

#endif // GOMOKUDDAI_MAINWINDOW_H
