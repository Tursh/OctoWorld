#include <GL/glew.h>
#include <Engine.h>
#include <States/DebugState.h>
#include <State/StateManager.h>
#include <Utils/TimeUtils.h>
#include <thread>
#include <GUI/Text/TextRenderer.h>

using namespace CGE;

void init()
{
    initEngine("Octo World", IO::DEFAULT_WIDTH, IO::DEFAULT_HEIGHT, false);
    GUI::Text::TextRenderer::init("res/graphics/fonts/Archivo-Regular.ttf");
    Utils::TPSClock::init();
    State::StateManager::constructAndSetCurrentState<DebugState>();
}

void loopTick()
{
    auto display = CGE::IO::getWindow();
    while (!display->shouldClose())
    {
        while (!display->shouldClose() && CGE::Utils::TPSClock::shouldTick())
        {
            CGE::State::StateManager::getCurrentState()->tick();
        }
    }
}

void loopRender()
{
    auto display = CGE::IO::getWindow();

    while (!display->shouldClose())
    {
        CGE::State::StateManager::getCurrentState()->draw();
        display->update();
    }
}

void terminate()
{
    CGE::State::StateManager::deleteCurrentState();
    stopEngine();
}

int main()
{
    init();
    //Start asynchronously the tick and render loop
    std::thread tickThread(loopTick);
    loopRender();

    //Wait for the two loops to end
    tickThread.join();
    terminate();

    return EXIT_SUCCESS;
}
