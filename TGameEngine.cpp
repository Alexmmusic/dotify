#include "TGameEngine.h"


//Initializes the SDL systems provided, as well as the PNG and JPG systems from SDL_Image and the TTF system if wanted. It must always be at the beginning of the program.
// If any subsystem fails to initialize correctly, the function will return -1
//_flags:
//SDL_INIT_TIMER - TIMER SUBSYSTEM
//SDL_INIT_AUDIO - AUDIO SUBSYSTEM
//SDL_INIT_VIDEO - VIDEO SUBSYSTEM
//SDL_INIT_JOYSTICK - JOYSTICK SUBSYSTEM
//SDL_INIT_HAPTIC
//SDL_INIT_GAMECONTROLLER - GAMECONTROLLER SUBSYSTEM (ALSO STARTS JOYSTICK SUBSYSTEM)
//SDL_INIT_EVENTS - FOR EVENTS HANDLING
//SDL_INIT_EVERYTHING - INTIALIZES ALL SYSTEM (RECOMMENDED)
//SDL_INIT_NOPARACHUTE - DON'T USE
int TGameEngine::StartSystem(Uint32 _flags, bool text) {
	if (SDL_Init(_flags) < 0) {
		std::cout << "Error in SDL_Init" << SDL_GetError() << std::endl;
		return -1;
	}
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "Error at IMG_init:", IMG_GetError();
		return -1;
	}
	if (text == true) {
		if (TTF_Init() == -1)
		{
			std::cerr << "Error starting TTF: " << TTF_GetError() << std::endl;
			return -1;
		}
		else TTFInitialized = true;
	}

	

	return 0;
}


//Creates a window
//You can create as many windows as you want with this
//If there is any error win the window creation, the function will return nullptr
//flags:
//SDL_WINDOW_FULLSCREEN - Creates the window in fullscreen mode
//SDL_WINDOW_FULLSCREEN_DESKTOP - Fullscreen mode but fixes to the screen resolution
//SDL_WINDOW_OPENGL - Creates a window with OpenGL support
//SDL_WINDOW_VULKAN - Creates a window with Vulkan support
//SDL_WINDOW_SHOWN - The window will be visible at creation
//SDL_WINDOW_HIDDEN - Window will by hidden by default
//SDL_WINDOW_BORDERLESS - the window will be borderlees
//SDL_WINDOW_RESIZABLE - resizable window
//SDL_MINIMIZED 
//SDL_MAXIMIZED
//SDL_WINDOW_INPUT_GRABBED - The mouse cant exit the game window
//SDL_WINDOW_MOUSE_FOCUS 
//SDL_WINDOW_INPUT_FOCUS
//SDL_WINDOW_HIGH_PIXEL_DENSITY - For macOS
SDL_Window* TGameEngine::CreateWindowEng(std::string windowName, int x0, int y0, int w0, int h0, Uint32 flags)
{
	SDL_Window* window = SDL_CreateWindow(windowName.c_str(), x0, y0, w0, h0, flags);
	if (window == NULL) {
		std::cout << "Error in SDL_CreateWindow: ", SDL_GetError();
		return nullptr;
	}
	return window;
}

//Creates a Surface structure, essential for handling pixels and images in SDL2.The window in which the surface is to be created is passed as a parameter.
SDL_Surface* TGameEngine::CreateSurface(SDL_Window* window)
{
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	if (surface == NULL) {
		DEBUG "Error in SDL_GetWindowSurface" << SDL_GetError() END;
		return nullptr;
	}
	return surface;
}

//Creates the texture renderer. TGameEngine works with textures so the texture renderer is necessary
//index - which renderer driver will be selected:
// -1 = SDL Will select the first compatible driver
// Starting from 0, the controller in the list corresponding to the index will be selected.
// You can use the SDL_GetNumRenderDrivers() function to obtain the total number of available drivers 
// and the SDL_GetRenderDriverInfo() function to get information about each driver, 
// such as its name and capabilities. This can help you decide which index to use.
// flags: 
// SDL_RENDERER_SOFTWARE: software base render
// SDL_RENDERER_ACCELERATED: uses hardware accelerated renderer if able
// SDL_RENDERER_PRESENTVSYNC: enables Vsync
// SDL_RENDERER_TARGETTEXTURE
SDL_Renderer* TGameEngine::CreateRenderer(SDL_Window* window, int index, Uint32 flags)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window, index, flags);
	if (renderer == NULL) {
		std::cout << "ERROR SDL_CreateRenderer: " << SDL_GetError();
	}
	return renderer;
}








void TGameEngine::RefreshRenderer(SDL_Renderer* renderer)
{
	SDL_RenderPresent(renderer);
}

void TGameEngine::CleanRenderer(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Color negro
	SDL_RenderClear(renderer);
}







//Loads a TTF font located at the specified path with a given size.
TTF_Font* TGameEngine::LoadFont(std::string path, int size)
{
	TTF_Font* font = TTF_OpenFont(path.c_str(), size);
	if (!font) {
		std::cerr << "Error at LoadFont() " << TTF_GetError() << std::endl;
		TTF_Quit();
		return nullptr;
	}
	return font;
}

