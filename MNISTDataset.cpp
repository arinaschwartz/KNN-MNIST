/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * A class to represent an in-memory MNIST dataset.
 *
 * See MNISTDataset.h for details on what each method does.
 *
 */
#include<fstream>
#include<iostream>
using namespace std;

#include "MNISTDataset.h"
#include "MNISTImageImpls.h"

MNISTFileException::MNISTFileException(const char* reason) throw():reason(reason)
{

}


const char* MNISTFileException::what() const throw()
{
	return reason;
}


MNISTDataset::MNISTDataset(istream &imageFile, istream &labelFile, string type)
{
	uint32 magic, numLabels;

	magic = readUInt32(imageFile);

	if(magic!=2051)
		throw MNISTFileException("Magic number in image file is not 2051");

	this->numImages = readUInt32(imageFile);
	this->numRows = readUInt32(imageFile);
	this->numCols = readUInt32(imageFile);

	magic = readUInt32(labelFile);
	if(magic!=2049)
		throw MNISTFileException("Magic number in label file is not 2049");

	numLabels = readUInt32(labelFile);

	if (numLabels != this->numImages)
		throw MNISTFileException("Number of images doesn't match the number of labels");

	imgs = new MNISTImage*[this->numImages];

	for(uint32 i=0; i<this->numImages; i++)
	{
		uint8 img[this->numCols*this->numRows];
		uint8 label;

		label = readUInt8(labelFile);
		readUInt8Array(imageFile, img, numCols*numRows);

		imgs[i] = createImage(img, label, type);
	}

}


MNISTDataset::~MNISTDataset()
{
	delete[] imgs;
}


uint32 MNISTDataset::getNumImages()
{
	return numImages;
}


const MNISTImage* MNISTDataset::getImage(uint32 i)
{
	return imgs[i];
}


MNISTImage* MNISTDataset::createImage(uint8 data[], uint8 label, string type)
{
	if(type == "full")
		return new FullArrayMNISTImage(data, this->numRows * this->numCols, label);
	else if(type == "downsample2")
		return new DownsampleMNISTImage(data, this->numRows * this->numCols, label, 2);
	else if(type == "downsample4")
		return new DownsampleMNISTImage(data, this->numRows * this->numCols, label, 4);
	else if(type == "downsample8")
		return new DownsampleMNISTImage(data, this->numRows * this->numCols, label, 8);
	else if(type == "scaled2")
		return new ScaledMNISTImage(data, this->numRows, this->numCols, label, 2);
	else if(type == "scaled4")
		return new ScaledMNISTImage(data, this->numRows, this->numCols, label, 4);
	else if(type == "scaled7")
		return new ScaledMNISTImage(data, this->numRows, this->numCols, label, 7);
	else if(type == "random")
		return new RandomMNISTImage(label);
	else if(type == "sum")
		return new SumMNISTImage(data, this->numRows * this->numCols, label);
	else
		throw MNISTFileException("Unknown MNIST type");
}


uint32 MNISTDataset::readUInt32(std::istream &is)
{
	char buf[4], *p;
	uint32 v = 0;

	is.read(buf, 4);

	p = ((char*) &v);

	p[0] = buf[3];
	p[1] = buf[2];
	p[2] = buf[1];
	p[3] = buf[0];

	return v;
}


uint8 MNISTDataset::readUInt8(std::istream &is)
{
	char buf;

	is.read(&buf, 1);

	return buf;
}


void MNISTDataset::readUInt8Array(std::istream &is, uint8 a[], uint32 n)
{
	is.read((char*) a, n);
}
