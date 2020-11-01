#pragma once

template <int states, typename T = int>
class StateMachine {
private:
    struct StateData {
        int state;
        T data;
        bool (*to[states])();
    };
    StateData list[states];
    int state;
public:
    StateMachine() {
        for (int i = 0; i < states; i++) {
                list[i].state = i;
                this->list[i].data = i;
                for (int j = 0; j < states; j++) {
                list[i].to[j] = nullptr;
            }
        }
    }

    StateMachine(T data[]) {
        for (int i = 0; i < states; i++) {
            list[i].state = i;
            this->list[i].data = data[i];
            for (int j = 0; j < states; j++) {
                list[i].to[j] = nullptr;
            }
        }
    }

    void link(int from, int to, bool* condition) {
        list[from].to[to] = condition;
    }

    void set(int i) {
        state = i;
    }

    int get() {
        return state;
    }

    T read() {
        return list[state].data;
    }

    void update() {
        for (int i = 0; i < states; i++) {
            if (list[state].to[i]()) {
                state = i;
                return;
            }
        }
    }
};