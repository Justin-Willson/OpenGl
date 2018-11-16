#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>
class Display
{
    public:
        Display(int width, int height, const std::string& title);
        virtual ~Display();
        void Update();
        bool IsClosed();

    protected:
    private:
        SDL_Window* m_window;
        SDL_GLContext m_glContext;
        bool m_isClosed;
};

#endif