#include<cstdlib>
using namespace std;

#include "MNISTDataset.h"
#include "knn.h"
#include<utility>
#include<queue>

typedef pair<double, uint8> distLabel;
typedef pair<uint8, uint8> labelCounter;

uint32 KNN(MNISTDataset &trainSet, MNISTDataset &testSet, uint32 k, uint32 max, bool verbose)
{    
    uint32 training_length = trainSet.getNumImages();
    const MNISTImage* test_image;
    const MNISTImage* train_image;
    uint8 classifications[max];
    uint32 numCorrect = 0;

    
    for(uint32 i = 0; i < max; i++){
        test_image = testSet.getImage(i);
        priority_queue<distLabel, vector<distLabel>, greater<distLabel> > imgQueue;
        for(uint32 j = 0; j < training_length; j++){
            train_image = trainSet.getImage(j);
            double current_distance = (*test_image).distance(train_image);
            uint8 current_label = (*train_image).getLabel();
            distLabel current_image;
            current_image.first = current_distance;
            current_image.second = current_label;
            imgQueue.push(current_image);
        }
        //Counts label frequency, stores in array by index
        uint32 labelFreq[10];
        for(uint32 iter = 0; iter < k; iter++){
            distLabel neighbor = imgQueue.top();
            labelFreq[neighbor.second] += 1;
            imgQueue.pop();
        }
        uint8 prevailing_label = 0;
        uint8 highest_frequency = 0;
        //Picks the most frequent label
        for(uint8 check_label = 0; check_label < 10; check_label++){
            if(labelFreq[check_label] > highest_frequency){
                prevailing_label = check_label;
            }
            labelFreq[check_label] = 0;
        }
            
        classifications[i] = prevailing_label;
    }

    for(uint32 i = 0; i < max; i++){
        
        if(classifications[i] == (*testSet.getImage(i)).getLabel()){
            numCorrect++;
        }
    }

    return numCorrect;
}

