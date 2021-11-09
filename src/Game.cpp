#include "../include/Game.h"
#include <stdio.h>

void Game::run()
{
    m_window = SDL_CreateWindow("GE2 | ECS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 768, SDL_WINDOW_INPUT_FOCUS);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (!(m_window && m_renderer)) {
        printf("Something went wrong while creating the SDL window and renderer: %s\n", SDL_GetError());
        exit(1);
    }

    Clock clock;
    Time lag(0U);
    const Time MS_PER_UPDATE = 1000U / 60U;
    clock.start();

    while (m_isRunning)
    {
        Time dT = clock.restart();
        lag += dT;
        processEvents();

        while (lag > MS_PER_UPDATE)
        {
            update(MS_PER_UPDATE);
            lag -= MS_PER_UPDATE;
        }

        update(dT);
        render();
    }
}

////////////////////////////////////////////////////////////

void Game::processEvents()
{
    SDL_Event sdl_event;
    while (SDL_PollEvent(&sdl_event))
    {
        if (SDL_QUIT == sdl_event.type)
            m_isRunning = false;
    }
}

////////////////////////////////////////////////////////////

void Game::update(Time t_dT)
{
}

////////////////////////////////////////////////////////////

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    SDL_RenderPresent(m_renderer);
}

////////////////////////////////////////////////////////////

void Game::cleanUp()
{
    SDL_Quit();
}