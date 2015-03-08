#include "ScanlineFill.h"

ScanlineFill::ScanlineFill() {
    bucket = NULL;
    offset = 0;
    bucketSize = 0;
    yMax = 0;
}

ScanlineFill::ScanlineFill(int yMin, int yMax, int offset) {
    ScanlineFill();
    bucketSize = yMax - yMin - offset + 1;
    ScanlineFill::yMax = yMax;
    bucket = new Edge*[bucketSize];
    for (int i = 0; i < bucketSize; ++i) bucket[i] = NULL;
    ScanlineFill::offset = offset;
    //printf("\nInitialized bucket with a size of %d and offset: %d\n\n", bucketSize, ScanlineFill::offset);
}

ScanlineFill::ScanlineFill(Coord* edgeArray, int size) {
    ScanlineFill();
    if (edgeArray == NULL) {
        printf("Empty edge array\n");
        return;
    }
//    if (size % 2 != 0) {
//        printf("Incorrect number of coordnates to make edges.\n");
//        return;
//    }
    int yMax = edgeArray[0].y;
    int yMin = edgeArray[0].y;
    int j = 0;

    for (int i = 0; i < size; ++i) {
        if (edgeArray[i].y < yMin)
            yMin = edgeArray[i].y;
        if (edgeArray[i].y > yMax)
            yMax = edgeArray[i].y;
    }

    ScanlineFill::yMax = yMax;
    printf("yMax: %d, yMin: %d\n", yMax, yMin);
    bucketSize = yMax - yMin + 1;
    bucket = new Edge*[bucketSize];
    for (int i = 0; i < bucketSize; ++i) bucket[i] = NULL;
    ScanlineFill::offset = yMin;
    printf("\nInitialized bucket with a size of %d and offset: %d\n\n", bucketSize, ScanlineFill::offset);

    while (j < size) {
        insertNewEdge(edgeArray[j],edgeArray[j + 1]);
        //printf("[%d]: (%d,%d),(%d,%d)\n",j,edgeArray[j].x,edgeArray[j].y,edgeArray[j + 1].x,edgeArray[j + 1].y);
        j++;
    }  
}

ScanlineFill::~ScanlineFill() {}

void ScanlineFill::initBucket(int yMin, int yMax) {
    bucket = new Edge*[yMax - yMin];
}

Edge* ScanlineFill::insertNewEdge(Coord vert1, Coord vert2) {
    if (vert2.y == vert1.y) {
        printf("Skipping Horizontal Edge: (%d,%d),(%d,%d)\n", vert1.x, vert1.y, vert2.x, vert2.y);
        return NULL;
    }
    bool isVert2Greater = (vert2.y > vert1.y);
    int yMin = isVert2Greater ? vert1.y : vert2.y;
    int yMax = 0;
    int xAtYMin = 0;
    float slope = 0.0f;

    if (isVert2Greater) {
        yMax = vert2.y;
        xAtYMin = vert1.x;
    } else {
        yMax = vert1.y;
        xAtYMin = vert2.x;
    }

    if (vert1.y == vert2.y || vert1.x == vert2.x) slope = 0.0f;
    slope = 1/((float(vert2.y) - vert1.y) / (vert2.x - vert1.x));

    printf("Inserting into bucket at idx %d:\n\tyMax: %d\n\txAtYMin: %d\n\txIncrement: %f\n", yMin - offset, yMax, xAtYMin, slope);

    Edge* newEdge = new Edge;
    const int idx = yMin - offset;
    Edge* current = NULL;

    newEdge->yMax = yMax;
    newEdge->xAtYMin = xAtYMin;
    newEdge->xIncrement = slope;
    newEdge->next = NULL;

    if (bucket[idx] == NULL || bucket[idx]->xAtYMin > newEdge->xAtYMin) {
        newEdge->next = bucket[idx];
        bucket[idx] = newEdge;
    } else {
        current = bucket[idx];
        while (current->next != NULL && current->next->xAtYMin < newEdge->xAtYMin)
            current = current->next;
        newEdge->next = current->next;
        current->next = newEdge;
    }

    return newEdge;
}

