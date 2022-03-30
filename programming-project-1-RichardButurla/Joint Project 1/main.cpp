// Name: Richard Buturla
// Login:C00272345 
// Date: 06/03/2022
// Approximate time taken: 50 hrs 
//---------------------------------------------------------------------------
// Project description: Zombie Shooter
// ---------------------------------------------------------------------------
// Known Bugs: Enemies can intefere visually with texts on screen
// ?
//session 1: 2hrs
//session 2: 2hrs
//session 3: 5hrs
//session 4: 6hrs
//session 5: 5hrs
//session 6: 2hrs

//////////////////////////////////////////////////////////// 
// include correct library file for release and debug versions
//////////////////////////////////////////////////////////// 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 


#include "Game.h"

/// <summary>
/// main enrtry point
/// </summary>
/// <returns>success or failure</returns>
int main()
{
	Game game;
	game.run();

	return 1; // success
}