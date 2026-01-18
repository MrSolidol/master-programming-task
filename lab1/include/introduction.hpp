#ifndef __INTRODUCTION_HPP__
#define __INTRODUCTION_HPP__

#include <string>
#include <string_view>

class introduction
{
public:
    std::string_view name() const
    {
        return name_;
    }

    std::string_view surename() const
    {
        return surename_;
    }

    std::string fullname() const
    {
        return std::string{name_} + " " + std::string{surename_};
    }

private:
    std::string name_{"Alexander"};
    std::string surename_{"Kolesnikov"};
};

#endif // __INTRODUCTION_HPP__
