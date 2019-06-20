#include "Disk.h"
#include "BinaryUtils.h"
#include <sstream>
#include <string>

#define BLOCK_SIZE 1024 // 1kb

using chank::DiskBlock;
using chank::Disk;

Disk::Disk(const int id, const int byteSize)
{
    this->id = id;
    this->byteSize = byteSize;
    this->buffer.reserve(byteSize);
}

Disk::~Disk()
{
}

int Disk::WriteBlock(const char* bytes, const int size)
{
    if (this->buffer.size() + size < this->buffer.capacity())
    {
        auto currentBlock = this->buffer.size() / BLOCK_SIZE;
        this->buffer.insert(this->buffer.begin() + currentBlock, bytes);
        this->buffer.emplace_back(bytes);

    }
    return -1;
}

void Disk::Format(const int byteSize)
{
    this->buffer.clear();
    this->buffer.reserve(byteSize);
}

void Disk::Save() const
{
    std::ostringstream s;
    s << "disk" << this->id << ".dat";

    chank::BinaryOut file(s.str().c_str());
    file << this->buffer;

    file.close();
}

int Disk::GetNumBlocks() const
{
    return this->byteSize / BLOCK_SIZE;
}
