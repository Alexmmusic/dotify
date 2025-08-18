//*****************************************************************************
//
//							Modified version of TRIOPS GAME ENGINE (to be released soon)
//							For Dotify Program
//							By Alejandro Martinez Manzano 
//							18/09/2025
//							contact: alemartinezman@gmail.com
//
//*****************************************************************************

#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>





#define DEBUG std::cout<<
#define END <<std::endl


//#include "gameEngineImage.h"
//
//
//#include "GameObject.h"
class TGameEngine
{
private:

	float deltaTimeVar = 0;
	int fadeOutIterator = 0;
	bool TTFInitialized = false;
	int charIndex = 0;
	int textTimeIterator = 0;
	
	bool audio = false;
	SDL_Rect fadeOutRect = { 0,0,0,0 };


public:
	struct datosObjetos {
		int  id, x, y, w, h;
		
	};

	//INITIALIZATION
	int StartSystem(Uint32, bool);
	SDL_Window* CreateWindowEng(std::string windowName, int x0, int y0, int w0, int h0, Uint32 flags);
	SDL_Surface* CreateSurface(SDL_Window* window);
	SDL_Renderer* CreateRenderer(SDL_Window* window, int index, Uint32 flags);





	

	//RENDER CLEAN AND REFRESH
	void RefreshRenderer(SDL_Renderer* renderer);
	void CleanRenderer(SDL_Renderer* renderer);
	//Calculates deltaTime and stores it in deltaTimeVar
	

	

	//TRUE TYPE FONT OPERATIONS
	TTF_Font* LoadFont(std::string path, int size);
	void CloseFont(TTF_Font* _font);
	//Renders a text starting at (x0, y0) with automatic size
	void RenderText(std::string text, TTF_Font* font, int color, SDL_Renderer* renderer, int x0, int y0);
	//Renders a text starting at (x0, y0) with (w0, h0) size
	void RenderText(std::string text, TTF_Font* font, int color, SDL_Renderer* renderer, int x0, int y0, const int w0, const int h0);





	void RenderText(std::string text, TTF_Font* font,const Uint8 r,const Uint8 g,const Uint8 b, SDL_Renderer* renderer, int x0, int y0, const int w0, const int h0);
	

	//ENDING
	void Quit(SDL_Window* window, SDL_Renderer* renderer);
	bool isTTFInitialized() const;
	
	

};