#include "pch.hpp"

#include "scene_graph/Node.hpp"

namespace flm
{

Node::~Node()
{
    if (auto parent = m_parent.lock()) {
        parent->RemoveChild(id);
    }
}


bool Node::operator<(const Node& other) const
{
    return drawOrder < other.drawOrder;
}


flm::Id Node::AddChild(std::shared_ptr<flm::Entity> entity, int64_t drawOrder)
{
    const auto node{ std::make_shared<Node>() };
    node->entity = entity;
    node->drawOrder = drawOrder;
    node->m_parent = shared_from_this();
    
    m_children.push_back(node);

    std::sort(std::begin(m_children), std::end(m_children), [] (auto rhs, auto lhs) {
        return *rhs < *lhs;
    });

    return node->id;
}


std::shared_ptr<Node> Node::GetChild(flm::Id id)
{
    for (auto child : m_children) {
        if (child->id == id) {
            return child;
        }
    }

    return nullptr;
}


bool Node::RemoveChild(flm::Id id)
{
    const auto it{ std::find_if(std::begin(m_children), std::end(m_children),
        [id] (const auto& child) { return child->entity->id == id; })
    };

    if (it != std::end(m_children)) {
        m_children.erase(it);
        return true;
    }

    return false;
}


void Node::Apply(std::function<void(std::shared_ptr<flm::Entity>)> function)
{
    function(entity);
    
    for(const auto& child : m_children) {
        child->Apply(function);
    }
}

} // namepsace flm