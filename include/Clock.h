#ifndef CLOCK_H
#define CLOCK_H

#include <SDL.h>

class Time
{
public:
	Time(Uint32 t_val) : val{ t_val } {}
	float asSeconds() { return val / 1000.0f; }
	float asMilliseconds() { return static_cast<float>(val); }

	Time& operator+=(const Time& rhs)
	{
		this->val += rhs.val;
		return *this;
	}

	Time& operator-=(const Time& rhs)
	{
		this->val -= rhs.val;
		return *this;
	}

	bool operator>(const Time& t) { return this->val > t.val; }
	bool operator<(const Time& t) { return this->val < t.val; }

private:
	Uint32 val;
};

class Clock
{
public:
	/// <summary>
	/// Starts our SDL clock
	/// </summary>
	void start() 
	{
		startTime = SDL_GetTicks();
	}

	/// <summary>
	/// Stops our SDL clock
	/// </summary>
	void stop()
	{
		timeElapsed += SDL_GetTicks() - startTime;
	}

	/// <summary>
	/// Returns the time elapsed so far
	/// </summary>
	Time getTimeElapsed()
	{
		stop();
		start();

		return Time(timeElapsed);
	}

	/// <summary>
	/// Resets the SDL_Clock and stops it.
	/// </summary>
	/// <returns>Time elapsed since the clock was started</returns>
	Time reset()
	{
		Time t(getTimeElapsed());
		startTime = 0U;
		timeElapsed = 0U;
		return t;
	};

	/// <summary>
	/// Resets the SDL clock and starts it again from 0.
	/// </summary>
	/// <returns>Time elapsed since the clock was started</returns>
	Time restart()
	{
		Time t(getTimeElapsed());
		timeElapsed = 0U;
		start();
		return t;
	}

private:
	Uint32 startTime{ 0U };
	Uint32 timeElapsed{ 0U };
};

#endif