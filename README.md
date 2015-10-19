# ETimer

written in C++11 with SFML 2.3 & SFGUI

A very simple little timer using SFGUI to create the buttons and labels and SFML to provide the window. It starts in clock mode (which uses time.h to display the current time). Pressing the green arrow button the first time sets the timer to zero and starts counting hh:mm:ss. Clicking on the blue pause button stops the count and clicking the green arrow resumes the count. The timer function uses C++ chrono library and namespace. Clicking the red stop button ends the timer and restores the time display. Dismiss the window with Escape or Space or the window close button.

