#include "Application.h"
#include "FastNoiseSIMD.h"

int main(int argc, char* argv[])
{
	Application app(1280, 720);
	
	
	app.Init();
	app.Run();

	return 0;
}