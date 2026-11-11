#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;
using namespace sf;

RectangleShape block[100][100];
bool bossRoomActive = false;
int bossRoomBlocksX = 0;
int bossRoomBlocksY = 0;
string map[100] = {
{"# ###########################################"},
{"#   # #       #   # #         #   #         #"},
{"### # # # ### # # # # # ##### # # ### ##### #"},
{"#   #   #   #   # # # #     # # #   # #   # #"},
{"### ######### ### # # # ##### # ### # # ### #"},
{"#   #   #     # # # # #   #     #     # #   #"},
{"# ### # # ##### # # # ### # # ######### # # #"},
{"# #   # # #     # #   #   # #     #       # #"},
{"# ### # # # ##### ##### ### ##### ###########"},
{"#     #   # #     #   #   #   #   #         #"},
{"########### # ##### # ### ### # ### ####### #"},
{"#     #     # #   # #   # #   #     #   #   #"},
{"# ### # ### # # # # ### ### ######### # # ###"},
{"#   # #   #   # # # #       #     #   #   # #"},
{"# # ##### ##### # # ######### # # # ####### #"},
{"# #     # #     #     #       # #   #       #"},
{"# ##### # # ######### ######### ########### #"},
{"#     # # #   # #   #   #   # #   # #       #"},
{"####### # ### # # # ### # # # ### # # ##### #"},
{"#       #   # # # #   #   # #     #   #     #"},
{"# ######### # # # ### ##### # ##### ### #####"},
{"# #   #     #   # # #     # # #     # #     #"},
{"# # # # # # ##### # # ### # # ##### # # ### #"},
{"#   #   # #       #   #     #       #   #   #"},
{"############################# ###############"},

};

int make_maze(RenderWindow &window)
{
    bossRoomActive = false;
    int width = window.getSize().x;
    int blocksX = width/30;

    int length = window.getSize().y;
    int blocksY = length/30;
    for(int i = 0; i <= blocksX; i++)
    {
        for(int j = 0; j <= blocksY; j++)
        {
            block[i][j].setSize(Vector2f(30, 30));
            block[i][j].setFillColor(Color::Yellow);
            block[i][j].setPosition(Vector2f(i*30, j*30));
            block[i][j].setOutlineColor(Color(80, 80, 80));
            block[i][j].setOutlineThickness(3.f);

            if (map[j][i] == '#')
            window.draw(block[i][j]);

        }
    }

    // cout << block[blocksX-1][blocksY-1].getPosition().x << " " << block[blocksX-1][blocksY-1].getPosition().y << endl;


    return 0;
}

bool mazeCollision(float x, float y, float width, float height)
{
    if(bossRoomActive)
    {
        return x < 30.0f || y < 30.0f ||
               x + width > bossRoomBlocksX * 30.0f ||
               y + height > bossRoomBlocksY * 30.0f;
    }

    const float tileSize = 30.0f;
    int firstColumn = static_cast<int>(floor(x / tileSize));
    int lastColumn = static_cast<int>(floor((x + width - 0.01f) / tileSize));
    int firstRow = static_cast<int>(floor(y / tileSize));
    int lastRow = static_cast<int>(floor((y + height - 0.01f) / tileSize));

    for(int row = firstRow; row <= lastRow; row++)
    {
        for(int column = firstColumn; column <= lastColumn; column++)
        {
            if(row < 0 || row >= 100 || column < 0 ||
               map[row].empty() || column >= static_cast<int>(map[row].size()) ||
               map[row][column] == '#')
                return true;
        }
    }

    return false;
}

bool mazeCompleted(float x, float y, float width, float height)
{
    float exitX = 29.0f * 30.0f;
    float exitY = 24.0f * 30.0f;
    float tileSize = 30.0f;

    return x < exitX + tileSize && x + width > exitX &&
           y < exitY + tileSize && y + height > exitY;
}

void makebossroom(RenderWindow &window)
{
    int width = window.getSize().x;
    int blocksX = width/30;

    int length = window.getSize().y;
    int blocksY = length/30;
    bossRoomActive = true;
    bossRoomBlocksX = blocksX;
    bossRoomBlocksY = blocksY;
    for(int i = 0; i <= blocksX; i++)
    {
        for(int j = 0; j <= blocksY; j++)
        {
            block[i][j].setSize(Vector2f(30, 30));
            block[i][j].setFillColor(Color::Yellow);
            block[i][j].setPosition(Vector2f(i*30, j*30));
            block[i][j].setOutlineColor(Color(80, 80, 80));
            block[i][j].setOutlineThickness(3.f);

            if (i == 0 || i == blocksX || j == 0 || j == blocksY)
            window.draw(block[i][j]);

        }
    }
}