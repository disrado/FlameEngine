template<typename T>
Node<T>::~Node()
{
    if (auto parent = m_parent.lock()) {
        parent->RemoveChild(m_id);
    }
}


template<typename T>
bool Node<T>::operator<(const Node& other) const
{
    return m_drawOrder > other.m_drawOrder;
}


template<typename T>
flm::Id Node<T>::AddChild(std::shared_ptr<T> object, int64_t drawOrder)
{
    const auto node{ std::make_shared<Node<T>>() };
    node->m_object = object;
    node->m_drawOrder = drawOrder;
    node->m_parent = this->shared_from_this();
    
    m_children.push_back(node);

    std::sort(std::begin(m_children), std::end(m_children), [] (auto rhs, auto lhs) {
        return *rhs < *lhs;
    });

    return node->GetId();
}


template<typename T>
void Node<T>::AddChild(std::shared_ptr<Node<T>> node)
{
    m_children.push_back(node);

    std::sort(std::begin(m_children), std::end(m_children), [] (auto rhs, auto lhs) {
        return *rhs < *lhs;
    });
}


template<typename T>
std::shared_ptr<Node<T>> Node<T>::GetChild(flm::Id id)
{
    const auto it{ std::find_if(std::begin(m_children), std::end(m_children),
        [id] (auto child) { return child->GetId() == id; })
    };

    if (it != std::end(m_children)) {
        return *it;
    }

    return nullptr;
}


template<typename T>
std::shared_ptr<Node<T>> Node<T>::GetDescendant(flm::Id id)
{
    if (auto child{ GetChild(id) }; child) {
        return child;
    }

    for (const auto child : m_children) {
        if (auto target{ child->GetChild(id) }; target) {
            return target;
        }
    }

    return nullptr;
}


template<typename T>
bool Node<T>::RemoveChild(flm::Id id)
{
    const auto it{ std::find_if(std::begin(m_children), std::end(m_children),
        [id] (const auto& child) { return child->GetId() == id; })
    };

    if (it != std::end(m_children)) {
        m_children.erase(it);
        return true;
    }

    return false;
}


template<typename T>
bool Node<T>::RemoveDescendant(flm::Id id)
{
    if (auto result{ RemoveChild(id) }; result) {
        return result;
    }

    for (const auto child : m_children) {
        if (child->RemoveChild(id)) {
            return true;
        }
    }

    return false;
}


template<typename T>
void Node<T>::Apply(std::function<void(std::shared_ptr<T>)> function)
{
    for(const auto& child : m_children) {
        child->Apply(function);
    }

    function(m_object);
}


template<typename T>
Id Node<T>::GetId() const
{
    return m_id;
}


template<typename T>
void Node<T>::AttachObject(std::shared_ptr<T> object)
{
    m_object = object;
}


template<typename T>
std::shared_ptr<T> Node<T>::DetachObject()
{
    const auto copy{ m_object };
    m_object = nullptr;
    return copy;
}


template<typename T>
std::shared_ptr<T> Node<T>::GetObject() const
{
    return m_object;
}


template<typename T>
std::shared_ptr<Node<T>> Node<T>::GetParent() const
{
    if (auto parent{ m_parent.lock() }; parent) {
        return parent;
    }

    return nullptr;
}
