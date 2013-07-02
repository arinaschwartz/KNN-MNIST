/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Header file for the KNN function.
 *
 */

#ifndef KNN_H_
#define KNN_H_

// This function takes the training set and the testing set, and runs KNN with k neighbours,
// using the first max images in the testing set (if max is 0, then all the images are used).
//
// The function should *not* print anything to the console, unless verbose is set to true.
//
// The function returns the number of images in the testing set that have been correctly labeled.
uint32 KNN(MNISTDataset &trainSet, MNISTDataset &testSet, uint32 k, uint32 max, bool verbose);


#endif /* KNN_H_ */
