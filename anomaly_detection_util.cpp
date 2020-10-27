/*
 * animaly_detection_util.cpp
 *
 * Author: write your ID and name here
 */

#include <math.h>
#include "anomaly_detection_util.hpp"

float avg(float *x, int size)
{
    float sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += x[i];
    }
    return sum / size;
}

// returns the variance of X and Y
float var(float *x, int size)
{
    float variance = 0;
    for (int i = 0; i < size; i++)
    {
        variance += pow(x[i], 2);
    }
    variance = variance / size;
    variance -= pow(avg(x, size), 2);
    return variance;
}

// returns the covariance of X and Y
float cov(float *x, float *y, int size)
{
    float avgx = avg(x, size), avgy = avg(y, size);
    float covariance = 0;
    for (int i = 0; i < size; i++)
    {
        covariance += (x[i] - avgx) * (y[i] - avgy);
    }
    covariance = covariance / size;
    return covariance;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size)
{
    float avgx = avg(x, size), avgy = avg(y, size);
    float numerator = 0, denominatorX = 0, denominatorY = 0;
    for (int i = 0; i < size; i++)
    {
        numerator += (x[i] - avgx) * (y[i] - avgy);
        denominatorX += pow((x[i] - avgx), 2);
        denominatorY += pow((y[i] - avgy), 2);
    }
    float denominator = sqrt(denominatorX * denominatorY);
    return numerator / denominator;
}

// performs a linear regression and returns the line equation
Line linear_reg(Point **points, int size)
{
    float a, b;
    float x[size];
    float y[size];
    for (int i = 0; i < size; i++)
    {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    a = cov(x, y, size) / var(x, size);
    b = avg(y, size) - a * avg(x, size);
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size)
{
    Line l = linear_reg(points, size);
    return dev(p, l);
}

// returns the deviation between point p and the line
float dev(Point p, Line l)
{
    float fx;
    fx = l.a * p.x + l.b;
    return fabs(fx - p.y);
}