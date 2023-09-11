//
// Created by grump on 09/09/2023.
//

#pragma once

#include <QImage>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>
#include <QWidget>

class MainGameScene : public QWidget {
    Q_OBJECT

private:
    int m_margin { 50 };
    int m_axis_count { 15 };
    int m_axis_spacing;
    double m_stone_radius;

    QList<QPoint> m_stone_coordinates {};
    QImage m_black_stone { QString("../assets/black_piece_sprite.png") };
    QImage m_white_stone { QString("../assets/white_piece_sprite.png") };

signals:
    void requestedMainMenuScene();

public slots:
    void keyPressEvent(QKeyEvent*) override;
    void mousePressEvent(QMouseEvent*) override;

public:
    explicit MainGameScene(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
};
