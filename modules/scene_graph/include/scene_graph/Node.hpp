#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>

#include <util/Id.hpp>
#include <util/Types.hpp>

namespace flm
{

template<typename T>
class Node final : public std::enable_shared_from_this<Node<T>>
{
public:
    Node() = default;
    ~Node();

    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    Node(const Node&&) = delete;
    Node& operator=(const Node&&) = delete;

    bool operator<(const Node& other) const;

    // Adds child of this node
    Id AddChild(std::shared_ptr<T> object, int64_t drawOrder);

    // Adds child of this node
    void AddChild(std::shared_ptr<Node<T>> node);

    // Returns child of this node
    std::shared_ptr<Node<T>> GetChild(Id id);

    // Removes child of this node
    bool RemoveChild(Id id);

    // Returns child wherever it is in descendants of this node
    std::shared_ptr<Node<T>> GetDescendant(Id id);

    // Removes child wherever it is in descendants of this node
    bool RemoveDescendant(Id id);

    // Applies function to all objects from this node to last descendant of this node
    void Apply(std::function<void(std::shared_ptr<T>)> function);

    // Returns id of this node
    Id GetId() const;

    // Attaches object to this node
    void AttachObject(std::shared_ptr<T> object);

    // Detaches object from this node
    std::shared_ptr<T> DetachObject();

    // Returns object which stored in this node
    std::shared_ptr<T> GetObject() const;

    // Returns parent of this node if it is exists
    std::shared_ptr<Node> GetParent() const;

private:
    const Id m_id = UniqueId();
    std::shared_ptr<T> m_object = nullptr;
    int64_t m_drawOrder = 0;
    std::weak_ptr<Node<T>> m_parent;
    std::vector<std::shared_ptr<Node>> m_children = {};
};

#include "../../src/Node.inl"

} // namepsace flm