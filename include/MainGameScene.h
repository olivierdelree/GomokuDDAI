//
// Created by grump on 09/09/2023.
//

#ifndef GOMOKUDDAI_MAINGAMESCENE_H
#define GOMOKUDDAI_MAINGAMESCENE_H

#include <QImage>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>
#include <QWidget>

class MainGameScene : public QWidget
{
    Q_OBJECT

public:
    explicit MainGameScene(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int mMargin{ 50 };
    int mAxisCount{ 15 };
    int mAxisSpacing;
    double mStoneRadius;

    QList<QPoint> mStoneCoordinates{};
    QImage mBlackStone{ QString("../assets/black_piece_sprite.png") };
    QImage mWhiteStone{ QString("../assets/white_piece_sprite.png") };

signals:
    void requestedMainMenuScene();

public slots:
    void keyPressEvent(QKeyEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
};

#endif // GOMOKUDDAI_MAINGAMESCENE_H
