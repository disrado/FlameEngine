#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>

#include <util/Id.hpp>
#include <util/Types.hpp>
#include <ecs/Entity.hpp>

namespace flm
{

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

    std::shared_ptr<Node> GetChild(Id id);

    bool RemoveChild(Id id);

    void Apply(std::function<void(std::shared_ptr<Entity>)> function);

public:
    const Id id = UniqueId();
    int64_t drawOrder = 0;
    std::shared_ptr<Entity> entity = nullptr;

private:
    std::weak_ptr<Node> m_parent;
    std::vector<std::shared_ptr<Node>> m_children = {};
};

} // namepsace flm