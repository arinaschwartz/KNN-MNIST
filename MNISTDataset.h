/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * A class to represent an in-memory MNIST dataset.
 *
 */
#ifndef MNISTDATASET_H_
#define MNISTDATASET_H_

#include<iostream>
#include<exception>
#include<string>

#include "MNISTImage.h"

// Exception class to be thrown whenever there is
// an error in the MNIST files.
class MNISTFileException: public std::exception
{
	// Error description
	const char *reason;

public:
	// Constructor
	MNISTFileException(const char* reason) throw();
	// Returns the reason for the error
	const char* what() const throw();
};

// Represents an MNIST dataset
class MNISTDataset
{
	// Array of pointers to MNISTImage objects.
	MNISTImage **imgs;
	// Number of images in the dataset
	uint32 numImages;
	// Number of rows and columns in each image
	uint32 numRows, numCols;

public:
	// Constructor
	//
	// Parameters:
	//  -imageFile: A stream containing the image file
	//  -labelFile: A stream containing the label file
	//  -type: The internal representation to use when creating the
	//         MNISTImage objects. The values are the same as the valid
	//         values of the -t parameter (see main.cpp)
	MNISTDataset(std::istream &imageFile, std::istream &labelFile, std::string type);

	// Destructor
	~MNISTDataset();

	// Getter for numImages
	uint32 getNumImages();

	// Returns a const pointer to the image at index i
	const MNISTImage* getImage(uint32 i);


private:
	// Creates an MNISTImage object (the type is determined by the "type" parameter)
	//
	// Parameters:
	// - data: An array of bytes containing the MNIST image, exactly as
	//         stored in the MNIST file.
	// - label: The image's label
	// - type: The type of MNISTImage to create
	MNISTImage* createImage(uint8 data[], uint8 label, std::string type);

	// Reads a big-endian 32-bit unsigned integer from a stream,
	// and converts it to a little-endian integer.
	uint32 readUInt32(std::istream &is);

	// Reads an 8-bit unsigned integer from a stream
	uint8 readUInt8(std::istream &is);

	// Reads a sequence of bytes from a stream and stores them in an array.
	void readUInt8Array(std::istream &is, uint8 a[], uint32 n);
};


#endif /* MNISTDATASET_H_ */
