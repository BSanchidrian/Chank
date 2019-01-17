#pragma once
// https://stackoverflow.com/questions/43602649/write-file-in-binary-format
#include <fstream>
#include <cstring>

namespace chank
{
	class BinaryOut : public std::ofstream
	{
	public:
		BinaryOut(const char* fname) :
			std::ofstream(fname, std::ios::binary)
		{}

		template<typename DataType>
		BinaryOut& operator << (const DataType& data)
		{
			this->write((char*)&data, sizeof(DataType));
			return *this;
		}

		template<typename DataType>
		BinaryOut& operator << (const DataType*& data)
		{
			this->write((char*)data, sizeof(DataType));
			return *this;
		}

		BinaryOut& operator << (const char* ptr)
		{
			auto len = strlen(ptr);
			this->write((char*)&len, 4);
			this->write(ptr, len);
			return *this;
		}
	};

	class BinaryIn : public std::ifstream
	{
	public:
		BinaryIn(const char* fname) :
			std::ifstream(fname, std::ios::binary)
		{}

		template<typename DataType>
		BinaryIn& operator >> (DataType& data)
		{
			this->read((char*)&data, sizeof(DataType));
			return *this;
		}

		BinaryIn& operator >> (char* ptr)
		{
			int len;
			this->read((char*)&len, 4);
			this->read(ptr, len);
			return *this;
		}
	};
}