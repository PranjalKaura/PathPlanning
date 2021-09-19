#define WITHOUT_NUMPY 

#include "matplot_Github/matplotlibcpp.h"
#include "header.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>


namespace plt = matplotlibcpp;
using namespace std;

// get the point at delta distance from point_near, using point_rand(point_far)
point2D* getPoint(point2D* point_near, point2D* point_far, double delta) {
    if (point_near->x == point_far->x)
        return new point2D(point_near->x, point_near->y + delta);
    if (point_near->y == point_far->y)
        return new point2D(point_near->x + delta, point_near->y);

    double Theta = atan((point_far->y - point_near->y)/(point_far->x - point_near->x));
    double x_new = 0;
    double y_new = 0;
    if (point_far->x < point_near->x)
        x_new = point_near->x - abs(cos(Theta)*delta);
    else
        x_new = point_near->x + abs(cos(Theta)*delta);
    if (point_far->y < point_near->y)
        y_new = point_near->y - abs(sin(Theta)*delta);
    else
        y_new = point_near->y + abs(sin(Theta)*delta);
    
    return new point2D(x_new, y_new);
}

void addObstacles(Obstacle* obs) {
    point2D* centre1 = new point2D(4.5, 3);
    obs->addObstacle(2, centre1);
    point2D* centre2 = new point2D(2, 12);
    obs->addObstacle(2, centre2);
    point2D* centre3 = new point2D(15, 15);
    obs->addObstacle(3, centre3);
}

void plotCircle(int r, double x, double y) {
    std::vector<double> points_X;
    std::vector<double> points_Y;
    for (double angle=0; angle<=2*M_PI; angle+=0.01) {
        // cout << x + r*cos(angle) << " "  << y + r*sin(angle) << endl;
        points_X.push_back(x + r*cos(angle)); 
        points_Y.push_back(y + r*sin(angle));
    }
    plt::plot(points_X, points_Y);
}

void plotObstacles(Obstacle* obs) {
    for(int i = 0;i<Obstacle::radius.size();i++) {
        plotCircle(Obstacle::radius[i], Obstacle::centre[i]->x, Obstacle::centre[i]->y);
    }
}

bool connectGraphs(Graph* graph, point2D* point, Obstacle* obs, int threshold_Dist) {
    Node* node = graph->findNearest(point);
    if (node->point->Euc_Dist(point) <= threshold_Dist & (! obs->checkCollision(node->point, point))) {
        graph->setLastNode(node);
        return true;
    }
    return false;
}

int main() {
    // plt::plot({5,6,7,8});
    // plotCircle(1, 1, 1);
    
    int xBound = 30;
    int yBound = 30;
    double delta = 1;

    point2D start(0, 0);
    point2D goal(20, 20);
    Node startNode(&start);
    Node goalNode(&goal);


    Obstacle obs;
    addObstacles(&obs);
    plotObstacles(&obs);

    int numSamples = 250;
    int curSamples = 0;

    int threshold_Dist = 1;

    Graph start_g(&startNode);
    Graph goal_g(&goalNode);

    int curGraph = 0;

    Obstacle::verbose = 0;

    while(curSamples < numSamples) {
        int x = rand()%xBound;
        int y = rand()%yBound;
        point2D pointRand(x, y);
        // cout << "RANDOM POINT: " << flush ;
        // pointRand.disp();
        Node* point_near;
        if (curGraph == 0) {
            point_near = start_g.findNearest(&pointRand);
        }
        else {
            point_near = goal_g.findNearest(&pointRand);
        }

        point2D* point_new = getPoint(point_near->point, &pointRand, delta);

        if(!obs.checkCollision(point_near->point, point_new)) {
            if (curGraph == 0) {
                Node* node = start_g.addNode(point_new);
                // cout << "POINT ADDED START: " << flush ;
                // point_new->disp();
                if (connectGraphs(&goal_g, point_new, &obs, threshold_Dist)){
                    start_g.setLastNode(node);
                    cout << "-------SUCCESS-----" << endl;
                    break;
                }
            }
            else {
                Node* node = goal_g.addNode(point_new);
                // cout << "POINT ADDED GOAL: " << flush;
                // point_new->disp();
                if (connectGraphs(&start_g, point_new, &obs, threshold_Dist)){
                    goal_g.setLastNode(node);
                    cout << "-------SUCCESS-----" << endl;
                    break;
                }
            }
        }

        curSamples+=1;
        curGraph = 1 - curGraph;


    }

    auto [startPath_x, startPath_y] = start_g.retracePath();
    auto [goalPath_x, goalPath_y] = goal_g.retracePath();

    plt::plot(startPath_x, startPath_y);
    plt::plot(goalPath_x, goalPath_y);

    // start_g.traversal(start_g.rootNode);
    plt::show();

}




