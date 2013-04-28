#ifndef _QH_SAREA_H
#define _QH_SAREA_H

#include <iostream.h>
#ifdef __WIN32
#include <conio.h>
#endif
#include <math.h>

#if defined(__cplusplus)
extern "C"
{
#endif
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qhull/qhull.h"
#include "qhull/mem.h"
#include "qhull/qset.h"
#include "qhull/geom.h"
#include "qhull/merge.h"
#include "qhull/poly.h"
#include "qhull/io.h"
#include "qhull/stat.h"

#if defined(__cplusplus)
}
#endif

#include "ldtypes.h"

class VorPoly
{
    public:
        int     NumVertices;
        int    *Vertices;       // NumVertices

    VorPoly() {}

    ~VorPoly()
    {
        delete [] Vertices;
    }
};

// Retorna um array com a area associada a cada ponto da esfera unitaria
bool GetPointAreas(int numPoints, coordT *points, float *areas);

// Retorna os vertices de voronoi
float *GetVoronoiVertices(int *numVert);

// Retorna os poligonos de voronoi
VorPoly *GetVoronoiPolygons(int *numPolys, int numVert, float *vert);

// Calcula a area de um poligono esferico
float SphericalPolyArea(VorPoly *poly, float *vert);

// Calcula o produto cruzado entre 2 vectors - resultado normalizado fica em c
void crossp(float *a, float *b, float *c);

#endif  // _QH_SAREA_H
