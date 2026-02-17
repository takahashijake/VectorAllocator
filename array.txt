#include <memory>
#include <iostream>

template<typename T, typename Alloc = std::allocator<T>>
class ArrayList{
    private:
        int count;
        int capacity;
        Alloc alloc;
        T* array;

    public:

        using Traits = std::allocator_traits<Alloc>;

        ArrayList(){
            count = 0;
            capacity = 10;
            array = Traits::allocate(alloc, capacity);
            std::cout << "Constructing a new ArrayList object" << std::endl;
        }

        void inflate(){
            T* temp = Traits::allocate(alloc, capacity * 2);
            for (int i = 0; i < count; i++){
                Traits::construct(alloc, temp + i, *(array + i));
                Traits::destroy(alloc, array + i);
            }
            Traits::deallocate(alloc, array, capacity);
            array = temp;
            capacity = capacity * 2;
        }

        void append(T value){
            if (count == capacity){
                inflate();
            }
            Traits::construct(alloc, array + count, value);
            count++;
        }

        void printList(){
            for (size_t i = 0; i < count; i++){
                std::cout << array[i] << std::endl;
            }
        }

        ~ArrayList(){
            if (array != nullptr){
                for (int i = 0; i < count; i++){
                    Traits::destroy(alloc, array + i);
                }
                Traits::deallocate(alloc, array, capacity);
            }
        }
};

int main(){

    ArrayList<int, std::allocator<int>> myList;
    for (size_t i = 0; i < 10; i++){
        myList.append(i);
    }
    myList.printList();
    
    return 0;
}