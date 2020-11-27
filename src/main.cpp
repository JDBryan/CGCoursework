#include "DrawingWindow.h"
#include "CanvasPoint.h"
#include "CanvasLine.h"
#include "CanvasTriangle.h"
#include "Utils.h"

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
		} else if (event.key.keysym.sym == SDLK_u) {
			CanvasPoint pointA = CanvasPoint(randomNumber(0, WIDTH), randomNumber(0, HEIGHT), 0);
			CanvasPoint pointB = CanvasPoint(randomNumber(0, WIDTH), randomNumber(0, HEIGHT), 0);
			CanvasPoint pointC = CanvasPoint(randomNumber(0, WIDTH), randomNumber(0, HEIGHT), 0);
			Colour colour = Colour(randomNumber(0, 256), randomNumber(0, 256), randomNumber(0, 256));
      CanvasTriangle(pointA, pointB, pointC, colour).fill(window);
    }
	}
}

int main(int argc, char *argv[]) {
	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);
	TextureMap texture = TextureMap("assets/texture.ppm");
	SDL_Event event;

	CanvasPoint pointA = CanvasPoint(160, 10, 0);
	pointA.setTexturePoint(195,5);
	CanvasPoint pointB = CanvasPoint(300, 230, 0);
	pointB.setTexturePoint(395,380);
	CanvasPoint pointC = CanvasPoint(10, 150, 0);
	pointC.setTexturePoint(65,330);
	CanvasTriangle triangle = CanvasTriangle(pointA, pointB, pointC);
	triangle.mapTexture(window, texture);

	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window);
		update(window);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
