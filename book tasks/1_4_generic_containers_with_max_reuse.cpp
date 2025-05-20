#include "doctest/doctest.h"
#include <cstddef>
#include <algorithm>
#include <initializer_list>

/* TO DO:
We need max reuse of copy constructor and copy operator
1. Write copy constructor 
2. Write copy operator + 
*/

template<typename T, size_t size>
class fixed_vector
{
    public:
        typedef T* iterator;
        typedef const T* const_iterator;
        iterator begin() {return v_;}
        iterator end() {return v_ + size;}
        const_iterator begin() const {return v_;}
        const_iterator end() const {return v_ + size;}
        fixed_vector<T, size>() {}
        fixed_vector<T, size>(std::initializer_list<T> ilist){
            std::copy(ilist.begin(), ilist.end(), begin());
        }
        fixed_vector<T, size> & operator=(const fixed_vector<T, size> & other){
            // if vector sizes aren't equal, is there a compilation error? Yes
            std::copy(other.begin(), other.end(), begin());
            return *this;
        }

        fixed_vector(const fixed_vector<T, size> & other){
            operator=(other);
        }
        bool operator==(const fixed_vector<T, size> & other){
            for (size_t i = 0; i < size; ++i){
                if (v_[i] != other.v_[i]) return false;
            }
            return true;
        }

        bool operator!=(const fixed_vector<T, size> & other){
           return !operator==(other);
        }

    private:
        T v_[size];
};



TEST_CASE("not equal operator"){
    SUBCASE("non-empty vectors with equal length"){
        const size_t size = 3;
        fixed_vector<int, size> fv_1 = {1, 2, 3};
        fixed_vector<int, size> fv_2 = {4, 5, 7};
        CHECK(fv_1 != fv_2);
    }
    SUBCASE("non-empty vectors with unequal length"){
        // fixed_vector<int, 3> fv_1 = {1, 2, 3};
        // fixed_vector<int, 2> fv_2 = {4, 5};
        // CHECK(fv_1 != fv_2); // compile time error
    }
}


TEST_CASE("assign operator"){
    
    SUBCASE("empty vectors"){
        const size_t size = 5;
        fixed_vector<int, size> fv_1;
        fixed_vector<int, size> fv_2;
        fv_1 = fv_2;
        CHECK(fv_1 == fv_2);
    }

    SUBCASE("non empty vectors"){
        const size_t size = 5;
        fixed_vector<int, size> fv_1 = {1, 2, 3, 4, 5};
        fixed_vector<int, size> fv_2 = {3, 4, 5, 6, 7};
        fv_1 = fv_2;
        CHECK(fv_1 == fv_2);
    }
    
}

TEST_CASE("copy constructor"){
    fixed_vector<int, 3> fv_1 = {1, 2, 3};
    fixed_vector fv_2(fv_1);
    CHECK(fv_1 == fv_2);
    *(fv_2.begin()) = 2;
    CHECK(fv_1 != fv_2);
}