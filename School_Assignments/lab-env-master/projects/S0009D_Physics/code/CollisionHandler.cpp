//
// Created by ivoako-5 on 5/14/18.
//

#include "CollisionHandler.h"

CollisionHandler::CollisionHandler()
{
    lines = std::multiset<Point>();
}

CollisionHandler::~CollisionHandler()
{
    lines.clear();
}

bool CollisionHandler::GJK(Cube &cube1, Cube &cube2)
{
    simplex.clear();
    //std::set<Vector4D>::iterator it;
    Vector4D dir(1,0,0);
    SupportPoint point = supportFunc(cube1, cube2, dir);
    simplex.push_back(point);
    dir = point.v * -1.0f;

    while(true)
    {
        SupportPoint end = supportFunc(cube1, cube1, dir);
        simplex.push_back(end);

        if(end.v.dot(dir) < 0)
        {
            return false;
        }
        else
        {
            if(containsOrigin(simplex, dir))
            {
                return true;
            }
        }
    }
}

bool CollisionHandler::containsOrigin(std::vector<SupportPoint> &s, Vector4D &dir)
{
    Vector4D A0;
    Vector4D AB;
    Vector4D AC;
    Vector4D AD;

    Vector4D ABperp;
    Vector4D ACperp;

    Vector4D ABCperp;
    Vector4D ACDperp;
    Vector4D ADBperp;

    int simplexSize = s.size();
    if(simplexSize == 2)
    {
        dir = (((s[0].v - s[1].v) * (s[1].v * -1)) * (s[0].v - s[1].v));
    }
    else if(simplexSize == 3)
    {
        A0 = s[2].v * -1;
        AB = s[1].v - s[2].v;
        AC = s[0].v - s[2].v;

        ABperp = (AC * AB) * AB;
        if(A0.dot(ABperp) > 0)
        {
            dir = (AB * A0) * AB;
            s.erase(s.begin());
        }
        else
        {
            ACperp = (AB * AC) * AC;
            if(A0.dot(ACperp) > 0)
            {
                dir = (AC * A0) * AC;
                s.erase(s.begin()+1);
            }
            else
            {
                ABCperp = AC * AB;
                if(A0.dot(ABCperp) > 0)
                {
                    dir = ABCperp;
                }
                else
                {
                    dir = ABCperp * -1;

                    SupportPoint temp = s[1];
                    s[1] = s[2];
                    s[2] = temp;
                }
            }
        }
    }
    else
    {
        A0 = s[3].v * -1;
        AB = s[2].v - s[3].v;
        AC = s[1].v - s[3].v;
        AD = s[0].v - s[3].v;

        ABCperp = AC * AB;
        if(A0.dot(ABCperp) > 0)
        {
            dir = ABCperp;
            s.erase(s.begin());
        }
        else
        {
            ACDperp = AD * AC;
            if(A0.dot(ACDperp) > 0)
            {
                dir = ACDperp;
                s.erase(s.begin()+2);
            }
            else
            {
                ADBperp = AB * AD;
                if(A0.dot(ADBperp) > 0)
                {
                    dir = ADBperp;
                    s.erase(s.begin()+1);

                    SupportPoint temp = s[1];
                    s[1] = s[2];
                    s[2] = temp;
                }
                else
                {
                    return true;
                }
            }
        }
    }
    return false;
}

SupportPoint CollisionHandler::supportFunc(Cube &cube1, Cube &cube2, Vector4D dir)
{
    SupportPoint p;
    p.supA = cube1.getFarthestPoint(dir);
    p.supB = cube2.getFarthestPoint(dir * -1);
    p.v = p.supA - p.supB;
    return p;
}

std::set<std::pair<int,int>> CollisionHandler::linesweep()
{
    std::set<std::pair<int,int>> intersect;
    std::vector<int> possibleCollisions = std::vector<int>();

    for(std::multiset<Point>::iterator it = lines.begin(); it != lines.end(); it++)
    {
        std::vector<int>::iterator intIt = possibleCollisions.begin();
        Point point = *it;
        if(point.start)
        {
            point.vectorIndex = possibleCollisions.size();
            possibleCollisions.push_back(point.index);
            intIt = possibleCollisions.end();
            for(int i = 1; i < possibleCollisions.size(); i++)
            {
                intersect.insert(std::pair<int,int>(possibleCollisions[i-1], possibleCollisions[i]));
            }
        }
        else
        {
            if(possibleCollisions.size() > 0)
            {
                possibleCollisions.erase(intIt);
                intIt = possibleCollisions.end();
            }
        }
    }
    return intersect;
}

