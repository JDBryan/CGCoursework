#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <limits>
#include "SDL.h"
#include "Colour.h"

class DrawingWindow {

public:
	size_t width;
	size_t height;

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	std::vector<uint32_t> pixelBuffer;
	std::vector<float> depthBuffer;


public:
	DrawingWindow();
	DrawingWindow(int w, int h, bool fullscreen);
	void renderFrame();
	void savePPM(const std::string &filename) const;
	void saveBMP(const std::string &filename) const;
	bool pollForInputEvents(SDL_Event &event);
	void setPixelColour(size_t x, size_t y, float z, Colour colour);
	void hardSetPixelColour(size_t x, size_t y, float z, Colour colour);
	void clearPixels();
};

void printMessageAndQuit(const std::string &message, const char *error);
