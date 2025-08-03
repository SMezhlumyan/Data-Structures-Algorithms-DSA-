#include <iostream>
#include <vector>

void  SievePrime(int n){
    if (n < 2)
        throw std::runtime_error("Invalid Input");

    std::vector<bool> prime(n + 1, true);

    prime[0] = prime[1] = false;

    for (int i = 2; i * i <= n; i++) 
    {
        if (prime[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                prime[j] = false;
            }
        }
    }

    for (int i = 2; i <= n; i++)
    {
        if (prime[i])
        {
            std::cout << i << " ";
        }
    }

}

int main()
{

    SievePrime(37);
}