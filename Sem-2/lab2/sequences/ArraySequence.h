//
// Created by Gregory Kogan on 03.05.2023.
//

#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H

#include "Sequence.h"
#include "../data_structures/DynamicArray.h"

namespace kogan {

    template <class T> class ArraySequence: public Sequence<T> {
        DynamicArray<T>* array;

    public:
        ArraySequence(T* items, int count);
        ArraySequence();
        ArraySequence(const ArraySequence<T> &arraySequence);

        ~ArraySequence();

        T get_first();
        T get_last();
        T get(int index);
        Sequence<T>* get_subsequence(int start_index, int end_index);
        size_t get_length();

        void set(int index, T item);
        void append(T item);
        void prepend(T item);
        void insert(T item, int index);

        std::string to_string();
    };

    template<class T>
    ArraySequence<T>::ArraySequence(T *items, int count) {
        array = new DynamicArray<T>(items, count);
    }

    template<class T>
    ArraySequence<T>::ArraySequence() {
        array = new DynamicArray<T>(0);
    }

    template<class T>
    ArraySequence<T>::ArraySequence(const ArraySequence<T> &arraySequence) {
        array = new DynamicArray<T>(*arraySequence.array);
    }

    template<class T>
    ArraySequence<T>::~ArraySequence() {
        delete array;
    }

    template<class T>
    T ArraySequence<T>::get_first() {
        return get(0);
    }

    template<class T>
    T ArraySequence<T>::get_last() {
        return get(get_length() - 1);
    }

    template<class T>
    T ArraySequence<T>::get(int index) {
        return array->get(index);
    }

    template<class T>
    Sequence<T>* ArraySequence<T>::get_subsequence(int start_index, int end_index) {
        if (start_index < 0 || start_index >= get_length())
            throw Exception(
                    ExceptionType::IndexOutOfRange,
                    "start_index " + std::to_string(start_index) + " is out of range: [0, " + std::to_string(get_length()) + ")"
            );

        if (end_index < 0 || end_index >= get_length())
            throw Exception(
                    ExceptionType::IndexOutOfRange,
                    "end_index " + std::to_string(end_index) + " is out of range: [0, " + std::to_string(get_length()) + ")"
            );

        if (end_index < start_index)
            throw Exception(
                    ExceptionType::InvalidArgument,
                    "start_index must be less than or equal to end_index (" + std::to_string(start_index) + " > " + std::to_string(end_index) + ")"
            );

        auto sub_seq = new ArraySequence<T>;
        for (int i = start_index; i <= end_index; ++i)
            sub_seq->append(get(i));
        return sub_seq;
    }

    template<class T>
    size_t ArraySequence<T>::get_length() {
        return array->get_length();
    }

    template<class T>
    void ArraySequence<T>::set(int index, T item) {
        array->set(index, item);
    }

    template<class T>
    void ArraySequence<T>::append(T item) {
        array->resize(get_length() + 1);
        set(get_length() - 1, item);
    }

    template<class T>
    void ArraySequence<T>::prepend(T item) {
        array->resize(get_length() + 1);
        for (int i = get_length() - 1; i > 0; --i)
            set(i, get(i - 1));
        set(0, item);
    }

    template<class T>
    void ArraySequence<T>::insert(T item, int index) {
        if (index == 0)
            prepend(item);
        else if (index == get_length())
            append(item);
        else {
            array->resize(get_length() + 1);
            for (int i = get_length() - 1; i > index; --i)
                set(i, get(i - 1));
            set(index, item);
        }
    }

    template<class T>
    std::string ArraySequence<T>::to_string() {
        if (get_length() == 0)
            return "[]";

        std::string str = "[" + std::to_string(get_first());
        for (int i = 1; i < get_length(); ++i)
            str += ", " + std::to_string(get(i));
        str += "]";
        return str;
    }

} // kogan

#endif //LAB2_ARRAYSEQUENCE_H