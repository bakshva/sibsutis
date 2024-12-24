#include "tPoint.hpp"
#include <cstdlib>
#include <ctime>

// Конструктор по умолчанию
tPoint::tPoint()
{
    radius = 3.0f;
    x = static_cast<float>(rand() % 800);                        // случайная координата по x (в пределах экрана)
    y = static_cast<float>(rand() % 600);                        // случайная координата по y (в пределах экрана)
    dx = static_cast<float>((rand() % 5) - 2);                   // случайная скорость по x
    dy = static_cast<float>((rand() % 5) - 2);                   // случайная скорость по y
    color = sf::Color(rand() % 255, rand() % 255, rand() % 255); // случайный цвет
}

// Конструктор с параметрами
tPoint::tPoint(float x, float y, sf::Color color) : x(x), y(y), color(color)
{
    radius = 3.0f;
    dx = static_cast<float>((rand() % 5) - 2); // случайная скорость по x
    dy = static_cast<float>((rand() % 5) - 2); // случайная скорость по y
}

// Получение координат точки
float tPoint::getX() const
{
    return x;
}

float tPoint::getY() const
{
    return y;
}

// Установка координат точки
void tPoint::setPosition(float newX, float newY)
{
    x = newX;
    y = newY;
}

// Метод для прямолинейного движения с отражением от стенок
void tPoint::moveLinear(float screenWidth, float screenHeight)
{
    x += dx;
    y += dy;

    // Проверка на столкновение со стенками
    if (x <= 0 || x >= screenWidth)
    {
        dx = -dx; // отражение по x
    }
    if (y <= 0 || y >= screenHeight)
    {
        dy = -dy; // отражение по y
    }
}

// Метод для случайного движения с отражением
void tPoint::moveRandom(float screenWidth, float screenHeight)
{
    x += dx;
    y += dy;

    // Проверка на столкновение со стенками
    if (x <= 0 || x >= screenWidth)
    {
        dx = static_cast<float>((rand() % 5) - 2); // новое случайное направление по x
    }
    if (y <= 0 || y >= screenHeight)
    {
        dy = static_cast<float>((rand() % 5) - 2); // новое случайное направление по y
    }
}

// Метод для рисования точки
void tPoint::draw(sf::RenderWindow &window)
{
    sf::CircleShape point(radius);
    point.setPosition(x, y);
    point.setFillColor(color);
    window.draw(point);
}
