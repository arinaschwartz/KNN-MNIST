/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Abstract class to represent an MNIST image
 *
 */

#ifndef MNISTIMAGE_H_
#define MNISTIMAGE_H_

// The MNIST files use two types of integers: unsigned 32-bit integers
// and unsigned bytes. For convenience, we typedef them.
typedef unsigned int uint32;
typedef unsigned char uint8;

class MNISTImage
{
protected:
	// The label for the image, as specified in the MNIST files
	uint8 label;

public:
	// Constructor
	// Notice that, since there are many possible representations,
	// including those that reduce the image to a single integer,
	// the only information that is common to all possible derived
	// classes is the label.
	MNISTImage(uint8 label);

	// Destructor
	virtual ~MNISTImage();

	// Abstract method that computes the distance to another image
	virtual double distance(const MNISTImage *img) const = 0;

	// Getter for the label
	int getLabel() const;
};

#endif /* MNISTIMAGE_H_ */
