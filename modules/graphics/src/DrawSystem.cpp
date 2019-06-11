#include "pch.hpp"

#include <graphics/DrawSystem.hpp>

#include <graphics/Components.hpp>
#include <graphics/Render.hpp>

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


Id Node::AddChild(std::shared_ptr<Entity> entity, int64_t drawOrder)
{
    const auto node{ std::make_shared<Node>() };
    node->m_entity = entity;
    node->drawOrder = drawOrder;
    node->m_parent = shared_from_this();

    m_children.insert({ node->id, node });

    return node->id;
}


bool Node::RemoveChild(const Id id)
{
    return static_cast<bool>(m_children.erase(id));
}


void Node::Apply(std::function<void(std::shared_ptr<Entity>)> function)
{
    for(const auto& child : m_children) {
        function(m_entity);
        child.second->Apply(function);
    }
}


void Node::Draw(std::shared_ptr<Render> render, const float dt)
{
    for (const auto& child : m_children) {
        child.second->Draw(render, dt);
    }

    if (!m_entity) {
        return;
    }

    const auto transform{ m_entity->GetComponent<TransformComponent>() };
    const auto texture{ m_entity->GetComponent<TextureComponent>() };

    if (!texture || !transform) {
        return;
    }

    SDL_Rect rect;
    rect.w = texture->texture->GetSize().width * transform->scale.x;
    rect.h = texture->texture->GetSize().height * transform->scale.y;
    rect.x = transform->position.x;
    rect.y = transform->position.y;

    SDL_RenderCopyEx(render->Get(), texture->texture->Get(), nullptr, &rect, transform->rotation, 
        nullptr, SDL_FLIP_NONE
    );
}


DrawSystem::DrawSystem(std::shared_ptr<Render> render)
    : m_root{ std::make_shared<Node>() }
    , m_render{ render }
{
}


std::shared_ptr<Node> DrawSystem::GetRoot()
{
    return m_root;
}


void DrawSystem::Update(const float dt)
{
    m_root->Draw(m_render, dt);
}

} // namepsace flm