/*
 * DebugState.h
 *
 * Created by tursh on 8/16/20.
*/

#pragma once

#include <GUI/Panel.h>
#include <State/State.h>
#include <GLFW/glfw3.h>

class DebugState : public CGE::State::State
{

public:
    virtual void tick() override;

    virtual void draw() override;

    DebugState();

private:

    CGE::GUI::Panel *pausePanel;

    void keyCallback(GLFWwindow *window, int key, int action);
};


