#include <Game.h>
#include <stdio.h>

void Game::run()
{
    _window = SDL_CreateWindow("GE2 | ECS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 768, SDL_WINDOW_INPUT_FOCUS);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if (!(_window && _renderer)) {
        printf("Something went wrong while creating the SDL window and renderer: %s\n", SDL_GetError());
        exit(1);
    }

    Coordinator* coordinator = Coordinator::getInstance();
    coordinator->init();

    coordinator->registerComponent<Input>();
    coordinator->registerComponent<Gravity>();
    coordinator->registerComponent<RigidBody>();
    coordinator->registerComponent<Transform>();
    coordinator->registerComponent<Health>();
    coordinator->registerComponent<Sprite>();

    _aiSystem = coordinator->registerSystem<AISystem>();
    _controlSystem = coordinator->registerSystem<ControlSystem>();
    _healthSystem = coordinator->registerSystem<HealthSystem>();
    _physicsSystem = coordinator->registerSystem<PhysicsSystem>();
    _renderSystem = coordinator->registerSystem<RenderSystem>();

    Signature aiSignature;
    aiSignature.set(coordinator->getComponentType<Health>());
    aiSignature.set(coordinator->getComponentType<Transform>());
    coordinator->setSystemSignature<AISystem>(aiSignature);

    Signature controlSignature;
    controlSignature.set(coordinator->getComponentType<RigidBody>());
    controlSignature.set(coordinator->getComponentType<Input>());
    coordinator->setSystemSignature<ControlSystem>(controlSignature);

    Signature healthSignature;
    healthSignature.set(coordinator->getComponentType<Health>());
    coordinator->setSystemSignature<HealthSystem>(healthSignature);

    Signature physicsSignature;
    physicsSignature.set(coordinator->getComponentType<Gravity>());
    physicsSignature.set(coordinator->getComponentType<RigidBody>());
    physicsSignature.set(coordinator->getComponentType<Transform>());
    coordinator->setSystemSignature<PhysicsSystem>(physicsSignature);

    Signature renderSignature;
    renderSignature.set(coordinator->getComponentType<Transform>());
    renderSignature.set(coordinator->getComponentType<Sprite>());
    coordinator->setSystemSignature<RenderSystem>(renderSignature);

    _player = coordinator->createEntity(RigidBody(), Transform(), Gravity(), Health(), Input(), Sprite());
    _villain = coordinator->createEntity(RigidBody(), Transform(), Gravity(), Health(), Sprite());
    _cortana = coordinator->createEntity(RigidBody(), Transform(), Gravity(), Health(), Sprite());
    _dinkyDi = coordinator->createEntity(RigidBody(), Transform(), Gravity(), Sprite());

    Clock clock;
    Time lag(0U);
    const Time MS_PER_UPDATE = 1000U / 60U;
    clock.start();

    while (_isRunning)
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
            _isRunning = false;
    }
}

////////////////////////////////////////////////////////////

void Game::update(Time t_dT)
{
    _physicsSystem->update(t_dT);


}

////////////////////////////////////////////////////////////

void Game::render()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    SDL_RenderPresent(_renderer);
}

////////////////////////////////////////////////////////////

void Game::cleanUp()
{
    SDL_Quit();
}