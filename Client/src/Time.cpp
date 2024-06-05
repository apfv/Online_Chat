#include "Time.h"

#include <ctime>
#include <iostream>

Time::Time() = default;

Time::~Time() = default;

void Time::getTime() {

    std::time_t now = std::time(nullptr);

    std::tm *tm_now = std::localtime(&now);

    int year = tm_now->tm_year + 1900;
    int month = tm_now->tm_mon + 1;
    int day = tm_now->tm_mday;

    int hour = tm_now->tm_hour;
    int minutes = tm_now->tm_min;
    int second = tm_now->tm_sec;

    std::cout << "[" << year << "-" << month << "-" << day << " " << hour << ":" << minutes << ":" << second << "]";
}
