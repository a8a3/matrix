#pragma once

#include <map>
#include <array>
#include <tuple>

// TODO
// #include <boost/stacktrace.hpp>

template<typename T, size_t N, const T def>
class matrix;

// ------------------------------------------------------------------
template<typename T, size_t N, const T def>
class storage {
    friend class matrix<T, N, def>;

public:
    using storage_index = std::array<size_t, N>;
    using storage_impl = std::map<storage_index, T>;
    using storage_iter = typename storage_impl::const_iterator;
 
    storage() = default;
   ~storage() = default;
   
    storage& operator[](size_t ind) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if (ind_token_ >= N) {
            throw std::out_of_range("incorrect index passed");
        }
        ind_[ind_token_] = ind;
        ++ind_token_;
        return *this;
    }
    
    operator T() const {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if (ind_token_ != N) {
            std::cout << "ind token: " << ind_token_ << std::endl;
            throw std::out_of_range("incorrect index passed");
        }
    
        auto it = data_.find(ind_);
        ind_token_ = 0;
        ind_ = {0};
        
        return it == data_.end() ? def : it->second;
    }

    bool operator== (const T& val) const {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if (ind_token_ != N) {
            std::cout << "ind token: " << ind_token_ << std::endl;
            throw std::out_of_range("incorrect index passed");
        }
    
        std::cout << "0" << std::endl;
        auto it = data_.find(ind_);
        std::cout << "1" << std::endl;
        ind_token_ = 0;
        std::cout << "2" << std::endl;
        ind_ = {0};
        std::cout << "3" << std::endl;

        if (it == data_.end()) {
        std::cout << "4" << std::endl;
            return false;
        }
        std::cout << "5" << std::endl;
        return it->second == val;
    }
    
    storage& operator= (const T& val) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "val: " << val << std::endl;
        if (ind_token_ != N) {
            throw std::out_of_range("incorrect index passed");
        }
    
        if (val == def) {
            auto it = data_.find(ind_);
            if (it != data_.end()) {
                data_.erase(it);
            }
        } else {
            data_[ind_] = val;
        }
        ind_token_ = 0;
        ind_ = {0};
        return *this;
    }
 
    size_t size() const {
        return data_.size();
    }
 
private:
    mutable storage_index ind_{0};
    mutable size_t ind_token_{0};
    storage_impl data_; 
};
 
template<typename T, size_t N, const T def>
class matrix_iterator;
 
// ------------------------------------------------------------------
template<typename T, size_t N, const T def = T()>
class matrix {
    storage<T, N, def> s_;
    
public:    
    matrix() = default;
   ~matrix() = default;
   
    storage<T, N, def>& operator[] (size_t ind) {
        return s_[ind];
    }
    
    matrix_iterator<T, N, def> begin() const {
        return matrix_iterator<T, N, def>(s_.data_.cbegin());
    }
    
    matrix_iterator<T, N, def> end() const {
        return matrix_iterator<T, N, def>(s_.data_.cend());
    }
    
    size_t size() const {
        return s_.size();
    }
};
 
// ------------------------------------------------------------------
template<typename T, size_t N, const T def>
class matrix_iterator : public std::iterator<std::input_iterator_tag, T> {
 
    template<typename Array, std::size_t... I>
    auto a2t_impl(const Array& a, std::index_sequence<I...>) {
        return std::make_tuple(a[I]...);
    }
    
    template<typename Indices = std::make_index_sequence<N>>
    auto a2t(const std::array<size_t, N>& a) {
        return a2t_impl(a, Indices{});
    }
 
public: 
    using const_iterator = typename storage<T, N, def>::storage_iter;
    const_iterator it_;
    
    explicit matrix_iterator(const_iterator it) : it_(it){
    }
 
    bool operator == (const matrix_iterator& other) const {
        return other.it_ == it_;
    }
    
    bool operator != (const matrix_iterator& other) const {
        return !operator==(other);
    }
 
    auto operator*() {
        return std::tuple_cat(a2t(it_->first), std::make_tuple(it_->second));
    }
 
    matrix_iterator& operator++() {
        ++it_;
        return *this;
    }
};

