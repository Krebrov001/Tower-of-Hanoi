#include "SDL.h"     // Simple DirectMedia Layer API structures and functions
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

// This struct holds the r, g, b values representing a color.
struct color {
    short int r;
    short int g;
    short int b;
};

// These defined constants are added to the degree value as an offset.
#define RED     0
#define GREEN 240
#define BLUE  120

/**
 * This class is responsible for drawing the state of the data structures in the class Hanoi,
 * I mean the towers with the disks on them and the disk_bits vector.
 * Since this class must access the private data members of class Hanoi, it must be it's friend class.
 */
class Drawer {
  public:
#ifdef COLORS
    Drawer(SDL_Window* window, SDL_Renderer* renderer, size_t num_disks) : window{window}, renderer{renderer}
#else
    Drawer(size_t num_disks)
#endif
    {
        colors.resize(num_disks);
	// We need to split the color wheel (360) degrees into equidistant colors.
	// 360 degrees is split up into equal pieces, and each element in degrees holds the degree of each angle.
	vector<short> degrees(num_disks, 0);
	// degrees[0] stores both the first element (the degree of the first angle), and it is also the common difference.
	degrees[0] = 360 / num_disks;
	for (size_t i = 1; i < num_disks; ++i) {
	    // degrees[i] = degrees[i-1] + the common difference
	    degrees[i] = degrees[i - 1] + degrees[0];
	}

	// Fills the colors vector.
	// Determines the r, g, b values for each color in the vector using their respective degrees in the color wheel.
	for (size_t i = 0; i < num_disks; ++i) {
	    colors[i].r = get_color_channel(degrees[i] + RED);
	    colors[i].g = get_color_channel(degrees[i] + GREEN);
	    colors[i].b = get_color_channel(degrees[i] + BLUE);
	}
    }

#ifdef COLORS
    void draw() const
    {
        // Light sand tan.
        // r = 200, g = 170, b = 120. a = 255 (solid)
        SDL_SetRenderDrawColor(renderer, 200, 170, 120, 255);
        // Fill the screen with this color.
        SDL_RenderClear(renderer);

        SDL_Rect color_square = { 20, 20, 20, 20 };

	size_t num_colors = colors.size();
	int x = 20;
	for (size_t i = 0; i < num_colors; ++i) {
	    color_square.x += 40;
	    SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, 255);
	    SDL_RenderFillRect(renderer, &color_square);

	    if (i != 0 && (i % 12) == 0) {
	        color_square.x  = 20;
		color_square.y += 40;
	    }
	}
	cout << color_square.x << endl;

        // Make all the saved changes to the state show up on the screen.
        SDL_RenderPresent(renderer);
        SDL_Delay(10000);
    }
#else
    void draw() const
    {
	size_t num_colors = colors.size();

        for (size_t i = 0; i < num_colors; ++i) {
            cout << colors[i].r << '-' << colors[i].g << '-' << colors[i].b << endl;
        }
    }
#endif

    short int get_color_channel(int num)
    {
	// If num > 360, this statement causes that angle to "wrap around".
        num %= 360;

	switch (num) {
	  case 0 ... 59:
	      // increasing
	      return (255 * (num / 60.0));
	  case 60 ... 180:
	      // maximum
	      return 255;
	  case 181 ... 239:
	      // decreasing
	      //return (255 * ((60 - (num - 180)) / 60.0));
	      return (255 * ((240 - num) / 60.0));
	  case 240 ... 360:
	      // zero
	      return 0;
	}
    }

  private:
    // This vector has size == num_disks, the number of disks in the game.
    // Each disk has a distinctive unique color, and each one of these elements holds the color of that disk.
    vector<color> colors;

#ifdef COLORS
    SDL_Window* window;
    SDL_Renderer* renderer;
#endif
};


int main()
{
    size_t num_colors = 0;
    cout << "How many colors do you want?\n > " << flush;
    cin  >> num_colors;

#ifdef COLORS
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
#endif

#ifdef COLORS
    Drawer drawer(window, renderer, num_colors);
#else
    Drawer drawer(num_colors);
#endif
    drawer.draw();

#ifdef COLORS
    /* This chunk of code is responsible for safely exiting the program. */

    /* Deallocate dynamic memory for the window and the renderer. */
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    /* Quit the SDL subsystems and free up any additional used resources. */
    SDL_Quit();
#endif

    return EXIT_SUCCESS;
}

