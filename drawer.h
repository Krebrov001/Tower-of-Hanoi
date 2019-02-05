#ifndef DRAWER_H
#define DRAWER_H

#include "hanoi.h"

#include "SDL.h"    // Simple DirectMedia Layer API structures and functions
// Some of these includes are also in the file hanoi.h
// However they will not be included twice because their header guards will prevent it,
// so it's safe to write these includes here also.
// I am writing these includes here also to explicitly specify which portions of the standard library
// are used by the class Drawer and it's member functions.
#include <cstdlib>  // for std::size_t
#include <vector>   // for std::vector

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
    Drawer(SDL_Window* window, SDL_Renderer* renderer, size_t num_disks);

    /**
     * Returns a 
     */
    short int get_color_channel(int num);

    /**
     * This function draws the Hanoi object of the game, which is simply a collection of three towers.
     * It draws a single "frame" of the game, when the exact position of all the disks is known.
     *
     * The current state of each tower, 1 through 3, is drawn.
     * All the disks currently in each tower are drawn with their respective colors.
     * The disks are drawn from the bottom to top on each tower.o
     *
     * This function also calls drawBackground().
     * It first draws the background, then it draws the disks.
     *
     * This function also calls handleEvents() before drawing anything,
     * so that the program will be responsive to commands from the user to terminate it.
     *
     * @param const Hanoi& hanoi - The Hanoi object containing the state of the game and
     *                             all it's respective  data structures.
     */
    void draw_Hanoi(const Hanoi& hanoi);

    /**
     * Draws the background over which all the disks will be drawn.
     * This includes the background itself, as well as the poles for the towers and the floor on which they stand.
     *
     * @param SDL_Renderer* renderer - Necessary to draw on the screen.
     */
    void drawBackground(SDL_Renderer* renderer);

    /**
     * This function allows the program to react to events from the outside world.
     * This function is called inside draw_Hanoi().
     *
     * If the user enters a large number of disks, such as 10, it will take very long for the animation
     * showing the disks moving around to stop; it will take many steps to get all the disks onto tower3.
     * The user might get impatient and would want to close the program prematurely.
     *
     * This function gets an event from the event queue,
     * and it will close the program window if the user signals that they want to quit the program.
     * If any other event will be gotten, it will simply be ignored.
     *
     * We allow the user to close the program two ways:
     * - by hitting the 'q' key on the keyboard.
     * - by typing Ctrl-C.
     *
     * Typing Ctrl-C will result in an SDL_QUIT event being created on most systems, but not all.
     * To enable Ctrl-C on those systems which do not provide explicit support for it,
     * I devised a solution to first listen for the RCTRL (right control) or LCTRL (left control) key getting hit,
     * then listen for the 'c' key getting hit.
     * If both keys get hit in sequence, then it means that the user provided Ctrl-C to the program.
     *
     * SDL_WINDOWEVENT_CLOSE gets generated if the window is closed unexpectedly.
     */
    void handleEvents();

  private:
    // This vector has size == num_disks, the number of disks in the game.
    // Each disk has a distinctive unique color, and each one of these elements holds the color of that disk.
    vector<color> colors;

    SDL_Window* window;
    SDL_Renderer* renderer;

    size_t num_disks;

    // Used for event handling.
    SDL_Event event;
};

#endif /* DRAWER_H */

