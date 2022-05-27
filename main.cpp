#include <SFML/Graphics.hpp>
#include <math.h>
#include <ctype.h>
#include <iostream>
using namespace std;


void draw(int row, int col, char arr[200][200], char initial, char replacement, sf::RenderWindow* window)
{
    sf::RectangleShape rect;
    //window->setFramerateLimit(60);

    rect.setPosition((float)window->getSize().x / 6, 30.0);
    rect.setSize({ 10.0, 10.0 });

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            rect.move(10, 0);
            if (arr[i][j] == replacement)
            {
                rect.setSize({ 30.0, 30.0 });
                rect.setFillColor(sf::Color::Red);
                rect.setSize({ 10.0, 10.0 });
                rect.setFillColor(sf::Color::Blue);
            }
            else if (arr[i][j] == initial)
            {
               
                rect.setSize({ 10, 10 });
                rect.setFillColor(sf::Color::White);
            }
            else
            {
         
                rect.setSize({ 10, 10 });
                rect.setFillColor(sf::Color::Black);
            }

            window->draw(rect);
        }
        rect.setPosition((float)window->getSize().x / 6, (float)30 + (i + 1) * 10);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window->close();
            return;
        }
    }
    window->display();

}

void floodfill(int row, int col, char arr[200][200], int x, int y, char initial, char replacement, sf::RenderWindow* window)
{

    if (x < 0 || x >= row || y < 0 || y >= col || arr[x][y] != initial) return;
    else
    {
        arr[x][y] = replacement;
        draw(row, col, arr, initial, replacement, window);
        floodfill(row, col, arr, x - 1, y, initial, replacement, window);
        floodfill(row, col, arr, x + 1, y, initial, replacement, window);
        floodfill(row, col, arr, x, y - 1, initial, replacement, window);
        floodfill(row, col, arr, x, y + 1, initial, replacement, window);
    }

}

void go(int row, int col, char arr[200][200], int x, int y, char initial, char replacement)
{
    sf::RenderWindow window(sf::VideoMode(1280, 900), "Stop", sf::Style::Fullscreen);
    floodfill(row, col, arr, x, y, initial, replacement, &window);
}

int main(void)
{
    int row, col, x, y;
    char replacement = '2';
    printf("Enter row count: ");
    cin >> row;
    printf("Enter column count: ");
    cin >> col;
    char arr[200][200];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (rand() % 3 == 0) arr[i][j] = '1';
            else arr[i][j] = '0';
        }
        //arr[i][j] = rand()%2;
    }

    printf("Enter start X, Y: ");
    cin >> x >> y;
    char initialc = arr[x][y];

    go(row, col, arr, x, y, initialc, replacement);


    return 0;

}