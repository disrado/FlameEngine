#pragma once

#include <flame/utils/Aliases.hpp>


namespace flm::utils
{


// One-call timer
class DeadlineTimer final
{
public:
	DeadlineTimer(Seconds delay, func<void()> callback = nullptr);
	~DeadlineTimer();
	
	DeadlineTimer(const DeadlineTimer&) = delete;
	DeadlineTimer(DeadlineTimer&&) = delete;
	
	DeadlineTimer& operator=(const DeadlineTimer&) = delete;
	DeadlineTimer& operator=(DeadlineTimer&&) = delete;

public:
	void Start();
	void Stop();
	void SetCallback(const func<void()> newCallback);
	bool IsStopped() const;

private:
	Seconds m_delay;
	func<void()> m_callback;
	std::atomic_bool m_isStopped;
	std::thread m_thread;
	std::mutex m_mutex;
	std::mutex m_membersMtx;
	std::condition_variable m_terminate;
};


// Cyclic timer which calls callback every delay time period
class Timer final
{
public:
	Timer(Seconds delay, func<void()> callback = nullptr);
	~Timer();

	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;

	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

public:
	void Start();
	void Stop();
	void SetCallback(const func<void()> newCallback);
	bool IsStopped() const;

private:
	Seconds m_delay;
	func<void()> m_callback;
	std::atomic_bool m_isStopped;
	std::thread m_thread;
	std::mutex m_mutex;
	std::mutex m_membersMtx;
	std::condition_variable m_terminate;
};


} // namespace timer