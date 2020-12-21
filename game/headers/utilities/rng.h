
struct Noise {
private:
unsigned int sd = 0, sq = 0;
public:
void seed(int seed);
void reseed(int seed);
unsigned int rand();
};