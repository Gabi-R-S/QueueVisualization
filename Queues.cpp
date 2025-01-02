#include <iostream>
#include "raylib.h"
#include <vector>

struct DeterministicQueue {
    std::vector<float> elems = {};
    std::vector<float> servedElems = {};
    float serveTime=0.5;
    float serveCounter = 1;
    float arrivalTime = 1;
    float arrivalCounter = 0;
};


struct PoissonQueue
{
    std::vector<float> elems = {};
    std::vector<float> servedElems = {};

    float arrivalProbability = 0.4;
    float serveProbability = 0.8;

    float timePeriod = 1;

    float arrivalCounter = 0;
    float serveCounter = 0;
};



float randomFloatBetween0And1() {
    return (float)(rand() % 10001)/ (float)(10000);
}


int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    struct PoissonQueue mm;
    float mmHeight = 250;
   
    DeterministicQueue dd;
    float ddHeight = 100;

    const float serveLinePlacement = 650;
    float pointDistanceBetween=10;
    float pointSpeed=75;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float delta = GetFrameTime();



     
        // Update
        //----------------------------------------------------------------------------------
       
        {
            if (mm.serveCounter < mm.timePeriod) {
                mm.serveCounter += delta;
            }

            mm.arrivalCounter += delta;
            if (mm.arrivalCounter > mm.timePeriod)
            {   
                if (randomFloatBetween0And1() < mm.arrivalProbability)
                {
                    mm.elems.push_back(-8.0);
                }
                else {
                    mm.arrivalCounter -= mm.timePeriod;
                }

            }

            for (int i = 0; i < mm.servedElems.size();)
            {
                mm.servedElems[i] = i != 0 ?
                    std::min(mm.servedElems[i] + pointSpeed * delta, mm.servedElems[i - 1] - pointDistanceBetween)
                    : mm.servedElems[i] + pointSpeed * delta;

                if (mm.servedElems[i] > 810)
                {
                    mm.servedElems.erase(mm.servedElems.begin());
                }
                else {
                    i++;
                }

            }

            bool erased = false;
            do {
                erased = false;
                if (mm.elems.size() > 1)
                {
                    auto& lastElement = *mm.elems.begin();
                    if (lastElement == serveLinePlacement)
                    {
                        if (mm.serveCounter > mm.timePeriod) {
                            if (randomFloatBetween0And1() < mm.serveProbability)
                            {
                                mm.elems.erase(mm.elems.begin());
                                mm.servedElems.push_back(serveLinePlacement);
                                erased=true;
                            }
                            else {
                                mm.serveCounter -= mm.timePeriod;
                            }
                        }
                    }
                    else {
                        float next = 1000;

                        if (mm.servedElems.size() > 0) {
                            next = *mm.servedElems.rbegin();
                        }

                        lastElement = std::min(next - pointDistanceBetween, lastElement + pointSpeed * delta);

                        if (lastElement >= serveLinePlacement)
                        {
                            lastElement = serveLinePlacement;
                            mm.serveCounter = 0;
                        }

                    }

                }
            } while (erased&& mm.elems.size() > 1);

            for (int i = 1; i < mm.elems.size(); i++)
            {
                //      std::cout << dd.elems[i]<< " "<< dd.elems[i] + pointSpeed * delta<< " " << dd.elems[i + 1] - pointDistanceBetween << "\n";
                mm.elems[i] = std::min(mm.elems[i] + pointSpeed * delta, mm.elems[i - 1] - pointDistanceBetween);
            }
            // std::cout << "\n\n\n";
        }





        {
            if (dd.serveCounter < dd.serveTime) {
                dd.serveCounter += delta;
            }

            dd.arrivalCounter += delta;
            if (dd.arrivalCounter > dd.arrivalTime)
            {
                dd.arrivalCounter -= dd.arrivalTime;
                dd.elems.push_back(-8.0);
            }

            for (int i = 0; i < dd.servedElems.size();)
            {
                dd.servedElems[i] = i != 0 ?
                    std::min(dd.servedElems[i] + pointSpeed * delta, dd.servedElems[i - 1] - pointDistanceBetween)
                    : dd.servedElems[i] + pointSpeed * delta;

                if (dd.servedElems[i] > 810)
                {
                    dd.servedElems.erase(dd.servedElems.begin());
                }
                else {
                    i++;
                }

            }


            bool erased = false;

            do{
                erased = false;
            if (dd.elems.size() > 1)
            {
                auto& lastElement = *dd.elems.begin();
                if (lastElement == serveLinePlacement)
                {
                    if (dd.serveCounter > dd.serveTime) {
                        dd.elems.erase(dd.elems.begin());
                        dd.servedElems.push_back(serveLinePlacement);
                        erased = true;
                    }
                }
                else {
                    float next = 1000;

                    if (dd.servedElems.size() > 0) {
                        next = *dd.servedElems.rbegin();
                    }

                    lastElement = std::min(next - pointDistanceBetween, lastElement + pointSpeed * delta);

                    if (lastElement >= serveLinePlacement)
                    {
                        lastElement = serveLinePlacement;
                        dd.serveCounter = 0;
                    }

                }

            }
            } while (erased && dd.elems.size() > 1);

            for (int i = 1; i < dd.elems.size(); i++)
            {
                //      std::cout << dd.elems[i]<< " "<< dd.elems[i] + pointSpeed * delta<< " " << dd.elems[i + 1] - pointDistanceBetween << "\n";
                dd.elems[i] = std::min(dd.elems[i] + pointSpeed * delta, dd.elems[i - 1] - pointDistanceBetween);
            }
            // std::cout << "\n\n\n";
        }

        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        
        
        for (auto& elem:dd.elems)
        {
            DrawCircle(elem, ddHeight, 4, BLUE);

        }
        for (auto& elem : dd.servedElems)
        {
            DrawCircle(elem, ddHeight, 3, DARKBLUE);
        }
        for (auto& elem : mm.elems)
        {
            DrawCircle(elem, mmHeight, 4, RED);

        }
        for (auto& elem : mm.servedElems)
        {
            DrawCircle(elem, mmHeight, 3, BROWN);
        }

        DrawLine(serveLinePlacement, 0, serveLinePlacement, 450, ORANGE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

