/*
 * DebugState.cpp
 *
 * Created by tursh on 8/16/20.
*/

#include <States/DebugState.h>
#include <GUI/Panel.h>
#include <GUI/GUIManager.h>
#include <IO/Input.h>
#include <GUI/Text/TextRenderer.h>
#include <Utils/TimeUtils.h>

namespace OW
{

    using namespace CGE;

    DebugState::DebugState()
    {
        IO::input::setYourOwnKeyCallBack(
                std::bind(&DebugState::keyCallback, this, std::placeholders::_1, std::placeholders::_2,
                          std::placeholders::_3)
        );

        //The pause panel is simply so the mouse callback get stopped
        pausePanel = new GUI::Panel({0, 0}, {0, 0}, CGE::GUI::IMAGE,
                                    std::bind(&DebugState::keyCallback, this, nullptr,
                                              std::placeholders::_1,
                                              std::placeholders::_2), false);
        pausePanel->setVisibility(false);
        GUI::GUIManager::addComponent(pausePanel);
    }

    void DebugState::tick()
    {
        world.tick();
    }

    void DebugState::draw()
    {
        world.render();

        GUI::Text::TextRenderer::renderText("FPS: " + std::to_string(Utils::getFPS()).substr(0, 4) + " TPS: " +
                                            std::to_string(Utils::TPSClock::getTPS()).substr(0, 4), {0.66f, 0.95f},
                                            0.1f,
                                            glm::vec3(1, 1, 1),
                                            false);
    }

    void DebugState::keyCallback(GLFWwindow *window, int key, int action)
    {
        if (key == GLFW_KEY_G && action == GLFW_PRESS)
            CGE::IO::input::toggleGrabMouse();
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            pausePanel->setVisibility(!pausePanel->getVisibility());
            CGE::IO::input::ungrabMouse();
        }
    }

}