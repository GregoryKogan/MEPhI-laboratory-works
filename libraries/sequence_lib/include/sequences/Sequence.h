#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
#pragma ide diagnostic ignored "misc-unconventional-assign-operator"
//
// Created by Gregory Kogan on 03.05.2023.
//

#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

#include <string>

namespace kogan {

    template <class T> class Sequence {

    public:
        virtual ~Sequence() = 0;

        virtual T get_first() const = 0;
        virtual T get_last() const = 0;
        virtual T get(int index) const = 0;
        virtual Sequence<T>* get_subsequence(int start_index, int end_index) const = 0;
        [[nodiscard]] virtual size_t get_length() const = 0;

        virtual void set(int index, T item) = 0;
        virtual void append(T item) = 0;
        virtual void prepend(T item) = 0;
        virtual void insert(int index, T item) = 0;
        virtual Sequence<T>* concat(Sequence<T>* sequence) = 0;
        virtual void clear() = 0;
        virtual void remove(int index) = 0;

        class SequenceGetSetProxy {
            int index;
            Sequence<T>* sequence;

        public:
            SequenceGetSetProxy(Sequence<T>* seq, int ind);
            operator T() const;
            void operator= (T item);
        };

        SequenceGetSetProxy operator[](int index);

        friend std::ostream& operator<<(std::ostream& os, const Sequence<T>& seq) {
            os << seq.to_string();
            return os;
        }

        [[nodiscard]] std::string to_string() const;
    };

    template<class T>
    Sequence<T>::SequenceGetSetProxy::SequenceGetSetProxy(Sequence<T> *seq, int ind) {
        sequence = seq;
        index = ind;
    }

    template<class T>
    Sequence<T>::SequenceGetSetProxy::operator T() const {
        return sequence->get(index);
    }

    template<class T>
    void Sequence<T>::SequenceGetSetProxy::operator=(T item) {
        sequence->set(index, item);
    }

    template<class T>
    typename Sequence<T>::SequenceGetSetProxy Sequence<T>::operator[](int index) {
        return SequenceGetSetProxy(this, index);
    }

    template<class T>
    Sequence<T>::~Sequence() = default;

    template<class T>
    std::string Sequence<T>::to_string() const {
        if (get_length() == 0)
            return "[]";

        std::string str = "[" + std::to_string(get_first());
        for (int i = 1; i < get_length(); ++i)
            str += ", " + std::to_string(get(i));
        str += "]";
        return str;
    }

} // kogan

#endif //LAB2_SEQUENCE_H

#pragma clang diagnostic pop