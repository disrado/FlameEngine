namespace flm
{

template<typename T>
class System
{
public:
    template<typename ...Args>
    std::shared_ptr<T> CreateComponent(Args... args);
    
    virtual void Update(const float dt);

private:
    std::vector<std::shared_ptr<T>> m_components;
};

template<typename T>
template<typename ...Args>
std::shared_ptr<T> System<T>::CreateComponent(Args... args)
{
    const auto it{ m_components.push_back(std::make_shared<T>(args...)) };
    return *it;
}


} // flm