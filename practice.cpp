#include <iostream> 
#include <memory>
struct Widget{
    int x;
    Widget(int v) : x(v) {
        std::cout << "Constructed" << std::endl;
    }

    ~Widget(){
        std::cout << "Destroying " << x << std::endl;
    }
};


int main(){

    std::allocator<int> alloc;

    using Traits = std::allocator_traits<std::allocator<int>>;

    int *p = Traits::allocate(alloc, 5);
    for (int i = 0; i < 5; i++){
        Traits::construct(alloc, p + i, i);
    }

    for (int j = 0; j < 5; j++){
        std::cout << p[j] << std::endl;
    }

    for (int i = 0; i < 5; i++){
        Traits::destroy(alloc, p + i);
    }

    Traits::deallocate(alloc, p, 5);


    std::allocator<Widget> myAlloc;
    using myTraits = std::allocator_traits<std::allocator<Widget>>;

    struct Widget* myWidgets = myTraits::allocate(myAlloc, 3);

    for (int i = 0; i < 3; i++){
        myTraits::construct(myAlloc, myWidgets + i, 10 + (i * 10));
    }

    for (int j = 0; j < 3; j++){
        std::cout << myWidgets[j].x << std::endl;
    }

    //for (int i = 0; i < 3; i++){
    //    myTraits::destroy(myAlloc, myWidgets + i);
    //}
   
    myTraits::deallocate(myAlloc, myWidgets, 3);

    return 0;
}