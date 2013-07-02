
#include<cstdlib>
using namespace std;
#include<iostream>
#include"MNISTImageImpls.h"
#include<math.h>
#include<vector>


RandomMNISTImage::RandomMNISTImage(uint8 label):
		MNISTImage(label)
{

}

double RandomMNISTImage::distance(const MNISTImage *img) const
{
	return ((double) (rand() % 714000)) / 100.0;
}


ArrayMNISTImage::ArrayMNISTImage(uint8 label):
		MNISTImage(label)
{
    this->data = NULL;
    this->size = 0;
}


double ArrayMNISTImage::distance(const MNISTImage *img) const
{
    const ArrayMNISTImage *arrayimg = dynamic_cast<const ArrayMNISTImage*>(img);
    double squared_distance = 0;
    double first_image_point;
    double second_image_point;
    double diff;

    for(uint32 i = 0; i < size; i++){
        first_image_point = this->data[i];
        second_image_point = arrayimg->data[i];
        diff = first_image_point - second_image_point;
        squared_distance += (diff*diff);
    }
	return sqrt(squared_distance);
}


FullArrayMNISTImage::FullArrayMNISTImage(uint8 data[], uint32 size, uint8 label):
		ArrayMNISTImage(label)
{
    
    this->data = new uint8[size];
    for(uint32 i = 0; i < size; i++){
        this->data[i] = data[i];
    }

    this->size = size;
    this->label = label;
}


DownsampleMNISTImage::DownsampleMNISTImage(uint8 data[], uint32 size, uint8 label, uint32 factor):
		ArrayMNISTImage(label)
{
    uint32 new_size = size/factor;
	this->data = new uint8[new_size];
    for(uint32 i = 0; i < size; i++){
        if(i % factor == 0){
            this->data[i/factor] = data[i];
        }
    }
    this->size = new_size;
    this->label = label;
}

ScaledMNISTImage::ScaledMNISTImage(uint8 data[], uint32 numRows, uint32 numCols, uint8 label, uint32 factor):
		ArrayMNISTImage(label)
{
    uint32 newNumRows = numRows/factor;
    uint32 newNumCols = numCols/factor;
    this->data = new uint8[newNumRows*newNumCols];
    for(uint32 i = 0; i < numRows; i++){
        for(uint32 j = 0; j < numCols; j++){
            this->data[(i/factor)*newNumRows + (j/factor)] +=
                        (data[(i * numRows) + j])/(factor*factor);
        }
    }
    this->size = newNumRows*newNumCols;
    this->label = label;
}



SumMNISTImage::SumMNISTImage(uint8 data[], uint32 size, uint8 label):
		MNISTImage(label)
{
	uint32 sum = 0;
    for(uint32 i = 0; i < size; i++){
        sum += data[i];
    }
    this->sum = sum;
}


double SumMNISTImage::distance(const MNISTImage *img) const
{
    const SumMNISTImage *arrayimg = dynamic_cast<const SumMNISTImage*>(img);
    double first_image_sum = this->sum;
    double second_image_sum = arrayimg->sum;
    double diff = first_image_sum - second_image_sum;
    double distance = sqrt((diff*diff));

	return distance;

}


