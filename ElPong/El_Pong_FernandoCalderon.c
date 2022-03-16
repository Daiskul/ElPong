/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;
    Rectangle rec = {20,screenHeight/2,30,90};
    Color col1 = RED;
    Vector2 cir = {screenWidth/2,screenHeight/2};
    int dirX = GetRandomValue(5,15);
    int dirY = dirX;
    Color col = VIOLET;
    int tam = 20;
    int puntos = 0;
    int vidas = 3;
    bool muerto = false;
    bool pausado = false;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] blab bla bla example - basic window");
    InitAudioDevice();
    SoundSound fxWav = LoadSound("gameover-game-over.wav");
    Sound fxWav2 = LoadSound("tambor.wav");
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        if (muerto==false)
        {
        if (rec.y<screenHeight-rec.height)
        {  
            if (IsKeyDown('S'))
            {
                rec.y+=8;
            }
        }       
        if (rec.y>0)
        {
             if (IsKeyDown('W'))
            {
                rec.y-=8;
            }
        }
        if (IsKeyPressed('P'))
        {
            pausado = !pausado;
        }
               
        //ACTUALIZAR LA POSICION EN BASE A LA DIRECCION
        
         
        
            
        if (pausado == false)
        {
            cir.x += dirX;
            cir.y += dirY;
        }

        if (cir.x >= screenWidth-tam)
        {
            dirX= -dirX;
            PlaySound(fxWav2);
        }
        if (cir.x <= 0+tam)
        {
            dirX= -dirX;
            vidas-=1;
            PlaySound(fxWav2);
        }
        if (cir.y >= screenHeight-tam)
        {
            dirY= -dirY;
            PlaySound(fxWav2);
        }
        if (cir.y <= 0+tam)
        {
            dirY= -dirY;
            PlaySound(fxWav2);
        }
        
        if (vidas<=0)
        {
            muerto = !false;
            PlaySound(fxWav);
            
        }
        }
        else
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                muerto=false;
                vidas +=3;
                puntos= 0;
                cir.x=screenWidth/2;
                cir.y=screenHeight/2;
                dirX = GetRandomValue(5,10);
                dirY = dirX;
            }
        }
        
        if (CheckCollisionCircleRec(cir, tam, rec))
        {
            dirX= -dirX;
            dirY= -dirY;
            puntos+=100;
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            DrawText(FormatText("PUNTUACION: %i",puntos),50,10,20,WHITE);
            DrawText(FormatText("VIDAS: %i",vidas),50,40,20,WHITE);
            DrawCircle(cir.x,cir.y,tam,col);
            DrawRectangleRec(rec,col1);
            DrawRectangle(200, 40, 330, 20, GRAY);
            if (pausado)
            {
                DrawText("Pause",screenHeight/2,200,100,WHITE);
            }
            if (muerto)
            {
                DrawText("Game Over", screenHeight/2,200,50,WHITE);
                DrawText("Pulsa espacio para continuar", screenHeight/2, 300, 20, WHITE);
            }
            if(!muerto)
            {
                 if (vidas==3)
            {
                DrawRectangle(200, 40, 330, 20, GREEN);
            }
            if (vidas==2)
            {
                DrawRectangle(200, 40, 220, 20, GREEN);
            }
            if (vidas==1)
            {
                DrawRectangle(200, 40, 110, 20, GREEN);
            }
            }
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadSound(fxWav2);     // Unload sound data

    CloseAudioDevice();     // Close audio device
    
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}