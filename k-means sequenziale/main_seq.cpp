#include <iostream>
#include <chrono>
#include "math.h"
#include "Point.h"
#include "Cluster.h"
#include <omp.h>
#include <fstream>

using namespace std;
using namespace std::chrono;

double max_range = 100000;
int num_point;
int num_cluster;
int seed = 30;

vector<Point> initializePoint(int num_point);
vector<Cluster> initializeCluster(int num_cluster);
double euclideanDistance (Point point, Cluster cluster);
void calculateDistance (vector<Point> &points, vector<Cluster> &clusters);
bool updateClusters(vector<Cluster> &clusters);
void drawPlot(vector<Point> points);



int main() {

    srand(seed);

    printf("Enter the number of points to generate:");
    cin>>num_point;

    printf("Enter the number of centroids to generate:");
    cin>>num_cluster;

    printf("Number of points: %d\n", num_point);
    printf("Number of cluster: %d\n", num_cluster);

    double time1 = omp_get_wtime(); //start cronometer

    vector<Point> points = initializePoint(num_point);

    vector<Cluster> clusters = initializeCluster(num_cluster);

    double time2 = omp_get_wtime();
    printf("Points and Cluster are generated in %f seconds\n", time2-time1 );



    bool conv = true;

    while (conv){

        calculateDistance(points,clusters);
        conv = updateClusters(clusters);
    }

    double time3 = omp_get_wtime();
    printf("Sequential k-means has taken %f seconds\n", time3-time2);



    printf("Drawing the chart...\n");
    drawPlot(points);


    return 0;
}


vector<Point> initializePoint(int num_point){

    vector<Point> points(num_point);
    Point *ptr;
    ptr=&points[0];

    for (int i = 0; i < num_point; ++i) {
        Point *point= new Point(rand() % (int)max_range,rand() % (int)max_range);
        ptr[i] = *point;

    }

    return points;
}


vector<Cluster> initializeCluster(int num_cluster){

    vector<Cluster> clusters(num_cluster);
    Cluster *ptr;
    ptr=&clusters[0];

    for (int i = 0; i < num_cluster; ++i) {
        Cluster *cluster= new Cluster(rand() % (int)max_range, rand() % (int)max_range);
        ptr[i] = *cluster;


    }

    return clusters;
}

double euclideanDistance (Point point, Cluster cluster){

    double distance = sqrt((pow(point.get_x_coord() - cluster.get_x_coord(),2))+
                           (pow(point.get_y_coord() - cluster.get_y_coord(),2)));

    return distance;
}

void calculateDistance (vector<Point> &points, vector<Cluster> &clusters){

    double min_distance;
    int index;

    for (int i = 0; i < points.size() ; ++i) {

        min_distance = euclideanDistance(points[i],clusters[0]);
        index = 0;

        for (int j = 0; j < clusters.size(); ++j) {

            double distance = euclideanDistance(points[i], clusters[j]);

                    if (distance < min_distance) {

                        min_distance=distance;
                        index = j;
                    }
        }

        points[i].set_id_cluster(index);
        clusters[index].add_point(points[i]);
    }

}

//update the centroid of clusters
bool updateClusters(vector<Cluster> &clusters){

    bool conv = false;



    for(int i = 0; i < clusters.size(); i++){

        conv = clusters[i].update_coords();
        clusters[i].free_point();

    }

    return conv;
}

void drawPlot(vector<Point> points){

    ofstream outfile("data.txt");

    for(int i = 0; i < points.size(); i++){

        Point point = points[i];
        outfile << point.get_x_coord() << " " << point.get_y_coord() << " " << point.get_id_cluster() << std::endl;

    }

    outfile.close();
    system("gnuplot -p -e \"plot 'data.txt' using 1:2:3 with points palette notitle\"");
    remove("data.txt");

}