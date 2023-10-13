#ifndef LAB1_WEAK_PTR_DECLARATION_HPP
#define LAB1_WEAK_PTR_DECLARATION_HPP

#include "../ControlBlock/ControlBlock.hpp"

namespace kogan {

template <class T>
class SharedPtr;

template <class T>
class WeakPtr {
   private:
    ControlBlock<T>* control_block_;

    friend class SharedPtr<T>;  // to access control_block_

   public:
    WeakPtr() noexcept;                           // default constructor
    WeakPtr(const WeakPtr& other) noexcept;       // copy constructor
    WeakPtr(const SharedPtr<T>& other) noexcept;  // constructor from SharedPtr
    WeakPtr(WeakPtr&& other) noexcept;            // move constructor

    WeakPtr<T>& operator=(const WeakPtr<T>& other) noexcept;    // copy assignment
    WeakPtr<T>& operator=(const SharedPtr<T>& other) noexcept;  // assignment from SharedPtr
    WeakPtr<T>& operator=(WeakPtr<T>&& other) noexcept;         // move assignment

    void reset() noexcept;               // release the reference to the managed object
    void swap(WeakPtr& other) noexcept;  // swaps the managed objects

    unsigned int use_count() const noexcept;  // returns the number of SharedPtr objects that manage the object
    bool expired() const noexcept;            // checks whether the referenced object was already deleted
    SharedPtr<T> lock() const noexcept;       // returns a SharedPtr of the managed object

    friend void swap(WeakPtr& lhs, WeakPtr& rhs) noexcept { lhs.swap(rhs); }
};

}  // namespace kogan

#include "WeakPtr.hh"

#endif