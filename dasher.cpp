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

    // hazard variables
    Texture2D hazard = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle hazardRec{0.0, 0.0, hazard.width/8, hazard.height/8};
    Vector2 hazPos{windowWidth, windowHeight - hazardRec.height};

    Rectangle haz2Rec{0.0, 0.0, hazard.width/8, hazard.height/8};
    Vector2 haz2Pos{windowWidth + 300, windowHeight - hazardRec.height};
    
    // hazard X velocity
    int hazVel{-200};

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // hazard animation variables
    
    int hazFrame{};
    const float hazUpdateTime{ 1.0 / 12.0 };
    float hazRunningTime{};

    int haz2Frame{};
    const float haz2UpdateTime { 1.0 / 12.0 };
    float haz2RunningTime{};


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

        // update hazard position
        hazPos.x += hazVel * dT;

        haz2Pos.x += hazVel * dT;

        // update scarfy position
        scarfyPos.y += velocity * dT;

        // update scarfy animation frame
        if(!isInAir)
        {
            // update running time
            runningtime += dT;
            if (runningtime >= updateTime)
            {
                runningtime = 0.0;
                // update aniamtion frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
        }

        // update hazard animation frame
        hazRunningTime += dT;
        if (hazRunningTime >= hazUpdateTime)
        {
            hazRunningTime = 0.0;
            hazardRec.x = hazFrame * hazardRec.width;
            hazFrame++;
            if (hazFrame > 7)
            {
                hazFrame = 0;
            }
        }

        // update hazard animation frame
        haz2RunningTime += dT;
        if (haz2RunningTime >= haz2UpdateTime)
        {
            haz2RunningTime = 0.0;
            haz2Rec.x = haz2Frame * haz2Rec.width;
            haz2Frame++;
            if (haz2Frame > 7)
            {
                haz2Frame = 0;
            }
        }
        
        }


        // Draw hazard
        DrawTextureRec(hazard, hazardRec, hazPos, WHITE);
        DrawTextureRec(hazard, haz2Rec, haz2Pos, RED);

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(hazard);
    CloseWindow();
}