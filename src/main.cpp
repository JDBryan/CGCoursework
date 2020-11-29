#include "DrawingWindow.h"
#include "CanvasLine.h"
#include "CanvasTriangle.h"
#include "ModelTriangle.h"
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
			Material material = Material(Colour(randomNumber(0, 256), randomNumber(0, 256), randomNumber(0, 256)));
      CanvasTriangle(pointA, pointB, pointC, material).fill(window);
    }
	}
}

int main(int argc, char *argv[]) {
	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);
	Camera camera = Camera(0, 0, 4, 2);
	TextureMap texture = TextureMap("assets/texture.ppm");
	SDL_Event event;

	ModelPoint pointA = ModelPoint(0, 200, 0);
	ModelPoint pointB = ModelPoint(200, -200, 2);
	ModelPoint pointC = ModelPoint(-200, -50, 2);
	pointA.setTexturePoint(195, 5);
	pointB.setTexturePoint(395, 380);
	pointC.setTexturePoint(65, 330);
	ModelTriangle triangle = ModelTriangle(pointA, pointB, pointC, Material(texture));
	triangle.mapTexture(window, camera, 1);

	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window);
		update(window);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
