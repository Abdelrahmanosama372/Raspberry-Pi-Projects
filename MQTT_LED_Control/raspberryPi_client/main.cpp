#include <iostream>
#include "subscriber.hpp"

int main()
{
    Subscriber sub("ledstate");
    sub.spin();
    return 0;
}