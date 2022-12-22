//
// Created by manet on 04/12/2022.
//

#ifndef K_MEANS_PARALLELO_CLUSTER_H
#define K_MEANS_PARALLELO_CLUSTER_H


#include <queue>
#include "Point.h"
#include <omp.h>

class Cluster {
public:
    Cluster(double x_coord, double y_coord) {
        points_x_coord = 0;
        points_y_coord = 0;
        size = 0;
        this->x_coord = x_coord;
        this->y_coord = y_coord;
    }

    Cluster() {
        points_x_coord = 0;
        points_y_coord = 0;
        size = 0;
        this->x_coord = 0;
        this->y_coord = 0;
    }


    void add_point(Point point) {
#pragma omp atomic
        points_x_coord += point.get_x_coord();
#pragma omp atomic
        points_y_coord += point.get_y_coord();
#pragma omp atomic
        size++;

    }

    void free_point() {
        this->size = 0;
        this->points_x_coord = 0;
        this->points_y_coord = 0;
    }

    double get_x_coord() {
        return this->x_coord;
    }

    double get_y_coord() {
        return this->y_coord;
    }

    // boolean method to check if the centroid has changed and if so update it
    bool update_coords() {

        if (this->x_coord == points_x_coord / this->size && this->y_coord == points_y_coord / this->size) {
            return false;
        }

        this->x_coord = points_x_coord / this->size;
        this->y_coord = points_y_coord / this->size;

        return true;

    }

private:
    //centroid
    double x_coord;
    double y_coord;
    //Accumulate the Point coords here
    double points_x_coord;
    double points_y_coord;
    //Number of points inside this Cluster
    int size;

};


#endif //K_MEANS_PARALLELO_CLUSTER_H
