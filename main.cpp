#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void drawPlayerSign(int arr[][3], int n);
void checkWinner(int arr[3][3], int &sum);

int main(void)
{
    // Initialization
    const int WIDTH = 600;
    const int HEIGHT = 300;

    InitWindow(WIDTH, HEIGHT + 1, "Tic tac toe");

    SetTargetFPS(60);

    // game variable
    int player{1};
    int block{100};
    int player1Score{0}, player2Score{0};
    bool gameOver{};

    const int gameWidth{300};
    const int gameHeight{300};
    Rectangle gameRect{1, 1, gameWidth, gameHeight};

    int arr[3][3] =
        {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
        };

    int n = sizeof(arr) / sizeof(int);
    int sum = 0;

    // Main game loop
    while (!WindowShouldClose())
    {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (sum != 3 && sum != -3))
        {
            int cellX = GetMousePosition().x / 100;
            int cellY = GetMousePosition().y / 100;
            // cout << "cell x = " << cellX <<
            //     "cell y = " << cellY << endl;
            if (arr[cellX][cellY] == 0)
            {
                // cout << sum << endl;
                arr[cellX][cellY] = player;
                player *= -1;
                checkWinner(arr, sum);
            }
        }

        if (IsKeyPressed(KEY_R))
        {
            sum = 0;
            gameOver = false;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    arr[i][j] = 0;
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawPlayerSign(arr, n);

        for (int row = 0; row < gameWidth / 2; row++)
        {
            // x ke y
            DrawLineEx(Vector2{0, static_cast<float>(row * block)}, Vector2{gameWidth, static_cast<float>(row * block)}, 2.2, GRAY);
            // y ke x
            DrawLineEx(Vector2{static_cast<float>(row * block), 0}, Vector2{static_cast<float>(row * block), gameHeight}, 2.2, GRAY);
        }

        DrawRectangleLinesEx(gameRect, 2.2, BLACK);
        DrawRectangle(gameWidth + 1, 0, 300, 300, RAYWHITE);
        DrawText("Tic tac toe", gameWidth + 53, 20, 30, BLACK);
        if (sum == 3)
        {
            DrawText("Player 1 Win!", gameWidth + 80, 90, 20, BLACK);
            if (!gameOver)
            {
                player1Score++;
                gameOver = true;
            }
        }

        if (sum == -3)
        {
            DrawText("Player 2 Win!", gameWidth + 80, 90, 20, BLACK);
            if (!gameOver)
            {
                player2Score++;
                gameOver = true;
            }
        }
        string turn = "Turn: ";

        // show turn player

        if (player == 1)
            turn.append("Player 1");
        else if (player == -1)
            turn.append("Player 2");

        if (!gameOver)
            DrawText(turn.c_str(), gameWidth + 75, 120, 20, BLACK);
        else
            DrawText("Press \"R\" to restart", gameWidth + 40, 150, 20, BLACK);

        // show score text
        DrawText("Score", gameWidth + 100, 200, 20, BLACK);
        string player1Text = "Player 1: " + to_string(player1Score);
        string player2Text = "Player 2: " + to_string(player2Score);
        DrawText(player1Text.c_str(), gameWidth + 100, 225, 20, BLUE);
        DrawText(player2Text.c_str(), gameWidth + 100, 245, 20, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void drawPlayerSign(int arr[][3], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[i][j] == 1)
            {
                DrawCircleLines(i * 100 + 50, j * 100 + 50, 35.0, BLUE);
                DrawCircleLines(i * 100 + 50, j * 100 + 50, 36.0, BLUE);
            }
            if (arr[i][j] == -1)
            {
                DrawLineEx(Vector2{static_cast<float>(i * 100 + 15), static_cast<float>(j * 100 + 15)}, Vector2{static_cast<float>(i * 100 + 85), static_cast<float>(j * 100 + 85)}, 2.0, RED);
                DrawLineEx(Vector2{static_cast<float>(i * 100 + 85), static_cast<float>(j * 100 + 15)}, Vector2{static_cast<float>(i * 100 + 15), static_cast<float>(j * 100 + 85)}, 2.0, RED);
            }
        }
    }
}

void checkWinner(int arr[3][3], int &sum)
{

    // check baris
    // player 1
    if (arr[0][0] + arr[0][1] + arr[0][2] == 3)
        sum = 3;
    if (arr[1][0] + arr[1][1] + arr[1][2] == 3)
        sum = 3;
    if (arr[2][0] + arr[2][1] + arr[2][2] == 3)
        sum = 3;

    // player 2
    if (arr[0][0] + arr[0][1] + arr[0][2] == -3)
        sum = -3;
    if (arr[1][0] + arr[1][1] + arr[1][2] == -3)
        sum = -3;
    if (arr[2][0] + arr[2][1] + arr[2][2] == -3)
        sum = -3;

    // check kolom
    // player 1
    if (arr[0][0] + arr[1][0] + arr[2][0] == 3)
        sum = 3;
    if (arr[0][1] + arr[1][1] + arr[2][1] == 3)
        sum = 3;
    if (arr[0][2] + arr[1][2] + arr[2][2] == 3)
        sum = 3;

    // player 2
    if (arr[0][0] + arr[1][0] + arr[2][0] == -3)
        sum = -3;
    if (arr[0][1] + arr[1][1] + arr[2][1] == -3)
        sum = -3;
    if (arr[0][2] + arr[1][2] + arr[2][2] == -3)
        sum = -3;

    // check silang
    // player 1
    if (arr[0][0] + arr[1][1] + arr[2][2] == 3)
        sum = 3;
    if (arr[0][2] + arr[1][1] + arr[2][0] == 3)
        sum = 3;

    // player
    if (arr[0][0] + arr[1][1] + arr[2][2] == -3)
        sum = -3;
    if (arr[0][2] + arr[1][1] + arr[2][0] == -3)
        sum = -3;
}
