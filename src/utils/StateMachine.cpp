#include "StateMachine.h"

template <int states, typename T> StateMachine<states, T>::StateMachine() {
    for (int i = 0; i < states; i++) {
        list[i].state = i;
        this->list[i].data = i;
        for (int j = 0; j < states; j++) {
            list[i].to[j] = nullptr;
        }
    }
}

template <int states, typename T>  StateMachine<states, T>::StateMachine(T data[]) {
    for (int i = 0; i < states; i++) {
        list[i].state = i;
        this->list[i].data = data[i];
        for (int j = 0; j < states; j++) {
            list[i].to[j] = nullptr;
        }
    }
}

template <int states, typename T>  void StateMachine<states, T>::link(int from, int to, bool* condition) {
    list[from].to[to] = condition;
}

template <int states, typename T>  void StateMachine<states, T>::set(int i) {
    state = i;
}

template <int states, typename T>  int StateMachine<states, T>::get() {
    return state;
}

template <int states, typename T>  T StateMachine<states, T>::read() {
    return list[state].data;
}

template <int states, typename T>  void StateMachine<states, T>::update() {
    for (int i = 0; i < states; i++) {
        if (list[state].to[i]()) {
            state = i;
            return;
        }
    }
}