#ifndef ENDIAN_STREAM_READER_H
#define ENDIAN_STREAM_READER_H
#include <stdint.h>
#include <fstream>

class EndianStreamReader {
private:
    bool needSwap;

    void swapBytes(uint16_t * twoBytes) {
       unsigned char * tmp = (unsigned char *)twoBytes;
       unsigned int i;
       i = tmp[1];
       tmp[1] = tmp[0];
       tmp[0] = i; 
    }

    void swapBytes(uint32_t * fourBytes) {
        unsigned char * tmp = (unsigned char *)fourBytes;

        unsigned int i;

        // Swap the outside two.
        i = tmp[0];
        tmp[0] = tmp[3];
        tmp[3] = i;

        // Swap the inside two.
        i = tmp[1];
        tmp[1] = tmp[2];
        tmp[2] = i; 
    }

    void swapBytes(uint64_t * eightBytes) {
        unsigned char * tmp = (unsigned char *)eightBytes;

        unsigned int x;
        for (int i = 0; i < 4; ++i) {
            x = tmp[i];
            tmp[i] = tmp [7 - i];
            tmp[7 - i] = x;
        } 
    }

public:

    EndianStreamReader(bool streamLittleEndian) {
        // Check endianess of machine
        short int one = 1;
        char *byte = (char *) &one;
        int machineLittleEndian = byte[0]; 
        
        // We need to swap bytes if the endianess is different for the stream.
        needSwap = (machineLittleEndian != streamLittleEndian);
    }
    
    // Reads [count] shorts from the stream into a buffer.
    void readShort(std::ifstream &in, char * out, int count) {
        
        uint16_t * tmp = (uint16_t *) out;

        for (int i = 0; i < count; ++i) {
            in.read((char*)tmp + i, 2);
        
            if (needSwap)
                swapBytes(tmp+i);
        }

    }  

    // Reads [count] ints from the stream into a buffer.
    void readInt(std::ifstream &in, char * out, int count) {
        
        uint32_t * tmp = (uint32_t *) out;

        for (int i = 0; i < count; ++i) {
            in.read((char*)tmp + i, 4);
        
            if (needSwap)
                swapBytes(tmp+i);
        }

    }

    // Reads [count] longs from the stream into a buffer.
    void readLong(std::ifstream &in, char * out, int count) {
        
        uint64_t * tmp = (uint64_t *) out;

        for (int i = 0; i < count; ++i) {
            in.read((char*)tmp + i, 8);
        
            if (needSwap)
                swapBytes(tmp+i);
        }

    }
};
#endif
