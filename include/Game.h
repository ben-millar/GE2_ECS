#include <string>
#include <array>
#include <SDL.h>
#include <SDL_image.h>

#include "Debug.h"
#include "Clock.h"

#include <Coordinator.h>
#include <AISystem.h>
#include <ControlSystem.h>
#include <HealthSystem.h>
#include <PhysicsSystem.h>
#include <RenderSystem.h>

class Game
{
private:
    SDL_Window* _window{ nullptr };
    SDL_Renderer* _renderer{ nullptr };
    bool _isRunning{ true };

    AISystem* _aiSystem;
    ControlSystem* _controlSystem;
    HealthSystem* _healthSystem;
    PhysicsSystem* _physicsSystem;
    RenderSystem* _renderSystem;

    Entity _player, _villain, _cortana, _dinkyDi;

public:
    Game() = default;
    ~Game() = default;

    void run();
    void processEvents();
    void update(Time t_dT);
    void render();
    void cleanUp();

    inline bool isRunning() { return _isRunning; }
};