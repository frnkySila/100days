#include <iostream>
#include <vector>
#include <algorithm>

class modulo1097calculator
{
    static const int TEN_TO_9TH_PLUS_7 = 1000 * 1000 * 1000 + 7;

    std::vector<int> powers2 { 1, 2 };

public:
    int get_2_to_the_power(int exp)
    {
        while(powers2.size() < exp + 1) {
            powers2.push_back((powers2.back() * 2) % TEN_TO_9TH_PLUS_7);
        }

        return powers2[exp];
    }

    static int get_decremented(int x)
    {
        return (x - 1) % TEN_TO_9TH_PLUS_7;
    }

    static int get_product(int a, int b)
    {
        long long result = ((long long)a * b) % TEN_TO_9TH_PLUS_7;

        return (int)result;
    }

    static int get_sum(int a, int b)
    {
        long long result = a;
        result += b;
        result %= TEN_TO_9TH_PLUS_7;

        return (int)result;
    }
};

int main()
{
    int num_computers;

    std::cin >> num_computers;

    std::vector<int> positions((size_t)num_computers);

    for(int i = 0; i < num_computers; i++)
    {
        std::cin >> positions[i];
    }

    std::sort(positions.begin(), positions.end());

    modulo1097calculator c;

    int result = 0;

    for(int i = 1; i < num_computers; i++) {
        int contribution = positions[i] - positions[i - 1];

        int num_sums = c.get_product(
                c.get_decremented(c.get_2_to_the_power(i)),
                c.get_decremented(c.get_2_to_the_power(num_computers - i))
        );

        result = c.get_sum(result, c.get_product(contribution, num_sums));
    }

    std::cout << result << std::endl;
}