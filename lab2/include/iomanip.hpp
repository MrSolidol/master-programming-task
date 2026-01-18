#ifndef __IOMANIP_HPP__
#define __IOMANIP_HPP__

#include <iostream>
#include <string>

//{ endm manipulator
inline std::ostream& endm(std::ostream& os) {
    return os << "[eol]\n";
}
//}

//{ squares manipulator
class squares_wrapper {
    std::ostream& os;
public:
    explicit squares_wrapper(std::ostream& stream) : os(stream) {}
    
    template<typename T>
    friend std::ostream& operator<<(squares_wrapper sw, const T& value) {
        sw.os << '[' << value << ']';
        return sw.os;
    }
};

struct squares_tag {};
inline squares_tag squares;

inline squares_wrapper operator<<(std::ostream& os, const squares_tag&) {
    return squares_wrapper(os);
}
//}

//{ add manipulator
template<typename T1>
class add_stage2;

class add_stage1 {
    std::ostream& os;
public:
    explicit add_stage1(std::ostream& stream) : os(stream) {}
    
    template<typename T1>
    friend add_stage2<T1> operator<<(add_stage1 stage, const T1& value1);
};

template<typename T1>
class add_stage2 {
    std::ostream& os;
    T1 value1;
public:
    add_stage2(std::ostream& stream, T1 v1) : os(stream), value1(v1) {}
    
    template<typename T2>
    friend std::ostream& operator<<(add_stage2<T1> stage, const T2& value2) {
        stage.os << (stage.value1 + value2);
        return stage.os;
    }
};

template<typename T1>
add_stage2<T1> operator<<(add_stage1 stage, const T1& value1) {
    return add_stage2<T1>(stage.os, value1);
}

struct add_tag {};
inline add_tag add;

inline add_stage1 operator<<(std::ostream& os, const add_tag&) {
    return add_stage1(os);
}
//}

#endif // __IOMANIP_HPP__