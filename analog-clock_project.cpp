#include <graphics.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <sstream>  // For std::ostringstream

#define PI 3.1415
using namespace std;

// Function to solve the knapsack problem
int knapsack(int W, int wt[], int val[], int n) {
    int dp[n + 1][W + 1];
    
    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    
    return dp[n][W];
}

// Function to convert int to string using std::ostringstream
string intToString(int num) {
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

int main()
{
    initwindow(500, 500, "ANALOG CLOCK");
    
    int page = 0;

    // Knapsack data
    int W = 50; // Maximum weight capacity
    int val[] = {60, 100, 120}; // Values
    int wt[] = {10, 20, 30}; // Weights
    int n = sizeof(val) / sizeof(val[0]); // Number of items

    int max_value = knapsack(W, wt, val, n); // Solve the knapsack problem

    while (1)
    {
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        setcolor(WHITE);
        circle(250, 250, 220);
        circle(250, 250, 5);

        // Drawing clock face
        for (int i = 1; i <= 12; ++i) {
            string text = intToString(i);
            outtextxy(250 + 200 * sin(i * PI / 6) - 5, 250 - 200 * cos(i * PI / 6), const_cast<char*>(text.c_str()));
        }

        // Draw hands
        time_t now = time(0);
        tm *ltm = localtime(&now);

        setcolor(RED);
        line(250, 250, 250 + 150 * sin(ltm->tm_hour * PI / 6), 250 - 150 * cos(ltm->tm_hour * PI / 6));

        setcolor(GREEN);
        line(250, 250, 250 + 190 * sin(ltm->tm_min * PI / 30), 250 - 190 * cos(ltm->tm_min * PI / 30));

        setcolor(WHITE);
        line(250, 250, 250 + 150 * sin(ltm->tm_sec * PI / 30), 250 - 150 * cos(ltm->tm_sec * PI / 30));

        // Display knapsack result
        setcolor(YELLOW);
        string result = "Max Value in Knapsack: " + intToString(max_value);
        outtextxy(10, 10, const_cast<char*>(result.c_str()));

        if (GetAsyncKeyState(VK_RETURN))
            break;

        delay(10);
        page = 1 - page;
    }

    closegraph();
    return 0;
}

