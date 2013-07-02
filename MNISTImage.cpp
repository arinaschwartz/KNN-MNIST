/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Abstract class to represent an MNIST image.
 * See MNISTImage.h for details on what each method does.
 *
 */

#include "MNISTImage.h"

MNISTImage::MNISTImage(uint8 label)
{
	this->label = label;
}

MNISTImage::~MNISTImage()
{
	// Does nothing
}

int MNISTImage::getLabel() const
{
	return label;
}
