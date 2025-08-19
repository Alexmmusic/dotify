#include "normalizador.h"
#include <filesystem>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
}

#include "include/TGameEngine.h"

void getConsoleSize(int& columns, int& rows);
void GuardarPantallaComoPNG(SDL_Renderer* renderer, const std::string& nombreArchivo);

int main(){

cout<<"*************DOTIFY 1.0*************"<<endl;


 int width, height, channels, columns, rows, srcY;

   
    cout<<"Write the path to the image you want to convert and press Enter to start"<<endl;
    cout<<"(Before pressing Enter, adjust the size of the Terminal, as it will be the size of the converted image)"<<endl;
    cout<<"path: ";

    
    string file;
    cin>>file;
    
    getConsoleSize(columns, rows);
  color arrayColores[rows][columns];
 
    
   
    unsigned char* data =  stbi_load(file.c_str(), &width, &height, &channels, 3); //Cargar imagen


    if(data==nullptr){
        cerr<<"Fail at stbi_load()\n" << stbi_failure_reason() <<endl;
        return 1;
    }
    else{
            //DIBUJAR EN COSOLA
   for (int y = 0; y < rows; y++) {
    srcY = y * height / rows; // Mapeo proporcional vertical -- ¿Que pixel de la imagen original vamos a coger?

    for (int x = 0; x < columns; x++) {
        int srcX = x * width / columns; // Mapeo proporcional horizontal -- ¿Que pixel de la imagen original vamos a coger

        int index = (srcY * width + srcX) * channels; //srcY * width = Pixeles que hay hasta el que yo quiero; + srcX = offset para X - En un array como data, que esta 
                                                      //todo en linea, es el offset necesario. Puesto que cada pixel contiene 3 canales (RGB) es necesario multiplicar
                                                      //por 3 (channels) para encontrar el pixel real.
        arrayColores[y][x] = {data[index], data[index+1], data[index +2]};
        printRGB(data[index], data[index + 1], data[index + 2], "*");
    }
    std::cout << "\n";
    }
    
    }







int option=0;
bool bucle = true;
cout<<"Do you want to save the image as JPG (1) or close the program (2)?: "<<endl;
cin>>option;

while(bucle==true){
if(option==1){

cout<<"Write file name: ";
string imageName;
cin>>imageName;

    TGameEngine engine;
unsigned int anchoVentana = columns * 10;
unsigned int altoVentana = rows * 20;

    engine.StartSystem(SDL_INIT_EVERYTHING, true);
    SDL_Window* ventana = engine.CreateWindowEng("main", 0,0, anchoVentana, altoVentana, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = engine.CreateRenderer(ventana, -1, 0);
     TTF_Font* fuente = nullptr;
     #ifdef _WIN32
     engine.LoadFont("fonts/firaMono.ttf", 11)
     #else
     engine.LoadFont("/usr/share/fonts/dotify/firaMono.ttf", 11);
     #endif

     if(fuente==nullptr) return 1;
 

bool running = true;
SDL_Event event;
engine.CleanRenderer(renderer);
    // //DIBUJAR EN SDL

for(int yBucleDos = 0; yBucleDos<rows; yBucleDos++){
    for(int e = 0; e<columns; e++){
        engine.RenderText("*", fuente, arrayColores[yBucleDos][e].R, arrayColores[yBucleDos][e].G, arrayColores[yBucleDos][e].B,renderer, e*10, yBucleDos*20, 10,20);
    }
}
  
engine.RefreshRenderer(renderer);
SDL_Delay(100);




 

   GuardarPantallaComoPNG(renderer, imageName);


    stbi_image_free(data);
    if(fuente!=nullptr){
         engine.CloseFont(fuente);
     }
    engine.Quit(ventana, renderer);

    bucle = false;
}
else if(option==2){
    return 0;
}
else{
    cout<<"Choose a valid option: ";
    cin>>option;
}
}
return 0;



}//main

void getConsoleSize(int& columns, int& rows) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    } else {
        columns = 80;
        rows = 25;
    }
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        columns = w.ws_col;
        rows = w.ws_row;
    } else {
        columns = 80;
        rows = 25;
    }
#endif
}



void GuardarPantallaComoPNG(SDL_Renderer* renderer,const std::string& nombreArchivo) {
   
   string ruta;
    #ifdef _WIN32
    
    ruta = std::string(getenv("USERPROFILE")) + "\\Dotify\\saved";
    #else
    
    ruta = std::string(getenv("HOME")) + "/Dotify/saved";
    #endif

  
    if (!std::filesystem::exists(ruta)) {
    std::filesystem::create_directories(ruta);
    }   
    string rutaConFormato = ruta + "/" + nombreArchivo + "saved.jpg";
    
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        std::cerr << "Error al crear superficie: " << SDL_GetError() << std::endl;
        return;
    }

    if (SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_RGBA32, surface->pixels, surface->pitch) != 0) {
        std::cerr << "Error al leer píxeles: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }
    IMG_SavePNG(surface, rutaConFormato.c_str());

    cout<<"File saved at: "<<rutaConFormato<<" !"<<endl;

    SDL_FreeSurface(surface);
}
