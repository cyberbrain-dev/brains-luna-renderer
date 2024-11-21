#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>

// SDL window instance
SDL_Window* window = NULL;
// SDL renderer instance
SDL_Renderer* renderer = NULL;

// An array, representing color buffer - a collection of pixel colors, that should be rendered
uint32_t* color_buffer = NULL;
// A texture that the color buffer is translated to and which is able to be rendered by SDL
SDL_Texture* color_buffer_texture = NULL;

int window_width = 800;
int window_height = 600;

// Indicates whether the gameloop is running or not
bool is_running = false;


// Updates the SDL texture with our color buffer and copies the texture to the rendering rarget
void translate_color_buffer(void)
{
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int) (window_width * sizeof(uint32_t))
    );

    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

// Fills the color buffer with the color passed
void fill_color_buffer(uint32_t color)
{
    // looping through all the pixels...
    for (int y = 0; y < window_height; y++)
    {
        for (int x = 0; x < window_width; x++)
        {
            // ...and setting the color
            color_buffer[y * window_width + x] = color;
        }
    }
}
/// Draws a dotted grid with cell sizes provided
void draw_solid_grid(int cell_width, int cell_height, uint32_t color)
{
    for (int y = 0; y < window_height; y++)
    {
        for (int x = 0; x < window_width; x++)
        {
            if (y % cell_height == 0)
            {
                color_buffer[y * window_width + x] = color;
                continue;
            }

            if (x % cell_width == 0)
            {
                color_buffer[y * window_width + x] = color;
            }
        }
    }
}
/// Draws a dotted grid with cell sizes provided
void draw_dotted_grid(int cell_width, int cell_height, uint32_t color)
{
    for (int y = 0; y < window_height; y += cell_height)
    {
        for (int x = 0; x < window_width; x += cell_width)
        {
            color_buffer[y * window_width + x] = color;
        }
    }
}
// Draws a rectangle
void draw_rect(int x_pos, int y_pos, int width, int height, uint32_t color)
{
    for (int y = y_pos; y < y_pos + height; y++)
    {
        for (int x = x_pos; x < x_pos + width; x++)
        {
            color_buffer[y * window_width + x] = color;
        }
    }
}

// Creates a simple Luna window
bool initialize_window(void)
{
    // initializing SDL subsystems...
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "An error occured initializing SDL subsystems.\n");
        return false;
    }

    // using the SDL to query the resolution of my monitor...
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

    // ...and setting the resolution 
    window_width = display_mode.w;
    window_height = display_mode.h;


    // initializing a SDL window
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN
    );

    if (!window)
    {
        fprintf(stderr, "An error occured initializing SDL window.\n");
        return false;
    }


    // initializin SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        fprintf(stderr, "An error occured initializing SDL renderer.\n");
        return false;
    }


    return true;
}

// Sets up a program before the render loop
void setup(void)
{
    // allocating memory in color buffer for each pixel of the window
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

    // creating SDL texture
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
}
// Checking any input the user does 
void process_input(void)
{
    // Creating and polling the current moment event
    SDL_Event current_event;
    SDL_PollEvent(&current_event);

    // Determining the type of the event
    switch (current_event.type)
    {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (current_event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;

            break;
    }

}
// Updates the states of the different objects in program 
void update(void)
{

}
// Renders the frame 
void render(void)
{
    // Setting a base color for "empty frame"...
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    // ... and clearing the rendering target before another render
    SDL_RenderClear(renderer);

    fill_color_buffer(0xFF000000);
    draw_dotted_grid(20, 20, 0xFFFFFFFF);
    draw_rect(100, 123, 60, 43, 0xFF00FFFF);

    // preparing the color buffer to render
    // * after that the color buffer can be modified without impact on rendering target
    translate_color_buffer();


    // Updating the screen
    SDL_RenderPresent(renderer);
}

// Releases all the resources the window has been using
void destroy_window(void)
{
    free(color_buffer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}


int main()
{
    is_running = initialize_window();


    // A simple game loop is down there...
    setup();

    while (is_running)
    {
        process_input();
        update();
        render();
    }

    destroy_window();


    return 0;
}
