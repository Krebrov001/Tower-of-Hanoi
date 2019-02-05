#include "SDL.h"     // Simple DirectMedia Layer API structures and functions
#include <cstdlib>   // for exit(), EXIT_SUCCESS, EXIT_FAILURE, NULL, std::size_t
#include <iostream>  // for std::cin, std::cout, std::cerr, std::endl;

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include "hanoi.h"   // for Hanoi class
#include "drawer.h"  // for Drawer class


// The preprocessor directive is used if we want to mix C and C++ code together.
// extern "C" tells the C++ compiler to not mangle the names of functions.
// This ensures that we will have no linker errors if we want to call functions written in C from C++ code and vice-versa.
// This could be an issue since the SDL Libraries are written in C while my project is written in C++.
#ifdef __cplusplus
    extern "C"
#endif
int main()
{
    // Initialization to 0 removes garbage values.
    // In case the cin statement fails,
    // the value in number_of_disks will be invalid, that value will be rejected, and the user prompted for input once again.
    size_t number_of_disks = 0;
    while (true) {
        cout << "Enter the number of disks [1 ... 10]\n > ";
        cin  >> number_of_disks;

	if (number_of_disks == 0) {
	    cerr << "Error: number of disks must be > 0." << endl;
	} else if (number_of_disks > 10) {
	    cerr << "Error: number of disks must be <= 10." << endl;
	} else {
	    break;
	}
    }

    /* This chunk of code is responsible for setting up the infrastructure used by the program. */

    /* Initialize the SDL Video subsystem and check for errors. */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Error: Initialization of SDL subsystems failed: " << SDL_GetError() << endl;
	exit(EXIT_FAILURE);
    }

    SDL_Window* window     = nullptr;
    SDL_Renderer* renderer = nullptr;

    /* Allocate dynamic memory for the SDL_Window and check for errors. */
    window = SDL_CreateWindow("Tower of Hanoi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
                               SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN);
    // If creating window failed, SDL_CreateWindow() returns a null pointer.
    if (!window) {
        cerr << "Error: Creating window failed: " << SDL_GetError() << endl;
	SDL_Quit();
	exit(EXIT_FAILURE);
    }

    /* Allocate dynamic memory for the SDL_Renderer and check for errors. */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // If creating renderer failed, SDL_CreateRenderer() returns a null pointer.
    if (!renderer) {
        cerr << "Error: Creating renderer failed: " << SDL_GetError() << endl;
	// Since the SDL_Window was previously created successfully,
	// we need to destroy it anyway to avoid a memory leak.
	SDL_DestroyWindow(window);
	SDL_Quit();
	window = nullptr;  // Make sure that window is not pointing to a deallocated object.
	exit(EXIT_FAILURE);
    }

    // Initialize the Towers of Hanoi.
    Hanoi game1(number_of_disks);
    // Initialize the Drawer.
    Drawer draw(window, renderer, number_of_disks);
    // Draw the initial state of the Tower of Hanoi.
    draw.draw_Hanoi(game1);
    // Play the game, drawing each move.
    game1.play(&draw);


    /* This chunk of code is responsible for safely exiting the program. */

    /* Deallocate dynamic memory for the window and the renderer. */
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    /* Quit the SDL subsystems and free up any additional used resources. */
    SDL_Quit();

    return EXIT_SUCCESS;
}
