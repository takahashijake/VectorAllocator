#include <iostream>
#include <memory> 
#include <string>

struct Person{
    std::string* name;

    Person(std::string argument){
        name = new std::string(argument);
        std::cout << "Constructing a person object with name " << *name << std::endl;
    }

    ~Person(){
        std::cout << "Destroying a person object with name " << *name << std::endl;
        delete name;
    }

};

int main(){

    std::allocator<Person> alloc;
    using Traits = std::allocator_traits<std::allocator<Person>>;

    struct Person* people = Traits::allocate(alloc, 5);

    Traits::construct(alloc, people, "James");
    Traits::construct(alloc, people + 1, "Alexandre");

    Traits::destroy(alloc, people);
    Traits::destroy(alloc, people + 1);

    Traits::deallocate(alloc, people, 5);


    return 0;
}