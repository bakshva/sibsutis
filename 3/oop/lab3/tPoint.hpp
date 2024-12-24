#ifndef TPOINT_HPP
#define TPOINT_HPP

#include <SFML/Graphics.hpp>

class tPoint
{
private:
    float x, y;      // Координаты точки
    float dx, dy;    // Скорости по осям
    sf::Color color; // Цвет точки
    float radius;    // Радиус точки

public:
    // Конструктор по умолчанию
    tPoint();

    // Конструктор с параметрами
    tPoint(float x, float y, sf::Color color);

    // Получение координат точки
    float getX() const;
    float getY() const;

    // Изменение координат точки
    void setPosition(float x, float y);

    // Метод для прямолинейного движения с отражением от стенок
    void moveLinear(float screenWidth, float screenHeight);

    // Метод для случайного движения с отражением
    void moveRandom(float screenWidth, float screenHeight);

    // Метод для рисования точки
    void draw(sf::RenderWindow &window);
};

#endif // TPOINT_HPP
