#include <iostream>
#include <memory> 

int main(){

    std::allocator<int> alloc;

    using Traits = std::allocator_traits<std::allocator<int>>;

    int* p = Traits::allocate(alloc, 1);
    Traits::construct(alloc, p, 5);

    std::cout << p[0] << std::endl;

    Traits::destroy(alloc, p);
    std::cout << p[0] << std::endl;
    return 0;
}