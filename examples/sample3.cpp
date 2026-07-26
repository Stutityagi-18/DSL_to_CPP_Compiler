#include <string>

using namespace std;

class Math
{
public:

    unsigned long long calc(unsigned long long a, unsigned long long b)
    {
        unsigned long long c = ((a * b) + 10);
        return c;
    }

};

int main()
{
    Math contract;
    return 0;
}
