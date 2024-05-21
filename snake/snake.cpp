// snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>//pair
#include <time.h>//rand()
#include <vector>
#include <Windows.h>//Sleep()
#include <conio.h>

using namespace std;

const int grid_size = 22;
char grid[grid_size][grid_size];
int x_obstacle, y_obstacle, x_head,y_head,x_apple,y_apple;
int direction = 1;
// 4-UP, 1-RIGHT, 2-DOWN,3-LEFT
vector <pair<int, int>> snake;
bool found_apple = 0;//0 when not found

void direction_handle()
{
    while (true)
    {
        if (GetAsyncKeyState(VK_UP) & 0x01) //0x8000
        {
            direction=1;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x01)
        {
            direction=2;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x01)
        {
            direction = 3;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x01)
        {
            direction = 4;
        }
        direction = (direction % 4) + 1;
    }
}

void generate_apple()
{
    x_apple = (rand() % (grid_size - 2)) + 1;
    y_apple = (rand() % (grid_size - 2)) + 1;
    while (grid[x_apple][y_apple] != ' ')
    {
        x_apple = (rand() % (grid_size - 2)) + 1;
        y_apple = (rand() % (grid_size - 2)) + 1;
    }
    grid[x_apple][y_apple] = '+';
}
void play_snake()
{
    
    // ' ' - free space
    // char(219) - snake
    // + - apple
    // # - obstacle

    ///////////////////////////////////////////// 
    //creating grid and setting borders
    //const int grid_size = 22;
    //char grid[grid_size][grid_size];
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            grid[i][j] = ' ';
        }
    }
    for (int i = 0; i < grid_size; i++)
    {
        grid[i][0] = '#';
        grid[i][grid_size-1] = '#';
        grid[0][i] = '#';
        grid[grid_size-1][i] = '#';
    }
    /////////////////////////////////////////////
    
    
    
    /////////////////////////////////////////////
    //set obstacles
    srand(time(NULL));
    x_obstacle = (rand() % (grid_size-2)) + 1;
    y_obstacle=(rand() % (grid_size - 2)) + 1;

    for (int i = 0; i < grid_size / 2; i++)
    {
        x_obstacle = (rand() % (grid_size - 2)) + 1;
        y_obstacle = (rand() % (grid_size - 2)) + 1;
        if (grid[x_obstacle][y_obstacle] == ' ')// if found free space
        {
            grid[x_obstacle][y_obstacle] = '#';//set obstacle
        }
        else
        {
            i--;
        }
    }
    /////////////////////////////////////////////
    
    
    
    /////////////////////////////////////////////
    // set starting point of snake
    x_head = (rand() % (grid_size - 2)) + 1;
    y_head= (rand() % (grid_size - 2)) + 1;
    while (grid[x_head][y_head] != ' ')
    {
        x_head = (rand() % (grid_size - 2)) + 1;
        y_head = (rand() % (grid_size - 2)) + 1;
    }
    //grid[x_head][y_head] = char(219);
    //vector <pair<int,int>> snake;
    snake.push_back(make_pair(x_head, y_head));
    /////////////////////////////////////////////

    /////////////////////////////////////////////
    //set first apple
    generate_apple();
    /////////////////////////////////////////////

    //direction = 1;
    
    
    while (true) // while snake is not on obstacle (snake can go through snake
    {//grid[snake[0].first][snake[0].second] != ' '
        if (GetAsyncKeyState(VK_UP) & 0x8000 && direction!=3)
        {
            direction = 1;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && direction!=4)
        {
            direction = 2;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000 && direction!=1)
        {
            direction = 3;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && direction!=2)
        {
            direction = 4;
        }
        // = (direction % 4) + 1;
        //Sleep(10);
        
        

        int snake_length = snake.size();
        x_head = snake[snake_length - 1].first;
        y_head = snake[snake_length - 1].second;
        
        
        if (direction == 1){x_head--;}
        else if (direction == 2) { y_head++; }
        else if (direction == 3) { x_head++; }
        else if (direction == 4) { y_head--; }

        if (grid[x_head][y_head] != ' ' && grid[x_head][y_head] != '+') { break; }
        if (grid[x_head][y_head] == '+') { found_apple = 1; generate_apple(); }
        snake.push_back(make_pair(x_head, y_head));
        // delete tail (if snake steps on '+') do not proceed
        if (found_apple == 0)
        {
            grid[snake[0].first][snake[0].second] = ' ';
            snake.erase(snake.begin());
            //found_apple = 0;
        }
        found_apple = 0;
        system("cls");
        //draw grid
        for (int i = 0; i < snake.size(); i++)
        {
            grid[snake[i].first][snake[i].second] = char(219);
        }
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                cout << grid[i][j];
            }
            cout << endl;
        }
        /*cout << endl;
        cout << snake[0].first << " " << snake[0].second << endl;
        cout<< ">"<<grid[snake[0].first][snake[0].second]<<"<"<<endl;*/
        //cout << found_apple << endl;
        Sleep(150);
    }
    cout << "PUNKTY: " << snake.size() << endl;
    char key;
    key = _getch();

}

int main()
{
    //direction_handle();
    play_snake();
}