void CollisionHandler::createLines(std::vector<Cube*> &objects, int axis)
{
    lines.clear();
    for(int i = 0; i < objects.size(); i++)
    {
        Point start(objects[i]->node->getAABB().min[axis], i, true);
        Point end(objects[i]->node->getAABB().max[axis], i, false);

        start.pair = &end;
        end.pair = &start;

        lines.insert(start);
        lines.insert(end);
    }
}

std::set<std::pair<int,int>> CollisionHandler::checkCollisions(std::vector<Cube*> &objects)
{
    std::set<std::pair<int,int>> collisions;
    createLines(objects, 0);
    std::set<std::pair<int,int>> xCollisions = linesweep();
    createLines(objects, 1);
    std::set<std::pair<int,int>> yCollisions = linesweep();
    createLines(objects, 2);
    std::set<std::pair<int,int>> zCollisions = linesweep();

    std::set<std::pair<int,int>>::iterator yIt;
    std::set<std::pair<int,int>>::iterator zIt;

    for(std::set<std::pair<int,int>>::iterator it = xCollisions.begin(); it != xCollisions.end(); it++)
    {
        if(yCollisions.size() > 0)
        {
            yIt = yCollisions.find(*it);
            if(zCollisions.size() > 0)
            {
                zIt = zCollisions.find(*yIt);
                collisions.insert(*zIt);
            }
        }
    }
    return collisions;
}

CollisionInfo CollisionHandler::EPA(Cube &cube1, Cube &cube2)
{
    CollisionInfo info;
    std::vector<Triangle> triangles;
    std::vector<Edge> edges;

    triangles.push_back(Triangle(simplex[2], simplex[1], simplex[0]));
    triangles.push_back(Triangle(simplex[3], simplex[2], simplex[0]));
    triangles.push_back(Triangle(simplex[3], simplex[1], simplex[2]));
    triangles.push_back(Triangle(simplex[3], simplex[0], simplex[1]));

    while(true)
    {
        float threshhold = INFINITY;
        int index = 0;
        float dot = 0;

        for (int i = 0; i < triangles.size(); i++)
        {
            dot = abs(triangles[i].normal.dot(triangles[i].points[1].v));
            if(dot < threshhold)
            {
                threshhold = dot;
                index = i;
            }
        }
        SupportPoint point = supportFunc(cube1, cube2, triangles[index].normal);
        float temp = (triangles[index].normal.dot(point.v))-threshhold;
        if(temp < 0.00001f)
        {
            info.normal = triangles[index].normal * -1.0f;
            info.depth = (triangles[index].normal.dot(triangles[index].points[0].v)) * 0.5f;

            Vector4D p = info.normal * info.depth;
            Vector4D uvw = calcPoint(p, triangles[index].points[0].v, triangles[index].points[1].v, triangles[index].points[2].v);

            info.point = (triangles[index].points[0].supA * uvw[0]) + (triangles[index].points[1].supA * uvw[1]) + (triangles[index].points[2].supA * uvw[2]);

            return info;
        }

        for(int i = 0; i < triangles.size(); i++)
        {
            if((triangles[i].normal.dot(point.v - triangles[i].points[0].v)) > 0)
            {
                addEdge(triangles[i].points[0], triangles[i].points[1], edges);
                addEdge(triangles[i].points[1], triangles[i].points[2], edges);
                addEdge(triangles[i].points[2], triangles[i].points[0], edges);
                triangles.erase(triangles.begin() + i);
                continue;
            }
        }

        for(int i = 0; i < edges.size(); i++)
        {
            triangles.push_back(Triangle(point, edges[i].points[0], edges[i].points[1]));

        }
        edges.clear();
    }
}

void CollisionHandler::addEdge(SupportPoint &a, SupportPoint &b, std::vector<Edge> &edges)
{
    for(int i = 0; i < edges.size(); i++)
    {
        if(edges[i].points[0] == b && edges[i].points[1] == a)
        {
            edges.erase(edges.begin() + i);
            return;
        }
    }
    edges.push_back(Edge(a,b));
}

Vector4D CollisionHandler::calcPoint(Vector4D &p, Vector4D &a, Vector4D &b, Vector4D &c)
{
    Vector4D v0 = b - a;
    Vector4D v1 = c - a;
    Vector4D v2 = p - a;

    float d00 = v0.dot(v0);
    float d01 = v0.dot(v1);
    float d11 = v1.dot(v1);
    float d20 = v2.dot(v0);
    float d21 = v2.dot(v1);
    float denom = (d00 * d11) - (d01 * d01);

    float z = (d00 * d21 - d01 * d20)/denom;
    float y = (d11 * d20 - d01 * d21)/denom;
    float x = 1.0f - y - z;

    return Vector4D(x, y, z);
}

double rate(double x, double y)
{
    return x * sqrt(y);
}