void TGameEngine::CloseFont(TTF_Font* _font)
{
	if (_font != nullptr) {
		TTF_CloseFont(_font);
	}

}

//Prints a text at a position (x0, y0) with a previously loaded font.
//Color:
// 0 black
// 1 white
// 2 blue
// 3 green
// 4 red
//default black
void TGameEngine::RenderText(std::string text, TTF_Font* font, int color, SDL_Renderer* renderer, int x0, int y0)
{
	SDL_Color colorUso = { 0,0,0,0 };
	switch (color) {
	case 0: //black
		colorUso = { 0,0,0,255 };
		break;
	case 1: //white
		colorUso = { 255,255,255,255 };
		break;
	case 2: //blue
		colorUso = { 0,0,255,255 };
		break;
	case 3: //green
		colorUso = { 0, 255, 0,255 }; 
		break;
	case 4: //red
		colorUso = { 255, 0, 0,255 }; 
		break;
	default:
		colorUso = { 0,0,0,255 }; //black
		break;
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), colorUso);

	if (!textSurface) {
		std::cerr << "Error al crear la superficie de texto en funcion ImprimirTexto(): " << TTF_GetError() << std::endl;
		TTF_CloseFont(font);
	}
	if (textSurface->w == 0) {
		textSurface->w = 1;
	}
	if (textSurface->h == 0) {
		textSurface->h = 1;
	}

	SDL_Rect textRect;
	textRect.x = x0; // Posici�n X
	textRect.y = y0; // Posici�n Y
	textRect.w = textSurface->w; // Ancho del texto
	textRect.h = textSurface->h; // Altura del texto





	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	if (!textTexture) {
		std::cerr << "Error at RenderText():  " << SDL_GetError() << std::endl;
		TTF_CloseFont(font);
	}

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);





}

void TGameEngine::RenderText(std::string text, TTF_Font* font, int color, SDL_Renderer* renderer, int x0, int y0, const int w0, const int h0)
{
	SDL_Color colorUso = { 0,0,0,0 };
	switch (color) {
	case 0: //black
		colorUso = { 0,0,0,255 };
		break;
	case 1: //white
		colorUso = { 255,255,255,255 };
		break;
	case 2: //blue
		colorUso = { 0,0,255,255 };
		break;
	case 3: //green
		colorUso = { 0, 255, 0,255 };
		break;
	case 4: //red
		colorUso = { 255, 0, 0,255 };
		break;
	default:
		colorUso = { 0,0,0,255 }; //black
		break;
	}

	if (font != nullptr) {
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), colorUso);
		if (!textSurface) {
			std::cerr << "Error al crear la superficie de texto en funcion ImprimirTexto(): " << TTF_GetError() << std::endl;
			TTF_CloseFont(font);
		}
		if (textSurface->w == 0) {
			textSurface->w = 1;
		}
		if (textSurface->h == 0) {
			textSurface->h = 1;
		}
		SDL_Rect textRect;
		textRect.x = x0; // Posici�n X
		textRect.y = y0; // Posici�n Y
		textRect.w = w0; // Ancho del texto
		textRect.h = h0; // Altura del texto





		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);
		if (!textTexture) {
			std::cerr << "Error at RenderText():  " << SDL_GetError() << std::endl;
			TTF_CloseFont(font);
		}

		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
	}
	

	

}

void TGameEngine::RenderText(std::string text, TTF_Font* font,const Uint8 r,const Uint8 g,const Uint8 b, SDL_Renderer* renderer, int x0, int y0, const int w0, const int h0)
{
	SDL_Color colorUso = { r,g,b,255 };

	if (font != nullptr) {
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), colorUso);
		if (!textSurface) {
			std::cerr << "Error al crear la superficie de texto en funcion ImprimirTexto(): " << TTF_GetError() << std::endl;
			TTF_CloseFont(font);
		}
		SDL_Rect textRect;
		textRect.x = x0; // Posici�n X
		textRect.y = y0; // Posici�n Y
		textRect.w = w0; // Ancho del texto
		textRect.h = h0; // Altura del texto





		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);
		if (!textTexture) {
			std::cerr << "Error at RenderText():  " << SDL_GetError() << std::endl;
			TTF_CloseFont(font);
		}

		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
	}
	

	

}









 
void TGameEngine::Quit(SDL_Window* window, SDL_Renderer* renderer)
{
	if (window != nullptr) {

		SDL_DestroyWindow(window);
		window = nullptr;
	}
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (TTFInitialized) TTF_Quit();
	
	

	SDL_Quit();
}

bool TGameEngine::isTTFInitialized() const
{
	return TTFInitialized;
}

//void TGameEngine::MostrarTexturaConViewport(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* viewport) {
//	//SDL_RenderClear(renderer);
//	if (SDL_RenderSetViewport(renderer, viewport) < 0) {
//		std::cout << "ERROR en RenderSetViewport (MostrarTexturaConViewport)" << SDL_GetError() << "\n";
//	}
//	//Render texture to screen
//	else SDL_RenderCopy(renderer, texture, NULL, NULL);
//}



