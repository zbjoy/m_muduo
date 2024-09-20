#pragma once

namespace m_muduo {

    /**
     *
     * nocopyable 被继承会导致 派生类对象可以正常构造和析构, 但是派生类对象无法拷贝构造和赋值
     *
     */

    class nocopyable
    {
    public:
        nocopyable(const nocopyable &) = delete;
        void operator=(const nocopyable &) = delete;

    protected:
        nocopyable() = default;
        ~nocopyable() = default;
    };

}
