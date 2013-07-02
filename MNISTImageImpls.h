/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Derived classes of MNISTImage.
 *
 */


#ifndef MNISTIMAGEIMPLS_H_
#define MNISTIMAGEIMPLS_H_

#include "MNISTImage.h"


// The ArrayMNISTImage class is the parent class for all the classes
// that store an MNIST image as an array of bytes.
// It provides an implementation of the distance function, computing
// the Euclidean distance between the arrays of two images, but
// the actual construction of the array is left to the derived classes
// (e.g., because some implementations may not store the full image,
// instead performing some subsampling).
class ArrayMNISTImage : public MNISTImage
{
protected:
	// The array of bytes
	uint8 *data;
	// The size of the array
	uint32 size;

public:
	// Constructor
	ArrayMNISTImage(uint8 label);

	// Computes the distance between this object and the parameter img.
	double distance(const MNISTImage *img) const;
};

// The FullArrayMNISTImage class is a child class of ArrayMNISTImage,
// and stores the entire image as a flat array.
class FullArrayMNISTImage : public ArrayMNISTImage
{
public:
	// Constructor
	// - data: An array of bytes containing the MNIST image, exactly as
	//         stored in the MNIST file.
	// - size: The size of the array
	// - label: The image's label
	FullArrayMNISTImage(uint8 data[], uint32 size, uint8 label);
};

// The DownsampleMNISTImage class is a child class of ArrayMNISTImage,
// and stores a downsampled version of the image. This means that,
// instead of storing the full array of bytes as specified in the MNIST file,
// this class will only store a portion of those bytes. This portions
// is determined by the downsampling factor. If the factor is 2, it means
// only the bytes at indices divisible by 2 will be stored. If the factor is 4,
// only the bytes at indices divisible by 4 will be stored. etc.
//
// So, if the array of bytes is { 10, 20, 30, 40, 50, 60, 70, 80 } and the
// downsampling factor is 2, then the "size" attribute of the object should
// be set to 4, and the following array should be stored: { 10, 30, 50, 70 }
class DownsampleMNISTImage : public ArrayMNISTImage
{
public:
	// Constructor
	// - data: An array of bytes containing the MNIST image, exactly as
	//         stored in the MNIST file.
	// - size: The size of the array
	// - label: The image's label
	// - factor: The downsampling factor.
	DownsampleMNISTImage(uint8 data[], uint32 size, uint8 label, uint32 factor);
};

// The ScaledMNISTImage class is a child class of ArrayMNISTImage,
// and stores a scaled version of the image. This is similar to what
// DownsampleMNISTImage does, except it is a bit smarter about reducing
// the size of the array.
//
// To scale the image, we will use a scaling factor. If we are given a
// scaling factor of 4, that means that we will divide the image into
// 4x4 squares, and reduce each square into a single pixel. So, a 28x28 pixel
// image would become a 7x7 image.
//
// To determine the value of the new pixel, we simply take the average of
// all the pixels in the n*n square that are being reduced into that pixel.
class ScaledMNISTImage : public ArrayMNISTImage
{
public:
	// Constructor
	// - data: An array of bytes containing the MNIST image, exactly as
	//         stored in the MNIST file.
	// - numRows: The number of rows in the image.
	// - numCols: The number of columns in the image.
	// - label: The image's label
	ScaledMNISTImage(uint8 data[], uint32 numRows, uint32 numCols, uint8 label, uint32 factor);
};


// The SumMNISTImage class is a child class of MNISTImage,
// which reduces the MNIST image into a single scalar: the sum
// of the values of all the pixels.
class SumMNISTImage : public MNISTImage
{
	// Sum of the pixels
	uint32 sum;

public:
	// Constructor
	// - data: An array of bytes containing the MNIST image, exactly as
	//         stored in the MNIST file.
	// - size: The size of the array
	// - label: The image's label
	SumMNISTImage(uint8 data[], uint32 size, uint8 label);

	// Computes the distance between this object and the parameter img.
	double distance(const MNISTImage *img) const;
};

// The RandomMNISTImage class is a child class of MNISTImage
// that doesn't actually store the image in any form. When
// computing the distance between two RandomMNISTImage objects,
// a random value is returned.
class RandomMNISTImage : public MNISTImage
{
public:
	// Constructor
	// - label: The image's label
	RandomMNISTImage(uint8 label);

	// Returns a random distance.
	double distance(const MNISTImage *img) const;
};


#endif /* MNISTIMAGEIMPLS_H_ */
