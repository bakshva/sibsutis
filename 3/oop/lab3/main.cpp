#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "tPoint.hpp"
#include <vector>
#include <iostream> // Для вывода отладочных сообщений
#include <cstdlib>
#include <ctime>

int main()
{
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(0)));

    // Попробуем отловить возможные ошибки
    try
    {
        // Создаем окно SFML
        sf::RenderWindow window(sf::VideoMode(800, 600), "Random Points");

        // Создаем массив точек
        std::vector<tPoint> points;
        for (int i = 0; i < 100; ++i)
        {
            points.push_back(tPoint());
        }

        // Главный цикл программы
        while (window.isOpen())
        {
            // Обрабатываем события
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            // Очищаем окно
            window.clear();

            // Обновляем и рисуем каждую точку
            for (auto &point : points)
            {
                point.moveLinear(800.0f, 600.0f); // Прямолинейное движение с отражением
                point.draw(window);               // Рисуем точку
            }

            // Отображаем содержимое окна
            window.display();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
