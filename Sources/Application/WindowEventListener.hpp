#pragma once

#include <Core/Core.hpp>

namespace gir
{
    class WindowEventListener
    {
    public:
        virtual ~WindowEventListener() = default;

        /// Event called when the user attempts to close the window.
        virtual void OnWindowClosed() {}

        /// Event called when the size of the window has changed.
        virtual void OnWindowResize(int width, int height) {}

        /// Event called when a key is pressed.
        virtual void OnKeyPressed(int keyCode) {}

        /// Event called when a key is released.
        virtual void OnKeyReleased(int keyCode) {}

        /// Event called when a mouse button is pressed.
        virtual void OnMousePressed(int button) {}

        /// Event called when a mouse button is released.
        virtual void OnMouseReleased(int button) {}

        /// Event called when the mouse position changed.
        virtual void OnMouseMoved(double xPos, double yPos) {}

        /// Event called when a scrolling device is used.
        virtual void OnMouseScrolled(double xOffset, double yOffset) {}
    };
}