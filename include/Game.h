#include <string>
#include <array>
#include <SDL.h>
#include <SDL_image.h>

#include "Debug.h"
#include "Clock.h"

#include <Coordinator.h>
#include <PhysicsSystem.h>

class Game
{
private:
    SDL_Window* m_window{ nullptr };
    SDL_Renderer* m_renderer{ nullptr };
    bool m_isRunning{ true };

public:
    Game() = default;
    ~Game() = default;

    void run();
    void processEvents();
    void update(Time t_dT);
    void render();
    void cleanUp();

    inline bool isRunning() { return m_isRunning; }
};