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
    m_stone_radius = m_axis_spacing / 2.5;

    m_black_stone = m_black_stone.scaled(2 * (int)m_stone_radius, 2 * (int)m_stone_radius);
    m_white_stone = m_white_stone.scaled(2 * (int)m_stone_radius, 2 * (int)m_stone_radius);
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
    QPoint stone_coordinates(intersection_coordinates[0], intersection_coordinates[1]);

    bool spot_is_free { true };
    for (int i { 0 }; i < m_stone_coordinates.count(); i++) {
        if (stone_coordinates == m_stone_coordinates[i]) {
            spot_is_free = false;
            break;
        }
    }
    if (spot_is_free) {
        m_stone_coordinates.push_back(stone_coordinates);
        QWidget::repaint();
    }
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

    int current_player_id = 1;
    for (auto point: m_stone_coordinates) {
        QPoint top_left(point.x() - (int)m_stone_radius, point.y() - (int)m_stone_radius);
        auto* current_sprite = current_player_id == 1 ? &m_black_stone : &m_white_stone;
        painter.drawImage(top_left, *current_sprite);
        current_player_id = -current_player_id;
    }
}
