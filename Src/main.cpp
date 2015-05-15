#include "gamecore.h"

#include "windows.h"

const double game_speed = 0.02;

//int main (int argc, char** argv)
int WINAPI WinMain(HINSTANCE hInstance,
HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	if (!Initialize())
		return false;

	time_passed = SDL_GetTicks();

	while (!Process())
{
	//time = TimeLeft()*game_speed;
}

	Free();

	return true;

}
