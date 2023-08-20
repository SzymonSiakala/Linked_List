#pragma once
#include <initializer_list>

template <typename T>
class Linked_List
{
private:
    struct Node
    {
        T data;
        std::unique_ptr<Node> next;

        Node(T value) : data(std::move(value)), next(nullptr) {}
    };

    std::unique_ptr<Node> head;

public:
    Linked_List() : head(nullptr) {}

    Linked_List(const std::initializer_list<T>& list) : Linked_List()
    {
        for (auto it = std::rbegin(list); it != std::rend(list); ++it)
{
            push_front(*it);
        }
    }

    Linked_List(Linked_List&& list) noexcept
    {
        head = std::move(list.head);
    }

    Linked_List& operator=(Linked_List&& element) noexcept
    {
        if (this != &element)
        {
            head = std::move(element.head);
        }
        return *this;
    }

    Node* operator[](const std::size_t index) const
    {
        Node* current = head.get();
        std::size_t i = 0;

        while (current)
        {
            if (i == index)
            {
                return current;
            }
            current = current->next.get();
            i++;
        }
        throw std::out_of_range("Index out of bounds.");
    }

    void push_front(const T& value)
    {
        auto new_node = std::make_unique<Node>(value);
        new_node->next = std::move(head);
        head = std::move(new_node);
    }

    void push_front(T&& value)
    {
        auto new_node = std::make_unique<Node>(std::move(value));
        new_node->next = std::move(head);
        head = std::move(new_node);
    }

    template <typename Input_Iterator>
    void push_front_range(Input_Iterator first, Input_Iterator last)
    {
        for (; first != last; ++first)
        {
            push_front(*first);
        }
    }

    void assign(const std::initializer_list<T>& list)
    {
        clear();
        for (const T& value : list)
        {
            push_front(value);
        }
    }

    template <typename Input_Iterator>
    void assign_range(Input_Iterator first, Input_Iterator last)
    {
        clear();
        for (; first != last; ++first)
        {
            push_front(*first);
        }
    }

    void insert_after(Node* position, const T& value)
    {
        auto new_node = std::make_unique<Node>(value);
        if (!position)
        {
            throw std::invalid_argument("Position is nullptr.");
        }
        new_node->next = std::move(position->next);
        position->next = std::move(new_node);
    }

    template <typename Input_Iterator>
    void insert_range_after(Node* position, Input_Iterator first, Input_Iterator last)
    {
        if (!position)
        {
            throw std::invalid_argument("Position is nullptr.");
        }
        for (; first != last; ++first)
        {
            insert_after(position, *first);
            position = position->next.get();
        }
    }

    void pop_front()
    {
        if (head)
        {
            head = std::move(head->next);
        }
    }

    void remove(const std::size_t index)
    {
        if (index < 0 || index >= size())
        {
            throw std::out_of_range("Index out of bounds.");
        }

        if (index == 0)
        {
            head = std::move(head->next);
            return;
        }

        Node* current = head.get();
        std::size_t i = 0;
        while (current && i < index - 1)
        {
            current = current->next.get();
            ++i;
        }

        if (current && current->next)
        {
            current->next = std::move(current->next->next);
        }
    }

    void remove(Node* pos)
    {
        if (!pos || !head)
        {
            return;
        }

        if (head.get() == pos)
        {
            head = std::move(head->next);
            return;
        }

        Node* current = head.get();
        while (current && current->next.get() != pos)
        {
            current = current->next.get();
        }

        if (current)
        {
            current->next = std::move(current->next->next);
        }
    }

    void remove_after(Node* pos)
    {
        if (pos && pos->next)
        {
            pos->next = std::move(pos->next->next);
        }
    }

    void clear()
    {
        while (head)
        {
            head = std::move(head->next);
        }
    }

    bool empty() const
    {
        return head == nullptr;
    }

    std::size_t size() const
    {
        std::size_t count = 0;
        Node* current = head.get();

        while (current)
        {
            count++;
            current = current->next.get();
        }

        return count;
    }

    Node* begin() const
	{
		return head.get();
	}

    Node* end() const
    {
        Node* current = head.get();
        for (std::size_t i = 0; i < size() - 1; i++)
		{
			current = current->next.get();
		}
        return current;
    }

    template<typename T>
    using Split_Predicate = std::function<bool(const T& value)>;

    Linked_List<T> split_when(Split_Predicate<T> condition)
    {
        Linked_List<T> new_list;
        Node* current = head.get();
        Node* prev = nullptr;

        while (current)
		{
            if (condition(current->data))
            {
                if (prev)
                {
                    new_list.head = std::move(prev->next);
                }
                else
                {
                    new_list.head = std::move(head);
                }
                break;
            }

			prev = current;
			current = current->next.get();
		}

        return new_list;
    }

























    //// Reverses the order of the elements
    //void reverse() {
    //    if (!head || !head->next) {
    //        return;
    //    }

    //    Node* prev = nullptr;
    //    Node* current = head.get();
    //    Node* next_node = nullptr;

    //    while (current) {
    //        next_node = current->next.get();
    //        current->next = std::move(prev);
    //        prev = current;
    //        current = next_node;
    //    }

    //    head = std::move(prev);
    //}

    //// Removes consecutive duplicate elements
    //void unique() {
    //    Node* current = head.get();

    //    while (current && current->next) {
    //        if (current->data == current->next->data) {
    //            current->next = std::move(current->next->next);
    //        }
    //        else {
    //            current = current->next.get();
    //        }
    //    }

    //}

};