#ifndef SFGUICLOCK_HPP_INCLUDED
#define SFGUICLOCK_HPP_INCLUDED

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFGUI/Renderers.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/OpenGL.hpp>
#include <time.h>
#include <chrono>
#include "icons.hpp"

using namespace std;
using namespace chrono;

class sfgClock
{
    ///chrono variables
    using steady_clock = chrono::steady_clock;
    using seconds = chrono::seconds;
    steady_clock::time_point m_start; /// these are time point defs.
    steady_clock::time_point m_paused;
public:
    void run();
    void eTimer();
    void updateTimeText();
    void clockTime();
    void setUp();
    void processEvents();
    void Render();

    void startTimer(); /// these are the functions triggered by the button signals
    void pauseTimer();
    void stopTimer();
    ///chrono variables
    void startTime() {m_start = steady_clock::now();} /// these functions initialize TPs
    void markTime() {m_paused = steady_clock::now();}
    seconds Elapse() const { return chrono::duration_cast<seconds>(steady_clock::now() - m_start); } /// these are durations...
    seconds Pause() const { return chrono::duration_cast<seconds>(steady_clock::now() - m_paused); }
    seconds elapsedSecs = seconds(0);   /// these are durations initialised to zero
    seconds pausedSecs = seconds(0);
    seconds interSecs = seconds(0);

    ///time variables and flags
    int  hrs, mins, secs; ///this is used to count time
    int runTime = 0; ///class variable
    bool runTimer = false; ///these flags control the flow-of-control
    bool isStarted = false;
    bool isPaused = false;

    int padding = 5;   ///sfg padding

    string hmsString(int in)
    {   stringstream ss;
        ss << setw(2) << setfill('0') << in;
        string str; ss >>  str;  return str; }

    sf::RenderWindow sfmlWindow;
    sf::Vector2f sfmlSize;
    sf::Clock clock;  ///used to refresh screen
    sfg::SFGUI m_sfgui;
    sfg::Entry::Ptr entry;
    sfg::Label::Ptr hourTextLabel;
    sfg::Label::Ptr minTextLabel;
    sfg::Label::Ptr secTextLabel;
    sfg::Window::Ptr sfgWindow;
    sfg::Desktop desktop;
    };
///***************************************************************************
class aTime /// test class
{   using steady_clock = chrono::steady_clock;
    using seconds = chrono::seconds;

public:
    explicit aTime(bool run = false) { if (run) startTime();}
    void startTime() {m_start = steady_clock::now();}
    void markTime() {m_paused = steady_clock::now();}
    seconds Elapse() const { return chrono::duration_cast<seconds>(steady_clock::now() - m_start); }
    seconds Pause() const { return chrono::duration_cast<seconds>(steady_clock::now() - m_paused); }
private:
    steady_clock::time_point m_start;
    steady_clock::time_point m_paused; };

#endif // SFGUICLOCK_HPP_INCLUDED
