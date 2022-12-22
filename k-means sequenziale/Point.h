//
// Created by jacopo manetti on 15/11/2022.
//

#ifndef K_MEANS_SEQUENZIALE_POINT_H
#define K_MEANS_SEQUENZIALE_POINT_H



class Point {

public:

    Point(double x_coord, double y_coord){
        this->x_coord = x_coord;
        this->y_coord = y_coord;
        id_cluster = 0;
    }

    Point(){
        x_coord = 0;
        y_coord = 0;
        id_cluster = 0;
    }

    double get_x_coord(){
        return this->x_coord;
    }

    double get_y_coord(){
        return this->y_coord;
    }

    int get_id_cluster(){
        return id_cluster;
    }

    void set_id_cluster(int id_cluster){
        this->id_cluster = id_cluster;
    }


private:
    double x_coord;
    double y_coord;
    int id_cluster;



};
