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

    // Store the current file pos
    int filePos = file.tellg();

    int typeSize = sizeOfType(out.type);
    int byteSize = out.count * typeSize;

    // If the actual value can fit in 4 bytes
    if ( byteSize < 5) {
    	// Then the pointer is the data. Seek back to the value
        file.seekg(-4, std::ios::cur);
    }
    // Otherwise we have to follow the pointer to get the actual value
    // from the file.
    else {
        file.seekg(valuePointer, std::ios::beg);
    }
	// Allocate enough dynamic memory for the value
	out.value = new char[byteSize];

	// Read the values into memory

	// Rationals have to be treated specially because they consist of two Long's
	if (out.type == RATIONAL || out.type == SRATIONAL) {
		typeSize = 4;
	}

	switch ( typeSize ) {
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

    return out;
} 

// Write an IFD Entry to a file. Takes a stream to write the entry to and an offset
// where values should be written if they don't fit in 4 bytes.
uint32_t IFD_Entry::writeToFile(std::ostream &file, uint32_t valuePointer) {

	file.write((char*)&tag, 2);
	file.write((char*)&type, 2);
	file.write((char*)&count, 4);

	size_t byteSize = sizeOfType(type) * count;
	if ( byteSize < 5 ) {
		file.write(value, byteSize);

		if (byteSize < 4)
			file.write("\0\0\0", 4 - byteSize);
	}
	else {
		file.write((char*)&valuePointer, 4);

		int lastPos = file.tellp();
		file.seekp(valuePointer, std::ios::beg);

		file.write(value, byteSize);

		file.seekp(lastPos, std::ios::beg);

		valuePointer += byteSize;
	}

	return valuePointer;
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

// Parse an IFD Rational into a double
double IFD_Entry::parseRational(uint64_t rational, bool sign) {
	double numerator, denominator;
	// TODO - Fix Rational bug, buried somewhere in here.
	//std::cout << "Rational: " << rational << std::endl;

	if (!sign) {
		//std::cout << "Numerator: " << (rational >> 32) << std::endl;
		//std::cout << "Denominator: " << (rational & 0xffff) << std::endl;
		numerator = static_cast<double>(rational >> 32);
		denominator = static_cast<double>(rational & 0xffff);
	}
	else {
		numerator = (double) ((int16_t) (rational >> 32));
		denominator = (double) ((int16_t)(rational & 0xffff));
	}


	return numerator / denominator;
}

// Resets the value of this entry
void IFD_Entry::setValue(void * input, size_t size, size_t count, Tiff_Value_Type type) {
	delete [] value;
	value = new char[size];
	memcpy(value, input, size);
	this->count = count;
	this->type = type;
}

// Print the values of this IFD_Entry
void IFD_Entry::printValues(size_t max_to_print) {
	for (size_t i = 0; i < count && i < max_to_print; ++i) {
		switch (type) {
			case BYTE:
				printf("0x%hhx", *(value + i));
				break;
			case ASCII:
				std::cout << *(value + i);
				break;
			case SBYTE:
				printf("%hhd", *(value + i));
				break;
			case UNDEFINED:
				printf("%hhx", *(value + i));
				break;
			case SHORT:
				printf("%hu", *((uint16_t *)value + i));
				break;
			case SSHORT:
				printf("%hd", *((int16_t *)value + i));
				break;
			case LONG:
				printf("%u", *((uint32_t *)value + i));
				break;
			case SLONG:
				printf("%d", *((int32_t *)value + i));
				break;
			case FLOAT:
				printf("%f", (const float)*((uint32_t *)value + i));
				break;
			case RATIONAL:
				printf("%lf", IFD_Entry::parseRational(*((uint64_t *)value + i), false));
				break;
			case SRATIONAL:
				printf("%lf", IFD_Entry::parseRational(*((uint64_t *)value + i), true));
				break;
			case DOUBLE:
				printf("%lf", (double) *((uint64_t *)value + i));
				break;
		}

		if (i < count - 1 && type != ASCII) {
			printf(" ");
		}

		if (i == max_to_print - 1) {
			printf("...");
		}
	}

	printf(">");
}

// Initialize the map for Tiff Tag names.
std::map<int, const char *> create_tag_map() {
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

// Initialize the map for Tiff Type names.
std::map<Tiff_Value_Type, const char *> create_type_map() {
    std::map<Tiff_Value_Type, const char *> m;
    m[BYTE] = "BYTE";
    m[ASCII] = "ASCII";
    m[SHORT] = "SHORT";
    m[LONG] = "LONG";
    m[RATIONAL] = "RATIONAL";
    m[SBYTE] = "SBYTE";
    m[UNDEFINED] = "UNDEFINED";
    m[SSHORT] = "SSHORT";
    m[SLONG] = "SLONG";
    m[SRATIONAL] = "SRATIONAL";
    m[FLOAT] = "FLOAT";
    m[DOUBLE] = "DOUBLE";
    return m;
}

const std::map<int, const char *> Tiff_Tag_Names = create_tag_map();
const std::map<Tiff_Value_Type, const char *> Tiff_Type_Names = create_type_map();
