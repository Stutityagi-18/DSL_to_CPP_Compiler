#include <string>

using namespace std;

class Demo
{
public:

    unsigned long long max(unsigned long long a, unsigned long long b)
    {
        if((a > b))
        {
            return a;
        } else
        {
            return b;
        }
    }

};

int main()
{
    Demo contract;
    return 0;
}
