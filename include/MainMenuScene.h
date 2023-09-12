//
// Created by grump on 09/09/2023.
//

#ifndef GOMOKUDDAI_MAINMENUSCENE_H
#define GOMOKUDDAI_MAINMENUSCENE_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class MainMenuScene : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuScene(QWidget *parent = nullptr);

private:
    QVBoxLayout *mLayout;
    QPushButton *mButtonPlay;
    QPushButton *mButtonConsole;
    QPushButton *mButtonQuit;

signals:
    void requestedMainGameScene();

public slots:
    static void startConsole();
};

#endif // GOMOKUDDAI_MAINMENUSCENE_H
