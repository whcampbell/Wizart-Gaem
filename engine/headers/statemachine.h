#pragma once

/**
 * class representing a general finite state machine. the first
 * template parameter is the number of states max, and the second
 * determines the type of data associated with each state (int by 
 * default). For best practice, use an enum value to correspond
 * to your integer states
 */ 
template <int states, typename T = int>
class StateMachine {
private:
    struct StateData {
        int state;
        T data;
        bool (*to[states])();
    };
    StateData list[states];
    int state = 0;
public:
    StateMachine() {
        for (int i = 0; i < states; i++) {
                list[i].state = i;
                for (int j = 0; j < states; j++) {
                list[i].to[j] = nullptr;
            }
        }
    }

    /**
     * sets the associated data for the finite state machine using the
     * inserted array elements
     * 
     * T data[] -   an array of elements organized according to which state
     *              they correspond to (eg, element at position 0 will
     *              correspond to state 0)
     */ 
    void init(T data[]) {
        for (int i = 0; i < states; i++)
            this->list[i].data = data[i];
    }

    /**
     * creates a link between two states which will allow a transition
     * assuming the given condition is met
     * 
     * int from             -   the state to begin in
     * int t8               -   the state to transition to
     * bool(*)() condition  -   a function pointer which determines when
     *                          the transition may occur
     */ 
    void link(int from, int to, bool(*condition)()) {
        list[from].to[to] = condition;
    }

    /**
     * sets the current state of the animator
     * 
     * int i    -   the state to move to
     */ 
    void set(int i) {
        state = i;
    }

    /**
     * gets the current state of the animator
     * 
     * returns  -   an int corresponding to the current state
     */ 
    int get() {
        return state;
    }

    /**
     * gets the data associated with the current state
     * 
     * returns  -   data of type T associated with current state.
     *              if the init() wasn't called on this state
     *              machine, this will have undefined behavior
     */ 
    T read() {
        return list[state].data;
    }

    /**
     * checks if it is valid for the current state to transition
     * to a new one, and transitions if it is
     */ 
    void update() {
        for (int i = 0; i < states; i++) {
            if (list[state].to[i] != nullptr && list[state].to[i]()) {
                state = i;
                return;
            }
        }
    }
};