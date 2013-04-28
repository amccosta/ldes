#include "qhsarea.h"
#include "ldmath.h"

char qh_version[] = "qad 2000/8/1"; // Used for error messages

// Retorna um array com a area associada a cada ponto da esfera unitaria
bool GetPointAreas(int numPoints, coordT *points, float *areas)
{
    assert(numPoints > 0);
    assert(points != NULL);
    assert(areas != NULL);

    // Inicialize QHull
    boolT   ismalloc = false;
    char    flags[] = "qhull n FN";
    FILE   *outfile = NULL;
    FILE   *errfile = NULL;
    int     exitcode;
    int     curlong, totlong;

    // Execute QHull
    exitcode = qh_new_qhull(3, numPoints, points, ismalloc, flags,
                            outfile, errfile);

    if (!exitcode) // If no error
    {
        int numVorPolys;
        int numVorVert;

        // Get voronoi vertices
        float *vorVert = GetVoronoiVertices(&numVorVert);
        // assert(vorVert != NULL && numVorVert > 0);
        if (vorVert == NULL || numVorVert < 1)
        {
            delete[] vorVert;
            return false;
        }

        // Get voronoi polygons
        VorPoly *vorPolys = GetVoronoiPolygons(&numVorPolys,
                                               numVorVert, vorVert);
        // assert(vorPolys != NULL && numVorPolys == numPoints);
        if (vorPolys == NULL || numVorPolys != numPoints)
        {
            delete[] vorVert;
            delete[] vorPolys;
            return false;
        }

        for (int i = 0; i < numVorPolys; i++) // For each polygon...
        {
            // Calculate the area of the polygon
            areas[i] = SphericalPolyArea(&(vorPolys[i]), vorVert);
        }

        delete[] vorVert;
        delete[] vorPolys;
    }

    // Terminate QHull
    qh_freeqhull(!qh_ALL);
    qh_memfreeshort(&curlong, &totlong);
#if 0
    if (curlong || totlong)
    {
        fprintf(errfile, "qhull: no free %d bytes of memory (%d pieces)\n",
                totlong, curlong);
        return false;
    }
#endif

    return true;
}

// Retorna os vertices de voronoi
float *GetVoronoiVertices(int *numVert)
{
    float *vert = new float[3 * qh num_facets];
    assert(vert != NULL);

    facetT *facet; // Set by FORALLfacets

    int i = 0;

    FORALLfacets
    {
        vert[i++] = float(facet->normal[0]);
        vert[i++] = float(facet->normal[1]);
        vert[i++] = float(facet->normal[2]);
    }

    *numVert = qh num_facets;

    return vert;
}

// Retorna os poligonos de voronoi
VorPoly *GetVoronoiPolygons(int *numPolys, int numVert, float *vert)
{
    assert(numVert > 0);
    assert(vert != NULL);

    FILE   *fp = NULL;
    facetT *facetlist = qh facet_list;
    setT   *facets = NULL;
    boolT   printall = !qh_ALL;

    int numfacets;
    int numsimplicial;
    int numridges;
    int totneighbors;
    int numneighbors;
    int numcoplanars;
    int numtricoplanars;
    int vertex_i;
    int vertex_n;
    int numpoints = qh num_points + qh_setsize(qh other_points);

    setT *vertices;
    setT *vertex_points;
    setT *coplanar_points;

    vertexT  *vertex;
    vertexT **vertexp;

    facetT  *facet;
    facetT **facetp;
    facetT  *neighbor;
    facetT **neighborp;

    pointT  *point;
    pointT **pointp;

    qh_countfacets(facetlist, facets, printall, &numfacets, &numsimplicial,
                   &totneighbors, &numridges, &numcoplanars, &numtricoplanars);     // Sets facet->visitid

    *numPolys = numpoints;

    VorPoly *polys = new VorPoly[numpoints];
    assert(polys != NULL);

    qh_vertexneighbors();

    vertices        = qh_facetvertices(facetlist, facets, printall);
    vertex_points   = qh_settemp(numpoints);
    coplanar_points = qh_settemp(numpoints);

    qh_setzero(vertex_points, 0, numpoints);
    qh_setzero(coplanar_points, 0, numpoints);

    FOREACHvertex_(vertices)
        qh_point_add(vertex_points, vertex->point, vertex);

    FORALLfacet_(facetlist)
    {
        FOREACHpoint_(facet->coplanarset)
            qh_point_add(coplanar_points, point, facet);
    }

    FOREACHfacet_(facets)
    {
        FOREACHpoint_(facet->coplanarset)
            qh_point_add(coplanar_points, point, facet);
    }

    int i = 0;

    FOREACHvertex_i_(vertex_points)
    {
        if (vertex)
        {
            numneighbors = qh_setsize(vertex->neighbors);

            qh_order_vertexneighbors(vertex); // Assumes 3D

            polys[i].NumVertices = numneighbors;

            polys[i].Vertices = new int[numneighbors];
            assert(polys[i].Vertices != NULL);

            int j = 0;

            FOREACHneighbor_(vertex)
                polys[i].Vertices[j++] = (neighbor->visitid ?
                    neighbor->visitid - 1 : neighbor->id);
        }

        i++;
    }

    qh_settempfree(&coplanar_points);
    qh_settempfree(&vertex_points);
    qh_settempfree(&vertices);

    return polys;
}

// Calcula a area de um poligono esferico
float SphericalPolyArea(VorPoly *poly, float *vert)
{
    int *pv = poly->Vertices; // 'pv' o vector de indices para vertices
    int  n  = poly->NumVertices; // 'n' o numero de vertices

    if (n < 3) return 0.0;

    float cp[3];

    float *nx = new float[n];
    float *ny = new float[n];
    float *nz = new float[n];

    n = n - 1; // n aponta para o vertice final

    int k1 = pv[n];
    int k2 = pv[0];

    crossp(&vert[3 * k1], &vert[3 * k2], cp);

    // Normal do plano n, associado aos vertices n, 0 e origem
    nx[n] = cp[0];
    ny[n] = cp[1];
    nz[n] = cp[2];

    int ii = n;
    double sum = 0.0;

    // Iteracao pelos vertices
    for (int i = 0; i <= n; i++)
    {
        if (i < n)
        {
            // O ultimo vertice foi calculado antes do ciclo
            int j = i + 1;
            k1 = pv[i];
            k2 = pv[j];

            crossp(&vert[3 * k1], &vert[3 * k2], cp);

            // Normal do plano i, associado aos vertices i, i+1 e origem
            nx[i] = cp[0];
            ny[i] = cp[1];
            nz[i] = cp[2];
        }

        // Produto escalar das normais ii e i
        // dx = cos(angulo das normais); dy = sin(angulo das normais)
        double dx = nx[ii] * nx[i] + ny[ii] * ny[i] + nz[ii] * nz[i];
        double dy = sqrt(1 - dx * dx);

        // Incrementa area
        sum += atan2(dy, dx);

        // Actualiza indice anterior
        ii = i;
    }

    delete[] nx;
    delete[] ny;
    delete[] nz;

    // Area normalizada entre 0 e 1
    return (2 * PI - sum) / 4.0 / PI;
}

// Calcula o produto cruzado entre 2 vectors - resultado normalizado fica em c
void crossp(float *a, float *b, float *c)
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];

    float inv_len = 1.0 / sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);

    c[0] *= inv_len;
    c[1] *= inv_len;
    c[2] *= inv_len;
}
