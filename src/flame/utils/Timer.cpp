#include "pch.hpp"

#include <flame/utils/Timer.hpp>


namespace flm::utils
{


DeadlineTimer::DeadlineTimer(Seconds delay, func<void()> callback)
	: m_delay{ delay }
	, m_callback{ callback }
	, m_isStopped{ true }
{
}


DeadlineTimer::~DeadlineTimer()
{
	Stop();
}


void DeadlineTimer::Start()
{
	Stop();

	m_isStopped = false;

	std::lock_guard<std::mutex> lg{ m_membersMtx };

	m_thread = std::thread{ [this] {
		auto locked{ std::unique_lock<std::mutex>(m_mutex) };

		const bool waitingResult{ m_terminate.wait_for(locked, m_delay, [this] {
			return static_cast<bool>(this->m_isStopped);
		}) };

		// wait_for returns false only if predicate returns false after waiting.
		// It is our case.
		if (!waitingResult)
		{
			{
				std::lock_guard<std::mutex> lg{ m_membersMtx };

				if (m_callback) {
					m_callback();
				}
			}
			m_isStopped = true;
		}
	} };
}


void DeadlineTimer::Stop()
{
	m_isStopped = true;

	m_terminate.notify_one();

	{
		std::lock_guard<std::mutex> lg{ m_membersMtx };
		
		if (m_thread.joinable()) {
			m_thread.join();
		}
	}
}


void DeadlineTimer::SetCallback(func<void()> newCallback)
{
	{
		std::lock_guard<std::mutex> lg{ m_membersMtx };
		
		m_callback = newCallback;
	}
}


bool DeadlineTimer::IsStopped() const
{
	return static_cast<bool>(m_isStopped);
}



Timer::Timer(Seconds delay, func<void()> callback)
	: m_delay{ delay }
	, m_callback{ callback }
	, m_isStopped{ true }
{
}


Timer::~Timer()
{
	Stop();
}


void Timer::Start()
{
	Stop();

	m_isStopped = false;

	std::lock_guard<std::mutex> lg{ m_membersMtx };

	m_thread = std::thread{ [this] {
		while(!m_isStopped)
		{
			auto locked{ std::unique_lock<std::mutex>(m_mutex) };

			const bool waitingResult{ m_terminate.wait_for(locked, m_delay, [this] {
				return static_cast<bool>(this->m_isStopped);
			}) };

			// wait_for returns false only if predicate returns false after waiting.
			// It is our case.
			if (!waitingResult)
			{
				{
					std::lock_guard<std::mutex> lg{ m_membersMtx };

					if (m_callback) {
						m_callback();
					}
				}
			}
		}
	} };
}


void Timer::Stop()
{
	m_isStopped = true;

	m_terminate.notify_one();

	{
		std::lock_guard<std::mutex> lg{ m_membersMtx };
		
		if (m_thread.joinable()) {
			m_thread.join();
		}
	}
}


void Timer::SetCallback(func<void()> newCallback)
{
	{
		std::lock_guard<std::mutex> lg{ m_membersMtx };
		
		m_callback = newCallback;
	}
}


bool Timer::IsStopped() const
{
	return static_cast<bool>(m_isStopped);
}


} // namespace flm::utils