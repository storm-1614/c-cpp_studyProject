/*
* storm-1614
* 2025-11-05 16:50
* 走迷宫
*/


#include <iostream>
#include <stack>
#include <vector>

int main(int argc, char *argv[])
{
    int w, h;
    int beganx, begany, endx, endy;
    std::cin >> w >> h;
    std::vector<std::vector<int>> maze(w, std::vector<int>(h));
    std::vector<std::vector<int>> vis(w, std::vector<int>(h, false));
    struct Node
    {
        int x;
        int y;
    };
    std::stack<Node> st;
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            std::cin >> maze[i][j];

    std::cin >> begany >> beganx >> endy >> endx;
    Node began = {beganx, begany};
    Node end = {endx, endy};
    int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    st.push(began);
    while (!st.empty())
    {
        Node current = st.top();
        if (current.x == end.x && current.y == end.y)
        {
            std::cout << "yes";
            return 0;
        }
        bool hasVisited = false;
        for (int i = 0; i < 4; i++)
        {
            int newX = current.x + direction[i][0];
            int newY = current.y + direction[i][1];
            if (newX > 0 && newX < w && newY > 0 && newY < h && maze[newX][newY] == 0 && vis[newX][newY] == false)
            {
                vis[newX][newY] = true;
                Node newNode = {newX, newY};
                st.push(newNode);
                hasVisited = true;
            }
        }
        if (!hasVisited)
            st.pop();
    }

    std::cout << "no";
    return 0;
}
