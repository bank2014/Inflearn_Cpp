#pragma once
#include <cassert>
#include <algorithm>
#include <array>
#include <memory>
#include <type_traits>
#include <vector>

namespace external {
    template<typename T>
    class vec2 {
        static_assert(std::is_arithmetic_v<T>, "vec2 can only be instantiated with arithmetic types");
    public:
        T x;
        T y;
        constexpr vec2<T>(T X = 0, T Y = 0) noexcept : x(X), y(Y)
        {

        }
        constexpr vec2<T> operator+(const vec2<T>& rhs) noexcept
        {
            this += rhs;
            return *this;
        }
        constexpr vec2<T> operator/(T t) noexcept
        {
            this /= t;
            return *this;
        }
        constexpr vec2<T>& operator+=(const vec2<T>& other) noexcept
        {
            x += other.x;
            y += other.y;
            return *this;
        }
        constexpr vec2<T>& operator/=(T t) noexcept
        {
            x /= t;
            y /= t;
            return *this;
        }
    };

    template<typename T>
    class Box
    {
        static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");
    public:
        T left;
        T top;
        T width;    // Must be positive
        T height;   // Must be positive

        constexpr Box(T Left = 0, T Top = 0, T Width = 0, T Height = 0) noexcept :
            left(Left), top(Top), width(Width), height(Height)
        {
        }
        constexpr Box(const vec2<T>& position, const vec2<T>& area) noexcept :
            left(position.x), top(position.y), width(area.x), height(area.y)
        {
        }
        constexpr T Right() const noexcept
        {
            return left + width;
        }
        constexpr T Bottom() const noexcept
        {
            return top + height;
        }
        constexpr vec2<T> TopLeft() const noexcept
        {
            return vec2<T>(left, top);
        }
        constexpr vec2<T> Center() const noexcept
        {
            return vec2<T>(left + width / 2, top + height / 2);
        }
        constexpr vec2<T> Area() const noexcept
        {
            return vec2<T>(width, height);
        }
        constexpr bool Contains(const Box<T>& box) const noexcept
        {
            return left <= box.left && box.Right() <= Right() &&
                top <= box.top && box.Bottom() <= Bottom();
        }
        constexpr bool Intersects(const Box<T>& box) const noexcept
        {
            return (left >= box.Right() || Right() <= box.left ||
                top >= box.Bottom() || Bottom() <= box.top);
        }
    };

    template<typename GameObject, typename GetBox, typename Equal = std::equal_to<GameObject>, typename Float = float>
    class Quadtree
    {
        static_assert(std::is_convertible_v<std::invoke_result_t<GetBox, const GameObject&>, Box<Float>>,
            "GetBox must be a callable of signature Box<Float>(const T&)");
        static_assert(std::is_convertible_v<std::invoke_result_t<Equal, const GameObject&, const GameObject&>, bool>,
            "Equal must be a callable of signature bool(const T&, const T&)");
        static_assert(std::is_arithmetic_v<Float>);

    private:
        static constexpr size_t Threshold = 16;  //maximum number of objects a node can contain before we try to split it
        static constexpr size_t MaxDepth = 8;    //maximum depth of the tree
        struct Node
        {
            std::array<std::unique_ptr<Node>, 4> children;
            std::vector<GameObject> objects;
        };
        Box<Float> mBox;
        std::unique_ptr<Node> mRoot;
        GetBox mGetBox;
        Equal mEqual;
        
    public:
        Quadtree(const Box<Float>& box, const GetBox& getBox = GetBox(), const Equal& equal = Equal()) :
            mBox(box), mRoot(std::make_unique<Node>()), mGetBox(getBox), mEqual(equal)
        {}
        void add(const GameObject& value)
        {
            add(mRoot.get(), 0, mBox, value);
        }
        void remove(const GameObject& value)
        {
            remove(mRoot.get(), mBox, value);
        }
        std::vector<GameObject> query(const Box<Float>& box) const
        {
            auto objects = std::vector<GameObject>();
            query(mRoot.get(), mBox, box, objects);
            return objects;
        }
        std::vector<std::pair<GameObject, GameObject>> findAllIntersections() const
        {
            auto intersections = std::vector<std::pair<GameObject, GameObject>>();
            findAllIntersections(mRoot.get(), intersections);
            return intersections;
        }
        Box<Float> getBox() const
        {
            return mBox;
        }

