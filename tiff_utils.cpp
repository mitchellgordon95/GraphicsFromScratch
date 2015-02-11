#include "tiff_utils.h"
#include <stdint.h>
#include <string.h>
#include <iostream>
#include "endian_stream_reader.h"

// Returns size of TIFF Type in bytes
int sizeOfType(Tiff_Value_Type type) {

    switch(type) {
        case BYTE:
        case ASCII:
        case SBYTE:
        case UNDEFINED:
            return 1;
        case SHORT:
        case SSHORT:
            return 2;
        case LONG:
        case SLONG:
        case FLOAT:
            return 4;
        case RATIONAL:
        case SRATIONAL:
        case DOUBLE:
            return 8; 
        default:
            return 0;
    }

}

// Read an IFD Entry from a file.
IFD_Entry IFD_Entry::readFromFile(std::ifstream &file, EndianStreamReader reader) {
    IFD_Entry out;
    reader.readShort(file, (char *) &out.tag, 1);

    uint16_t value_type;
    reader.readShort(file, (char *) &value_type, 1);
    out.type = (Tiff_Value_Type) value_type;

    reader.readInt(file, (char *) &out.count, 1);

    int valuePointer;
    reader.readInt(file, (char * ) &valuePointer, 1);

    int byteSize = out.count * sizeOfType(out.type);
    // If the actual value can fit in 4 bytes
    if ( byteSize < 5) {
        // Then the pointer is the data.
        out.value = new char[byteSize];
        
        if ( sizeOfType( out.type ) == 2 )
           *((uint16_t *)out.value) = (uint16_t) valuePointer;
        if ( sizeOfType( out.type ) == 4 )
           *((uint32_t *)out.value) = (uint32_t) valuePointer;
    }
    // Otherwise we have to follow the pointer to get the actual value
    // from the file.
    else {
        // Store the current file pos
        int filePos = file.tellg();

        // Go to the location of the value
        file.seekg(valuePointer, std::ios::beg);

        // Allocate enough dynamic memory for the value 
        out.value = new char[byteSize];
        
        // Read the values into memory
        switch ( sizeOfType(out.type) ) {
            case 1:
                file.read (out.value, byteSize);
                break;
            case 2:
                reader.readShort(file, out.value, byteSize / 2);
                break;
            case 4:
                reader.readInt(file, out.value, byteSize / 4);
                break; 
            case 8:
                reader.readLong(file, out.value, byteSize / 8);
                break;
        }
        
        // Seek back to where we were before.
        file.seekg(filePos, std::ios::beg);
    }

    return out;
} 

// Copy Constructor
IFD_Entry::IFD_Entry(const IFD_Entry &other): tag(other.tag), type(other.type), count(other.count) {
    // Make a dynamic copy of value.
    int byteSize = count * sizeOfType( type );
    value = new char[byteSize];
    
    memcpy(value, other.value, byteSize); 
}

// Destructor
IFD_Entry::~IFD_Entry() {
    delete [] value;
}

// Initialize the map for Tiff Tag names.
std::map<int, const char *> create_map() {
    std::map<int, const char *> m;
    m[254] = "NewSubfileType";
    m[255] = "SubfileType";
    m[256] = "ImageWidth";
    m[257] = "ImageLength";
    m[258] = "BitsPerSample";
    m[259] = "Compression";
    m[262] = "PhotometricInterpretation";
    m[263] = "Threshholding";
    m[264] = "CellWidth";
    m[265] = "CellLength";
    m[266] = "FillOrder";
    m[269] = "DocumentName";
    m[270] = "ImageDescription";
    m[271] = "Make";
    m[272] = "Model";
    m[273] = "StripOffsets";
    m[274] = "Orientation";
    m[277] = "SamplesPerPixel";
    m[278] = "RowsPerStrip";
    m[279] = "StripByteCounts";
    m[280] = "MinSampleValue";
    m[281] = "MaxSampleValue";
    m[282] = "XResolution";
    m[283] = "YResolution";
    m[284] = "PlanarConfiguration";
    m[285] = "PageName";
    m[286] = "XPosition";
    m[287] = "YPosition";
    m[288] = "FreeOffsets";
    m[289] = "FreeByteCounts";
    m[290] = "GrayResponseUnit";
    m[291] = "GrayResponseCurve";
    m[292] = "T4Options";
    m[293] = "T6Options";
    m[296] = "ResolutionUnit";
    m[297] = "PageNumber";
    m[301] = "TransferFunction";
    m[305] = "Software";
    m[306] = "DateTime";
    m[315] = "Artist";
    m[316] = "HostComputer";
    m[317] = "Predictor";
    m[318] = "WhitePoint";
    m[319] = "PrimaryChromaticities";
    m[320] = "ColorMap";
    m[321] = "HalftoneHints";
    m[322] = "TileWidth";
    m[323] = "TileLength";
    m[324] = "TileOffsets";
    m[325] = "TileByteCounts";
    m[332] = "InkSet";
    m[333] = "InkNames";
    m[334] = "NumberOfInks";
    m[336] = "DotRange";
    m[337] = "TargetPrinter";
    m[338] = "ExtraSamples";
    m[339] = "SampleFormat";
    m[340] = "SMinSampleValue";
    m[341] = "SMaxSampleValue";
    m[342] = "TransferRange";
    m[512] = "JPEGProc";
    m[513] = "JPEGInterchangeFormat";
    m[514] = "JPEGInterchangeFormatLngth";
    m[515] = "JPEGRestartInterval";
    m[517] = "PEGLosslessPredictors";
    m[518] = "JPEGPointTransforms";
    m[519] = "JPEGQTables";
    m[520] = "JPEGDCTables";
    m[521] = "JPEGACTables";
    m[529] = "YCbCrCoefficients";
    m[530] = "YCbCrSubSampling";
    m[531] = "YCbCrPositioning";
    m[532] = "ReferenceBlackWhite";
    m[33432] = "Copyright";
    return m;
}

const std::map<int, const char *> Tiff_Tag_Names = create_map();

