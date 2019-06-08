template<typename T>
EntryCollector& EntryCollector::operator<<(const T& message)
{
	if (m_mode == Mode::process ) {
		*m_entry << message;
	}

	return *this;
}