double euler(double(*func)(double, double), double dt, double h, double acc)
{
    double* y = new double[(int)(dt * h)+1];
    y[0] = acc;
    y[1] = y[0] + dt * func(h,y[0]);

    for (int i = 2; i < dt * h; i++)
    {
        y[i] = y[i-1] + i * h * func(i*h, y[i-1]);
    }

    return y[(int)(dt*h)];
}

double midPoint(double(*func)(double, double), double dt, double vel, double acc)
{
    double dx = dt * 0.1;
    double temp = (func(vel, acc + temp)*0.5)*dx;

    for(int i = 0; i < 9; i++)
    {
        temp += (func(vel + dt, acc + temp)*0.5)*dt;
    }
    return vel + temp;
}

double rungeKutta(double(*func)(double, double), double dt, double vel, double acc)
{
    double k1 = dt * func(vel, acc);
    double k2 = dt * func((vel + dt) * 0.5f, (acc + k1) * 0.5f);
    double k3 = dt * func((vel + dt) * 0.5f, (acc + k2) * 0.5f);
    double k4 = dt * func(vel + dt, acc + k3);

    return (vel + (k1 + k2 + k3 + k4)/6);
}

void CollisionHandler::calcImpulse(Cube &cube1, Cube &cube2, CollisionInfo info, float dt, int integrator)
{

    if(cube1.rb->resting)
        cube1.rb->resting = false;
    if(cube2.rb->resting)
        cube2.rb->resting = false;

    float aMass = 1.0f/cube1.rb->mass;
    float bMass = 1.0f/cube2.rb->mass;

    Vector4D PA = cube1.rb->velocity + cube1.rb->spin * (info.point - cube1.CoM);
    Vector4D PB = cube2.rb->velocity + cube2.rb->spin * (info.point - cube2.CoM);

    Vector4D diffVel = PA - PB;

    float relativeVel = info.normal.dot(diffVel);

    if(relativeVel > 0.f)
    {
        return;
    }

    float sprintConst = 0.8f;

    float J = -((1.0f + sprintConst)*relativeVel)/((aMass + bMass) +
            info.normal.dot(cube1.rb->inertiaTensor * ((cube1.rb->velocity * info.normal) * cube1.rb->angularMomentum)) +
            info.normal.dot(cube2.rb->inertiaTensor * ((cube2.rb->velocity * info.normal) * cube2.rb->angularMomentum)));
    if(J > 10.0f) J = 10.0f;
    if(J < -10.0f) J = -10.0f;

    Vector4D JA = info.normal * J;
    Vector4D JB = info.normal * J * -1.0f;

    if(J != J) return;

    printf("Impulse: %f\n", J);

    Vector4D aTorque = (info.point - cube1.CoM) * JA;
    Vector4D bTorque = (info.point - cube2.CoM) * JB;

    cube1.rb->angularMomentum = cube1.rb->angularMomentum + aTorque;
    cube2.rb->angularMomentum = cube2.rb->angularMomentum + bTorque;

    cube1.rb->spin = cube1.rb->inertiaTensor * cube1.rb->angularMomentum;
    cube2.rb->spin = cube2.rb->inertiaTensor * cube2.rb->angularMomentum;

    printf("EULER: %f\n", euler(rate, dt, dt*0.1f, fabs(J/cube2.rb->mass)));
    printf("MIDPOINT: %f\n", midPoint(rate, dt, cube2.rb->velocity.length(), fabs(J/cube2.rb->mass)));
    printf("RUNGE-KUTTA: %f\n", rungeKutta(rate, dt, cube2.rb->velocity.length(), fabs(J/cube2.rb->mass)));

    switch(integrator)
    {
        case 1:
            cube1.rb->velocity = cube1.rb->velocity + info.normal * euler(rate, dt, dt*0.1f, fabs(J/cube1.rb->mass));
            cube2.rb->velocity = cube2.rb->velocity + (Vector4D(0, 0, 0) - info.normal) * euler(rate, dt, dt*0.1f, fabs(J/cube2.rb->mass));
            break;
        case 2:
            cube1.rb->velocity = cube1.rb->velocity + info.normal * midPoint(rate, dt, cube1.rb->velocity.length(), fabs(J/cube1.rb->mass));
            cube2.rb->velocity = cube2.rb->velocity + (Vector4D(0, 0, 0) - info.normal) * midPoint(rate, dt, cube2.rb->velocity.length(), fabs(J/cube2.rb->mass));
            break;
        case 3:
            cube1.rb->velocity = cube1.rb->velocity + info.normal * rungeKutta(rate, dt, cube1.rb->velocity.length(), fabs(J/cube1.rb->mass));
            cube2.rb->velocity = cube2.rb->velocity + (Vector4D(0, 0, 0) - info.normal) * rungeKutta(rate, dt, cube2.rb->velocity.length(), fabs(J/cube2.rb->mass));
            break;
    }
}