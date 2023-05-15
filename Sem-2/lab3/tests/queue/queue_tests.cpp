//
// Created by Gregory Kogan on 15.05.2023.
//

#include "queue_tests.hpp"


kogan::TestSuite queue_test_suite("Queue");


TEST(empty_constructor, queue_test_suite) {
    kogan::Queue<int> q;

    ASSERT(q.size() == 0); // NOLINT(readability-container-size-empty)
    ASSERT(q.empty());
}

TEST(array_constructor, queue_test_suite) {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 1;

    kogan::Queue<int> q(values, 10);
    delete[] values;

    ASSERT(q.size() == 10);
    ASSERT(!q.empty());
    ASSERT(q.pop() == 1);
    ASSERT(q.pop() == 2);
}

TEST(sequence_constructor, queue_test_suite) {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 1;

    kogan::ArraySequence<int> init_seq(values, 10);
    kogan::Queue<int> q(&init_seq);
    delete[] values;

    ASSERT(q.size() == init_seq.get_length());
    ASSERT(q.size() == 10);
    ASSERT(!q.empty());
    ASSERT(q.pop() == 1);
    ASSERT(q.pop() == init_seq[1]);
}

TEST(queue_constructor, queue_test_suite) {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 1;

    kogan::Queue<int> init_q(values, 10);
    kogan::Queue<int> q(&init_q);
    delete[] values;

    ASSERT(q.size() == init_q.size());
    ASSERT(q.size() == 10);
    ASSERT(!q.empty());
    ASSERT(q.pop() == 1);
    ASSERT(init_q.pop() == 1);
    ASSERT(q.pop() == init_q.pop());
}

TEST(empty, queue_test_suite) {
    kogan::Queue<int> q;
    ASSERT(q.empty());

    q.push(1);
    ASSERT(!q.empty());

    q.pop();
    ASSERT(q.empty());
}

TEST(size, queue_test_suite) {
    kogan::Queue<int> q;
    ASSERT(q.size() == 0); // NOLINT(readability-container-size-empty)

    q.push(1);
    ASSERT(q.size() == 1);

    q.pop();
    ASSERT(q.size() == 0); // NOLINT(readability-container-size-empty)

    for (int i = 0; i < 100; ++i)
        q.push(i);
    ASSERT(q.size() == 100);
}

TEST(swap, queue_test_suite) {
    kogan::Queue<int> q1;
    kogan::Queue<int> q2;

    q1.push(1);
    q1.push(2);
    q1.push(3);

    q2.push(4);
    q2.push(5);

    q1.swap(q2);

    ASSERT(q1.size() == 2);
    ASSERT(q2.size() == 3);

    ASSERT(q1.pop() == 4);
    ASSERT(q1.pop() == 5);

    ASSERT(q2.pop() == 1);
    ASSERT(q2.pop() == 2);
    ASSERT(q2.pop() == 3);
}

TEST(push, queue_test_suite) {
    kogan::Queue<int> q;

    q.push(1);
    ASSERT(q.size() == 1);
    ASSERT(q.pop() == 1);

    q.push(2);
    q.push(3);
    ASSERT(q.size() == 2);
    ASSERT(q.pop() == 2);
    ASSERT(q.pop() == 3);
}

TEST(pop, queue_test_suite) {
    kogan::Queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    ASSERT(q.pop() == 1);
    ASSERT(q.pop() == 2);
    ASSERT(q.pop() == 3);
}

TEST(pop_EmptyContainerException, queue_test_suite) {
    kogan::Queue<int> q;

    bool emptyContainerExceptionThrown = false;
    try {
        q.pop();
    } catch (kogan::EmptyContainerException& e) {
        emptyContainerExceptionThrown = true;
    }
    ASSERT(emptyContainerExceptionThrown);
}

TEST(concat, queue_test_suite) {
    kogan::Queue<int> q1;
    kogan::Queue<int> q2;

    q1.push(1);
    q1.push(2);
    q1.push(3);

    q2.push(4);
    q2.push(5);

    auto q3 = q1.concat(q2);

    ASSERT(q1.size() == 3);
    ASSERT(q2.size() == 2);

    ASSERT(q3->size() == 5);
    ASSERT(q3->pop() == 1);
    ASSERT(q3->pop() == 2);
    ASSERT(q3->pop() == 3);
    ASSERT(q3->pop() == 4);
    ASSERT(q3->pop() == 5);
    ASSERT(q3->empty());
    delete q3;

    auto q4 = q2.concat(q1);

    ASSERT(q1.size() == 3);
    ASSERT(q2.size() == 2);

    ASSERT(q4->size() == 5);
    ASSERT(q4->pop() == 4);
    ASSERT(q4->pop() == 5);
    ASSERT(q4->pop() == 1);
    ASSERT(q4->pop() == 2);
    ASSERT(q4->pop() == 3);
    ASSERT(q4->empty());
    delete q4;
}

TEST(get_subsequence, queue_test_suite) {
    kogan::Queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    kogan::Sequence<int>* sq = q.get_subsequence(0, 4);
    ASSERT(sq->get_length() == 5);
    ASSERT(sq->get(0) == 1);
    ASSERT(sq->get(4) == 5);
    delete sq;

    sq = q.get_subsequence(1, 3);
    ASSERT(sq->get_length() == 3);
    ASSERT(sq->get(0) == 2);
    ASSERT(sq->get(1) == 3);
    ASSERT(sq->get(2) == 4);
    delete sq;

    sq = q.get_subsequence(2, 2);
    ASSERT(sq->get_length() == 1);
    ASSERT(sq->get(0) == 3);
    delete sq;
}

kogan::TestSuite get_queue_test_suite() {
    return queue_test_suite;
}