/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * KNN with the MNIST Dataset
 *
 * This file is the entry point into the program. When run, the program
 * runs KNN on the entire testing set.
 *
 * It accepts the following command-line parameters:
 *
 *  -d DIRECTORY: The directory where the MNIST files are located
 *                (t10k-images-idx3-ubyte, t10k-labels-idx1-ubyte,
 *                 train-images-idx3-ubyte, and train-labels-idx1-ubyte).
 *
 *  -t TYPE: The distance strategy to use. Valid values are:
 *    full: Euclidean distance between all 784 coordinates.
 *    downsample2: Downsampling by a factor of 2
 *    downsample4: Downsampling by a factor of 4.
 *    downsample8: Downsampling by a factor of 8.
 *    scale2: Scaling the image by a factor of 2
 *    scale4: Scaling the image by a factor of 4.
 *    scale7: Scaling the image by a factor of 7.
 *    sum: Distance between the sums of the coordinates.
 *    random: Random distances
 *
 *  -k K: The value of K to use when running KNN.
 *
 *  -n N: Use only the first N images from the testing set.
 *
 *  -v: Verbose mode. Prints out more messages to the console.
 *
 */

#include<getopt.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cfloat>
using namespace std;

#include "MNISTDataset.h"
#include "knn.h"

const string USAGE = "-d DIRECTORY [-t TYPE] [-k K] [-n N] [-v]";

int main(int argc, char** argv)
{
	// For parsing command-line options
	int opt;
	// Should we be verbose?
	bool verbose = false;
	// Directory containing MNIST files
	string directory = "";
	// Distance strategy
	string type = "full";
	// K
	int k = 1;
	// Process only these many images in the testing set (0 = process all)
	int max = 0;
	// Number of images labelled correctly
	uint32 correct;

	// Parse command-line options
	while ((opt = getopt(argc, argv, "d:t:n:k:vh")) != -1)
		switch (opt)
		{
			case 'd':
				directory = optarg;
				break;
			case 't':
				type = optarg;
				break;
			case 'v':
				verbose = true;
				break;
			case 'k':
				k = atoi(optarg);
				break;
			case 'n':
				max = atoi(optarg);
				break;
			default:
				cerr << "Usage: " << argv[0] << " " << USAGE << endl;
				cerr << "ERROR: Unknown option -" << char(opt) << endl;
				exit(-1);
		}

	if(directory == "")
	{
		cerr << "Usage: " << argv[0] << " " << USAGE << endl;
		cerr << "ERROR: Must specify a directory with -d" << endl;
		exit(-1);
	}

	// Load files
	ifstream trainImageFile((directory + "/train-images-idx3-ubyte").c_str(), ios::in|ios::binary);
	ifstream trainLabelFile((directory + "/train-labels-idx1-ubyte").c_str(), ios::in|ios::binary);
	ifstream testImageFile((directory + "/t10k-images-idx3-ubyte").c_str(), ios::in|ios::binary);
	ifstream testLabelFile((directory + "/t10k-labels-idx1-ubyte").c_str(), ios::in|ios::binary);

	MNISTDataset *trainSet, *testSet;

	try
	{
		trainSet = new MNISTDataset(trainImageFile, trainLabelFile, type);
		testSet = new MNISTDataset(testImageFile, testLabelFile, type);
	} catch (MNISTFileException &e)
	{
		cerr << e.what() << endl;
		exit(-2);
	}

	if(max==0)
		max = testSet->getNumImages();

	// Run KNN
	correct = KNN(*trainSet, *testSet, k, max, verbose);

	// Print summary
	cout << type << " " << k << " " << max << " " << correct << " " << (max - correct) << " " << (float(max-correct)*100.0/max) << endl;

	// Clean up
	delete testSet;
	delete trainSet;

	trainImageFile.close();
	trainLabelFile.close();
	testImageFile.close();
	testLabelFile.close();
}
