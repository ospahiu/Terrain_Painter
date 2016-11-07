#include "VECTOR3D.h"
#include "Blob.h"
#include <vector>

using namespace std;

#ifndef QuadMesh_H
#define QuadMesh_H

//class VECTOR3D;
float RandomFloat(float a, float b);

struct MeshVertex {
    VECTOR3D position;
    VECTOR3D normal;
};

struct MeshQuad {
    // pointers to vertices of each quad
    MeshVertex *vertices[4];
};

class QuadMesh {
private:

    int maxMeshSize;
    int minMeshSize;
    float meshDim;
    bool reset;

    int numVertices;
    MeshVertex *vertices;

    int numQuads;
    MeshQuad *quads;

    int numFacesDrawn;

    GLfloat mat_ambient[4];
    GLfloat mat_specular[4];
    GLfloat mat_diffuse[4];
    GLfloat mat_shininess[1];


private:
    bool CreateMemory();

    void FreeMemory();

public:

    typedef std::pair<int, int> MaxMeshDim;

    QuadMesh(int maxMeshSize = 40, float meshDim = 1.0f);

    ~QuadMesh() {
        FreeMemory();
    }

    MaxMeshDim GetMaxMeshDimensions() {
        return MaxMeshDim(minMeshSize, maxMeshSize);
    }

    void resetPlane();

    bool InitMesh(int meshSize, VECTOR3D origin, double meshLength, double meshWidth, VECTOR3D dir1, VECTOR3D dir2,
                  Blob blob);

    void DrawMesh(int meshSize);

    void UpdateMesh(Blob blob);

    void SetMaterial(VECTOR3D ambient, VECTOR3D diffuse, VECTOR3D specular, double shininess);

    void ComputeNormals();

    float getInfluenceHeight(Blob &blob, const VECTOR3D &meshpt);
};

#endif