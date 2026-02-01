///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file static_list.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 14-10-2025
///
/// @brief Statically allocated double linked list.
///
///-----------------------------------------------------------------------------

#ifndef MTL_STATIC_LIST_H
#define MTL_STATIC_LIST_H

#include <cstdint>

#include "array.h"
#include "type_traits.h"

namespace mtl
{
template <typename T, std::size_t N> class static_list;

namespace static_list_detail
{
    // Basic element of a linked list.
    // The contained data type is allocated directly in this structure.
    // The intention is to allocate this type within a flat memory buffer.
    template <typename T> struct static_list_node
    {
        static_list_node *next = nullptr;
        static_list_node *prev = nullptr;
        T                 value{};

        constexpr static_list_node() noexcept = default;
    };

    // Iterator for this linked list.
    // Can be used to traverse forwards and reverse.
    template <typename T, std::size_t N, bool Reverse = false> class static_list_iterator
    {
        static_list_node<T> *_v{nullptr};
        friend static_list<T, N>;

        public:
        constexpr T *operator->() const noexcept { return &this->_v->value; }
        constexpr T &operator*() const noexcept { return this->_v->value; }

        // Move to the next element in the list.
        constexpr const static_list_iterator &operator++() noexcept
        {
            if (this->_v)
            {
                if constexpr (Reverse)
                {
                    this->_v = this->_v->prev;
                }
                else
                {
                    this->_v = this->_v->next;
                }
            }
            return *this;
        }

        constexpr friend auto operator<=>(
            const static_list_iterator &lhs, const static_list_iterator &rhs) = default;

        explicit constexpr static_list_iterator(static_list_node<T> *v) noexcept : _v{v} {}
    };
} // namespace static_list_detail

// Statically allocated doubly linked list.
// Each element is allocated within a statically allocated buffer.
//
// A list of allocated and free elements is maintained.
//
// The interface is consistent with std::list, but not guaranteed to
// be a replacement.
//
// The list does not use C++ exceptions. Instead, errors will result
// in operating system exceptions (SEGV) or hardware exceptions.
template <typename T, std::size_t N> class static_list
{
    template <typename TT> using static_list_node = static_list_detail::static_list_node<TT>;
    template <typename TT, std::size_t NN, bool Reverse>
    using static_list_iterator = static_list_detail::static_list_iterator<TT, NN, Reverse>;

    //! Use and array to store all nodes in the same memory block as this data
    //! structure.
    array<std::uint8_t, sizeof(static_list_node<T>) * N> _buffer;
    //! The free elements. nullptr when all elements reserved.
    static_list_node<T> *_free = this->get_array_entry(0);
    //! Start of the list. nullptr when empty.
    static_list_node<T> *_first = nullptr;
    //! End of the list. nullptr when empty.
    static_list_node<T> *_last = nullptr;

    /// @brief Get the next element in the free list.
    /// @note As this list does not allocate memory, all elements are stored in a free list.
    ///
    /// @return static_list_node<T>* Pointer to the next free element, or nullptr when none
    /// available.
    constexpr static_list_node<T> *get_free_elem()
    {
        if (this->_free != nullptr)
        {
            auto *elem  = _free;
            this->_free = elem->next;
            if (this->_free)
            {
                this->_free->prev = nullptr;
            }

            return elem;
        }

        return nullptr;
    }

    /// @brief Return am element to the free list.
    /// @note As this list does not allocate memory, all elements are stored in a free list.
    constexpr void return_free_elem(static_list_node<T> *elem)
    {
        elem->prev = nullptr;
        elem->next = this->_free;
        if (this->_free)
        {
            this->_free->prev = elem;
        }
        this->_free = elem;
    }

    /// @brief Directly Access the array elements that store the nodes.
    constexpr static_list_node<T> *get_array_entry(std::size_t i)
    {
        auto v = reinterpret_cast<static_list_node<T> *>(this->_buffer.data());
        return &v[i];
    }

    public:
    using iterator        = const static_list_iterator<T, N, false>;
    using const_iterator  = const static_list_iterator<T, N, false>;
    using riterator       = const static_list_iterator<T, N, true>;
    using const_riterator = const static_list_iterator<T, N, true>;

    /// @brief Forward iterator to start of list.
    constexpr iterator begin() const noexcept { return iterator(this->_first); }
    /// @brief Forward iterator to end of list.
    constexpr iterator end() const noexcept { return iterator(nullptr); }
    /// @brief Constant forward iterator to start of list.
    constexpr const_iterator cbegin() const noexcept { return iterator(this->_first); }
    /// @brief Constant forward iterator to end of list.
    constexpr const_iterator cend() const noexcept { return iterator(nullptr); }
    /// @brief Reverse iterator to start of list.
    constexpr riterator rbegin() const noexcept { return riterator(this->_last); }
    /// @brief Reverse iterator to end of list.
    constexpr riterator rend() const noexcept { return riterator(nullptr); }
    /// @brief Constant reverse iterator to start of list.
    constexpr const_riterator crbegin() const noexcept { return const_riterator(this->_last); }
    /// @brief Constant reverse iterator to end of list.
    constexpr const_riterator crend() const noexcept { return const_riterator(nullptr); }

    /// @brief Return a reference to the first element in the list.
    /// @note Will cause nullptr dereference error when the list is empty. (SEGV or HW Exception)
    constexpr T &front() noexcept { return this->_first->value; }

    /// @brief Return a reference to the last element in the list.
    /// @note Will cause nullptr dereference error when the list is empty. (SEGV or HW Exception)
    constexpr T &back() noexcept { return this->_last->value; }

    /// @brief Remove the first element in the list, return it to the free list.
    constexpr void pop_front() noexcept
    {
        if (this->_first)
        {
            auto *next = this->_first->next;
            if (next)
            {
                next->prev = nullptr;
            }

            this->return_free_elem(this->_first);
            if (this->_first == this->_last)
            {
                this->_last = next;
            }

            this->_first = next;
        }
    }

    /// @brief Remove the last element in the list, return it to the free list.
    constexpr void pop_back() noexcept
    {
        if (this->_last)
        {
            auto *prev = this->_last->prev;
            if (prev)
            {
                prev->next = nullptr;
            }

            this->return_free_elem(this->_last);
            if (this->_first == this->_last)
            {
                this->_first = prev;
            }

            this->_last = prev;
        }
    }

    /// @brief Test for an empty list.
    [[nodiscard]] constexpr bool empty() const { return this->_first == nullptr; }

    /// @brief Instanciate an element at before the iterator position in the list.
    ///
    /// @tparam Args Argument types to forward to the constructor of T.
    /// @param i Iterator position to insert before. Use end() to insert at the end of the list.
    /// @param args Arguments to forward to the constructor of T.
    template <typename... Args> constexpr void emplace(iterator i, Args &&...args)
    {
        if (auto elem = this->get_free_elem())
        {
            // Allocate in place
            (void)new (reinterpret_cast<unsigned char *>(&elem->value)) T(forward<Args>(args)...);

            // Insert
            if (i == this->end())
            {
                elem->prev = this->_last;
                elem->next = nullptr;
                if (this->_last)
                {
                    this->_last->next = elem;
                }

                this->_last = elem;
                if (!this->_first)
                {
                    // Corner case, adding to empty list
                    this->_first = elem;
                }
            }
            else
            {
                auto *i_prev = i.v_->prev;
                auto *next   = i.v_;
                elem->prev   = i_prev;
                if (i_prev)
                {
                    i_prev->next = elem;
                }
                else
                {
                    this->_first = elem;
                }

                elem->next = next;
                if (next)
                {
                    next->prev = elem;
                }
                else
                {
                    this->_last = elem;
                }
            }
        }
    }

    /// @brief Instanciate an element at the last place in the list.
    ///
    /// @tparam Args Argument types to forward to the constructor of T.
    /// @param args Arguments to forward to the constructor of T.
    template <typename... Args> constexpr void emplace_back(Args &&...args)
    {
        if (auto elem = this->get_free_elem())
        {
            // Allocate in place
            (void)new (reinterpret_cast<std::uint8_t *>(&elem->value)) T(forward<Args>(args)...);

            // Insert
            elem->prev = this->_last;
            elem->next = nullptr;
            if (this->_last)
            {
                this->_last->next = elem;
            }

            this->_last = elem;
            if (!this->_first)
            {
                // Corner case, adding to empty list
                this->_first = elem;
            }
        }
    }

    constexpr void push_back(const T &value) { this->emplace_back(value); }
    constexpr void push_back(T &&value) { this->emplace_back(move(value)); }

    /// @brief Erase at iterator position.
    constexpr void erase(iterator i)
    {
        auto org_ptr = i.v_;
        // Remove from list
        auto org_next = org_ptr->next;
        auto org_prev = org_ptr->prev;
        if (org_prev)
        {
            org_prev->next = org_next;
        }
        else
        {
            // When prev is not set, this is the first elemnt.
            this->_first = org_next;
        }

        if (org_next)
        {
            org_next->prev = org_prev;
        }
        else
        {
            // When next is not set, this is the last element.
            this->_last = org_prev;
        }

        // Save to free list
        this->return_free_elem(org_ptr);
    }

    /// @brief Construct a new list.
    constexpr static_list() noexcept
    {
        static_list_node<T> *prev      = nullptr;
        static_list_node<T> *this_node = this->get_array_entry(0);

        // Iterate over each element and ensure next and prev are set.
        for (std::size_t i = 0u; i < N; ++i)
        {
            this_node->prev = prev;
            if (prev)
            {
                prev->next = this_node;
            }

            prev = this_node++;
        }

        prev->next = nullptr;
    }

    static_list(static_list &)                  = delete;
    static_list(static_list &&)                 = delete;
    static_list &operator=(const static_list &) = delete;
    static_list &operator=(static_list &&)      = delete;
};
} // namespace util

#endif