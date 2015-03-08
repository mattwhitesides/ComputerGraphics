#ifndef SCANLINEFILL_H
#define SCANLINEFILL_H

#include <QVector>
#include <GLWidget.h>
#include <stdlib.h>
#include <DrawingAlgorithms.h>

// (y_max-vertex, x_min-vertex, delta_x, delta_y, -> or NULL)

struct Edge {
    int yMax;
    int xAtYMin;
    float xIncrement;
    Edge* next;
};

struct AET {
    int yMax;
    float x;
    float xIncrement;
    AET* next;
};

class ScanlineFill
{

private:
    int offset;
    int yMax;

public:
    Edge** bucket;
    int bucketSize;

    ScanlineFill();
    ScanlineFill(int yMin, int yMax, int offset);
    ScanlineFill(Coord* edgeArray, int size);
    ~ScanlineFill();

    //Initializes memory for the SET bucket based on max and min edges
    void initBucket(int yMin, int yMax);

    void printBucketContents();

    //Create an edge
    Edge* insertNewEdge(Coord vert1, Coord vert2);

    AET* insertAET(AET* list, int yMax, int x, float xIncrement);
    AET* removeNodeAET(AET* curr, int yMax);
    AET* insertSortedIntoActive(AET* list, Edge* set);
    AET* sortActive(AET* list);
    void freeAET(AET* list);
    void printActive(AET* list);

    void scanLineFillAlgorithm();
    void fillIntersection(AET* list, int y);
    void updateActiveX(AET* list);
};

#endif // SCANLINEFILL_H
