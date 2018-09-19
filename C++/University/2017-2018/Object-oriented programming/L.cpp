#include <string>
#include <iostream>
#include <utility>
#include <memory>
#include <type_traits>

using namespace std;

// class Data
// {
//   public:
//     Data()
//     {
//         cout << "constructor()" << endl;
//     }

//     Data(const Data &asd)
//     {
//         cout << "constructor(const TestingData &)" << endl;
//     }

//     Data(Data &&asd)
//     {
//         cout << "constructor(TestingData &&)" << endl;
//     }
// };

class DataPair
{
  private:
    std::unique_ptr<Data> first_;
    std::unique_ptr<Data> second_;

  public:
    DataPair(const DataPair &other) noexcept(is_nothrow_copy_constructible<Data>::value)
    {
        first_ = std::unique_ptr<Data>(new Data(*other.first_.get()));
        second_ = std::unique_ptr<Data>(new Data(*other.second_.get()));
    }

    DataPair(DataPair &&other) noexcept
    {
        std::swap(first_, other.first_);
        std::swap(second_, other.second_);
    }

    DataPair(const Data &f, const Data &s) noexcept(is_nothrow_copy_constructible<Data>::value)
    {
        first_ = std::unique_ptr<Data>(new Data(f));
        second_ = std::unique_ptr<Data>(new Data(s));
    }

    DataPair(Data &&f, const Data &s) noexcept(is_nothrow_move_constructible<Data>::value &&is_nothrow_copy_constructible<Data>::value)
    {
        second_ = std::unique_ptr<Data>(new Data(s));
        first_ = std::unique_ptr<Data>(new Data(move(f)));
    }

    DataPair(const Data &f, Data &&s) noexcept(is_nothrow_move_constructible<Data>::value &&is_nothrow_copy_constructible<Data>::value)
    {
        first_ = std::unique_ptr<Data>(new Data(f));
        second_ = std::unique_ptr<Data>(new Data(move(s)));
    }

    DataPair(Data &&f, Data &&s) noexcept(is_nothrow_move_constructible<Data>::value || is_nothrow_copy_constructible<Data>::value)
    {
        if (is_nothrow_move_constructible<Data>::value)
        {
            first_ = std::unique_ptr<Data>(new Data(move(f)));
            second_ = std::unique_ptr<Data>(new Data(move(s)));
        }
        else
        {
            first_ = std::unique_ptr<Data>(new Data(f));
            second_ = std::unique_ptr<Data>(new Data(s));
        }
    }

    DataPair &operator=(DataPair &&other) noexcept
    {
        // if (this != &other)
        // {
        std::swap(first_, other.first_);
        std::swap(second_, other.second_);
        // }
        return *this;
    }

    DataPair &operator=(const DataPair &other) noexcept(is_nothrow_copy_constructible<Data>::value)
    {
        DataPair n = other;
        std::swap(*this, n);
        return *this;
    }

    const Data &first() const noexcept
    {
        return *first_.get();
    }

    const Data &second() const noexcept
    {
        return *second_.get();
    }
};

// int main()
// {
//     Data a, b, c, d, e, f;
//     cout << "1." << endl;
//     DataPair(move(b), move(a));
//     cout << "2." << endl;
//     DataPair p(c, move(d));
//     cout << "3." << endl;
//     DataPair q(e, f);
//     cout << "4." << endl;
//     DataPair r(p);
//     cout << "5." << endl;
//     DataPair s(move(q));

//     cout << boolalpha << "copy constructor is noexcept? " << noexcept(DataPair(p)) << endl;
//     getchar();
//     return 0;
// }