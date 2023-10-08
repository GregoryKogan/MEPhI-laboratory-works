#ifndef LAB1_LINKED_LIST_SEQUENCE_HPP
#define LAB1_LINKED_LIST_SEQUENCE_HPP

#include "SmartPtrSequence.hpp"
#include "sequence_lib.hpp"

namespace kogan {

template <class T>
class SmartPtrLinkedListSequence : public SmartPtrSequence<T> {
    UniquePtr<LinkedList<T>> list;

   public:
    SmartPtrLinkedListSequence(T *items, int count);
    SmartPtrLinkedListSequence();
    SmartPtrLinkedListSequence(const SmartPtrLinkedListSequence<T> &linkedListSequence);

    T get_first() const override;
    T get_last() const override;
    T get(int index) const override;
    UniquePtr<SmartPtrSequence<T>> get_subsequence(int start_index, int end_index) const override;
    [[nodiscard]] size_t get_length() const override;

    void set(int index, T item) override;
    void append(T item) override;
    void prepend(T item) override;
    void insert(int index, T item) override;
    UniquePtr<SmartPtrSequence<T>> concat(SharedPtr<SmartPtrSequence<T>> sequence) const override;
    void clear() override;
    void remove(int index) override;

    T &operator[](int index) override;
};

template <class T>
SmartPtrLinkedListSequence<T>::SmartPtrLinkedListSequence(T *items, int count) {
    list = make_unique<LinkedList<T>>(items, count);
}

template <class T>
SmartPtrLinkedListSequence<T>::SmartPtrLinkedListSequence() {
    list = make_unique<LinkedList<T>>();
}

template <class T>
SmartPtrLinkedListSequence<T>::SmartPtrLinkedListSequence(const SmartPtrLinkedListSequence<T> &linkedListSequence) {
    list = make_unique<LinkedList<T>>(*linkedListSequence.list);
}

template <class T>
T SmartPtrLinkedListSequence<T>::get_first() const {
    return list->get_first();
}

template <class T>
T SmartPtrLinkedListSequence<T>::get_last() const {
    return list->get_last();
}

template <class T>
T SmartPtrLinkedListSequence<T>::get(int index) const {
    return list->get(index);
}

template <class T>
UniquePtr<SmartPtrSequence<T>> SmartPtrLinkedListSequence<T>::get_subsequence(int start_index, int end_index) const {
    LinkedList<T> sub_list = list->get_sublist(start_index, end_index);

    auto sub_seq = UniquePtr<SmartPtrSequence<T>>(new SmartPtrLinkedListSequence<T>());
    for (int i = 0; i < sub_list.get_length(); ++i) sub_seq->append(sub_list.get(i));
    return sub_seq;
}

template <class T>
size_t SmartPtrLinkedListSequence<T>::get_length() const {
    return list->get_length();
}

template <class T>
void SmartPtrLinkedListSequence<T>::set(int index, T item) {
    list->set(index, item);
}

template <class T>
void SmartPtrLinkedListSequence<T>::append(T item) {
    list->append(item);
}

template <class T>
void SmartPtrLinkedListSequence<T>::prepend(T item) {
    list->prepend(item);
}

template <class T>
void SmartPtrLinkedListSequence<T>::insert(int index, T item) {
    list->insert(index, item);
}

template <class T>
UniquePtr<SmartPtrSequence<T>> SmartPtrLinkedListSequence<T>::concat(SharedPtr<SmartPtrSequence<T>> sequence) const {
    auto concatenation = UniquePtr<SmartPtrSequence<T>>(new SmartPtrLinkedListSequence<T>(*this));
    for (int i = 0; i < sequence->get_length(); ++i) concatenation->append(sequence->get(i));
    return concatenation;
}

template <class T>
void SmartPtrLinkedListSequence<T>::clear() {
    list->clear();
}

template <class T>
void SmartPtrLinkedListSequence<T>::remove(int index) {
    list->remove(index);
}

template <class T>
T &SmartPtrLinkedListSequence<T>::operator[](int index) {
    return list->operator[](index);
}

}  // namespace kogan

#endif