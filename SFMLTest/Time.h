// Implements deWiTTERS Game Loop
#pragma once

#include <chrono>

// only because I hate std's overly verbose API
using namespace std::chrono;

namespace Engine {

class GameClock
{
public:	
	GameClock(int ticksPerSec) : m_skipTicks(1000 / ticksPerSec), m_gameTicks(1) {}

	void Start()
	{
		epoch = high_resolution_clock::now();
		m_nextGameTick = Elapsed();
	}
	
	void Restart() { Start(); }

	void Advance()
	{
		m_nextGameTick += m_skipTicks;
		m_gameTicks++;
	}

	uint64_t GetGameTick() { return m_gameTicks; }

	bool IsReady() { return Elapsed() > m_nextGameTick; }

	high_resolution_clock::duration Elapsed() const { return high_resolution_clock::now() - epoch; }
	
	high_resolution_clock::time_point Now() const { return high_resolution_clock::now(); }

	float GetInterpolation()
	{
		return duration<float>( Elapsed() + m_skipTicks - m_nextGameTick ) / duration<float>( m_skipTicks );
	}

private:
	high_resolution_clock::time_point epoch;

	// After updating, how far we should advance
	milliseconds m_skipTicks;

	// Tracks when we should be allowed to "trigger" again
	high_resolution_clock::duration m_nextGameTick;

	// Total amount of game ticks since start of program
	uint64_t m_gameTicks;
};

} // namespace Engine