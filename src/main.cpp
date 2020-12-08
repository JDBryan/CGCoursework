#include "DrawingWindow.h"
#include "CanvasLine.h"
#include "CanvasTriangle.h"
#include "Model.h"
#include "Ray.h"
#include "Utils.h"
#include <chrono>

#define WIDTH 256
#define HEIGHT 256

void update(DrawingWindow &window, Camera &camera, Model &model, int renderType) {
	window.clearPixels();
	if (renderType == 0) {
		auto t1 = std::chrono::high_resolution_clock::now();
		model.drawFrame(window, camera, 500);
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1).count();
		std::cout << duration << std::endl;
	} else if (renderType == 1) {
		auto t1 = std::chrono::high_resolution_clock::now();
		model.fillWithTextures(window, camera, 500);
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1).count();
		std::cout << duration << std::endl;
	} else if (renderType == 2) {
		auto t1 = std::chrono::high_resolution_clock::now();
		model.fillRayTracing(window, camera, 500, "all", "phong");
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1).count();
		std::cout << duration << std::endl;
	}
}

int handleEvent(SDL_Event event, DrawingWindow &window, Camera &camera, int renderType, Model model) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) {
			camera.pan(-0.1);
		} else if (event.key.keysym.sym == SDLK_RIGHT) {
			camera.pan(0.1);
		} else if (event.key.keysym.sym == SDLK_UP) {
			camera.translate(0,0,-0.1);
		} else if (event.key.keysym.sym == SDLK_DOWN) {
			camera.translate(0,0,0.1);
		} else if (event.key.keysym.sym == SDLK_w) {
			camera.tilt(0.1);
		} else if (event.key.keysym.sym == SDLK_a) {
			camera.pan(-0.1);
		} else if (event.key.keysym.sym == SDLK_s) {
			camera.tilt(-0.1);
		} else if (event.key.keysym.sym == SDLK_d) {
			camera.pan(0.1);
		} else if (event.key.keysym.sym == SDLK_q) {
			camera.roll(-0.1);
		} else if (event.key.keysym.sym == SDLK_e) {
			camera.roll(0.1);
		} else if (event.key.keysym.sym == SDLK_z) {
			camera.translate(0,1,0);
		} else if (event.key.keysym.sym == SDLK_x) {
			camera.translate(0,-1,0);
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			window.savePPM("output.ppm");
		} else if (event.key.keysym.sym == SDLK_r) {
			renderType += 1;
			if (renderType == 3) {renderType = 0;}
    }
		update(window, camera, model, renderType);
	}
	return renderType;
}

int main(int argc, char *argv[]) {
	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);
	Camera camera = Camera(0, 0, 4, 2);
	TextureMap texture = TextureMap("assets/texture.ppm");
	Model sphere = Model("assets/", "sphere.obj", 0.17);
	Model cornellBox = Model("assets/", "textured-cornell-box.obj", 0.17);
	cornellBox.merge(sphere);
	cornellBox.drawFrame(window, camera, 500);
	int renderType = 0;
	SDL_Event event;



	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) renderType = handleEvent(event, window, camera, renderType, cornellBox);


		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
