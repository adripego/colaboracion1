#include "stdafx.h"
#include <conio.h>
#include <Windows.h>

//Probando git
int g_iPosMainChar = 1;
int g_iCharLives = 3;
int g_iPosBullet = 764764;
bool g_bExistsBullet = false;
bool g_bBulletLeft = false;
bool g_bExistsMob = false;
int g_iPosMob = 0;
bool g_bMobLeft = false;
unsigned int g_iScore = 0;
const unsigned int WORLD_WIDTH = 70;
const unsigned int WORLD_LEFT_CAP = 0;

// Comprueba las teclas pulsadas por el usuario.
void inputCheck()
{
	if (_kbhit())
	{
		char keyTapped = _getch();
		if (keyTapped == 'a')
		{
			g_iPosMainChar--;
		}
		else if (keyTapped == 'd')
		{
			g_iPosMainChar++;
		}
		else if (keyTapped == 'e')
		{
			g_bExistsBullet = true;
			g_iPosBullet = g_iPosMainChar + 1;
            g_bBulletLeft = false;
		}
        else if (keyTapped == 'q')
        {
            g_bExistsBullet = true;
            g_iPosBullet = g_iPosMainChar - 1;
            g_bBulletLeft = true;
        }
	}
}

// Pinta en pantalla.
void draw()
{
    
    printf("\r");
   // printf("Vidas: %d | Puntuacion %d", g_iCharLives, g_iScore);
    for (unsigned int i = 0; i < WORLD_WIDTH; i++)
    {
        if (i == g_iPosMainChar)
        {
            printf("&");
        }
        else if (i == g_iPosBullet)
        {
            if (g_bExistsBullet)
            {
                printf("*");
            }
        }
        else if (i == g_iPosMob)
        {
            if (g_bExistsMob)
            {
                printf("@");
            }
        }
        else
        {
            printf("_");
        }
    }
    printf("Vidas: %d", g_iCharLives);
}
    

// Actualiza las variables de estado del juego.
void updateGameState()
{
    if (!g_bExistsMob)
    {
        unsigned int randomSpawn = rand() % 100;
        unsigned int randomDir = rand() % 100;
        if (randomSpawn < 5)
        {
            g_bExistsMob = true;
            if (randomDir < 40)
            {
                g_iPosMob = 69;
                g_bMobLeft = false;
            }
            else
            {
                g_iPosMob = 1;
                g_bMobLeft = true;
            }
        }
    }
    
    //****************** Colisiones ******************
    if (g_bExistsBullet)
    { 
        // Comprobando colision.
        if (g_iPosBullet == g_iPosMob)
        {
            g_bExistsBullet = false;
            g_bExistsMob = false;
            g_iScore = g_iScore + 5;
        }
        if (g_iPosBullet < WORLD_WIDTH && g_iPosBullet > WORLD_LEFT_CAP)
        {
            if (g_bBulletLeft)
            {
                g_iPosBullet = g_iPosBullet - 2;
            }
            else
            {
                g_iPosBullet = g_iPosBullet + 2;
            }
        }
        else
        {
            g_bExistsBullet = false;
        }
    }

    if (g_bExistsMob)
    {
        if (g_iPosMob == g_iPosMainChar)
        {
            g_bExistsMob = false;
            g_iCharLives--;

        }
        if (g_iPosMob > WORLD_LEFT_CAP)
        {
            if (!g_bMobLeft)
            {
                g_iPosMob--;
            }
            else
            {
                g_iPosMob++;
            }
        }
        else
        {
            g_bExistsMob = false;
        }
    }
}

void gameOver()
{
    printf("\nGame Over! Puntuacion: %d\n", g_iScore);
}

int _tmain(int argc, _TCHAR* argv[])
{
    while (g_iCharLives > 0)
    {
        inputCheck();
        updateGameState();
        draw();
        Sleep(50);
    }
    gameOver();
    getchar();
    return 0;
}