#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;
using namespace sf;

RectangleShape block[100][100];
bool bossRoomActive = false;
int bossRoomBlocksX = 0;
int bossRoomBlocksY = 0;
int currentMaze = 1;

string map[100] = {
    "# ###########################################",
    "#                                             #",
    "#                                             #",
    "#                                             #",
    "############# ####### ########################",
    "#       #       #       #           #         #",
    "# ##### # ##### # ##### # ######### # ######  #",
    "# #     # #     # #     #     #     #      #  #",
    "# # ##### # ##### # ######### # ######### #  #",
    "# #       #       #       #   #         # #  #",
    "# ######### ####### ##### # ######### # # #  #",
    "#         #       # #     #     #     #   #  #",
    "######### ####### # # ######### # #########  #",
    "#       #       # # #     #     #           #",
    "# ##### ####### # # ##### # ##################",
    "# #   #       # #       # #       #          #",
    "# # ######### # ####### # ####### # ######## #",
    "# #         # #     #   #       # #        # #",
    "# ######### # ##### # ######### # ######## # #",
    "#         # #     # #         # #          # #",
    "######### # ##### # ######### # ############ #",
    "#       # #     # #       #   #              #",
    "# ##### # ##### # ####### # ################ #",
    "#       #       #         #                  #",
    "############################# ################"
};

string map2[100] = {
    "# ###########################################",
    "#                                             #",
    "#                                             #",
    "#                                             #",
    "############# ####### ########################",
    "#   #       #       #       #                 #",
    "### # ##### ####### # ##### # ##############  #",
    "#   #     #         # #     #       #        #",
    "# ####### ########### # ########### # ###### #",
    "#       #       #     #           # #      # #",
    "####### ##### # # ############# # # ###### # #",
    "#     #       # #       #       # #        # #",
    "# ### ######### ####### # ####### ########## #",
    "#   #         #       # #       #            #",
    "### ######### ####### # ####### ##############",
    "#       #           # #       #              #",
    "####### # ######### # ####### # ############ #",
    "#       # #       # #       # #            # #",
    "# ####### # ##### # ####### # ############ # #",
    "#         #     # #       # #              # #",
    "######### ##### # ####### # ################ #",
    "#       #     # #       # #                  #",
    "# ##### ##### # ####### # ################## #",
    "#           #           #                    #",
    "############################# ################"
};

string map3[100] = {
    "# #############################################",
    "#                                             #",
    "#                                             #",
    "#                                             #",
    "############# ######## ########################",
    "# #         # #        #       #             #",
    "# # ####### # # ###### # ##### # ########### #",
    "# #       # # #      # #     # #           # #",
    "# ####### # # ###### # ##### # ######### # # #",
    "#       # # #      # #     # #         # #   #",
    "####### # # ###### # ##### # ######### # #####",
    "#     # # #      # #     # #         # #     #",
    "### # # # ###### # ##### # ######### # ##### #",
    "#   # # #        #     # #       #   #     # #",
    "# ### # ######## ##### # ####### # ####### # #",
    "#   # #        #     # #       # #       #   #",
    "### # ######## ####### ####### # ####### #####",
    "#   #        #       #       # #       #     #",
    "# ########## ####### ####### # ####### ##### #",
    "#          #       #       # #     #         #",
    "########## ####### ####### # ##### ######### #",
    "#        #       #       # #     #           #",
    "# ###### ####### ####### # ##### ############ ",
    "#                  #     #                    #",
    "############################# #################"
};

string map4[100] = {
    "# #############################################",
    "#                                             #",
    "#                                             #",
    "#                                             #",
    "############# ######## ########################",
    "#       #       #       #       #             #",
    "####### # ##### # ##### # ##### # ########### #",
    "#       #     # #     # #     # #           # #",
    "# ########### # ##### # ##### # ######### # # #",
    "#           # #     # #     # #         # #   #",
    "########### # ##### # ##### # ######### ##### #",
    "#         # #     # #     # #       #         #",
    "####### # # ##### # ##### # ####### ######### #",
    "#       # #     # #     # #       #         # #",
    "# ####### ##### # ##### # ####### ######### # #",
    "#       #     # #     # #       #         #   #",
    "####### ### # # ##### # ####### ########### ###",
    "#         # # #     # #       #             # #",
    "# ######### # ##### # ####### ############# # #",
    "#         # #     # #     #                 # #",
    "######### # ##### # ##### ################### #",
    "#       # #     # #     #                     #",
    "# ##### # ##### # ##### ####################  #",
    "#                   #                          #",
    "############################# #################"
};



string* selectedMap = map;
void selectRandomMaze()
{
    currentMaze = rand() % 4 + 1;

    if(currentMaze==1)
    {
        selectedMap = map;
    }
    else if(currentMaze==2)
    {
        selectedMap = map2;
    }
    else if(currentMaze==3)
    {
        selectedMap = map3;
    }
    else
    {
        selectedMap = map4;
    }
}

int make_maze(RenderWindow& window)
{
    bossRoomActive = false;
    static Texture brickTexture;
    static bool textureLoaded =
        brickTexture.loadFromFile("data/images/game_brick.jpg");

    if (!textureLoaded)
    {
        cout << "Failed to load game_brick.jpg!" << endl;
        return -1;
    }

    int width = window.getSize().x;
    int blocksX = width / 30;

    int length = window.getSize().y;
    int blocksY = length / 30;

    for (int i = 0; i <= blocksX; i++)
    {
        for (int j = 0; j <= blocksY; j++)
        {
            block[i][j].setSize(Vector2f(30.f, 30.f));
            block[i][j].setTexture(&brickTexture);
            block[i][j].setFillColor(Color::White);
            block[i][j].setPosition(Vector2f(i * 30.f, j * 30.f));
            if (j < 25 &&
                i < selectedMap[j].size() &&
                selectedMap[j][i] == '#')
            {
                window.draw(block[i][j]);
            }
        }
    }

    return 0;}


bool mazeCollision(float x, float y, float width, float height)
{
    if (bossRoomActive)
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

    for (int row = firstRow; row <= lastRow; row++)
    {
        for (int column = firstColumn; column <= lastColumn; column++)
        {
            if (row < 0 || row >= 25 ||
                column < 0 ||
                column >= selectedMap[row].size() ||
                selectedMap[row][column] == '#')
            {
                return true;
            }
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