#pragma once
#include <vector>

namespace chank
{
    class DiskBlock
    {
    public:
        DiskBlock();
        ~DiskBlock();

        std::vector<char>& GetBytes() const
        {
            auto temp = std::vector<char>();
            return temp;
        }

    private:
        
    };
}
