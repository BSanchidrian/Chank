#pragma once
#include "DiskBlock.h"
#include <vector>

namespace chank
{
    class DiskBlock;

    class Disk
    {
    public:
        Disk(const int id, const int byteSize);

        ~Disk();

        void WriteBlock(const DiskBlock& diskBlock);

        void Format(const int byteSize);

        void Save() const;

        // GETTERS | SETTERS
        int GetNumBlocks() const;

    private:
        int id;
        int byteSize;
        std::vector<char> buffer;
    };
}
