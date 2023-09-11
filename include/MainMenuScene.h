//
// Created by grump on 09/09/2023.
//

#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class MainMenuScene : public QWidget {
    Q_OBJECT

private:
    QVBoxLayout* m_layout;
    QPushButton* m_button_play;
    QPushButton* m_button_settings;
    QPushButton* m_button_quit;

signals:
    void requestedMainGameScene();
    void requestedMainSettingsScene();

public:
    explicit MainMenuScene(QWidget* parent = nullptr);
};