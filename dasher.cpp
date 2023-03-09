#include "raylib.h"


int main()
{
    // Window Settings
    const int windowWidth{512};
    const int windowHeight{380};
    // initialize window
    InitWindow(windowWidth, windowHeight, "Running Dash");

    // acceleration due to gravity (pixels/sec)/sec
    const int gravity{1'000};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // animation frame
    int frame{};
    // amount of time before update animation frame
    const float updateTime{ 1.0 / 12.0 };

    float runningtime{};

    //
    const int jumpVel(-600);

    // Air Check
    bool isInAir{};

    int velocity{0};

    

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {

        // delta time (tiem since last frame)
        const float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        

        // ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // in air check
            velocity += gravity * dT;
            isInAir = true;
        }

        // check for jump
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        
        // update position
        scarfyPos.y += velocity * dT;

        // update running time
        runningtime += dT;
        if (runningtime >= updateTime)
        {
            runningtime = 0;
            // update aniamtion frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }
        }


        

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}