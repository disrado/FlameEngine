#pragma once

namespace flm
{

class Render;
class Entity;

class DrawSystem : public System
{
private:
    class Node final : public std::enable_shared_from_this<Node>
    {
    public:
        Node() = default;
        ~Node();

        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node(const Node&&) = delete;
        Node& operator=(const Node&&) = delete;

        bool operator<(const Node& other) const;

        Id AddChild(std::shared_ptr<Entity> entity, int64_t drawOrder);

        bool RemoveChild(const Id id);

        void Apply(std::function<void(std::shared_ptr<Entity>)> function);

        void Draw(std::shared_ptr<Render> render, const float dt);

    public:
        int64_t drawOrder = 0;

    private:
        const Id id = UniqueId();
        std::shared_ptr<Entity> m_entity = nullptr;
        std::weak_ptr<Node> m_parent;
        std::map<int64_t, std::shared_ptr<Node>> m_children = {};
    };

public:
    DrawSystem(std::shared_ptr<Render> render);

    std::shared_ptr<DrawSystem::Node> GetRoot();

    void Update(const float dt) override;

private:
    std::shared_ptr<Node> m_root = std::make_shared<Node>();
    std::shared_ptr<Render> m_render = nullptr;
};

} // namepsace flm