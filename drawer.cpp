#include "hanoi.h"
#include "drawer.h"

#include "SDL.h"


Drawer::Drawer(SDL_Window* window, SDL_Renderer* renderer, size_t num_disks) : window{window}, renderer{renderer}, num_disks{num_disks}
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


short int Drawer::get_color_channel(int num)
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
    return 0;  // To remove warning.
}


void Drawer::draw_Hanoi(const Hanoi& hanoi)
{
    // Handle events just before drawing a "frame".
    handleEvents();

    drawBackground(renderer);

    // The varies values get calculated during the runtime.
    // x = varies, y = varies, w = varies, h = 15 always
    SDL_Rect disk = { 0, 0, 0, 15};

    // The first pole starts at x = 112.
    int pole_x = 112;
    // The bottom disk always starts flat on the floor.
    // Each disk is 15 high.
    int disk_y = 455;

    // Start at the bottom disk.
    Disk* temp = hanoi.tower1.bot_disk;
    while (temp != nullptr) {
        // 10 for the pole, 7 * (temp-> number + 1) on both sides.
        disk.w = (temp->number + 1) * 7 * 2 + 10;
        // The disk starts 7 * (temp->number + 1) before the start of the pole.
        disk.x = pole_x - (temp->number + 1) * 7;
        disk.y = disk_y;

        // Draw the disk.
        SDL_SetRenderDrawColor(renderer, colors[temp->number].r, colors[temp->number].g, colors[temp->number].b, 255);
        SDL_RenderFillRect(renderer, &disk);

        // Update the relevant variables.
        temp = temp->next;
        // Set the initial y-position of the next disk.
        disk_y -= 20;  // Each disk is 15 high, and there is 5 space between the disks.
    }

    // The second pole starts at x = 305.
    pole_x = 305;
    // The bottom disk always starts flat on the floor.
    // Each disk is 15 high.
    disk_y = 455;

    // Start at the bottom disk.
    temp = hanoi.tower2.bot_disk;
    while (temp != nullptr) {
        // 10 for the pole, 7 * (temp-> number + 1) on both sides.
        disk.w = (temp->number + 1) * 7 * 2 + 10;
        // The disk starts 7 * (temp->number + 1) before the start of the pole.
        disk.x = pole_x - (temp->number + 1) * 7;
        disk.y = disk_y;

        // Draw the disk.
        SDL_SetRenderDrawColor(renderer, colors[temp->number].r, colors[temp->number].g, colors[temp->number].b, 255);
        SDL_RenderFillRect(renderer, &disk);

        // Update the relevant variables.
        temp = temp->next;
        // Set the initial y-position of the next disk.
        disk_y -= 20;  // Each disk is 15 high, and there is 5 space between the disks.
    }

    // The third pole starts at x = 498.
    pole_x = 498;
    // The bottom disk always starts flat on the floor.
    // Each disk is 15 high.
    disk_y = 455;

    // Start at the bottom disk.
    temp = hanoi.tower3.bot_disk;
    while (temp != nullptr) {
        // 10 for the pole, 7 * (temp-> number + 1) on both sides.
        disk.w = (temp->number + 1) * 7 * 2 + 10;
        // The disk starts 7 * (temp->number + 1) before the start of the pole.
        disk.x = pole_x - (temp->number + 1) * 7;
        disk.y = disk_y;

        // Draw the disk.
        SDL_SetRenderDrawColor(renderer, colors[temp->number].r, colors[temp->number].g, colors[temp->number].b, 255);
        SDL_RenderFillRect(renderer, &disk);

        // Update the relevant variables.
        temp = temp->next;
        // Set the initial y-position of the next disk.
        disk_y -= 20;  // Each disk is 15 high, and there is 5 space between the disks.
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
}


void Drawer::drawBackground(SDL_Renderer* renderer)
{
    // Light sand tan.
    // r = 200, g = 170, b = 120. a = 255 (solid)
    SDL_SetRenderDrawColor(renderer, 200, 170, 120, 255);
    // Fill the screen with this color.
    SDL_RenderClear(renderer);

    // This rectangle represents a tower pole.
    // It is reused and moved around for drawing multiple such rectangles, or tower poles.
    // The first pole starts at x = 112.
    // x = 112, y = 100, w = 10, h = 370
    SDL_Rect tower_pole = { 112, 100, 10, 370 };
    // Dark navy blue.
    // r = 0, g = 20, b = 70, a = 255 (solid)
    SDL_SetRenderDrawColor(renderer, 0, 20, 70, 255);
    SDL_RenderFillRect(renderer, &tower_pole);
    // The second pole starts at x = 305.
    tower_pole.x = 305;
    SDL_RenderFillRect(renderer, &tower_pole);
    // The third pole starts at x = 498.
    tower_pole.x = 498;
    SDL_RenderFillRect(renderer, &tower_pole);

    // This rectangle is the floor on the bottom.
    // x = 0, y = 470, w = 640, h = 10  NOTE: screen is w = 640, h = 480
    SDL_Rect floor = { 0, 470, 640, 10 };
    // Black.
    // r = 0, g = 0, b = 0, a = 255 (solid)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &floor);

    // Make all the saved changes to the state show up on the screen.
    SDL_RenderPresent(renderer);
    //SDL_Delay(10000);
}


void Drawer::handleEvents()
{
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
	  case SDL_KEYDOWN:
	      // If the key pressed was 'q', it goes straight down past the if () statement.
	      // All other keys go into the if () statement.
	      if (event.key.keysym.sym != SDLK_q) {
	          // If the control key was pressed.
	          if (event.key.keysym.sym == SDLK_RCTRL || event.key.keysym.sym == SDLK_LCTRL) {
		      // Get the 'c' character key pressed from the event queue.
		      // The Ctrl and 'c' keys being pressed are separate events.
		      SDL_PollEvent(&event);
		      // Invert the desired conditional statement.
		      // If anything other than the 'c' key was pressed, do nothing and return.
		      // Else if the 'c' key was pressed, we go out of the conditional statement and
		      // fall down the switch cases.
		      if (!(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c)) {
		          return;
		      }
		  // Any other key was pressed, do nothing and return.
		  } else {
	              return;
		  }
	      }
	  case SDL_QUIT:
	  case SDL_WINDOWEVENT_CLOSE:
	      SDL_DestroyWindow(window);
	      SDL_DestroyRenderer(renderer);
	      SDL_Quit();
	      exit(EXIT_SUCCESS);
	}
    }
}
