#include <iostream>
#include "sequences/ArraySequence.h"
#include "sequences/LinkedListSequence.h"


void logic() {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 1;

//    kogan::ArraySequence<int> arr_seq(values, 10);
    kogan::LinkedListSequence<int> arr_seq(values, 10);

    arr_seq.insert(42, 7);
    arr_seq.prepend(12);
    arr_seq.append(89);
    arr_seq.set(3, 999);
    auto arr_seq2 = arr_seq.get_subsequence(2, 5);

    auto arr_seq3 = arr_seq2->concat(&arr_seq);
    arr_seq3->append(13);

    std::cout << arr_seq.to_string() << std::endl;
    std::cout << arr_seq2->to_string() << std::endl;
    std::cout << arr_seq3->to_string() << std::endl;

    delete arr_seq2;
    delete arr_seq3;
    delete [] values;
}


int main() {
    try {
        logic();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
