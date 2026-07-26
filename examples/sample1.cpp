#include <string>

using namespace std;

class Calculator
{
public:

    unsigned long long add(unsigned long long a, unsigned long long b)
    {
        unsigned long long c = (a + b);
        return c;
    }

};

int main()
{
    Calculator contract;
    return 0;
}
