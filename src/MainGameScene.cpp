//
// Created by grump on 09/09/2023.
//

#include "MainGameScene.h"
#include <QPainter>
#include <cmath>

MainGameScene::MainGameScene(QWidget* parent)
    : QWidget(parent)
{
    m_axis_spacing = (parent->width() - 2 * m_margin) / (m_axis_count - 1);
    m_stone_radius = m_axis_spacing / 2.3;
}

void MainGameScene::keyPressEvent(QKeyEvent* event)
{
    QWidget::keyPressEvent(event);

    if (event->key() == Qt::Key_Escape) {
        emit requestedMainMenuScene();
    }
}

void MainGameScene::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);

    int intersection_coordinates[2] { -1, -1 };
    auto mouse_coordinates = event->pos();

    int far_limit = m_margin + ((m_axis_count - 1) * m_axis_spacing);
    for (int i { 0 }, x_intersection { m_margin }; x_intersection < far_limit + 1; i++, x_intersection = x_intersection + m_axis_spacing) {
        for (int j { 0 }, y_intersection { m_margin }; y_intersection < far_limit + 1; j++, y_intersection = y_intersection + m_axis_spacing) {
            if (std::pow((mouse_coordinates.x() - x_intersection), 2) + std::pow((mouse_coordinates.y() - y_intersection), 2) <= std::pow(m_stone_radius, 2)) {
                intersection_coordinates[0] = i;
                intersection_coordinates[1] = j;
            }
        }
    }

    // The click wasn't on an intersection
    if (intersection_coordinates[0] == -1)
        return;

    intersection_coordinates[0] = m_margin + intersection_coordinates[0] * 50;
    intersection_coordinates[1] = m_margin + intersection_coordinates[1] * 50;
    m_list_of_crosses.push_back(QPoint(intersection_coordinates[0], intersection_coordinates[1]));
    QWidget::repaint();
}

void MainGameScene::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    int far_limit = m_margin + ((m_axis_count - 1) * m_axis_spacing);
    for (int i { m_margin }; i < far_limit + 1; i = i + m_axis_spacing) {
        painter.drawLine(i, m_margin, i, far_limit);
        painter.drawLine(m_margin, i, far_limit, i);
    }

    int cross_length { 25 };
    for (auto point : m_list_of_crosses) {
        QPoint top_left(point.x() - cross_length / 2, point.y() - cross_length / 2);
        QPoint bottom_right(point.x() + cross_length / 2, point.y() + cross_length / 2);
        QPoint top_right(point.x() + cross_length / 2, point.y() - cross_length / 2);
        QPoint bottom_left(point.x() - cross_length / 2, point.y() + cross_length / 2);

        painter.drawLine(top_left, bottom_right);
        painter.drawLine(top_right, bottom_left);
    }
}
