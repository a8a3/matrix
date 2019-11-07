#pragma once

#include <unordered_map>
#include <numeric>

namespace {

template<typename T>
class matrix_iterator : public std::iterator<std::input_iterator_tag, T> {
    friend class matrix;
public:
    matrix_iterator(const matrix_iterator& it) 
    : value_(it.value_) {}

    bool operator == (const matrix_iterator& other) const {
        return other.value_ == value_;
    }
    
    bool operator != (const matrix_iterator& other) const {
        return !operator==(other);
    }

    typename matrix_iterator::reference operator*() const {
        return *value_;
    }

    matrix_iterator& operator++() {
        ++value_;
        return *this;
    }

private:
    matrix_iterator(T* value) : value_(value) {};
    T* value_;
};

} // namespace

// ------------------------------------------------------------------
template<typename T, const T default_value>
class matrix {
    
    struct row {
        std::unordered_map<size_t, T> elems_;

        T& operator[] (const size_t& index) {
            return elems_[index];
        }

        size_t size() const {
            return elems_.size();
        }
    };
    std::unordered_map<size_t, row> rows_;

public:
    using iterator = matrix_iterator<T>;
 
    iterator begin() const {
        
    }

    iterator end() const {

    }

    matrix() = default;
   ~matrix() = default;

    size_t size() const {
        return std::accumulate(rows_.begin(), rows_.end(), 0, 
        [] (size_t size, const auto& r) {
            return size + r.second.size();
        });  
    }

    row& operator[] (const size_t& index) {
        return rows_[index];
    }
};

// ------------------------------------------------------------------
// template<size_t N>
// struct index_getter {
//     bool getting_index_ {false};
//     std::array<size_t, N> index_;
    
//     index_getter& operator[] (const size_t& index_part) {
//         if (!getting_index_) {
//             getting_index_ = true;
//             return *this;
//         }
//     }
// };