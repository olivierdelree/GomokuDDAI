//
// Created by grump on 09/09/2023.
//

#include "MainGameScene.h"
#include <QPainter>
#include <cmath>
#include <QFont>
#include <QFontMetrics>

MainGameScene::MainGameScene(QWidget *parent) : QWidget(parent)
{
    mAxisSpacing = (parent->width() - 2 * mMargin) / (mAxisCount - 1);
    mStoneRadius = mAxisSpacing / 2.5;

    mBlackStone = mBlackStone.scaled(2 * (int)mStoneRadius, 2 * (int)mStoneRadius);
    mWhiteStone = mWhiteStone.scaled(2 * (int)mStoneRadius, 2 * (int)mStoneRadius);
}

void MainGameScene::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);

    if (event->key() == Qt::Key_Escape) {
        emit requestedMainMenuScene();
    }
}

void MainGameScene::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    int intersection_coordinates[2]{ -1, -1 };
    auto mouse_coordinates = event->pos();

    int far_limit = mMargin + ((mAxisCount - 1) * mAxisSpacing);
    for (int i{ 0 }, x_intersection{ mMargin }; x_intersection < far_limit + 1; i++, x_intersection = x_intersection + mAxisSpacing) {
        for (int j{ 0 }, y_intersection{ mMargin }; y_intersection < far_limit + 1; j++, y_intersection = y_intersection + mAxisSpacing) {
            if (std::pow((mouse_coordinates.x() - x_intersection), 2) + std::pow((mouse_coordinates.y() - y_intersection), 2) <= std::pow(mStoneRadius, 2)) {
                intersection_coordinates[0] = i;
                intersection_coordinates[1] = j;
            }
        }
    }

    // The click wasn't on an intersection
    if (intersection_coordinates[0] == -1)
        return;

    intersection_coordinates[0] = mMargin + intersection_coordinates[0] * 50;
    intersection_coordinates[1] = mMargin + intersection_coordinates[1] * 50;
    QPoint stone_coordinates(intersection_coordinates[0], intersection_coordinates[1]);

    bool spot_is_free{ true };
    for (int i{ 0 }; i < mStoneCoordinates.count(); i++) {
        if (stone_coordinates == mStoneCoordinates[i]) {
            spot_is_free = false;
            break;
        }
    }
    if (spot_is_free) {
        mStoneCoordinates.push_back(stone_coordinates);
        QWidget::repaint();
    }
}

void MainGameScene::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));

    QFont axisFont;
    axisFont.setBold(true);
    axisFont.setPixelSize(mMargin / 3);
    painter.setFont(axisFont);
    QFontMetrics axisFontMetrics{ axisFont };

    int far_limit = mMargin + ((mAxisCount - 1) * mAxisSpacing);
    for (int i{ mMargin }; i < far_limit + 1; i = i + mAxisSpacing) {
        auto axisText = QString::number((i - mMargin) / mAxisSpacing);
        auto axisTextTightBoundingRect = axisFontMetrics.tightBoundingRect(axisText);

        // Vertical axes
        painter.drawLine(i, mMargin, i, far_limit);
        axisTextTightBoundingRect.moveCenter(QPoint(i, (mMargin / 3)));
        painter.drawText(axisTextTightBoundingRect, Qt::AlignCenter | Qt::TextDontClip, axisText);

        // Horizontal axes
        painter.drawLine(mMargin, i, far_limit, i);
        axisTextTightBoundingRect.moveCenter(QPoint((mMargin / 3), i));
        painter.drawText(axisTextTightBoundingRect, Qt::AlignCenter | Qt::TextDontClip, axisText);
    }

    int current_player_id = 1;
    for (auto point : mStoneCoordinates) {
        QPoint top_left(point.x() - (int)mStoneRadius, point.y() - (int)mStoneRadius);
        auto *current_sprite = current_player_id == 1 ? &mBlackStone : &mWhiteStone;
        painter.drawImage(top_left, *current_sprite);
        current_player_id = -current_player_id;
    }
}
