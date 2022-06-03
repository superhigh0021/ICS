#include <iostream>

template <typename T>
class sharedPtr {
public:
    sharedPtr(T* p = nullptr)
        : ptr(p), count(new int(1)) {}

    sharedPtr(const sharedPtr<T>& p)
        : ptr(p.ptr), count(p.count) {}

    sharedPtr(sharedPtr<T>&& p)
        : ptr(std::move(p.ptr)), count(std::move(p.count)) {
        p.~sharedPtr();
        std::cout << "move" << std::endl;
    }

    sharedPtr& operator=(const sharedPtr<T>& p) {
        if (this != &p) {
            if (--(*(this->count)) == 0) {
                delete this->ptr;
                delete this->count;
            }
            this->ptr = p.ptr;
            this->count = p.count;
            ++(*(this->count));
        }
        return *this;
    }

    T& operator*() {
        return *(this->ptr);
    }

    T* operator->() {
        return this->ptr;
    }

    ~sharedPtr() {
        --(*(this->count));
        std::cout << *(this->count) << std::endl;
        if (*(this->count) == 0) {
            delete this->ptr;
            this->ptr = nullptr;
            delete this->count;
            this->count = nullptr;
        }
        std::cout << "des" << std::endl;
    }

private:
    T* ptr;
    int* count;
};