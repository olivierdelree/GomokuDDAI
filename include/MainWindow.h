//
// Created by grump on 09/09/2023.
//

#pragma once

#include "MainGameScene.h"
#include "MainMenuScene.h"
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

public slots:
    void activateMainMenuScene();
    void activateMainGameScene();

public:
    explicit MainWindow(QWidget* parent = nullptr);
};
