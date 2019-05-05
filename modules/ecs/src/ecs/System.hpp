namespace flm::ecs
{

template<typename T>
class System
{

public:
	template<typename P...>
	std::shared_ptr<T> CreateComponent();
	
	virtual void Update(const float dt);
	
private:
	std::vector<std::shared_ptr<T>> m_components;
};

template<typename T, typename P...>
std::shared_ptr<T> System<T>::CreateComponent()
{
	const auto it{ m_components.push_back(std::make_shared<T>(...P)); };
	return *it;
}


} // flm::ecs