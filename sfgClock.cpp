/** Brownian Motion 2015
 * \date :29 09 15
 * \file :sfgClock.cpp
 * \brief : using chrono and sfg to make a simple stopwatch
*/

#include "sfgClock.hpp"

void sfgClock::run()
{   setUp();
    Render(); }

void sfgClock::clockTime()
{   time_t now;
    struct tm * thisTime;
    time (&now);
    thisTime = localtime (&now);
    hrs = thisTime->tm_hour;
    mins = thisTime->tm_min;
    secs = thisTime->tm_sec;
    updateTimeText(); }

void sfgClock::updateTimeText()
{   hourTextLabel->SetText(hmsString(hrs));
    minTextLabel->SetText(hmsString(mins));
    secTextLabel->SetText(hmsString(secs)); }

/// these three functions are triggered by the button signals:

void sfgClock::startTimer()
{   runTimer = true;
    isPaused = false;
    interSecs = interSecs + pausedSecs; }

void sfgClock::pauseTimer()
{    markTime();
    isPaused = true; }

void sfgClock::stopTimer()
{   interSecs = seconds(0);
    elapsedSecs = seconds(0);   /// these are durations initialised to zero
    pausedSecs = seconds(0);
    runTimer = false;
    isStarted = false;
    isPaused = false;
    runTime = 0; }

void sfgClock::eTimer()
{   if (!isStarted) {startTime(); isStarted = true;}
    if(!isPaused)
    {   elapsedSecs = Elapse() - interSecs;
        runTime = elapsedSecs.count(); }
    else {    pausedSecs = Pause(); }
    hrs = (runTime/3600) % 24;
    mins = ((runTime/60) % 60) % 60;
    secs = (runTime % 3600) % 60;
    updateTimeText(); }


void sfgClock::setUp()
{   /// multimedia setup
    sf::Image eplay; eplay.loadFromFile("play.png"); auto eplays = sfg::Image::Create(); eplays->SetImage(eplay);
    sf::Image epause; epause.loadFromFile("pause.png"); auto epauses = sfg::Image::Create(); epauses->SetImage(epause);
    sf::Image estop; estop.loadFromFile("stop.png"); auto estops = sfg::Image::Create(); estops->SetImage(estop);
    desktop.LoadThemeFromFile("Cezanne.theme");
    desktop.SetProperty( "*", "FontSize",23);
    desktop.SetProperty("*", "FontName", "Microgramma-D-OT-Medium-Extended.ttf");


    sfgWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);

    hourTextLabel = sfg::Label::Create("00");
    auto sep1 = sfg::Label::Create( ":" );
    minTextLabel = sfg::Label::Create("00");
    auto sep2 = sfg::Label::Create( ":" );
    secTextLabel = sfg::Label::Create("00");

    auto dTime = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, padding);
    dTime->Pack(hourTextLabel);
    dTime->Pack(sep1);
    dTime->Pack(minTextLabel);
    dTime->Pack(sep2);
    dTime->Pack(secTextLabel);
    auto controls = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, padding);

    auto start = sfg::Button::Create(); start->SetImage(eplays) ;
    auto stop = sfg::Button::Create();   stop->SetImage(epauses);
    auto reset = sfg::Button::Create(); reset->SetImage(estops);
    start->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &sfgClock::startTimer, this));
    stop->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &sfgClock::pauseTimer, this));
    reset->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &sfgClock::stopTimer, this));

    controls->Pack(start);
    controls->Pack(stop);
    controls->Pack(reset);
    auto mainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, padding);
    mainBox->Pack(dTime);
    mainBox->Pack(sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL), false);
    mainBox->Pack(controls);
    sfgWindow->Add(mainBox);
    desktop.Add(sfgWindow);
    sfmlSize = {sfgWindow->GetAllocation().width, sfgWindow->GetAllocation().height };  }

void sfgClock::processEvents()
{   sf::Event event;
    while (sfmlWindow.pollEvent(event))
    {   desktop.HandleEvent(event);
        switch (event.type)
        {   case sf::Event::Closed: sfmlWindow.close(); break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {   case sf::Keyboard::Escape: sfmlWindow.close(); break;
                    case sf::Keyboard::Space: sfmlWindow.close(); break;
                    case sf::Keyboard::F5: break;
                    default: break; }
            default: break; } } }

void sfgClock::Render()
{   sfmlWindow.create(sf::VideoMode(sfmlSize.x, sfmlSize.y), "T");//, sf::Style::None);//|sf::Style::Close);
    sfmlWindow.setIcon( plastic_clock_ico.width,  plastic_clock_ico.height,  plastic_clock_ico.pixel_data );
    sfmlWindow.setPosition({1535,50 });
    sfmlWindow.setFramerateLimit(10);
    sfmlWindow.resetGLStates();
    while (sfmlWindow.isOpen())
    {   if(!runTimer) clockTime();
        else eTimer();
        processEvents();
        desktop.Update(clock.restart().asSeconds());
        sfmlWindow.clear();
        m_sfgui.Display(sfmlWindow);
        sfmlWindow.display(); } }


