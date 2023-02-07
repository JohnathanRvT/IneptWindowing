#pragma once

#include <map>
#include <vector>
#include <functional>

namespace Inept::Windowing
{
    class InputManagerBase
    {
    public:
        /*
        * @brief Constructor for the InputManagerBase class.
        */
        InputManagerBase() {}    /*
     * @brief Virtual destructor for the InputManagerBase class.
     */
        virtual ~InputManagerBase() = default;

        /*
         * @brief Check if a specific key is currently pressed.
         * @param key The key to check.
         * @return true if the key is pressed, false otherwise.
         */
        virtual bool IsKeyPressed(int key) = 0;

        /*
         * @brief Check if a specific mouse button is currently pressed.
         * @param button The button to check.
         * @return true if the button is pressed, false otherwise.
         */
        virtual bool IsMouseButtonPressed(int button) = 0;

        /*
         * @brief Get the current position of the mouse.
         * @return A pair of x and y coordinates representing the position of the mouse.
         */
        virtual std::pair<int, int> GetMousePosition() = 0;

        /*
         * @brief Get the current state of all keys.
         * @return A map of key codes to their current state (true for pressed, false for released).
         */
        virtual std::map<int, bool> GetKeyStates() = 0;

        /*
         * @brief Get the current state of all mouse buttons.
         * @return A map of button codes to their current state (true for pressed, false for released).
         */
        virtual std::map<int, bool> GetMouseButtonStates() = 0;

        /*
         * @brief Register a callback function to be called when a specific key is pressed.
         * @param key The key to register the callback for.
         * @param callback The
callback function to be called when the key is pressed. The function should take no parameters and return void.
*/
        virtual void RegisterKeyCallback(int key, std::function<void(int)> callback) = 0;
        /*
         * @brief Register a callback function to be called when a specific mouse button is pressed.
         * @param button The button to register the callback for.
         * @param callback The callback function to be called when the button is pressed. The function should take no parameters and return void.
         */
        virtual void RegisterMouseButtonCallback(int button, std::function<void(int)> callback) = 0;

        /*
         * @brief Register a callback function to be called when the mouse is moved.
         * @param callback The callback function to be called when the mouse is moved. The function should take two parameters, the x and y coordinates of the mouse, and return void.
         */
        virtual void RegisterMouseMoveCallback(std::function<void(int, int)> callback) = 0;

        virtual void PollEvents() =0 ;
    };
}