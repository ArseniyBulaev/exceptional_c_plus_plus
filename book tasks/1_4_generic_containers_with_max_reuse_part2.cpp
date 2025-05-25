#include "doctest/doctest.h"
#include <cstddef>
#include <initializer_list>
#include <algorithm>


template<typename T, size_t size>
class fixed_vector{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    fixed_vector() {} // our old pal default constructor

    // I think here there is a problem, 
    // because if vector will construct with template parameter size > osize,
    // we won't have a normal other copy,
    // because new vector will consit of other elements and tail of default empty elements
    // Also we duplicate operator=. We can simply write in body operator=(other).
    template<typename O, size_t osize>
    fixed_vector(const fixed_vector<O, osize>& other){
        std::copy( other.begin(),
              other.begin() + std::min(size, osize),
              begin()
        );
    }

    // Here there is a problem, if osize < size.
    // If so, we will have osize elements from other and size - osize elements witch were there before copy
    // If osize == 0, we don't copy anything at all
    // I don't think it's the behaviour someone would want
    template<typename O, size_t osize>
    fixed_vector<T, size> & 
    operator=(const fixed_vector<O, osize> & other)
    {
        std::copy(other.begin(),
             other.begin() + std::min(size, osize),
             begin());
        return *this;
    }

    // My code
    fixed_vector<T, size>(std::initializer_list<T> ilist){
            std::copy(ilist.begin(), ilist.end(), begin());
    }
    bool operator==(const fixed_vector<T, size> & other){
            for (size_t i = 0; i < size; ++i){
                if (v_[i] != other.v_[i]) return false;
            }
            return true;
    }

    iterator begin() {return v_; }
    iterator end() {return v_ + size; }
    const_iterator begin() const { return v_; }
    const_iterator end() const {return v_ + size; }
private:
    T v_[size];
};


TEST_CASE("assigment operator"){
    SUBCASE("size > osize"){
        fixed_vector<int, 5> fv_1 = {1, 2, 3, 4, 5};
        fixed_vector<int, 3> fv_2 = {4, 4, 4};
        fv_1 = fv_2;
        fixed_vector<int, 5> fv_2_should_be = {4, 4, 4, 4, 5};
        CHECK(fv_2 == fv_2_should_be);
    }
}