#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    // Window Settings
    const int windowWidth{512};
    const int windowHeight{380};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Running Dash");

    // acceleration due to gravity (pixels/sec)/sec
    const int gravity{1'000};

    // neb variables
    Texture2D neb = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    AnimData nebData
    { 
        {0.0, 0.0, neb.width/8, neb.height/8}, // Rectangle rec
        {windowWidth, windowHeight - neb.height/8}, // Vector2 Pos
        0, // int frame
        1.0/12.0,  // float updateTime
        0 // float runningTime
    };

    AnimData neb2Data{
        {0.0, 0.0, neb.width/8, neb.height/8},
        {windowWidth + 300, windowHeight - neb.height/8},
        0, 
        1.0/16.0,
        0.0
    };
    
    // neb X velocity
    int hazVel{-200};

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

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
        if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height)
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

        // update neb position
        nebData.pos.x += hazVel * dT;

        neb2Data.pos.x += hazVel * dT;

        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // update scarfy animation frame
        if(!isInAir)
        {
            // update running time
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;
                // update aniamtion frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
        }

        // update neb animation frame
        nebData.runningTime += dT;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if (nebData.frame > 7)
            {
                nebData.frame = 0;
            }
        }

        // update neb animation frame
        neb2Data.runningTime += dT;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.0;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if (neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
        }
        
        }


        // Draw neb
        DrawTextureRec(neb, nebData.rec, nebData.pos, WHITE);
        DrawTextureRec(neb, neb2Data.rec, neb2Data.pos, RED);

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(neb);
    CloseWindow();
}