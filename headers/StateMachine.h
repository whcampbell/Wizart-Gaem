
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
    StateMachine();
    StateMachine(T data[]);
    void link(int from, int to, bool* condition);
    void set(int i);
    int get();
    T read();

    void update();
};