    private:
        bool isLeaf(const Node* node) const
        {
            return !static_cast<bool>(node->children[0]);
        }
        Box<Float> computeBox(const Box<Float>& box, int i) const
        {
            auto origin = box.TopLeft();
            auto childSize = box.Area() / static_cast<Float>(2);
            switch (i)
            {
                // North West
            case 0:
                return Box<Float>(origin, childSize);
                // Norst East
            case 1:
                return Box<Float>(vec2<Float>(origin.x + childSize.x, origin.y), childSize);
                // South West
            case 2:
                return Box<Float>(vec2<Float>(origin.x, origin.y + childSize.y), childSize);
                // South East
            case 3:
                return Box<Float>(origin + childSize, childSize);
            default:
                assert(false && "Invalid child index");
                return Box<Float>();
            }
        }
        int getQuadrant(const Box<Float>& nodeBox, const Box<Float>& valueBox) const
        {
            auto center = nodeBox.Center();
            // West
            if (valueBox.Right() < center.x)
            {
                // North West
                if (valueBox.Bottom() < center.y)
                    return 0;
                // South West
                else if (valueBox.top >= center.y)
                    return 2;
                // Not contained in any quadrant
                else
                    return -1;
            }
            // East
            else if (valueBox.left >= center.x)
            {
                // North East
                if (valueBox.Bottom() < center.y)
                    return 1;
                // South East
                else if (valueBox.top >= center.y)
                    return 3;
                // Not contained in any quadrant
                else
                    return -1;
            }
            // Not contained in any quadrant
            else
                return -1;
        }
        void add(Node* node, std::size_t mDepth, const Box<Float>& box, const GameObject& value)
        {
            assert(node != nullptr);
            assert(box.Contains(mGetBox(value)));
            if (isLeaf(node))
            {
                // Insert the value in this node if possible
                if (mDepth >= MaxDepth || node->objects.size() < Threshold)
                    node->objects.push_back(value);
                // Otherwise, we split and we try again
                else
                {
                    split(node, box);
                    add(node, mDepth, box, value);
                }
            }
            else
            {
                auto i = getQuadrant(box, mGetBox(value));
                // Add the value in a child if the value is entirely contained in it
                if (i != -1)
                    add(node->children[static_cast<std::size_t>(i)].get(), mDepth + 1, computeBox(box, i), value);
                // Otherwise, we add the value in the current node
                else
                    node->objects.push_back(value);
            }
        }
        void split(Node* node, const Box<Float>& box)
        {
            assert(node != nullptr);
            assert(isLeaf(node) && "Only leaves can be split");
            // Create children
            for (auto& child : node->children)
                child = std::make_unique<Node>();
            // Assign objects to children
            auto newValues = std::vector<GameObject>(); // New objects for this node
            for (const auto& value : node->objects)
            {
                auto i = getQuadrant(box, mGetBox(value));
                if (i != -1)
                    node->children[static_cast<std::size_t>(i)]->objects.push_back(value);
                else
                    newValues.push_back(value);
            }
            node->objects = std::move(newValues);
        }
        bool remove(Node* node, const Box<Float>& box, const GameObject& value)
        {
            assert(node != nullptr);
            assert(box.Contains(mGetBox(value)));
            if (isLeaf(node))
            {
                // Remove the value from node
                removeValue(node, value);
                return true;
            }
            else
            {
                // Remove the value in a child if the value is entirely contained in it
                auto i = getQuadrant(box, mGetBox(value));
                if (i != -1)
                {
                    if (remove(node->children[static_cast<std::size_t>(i)].get(), computeBox(box, i), value))
                        return tryMerge(node);
                }
                // Otherwise, we remove the value from the current node
                else
                    removeValue(node, value);
                return false;
            }
        }
        void removeValue(Node* node, const GameObject& value)
        {
            // Find the value in node->objects
            auto it = std::find_if(std::begin(node->objects), std::end(node->objects),
                [this, &value](const auto& rhs) { return mEqual(value, rhs); });
            assert(it != std::end(node->objects) && "Trying to remove a value that is not present in the node");
            // Swap with the last element and pop back
            *it = std::move(node->objects.back());
            node->objects.pop_back();
        }
        bool tryMerge(Node* node)
        {
            assert(node != nullptr);
            assert(!isLeaf(node) && "Only interior nodes can be merged");
            auto nbValues = node->objects.size();
            for (const auto& child : node->children)
            {
                if (!isLeaf(child.get()))
                    return false;
                nbValues += child->objects.size();
            }
            if (nbValues <= Threshold)
            {
                node->objects.reserve(nbValues);
                // Merge the objects of all the children
                for (const auto& child : node->children)
                {
                    for (const auto& value : child->objects)
                        node->objects.push_back(value);
                }
                // Remove the children
                for (auto& child : node->children)
                    child.reset();
                return true;
            }
            else
                return false;
        }
        void query(Node* node, const Box<Float>& box, const Box<Float>& queryBox, std::vector<GameObject>& objects) const
        {
            assert(node != nullptr);
            assert(queryBox.Intersects(box));
            for (const auto& value : node->objects)
            {
                if (queryBox.Intersects(mGetBox(value)))
                    objects.push_back(value);
            }
            if (!isLeaf(node))
            {
                for (auto i = std::size_t(0); i < node->children.size(); ++i)
                {
                    auto childBox = computeBox(box, static_cast<int>(i));
                    if (queryBox.Intersects(childBox))
                        query(node->children[i].get(), childBox, queryBox, objects);
                }
            }
        }
        void findAllIntersections(Node* node, std::vector<std::pair<GameObject, GameObject>>& intersections) const
        {
            // Find intersections between objects stored in this node
            // Make sure to not report the same intersection twice
            for (auto i = std::size_t(0); i < node->objects.size(); ++i)
            {
                for (auto j = std::size_t(0); j < i; ++j)
                {
                    if (mGetBox(node->objects[i]).Intersects(mGetBox(node->objects[j])))
                        intersections.emplace_back(node->objects[i], node->objects[j]);
                }
            }
            if (!isLeaf(node))
            {
                // Values in this node can intersect objects in descendants
                for (const auto& child : node->children)
                {
                    for (const auto& value : node->objects)
                        findIntersectionsInDescendants(child.get(), value, intersections);
                }
                // Find intersections in children
                for (const auto& child : node->children)
                    findAllIntersections(child.get(), intersections);
            }
        }
        void findIntersectionsInDescendants(Node* node, const GameObject& value, std::vector<std::pair<GameObject, GameObject>>& intersections) const
        {
            // Test against the objects stored in this node
            for (const auto& other : node->objects)
            {
                if (mGetBox(value).Intersects(mGetBox(other)))
                    intersections.emplace_back(value, other);
            }
            // Test against objects stored into descendants of this node
            if (!isLeaf(node))
            {
                for (const auto& child : node->children)
                    findIntersectionsInDescendants(child.get(), value, intersections);
            }
        }
    };

}