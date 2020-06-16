//
// Created by ivoako-5 on 5/14/18.
//

#ifndef GSCEPT_LAB_ENV_COLLISIONHANDLER_H
#define GSCEPT_LAB_ENV_COLLISIONHANDLER_H

#include <set>
#include "Cube.h"

struct Point
{
    Point(){};
    Point(float b, int i, bool s)
    {
        p = b;
        index = i;
        start = s;
    };
    bool operator<(const Point &rhs) const
    {
        if(this->p == rhs.p)
        {
            return(this->start);
        }
        return(this->p < rhs.p);
    };

    float p;
    int index = -1;
    bool start = false;
    int vectorIndex = -1;
    Point* pair;
};

struct SupportPoint
{
    SupportPoint()
    {
        v = Vector4D();
        supA = Vector4D();
        supB = Vector4D();
    };

    bool operator==(SupportPoint &rhs)
    {
        return (this->v == rhs.v);
    }

    Vector4D v; //Minkowski sum
    Vector4D supA;
    Vector4D supB;
};

struct Edge
{
    Edge(){};
    Edge(SupportPoint p1, SupportPoint p2)
    {
        points[0] = p1;
        points[1] = p2;
    };

    SupportPoint points[2];
};

struct Triangle
{
    Triangle(){};
    Triangle(SupportPoint a, SupportPoint b, SupportPoint c)
    {
        points[0] = a;
        points[1] = b;
        points[2] = c;

        Vector4D AB = b.v - a.v;
        Vector4D AC = c.v - a.v;
        normal = ((b.v - a.v) * (c.v - a.v)).normalize();
    };

    SupportPoint points[3];
    Vector4D normal;
};

struct CollisionInfo
{
    CollisionInfo()
    {
        normal = Vector4D();
        depth = 0;
    };
    Vector4D normal;
    Vector4D point;
    float depth;
};

class CollisionHandler
{
public:
    CollisionHandler();
    ~CollisionHandler();

    bool GJK(Cube &cube1, Cube &cube2);
    SupportPoint supportFunc(Cube &mesh1, Cube &mesh2, Vector4D dir);
    std::set<std::pair<int,int>>linesweep();
    void createLines(std::vector<Cube*>& objects, int axis);
    std::set<std::pair<int,int>> checkCollisions(std::vector<Cube*>& objects);
    bool containsOrigin(std::vector<SupportPoint>& s, Vector4D &dir);
    CollisionInfo EPA(Cube &cube1, Cube &cube2);
    void addEdge(SupportPoint &a, SupportPoint &b, std::vector<Edge> &edges);
    Vector4D calcPoint(Vector4D &p, Vector4D &a, Vector4D &b, Vector4D &c);
    void calcImpulse(Cube &cube1, Cube &cube2, CollisionInfo info, float dt, int integrator);

    std::multiset<Point> lines;
    std::vector<SupportPoint> simplex;

};


#endif //GSCEPT_LAB_ENV_COLLISIONHANDLER_H
