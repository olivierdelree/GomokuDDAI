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

    int intersectionCoordinates[2]{ -1, -1 };
    auto mouseCoordinates = event->pos();

    int farLimit = mMargin + ((mAxisCount - 1) * mAxisSpacing);
    for (int i{ 0 }, xIntersection{ mMargin }; xIntersection < farLimit + 1; i++, xIntersection = xIntersection + mAxisSpacing) {
        for (int j{ 0 }, yIntersection{ mMargin }; yIntersection < farLimit + 1; j++, yIntersection = yIntersection + mAxisSpacing) {
            if (std::pow((mouseCoordinates.x() - xIntersection), 2) + std::pow((mouseCoordinates.y() - yIntersection), 2) <= std::pow(mStoneRadius, 2)) {
                intersectionCoordinates[0] = i;
                intersectionCoordinates[1] = j;
            }
        }
    }

    // The click wasn't on an intersection
    if (intersectionCoordinates[0] == -1)
        return;

    intersectionCoordinates[0] = mMargin + intersectionCoordinates[0] * 50;
    intersectionCoordinates[1] = mMargin + intersectionCoordinates[1] * 50;
    QPoint stoneCoordinates(intersectionCoordinates[0], intersectionCoordinates[1]);

    bool spotIsFree{ true };
    for (int i{ 0 }; i < mStoneCoordinates.count(); i++) {
        if (stoneCoordinates == mStoneCoordinates[i]) {
            spotIsFree = false;
            break;
        }
    }
    if (spotIsFree) {
        mStoneCoordinates.push_back(stoneCoordinates);
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

    int farLimit = mMargin + ((mAxisCount - 1) * mAxisSpacing);
    for (int i{ mMargin }; i < farLimit + 1; i = i + mAxisSpacing) {
        auto axisText = QString::number((i - mMargin) / mAxisSpacing);
        auto axisTextTightBoundingRect = axisFontMetrics.tightBoundingRect(axisText);

        // Vertical axes
        painter.drawLine(i, mMargin, i, farLimit);
        axisTextTightBoundingRect.moveCenter(QPoint(i, (mMargin / 3)));
        painter.drawText(axisTextTightBoundingRect, Qt::AlignCenter | Qt::TextDontClip, axisText);

        // Horizontal axes
        painter.drawLine(mMargin, i, farLimit, i);
        axisTextTightBoundingRect.moveCenter(QPoint((mMargin / 3), i));
        painter.drawText(axisTextTightBoundingRect, Qt::AlignCenter | Qt::TextDontClip, axisText);
    }

    int currentPlayerId = 1;
    for (auto point : mStoneCoordinates) {
        QPoint topLeft(point.x() - (int)mStoneRadius, point.y() - (int)mStoneRadius);
        auto *currentSprite = currentPlayerId == 1 ? &mBlackStone : &mWhiteStone;
        painter.drawImage(topLeft, *currentSprite);
        currentPlayerId = -currentPlayerId;
    }
}
