#include "DrawingWindow.h"
#include "CanvasLine.h"
#include "CanvasTriangle.h"
#include "Model.h"
#include "Ray.h"
#include "Utils.h"

#define WIDTH 512
#define HEIGHT 512

void update(DrawingWindow &window, Camera &camera, Model &model) {
	window.clearPixels();
	model.fillRayTracing(window, camera, 500);
}

void handleEvent(SDL_Event event, DrawingWindow &window, Camera &camera, Model model) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) {
			camera.pan(0.1);
		} else if (event.key.keysym.sym == SDLK_RIGHT) {
			camera.pan(-0.1);
		} else if (event.key.keysym.sym == SDLK_UP) {
			camera.tilt(0.1);
		} else if (event.key.keysym.sym == SDLK_DOWN) {
			camera.tilt(-0.1);
		} else if (event.key.keysym.sym == SDLK_w) {
			camera.translate(0,0,-1);
		} else if (event.key.keysym.sym == SDLK_a) {
			camera.roll(-0.1);
		} else if (event.key.keysym.sym == SDLK_s) {
			camera.translate(0,0,1);
		} else if (event.key.keysym.sym == SDLK_d) {
			camera.roll(0.1);

		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			window.savePPM("output.ppm");
		} else if (event.key.keysym.sym == SDLK_u) {
			
    } else if (event.key.keysym.sym == SDLK_f) {

    }
		//update(window, camera, model);
	}
}

int main(int argc, char *argv[]) {
	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);
	Camera camera = Camera(0, 0, 4, 2);
	TextureMap texture = TextureMap("assets/texture.ppm");
	Model cornellBox = Model("assets/", "cornell-box.obj", 0.17);
	SDL_Event event;
	time_t start_time = time(NULL);
	cornellBox.fillRayTracing(window, camera, 500);
	time_t end_time = time(NULL);
	std::cout << end_time - start_time << std::endl;
	//cornellBox.fill(window, camera, 1);

	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window, camera, cornellBox);
		//update(window, camera, cornellBox);

		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
