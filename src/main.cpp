#include "DrawingWindow.h"

#define WIDTH 512
#define HEIGHT 512

void update(DrawingWindow &window) {

}

void handleEvent(SDL_Event event, DrawingWindow &window) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) {
		} else if (event.key.keysym.sym == SDLK_RIGHT) {
		} else if (event.key.keysym.sym == SDLK_UP) {
		} else if (event.key.keysym.sym == SDLK_DOWN) {
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			window.savePPM("output.ppm");
		}
	}
}

int main(int argc, char *argv[]) {
	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);
	SDL_Event event;
	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window);
		update(window);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