void ScanlineFill::printBucketContents() {
    int j = 0;
    Edge* counter;
    for (int i = 0; i < bucketSize; ++i) {
        counter = bucket[i];
        j = 0;
        while (counter) {
            printf("Bucket at idx %d->%d:\n\tyMax: %d\n\txAtYMin: %d\n\txIncrement: %f\n", i, j, counter->yMax, counter->xAtYMin, counter->xIncrement);
            counter = counter->next;
            ++j;
        }
    }
}

AET* ScanlineFill::insertAET(AET* list, int yMax, int x, float xIncrement) {
    AET* head = new AET;
    head->yMax = yMax;
    head->x = x;
    head->xIncrement = xIncrement;
    head->next = list;
    return head;
}

void ScanlineFill::freeAET(AET* list) {
    AET* prev = NULL;
    while (list != NULL) {
        prev = list;
        list = list->next;
        delete prev;
    }
}

AET* ScanlineFill::removeNodeAET(AET* curr, int yMax) {
    if (curr == NULL)
      return NULL;

    if (curr->yMax == yMax) {
      AET* tempNextP;

      tempNextP = curr->next;

      delete curr;

      return tempNextP;
    }

    curr->next = removeNodeAET(curr->next, yMax);

    return curr;
}

AET* ScanlineFill::insertSortedIntoActive(AET* list, Edge* set) {
    if (!set) return list;
    Edge* current = set;
    while (current) {
        list = insertAET(list,current->yMax,current->xAtYMin,current->xIncrement);
        current = current->next;
    }
    return list;
}

AET* ScanlineFill::sortActive(AET* list) {

    AET* head = list;
    AET* insert = list;
    int tempYMax = 0;
    float tempX = 0.0f;
    float tempXInc = 0.0f;

    //printActive(list);

    list = list->next;

    while (list) {
        insert = head;
        while (insert != list) {
            if (insert->x > list->x) {
                tempX = list->x;
                tempYMax = list->yMax;
                tempXInc = list->xIncrement;
                list->x = insert->x;
                list->xIncrement = insert->xIncrement;
                list->yMax = insert->yMax;
                insert->x = tempX;
                insert->yMax = tempYMax;
                insert->xIncrement = tempXInc;
            } else {
                insert = insert->next;
            }
        }
        list = list->next;
    }

    return head;
}

void ScanlineFill::printActive(AET* list) {
    printf("AET: \n");
    while (list) {
        printf("\tYmax: %d\n\tX: %f\n\t(1/m): %f\n", list->yMax, list->x, list->xIncrement);
        list = list->next;
    }
}

void ScanlineFill::fillIntersection(AET* list, int y) {
    AET* p1;
    AET* p2;

    p1 = list;
    p2 = list->next;
    while (p2) {
        if (p1 && p2) {
            glVertex2i(p1->x,y + offset);
            glVertex2i(p2->x,y + offset);
        }
        p2 = p2->next;
        p1 = p1->next;
    }
}

void ScanlineFill::updateActiveX(AET* list) {
    while (list) {
        list->x += list->xIncrement;
        list = list->next;
    }
}

void ScanlineFill::scanLineFillAlgorithm() {
    if (bucketSize == 0) {
        printf("Please Initialize a Bucket.\n");
        return;
    }

    int y = 0;
    AET* act = NULL;
    act = insertSortedIntoActive(act, bucket[0]);

    glBegin(GL_LINES);

    while(y < bucketSize) {
        fillIntersection(act,y);
        act = removeNodeAET(act, y);
        act = insertSortedIntoActive(act, bucket[y]);
        act = sortActive(act);
        updateActiveX(act);
        //printf("y: %d\n",y);
        //printActive(act);
        ++y;
    }

    glEnd();
}
