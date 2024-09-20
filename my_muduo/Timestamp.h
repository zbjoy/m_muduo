#pragma once

// #include <cstdint>
// #include <stdint.h>
#include <iostream>
#include <string>

namespace m_muduo
{

    class Timestamp
    {
    public:
        Timestamp();
        explicit Timestamp(int64_t microSecondsSinceEpoch);

        static Timestamp now();
        std::string toString() const;

    private:
        int64_t microSecondsSinceEpoch_;
    };

}
