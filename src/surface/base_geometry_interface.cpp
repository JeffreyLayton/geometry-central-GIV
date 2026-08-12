#include "geometrycentral/surface/base_geometry_interface.h"

namespace geometrycentral {
namespace surface {


// clang-format off
BaseGeometryInterface::BaseGeometryInterface(SurfaceMesh& mesh_)
    : mesh(mesh_),
      
  // Construct the dependency graph of managed quantities and their callbacks

  vertexIndicesQ           (&vertexIndices,         std::bind(&BaseGeometryInterface::computeVertexIndices, this),          quantities),
  interiorVertexIndicesQ   (&interiorVertexIndices, std::bind(&BaseGeometryInterface::computeInteriorVertexIndices, this),  quantities),
  edgeIndicesQ             (&edgeIndices,           std::bind(&BaseGeometryInterface::computeEdgeIndices, this),            quantities),
  halfedgeIndicesQ         (&halfedgeIndices,       std::bind(&BaseGeometryInterface::computeHalfedgeIndices, this),        quantities),
  cornerIndicesQ           (&cornerIndices,         std::bind(&BaseGeometryInterface::computeCornerIndices, this),          quantities),
  faceIndicesQ             (&faceIndices,           std::bind(&BaseGeometryInterface::computeFaceIndices, this),            quantities),
  boundaryLoopIndicesQ     (&boundaryLoopIndices,   std::bind(&BaseGeometryInterface::computeBoundaryLoopIndices, this),    quantities)

  {
  }
// clang-format on

BaseGeometryInterface::~BaseGeometryInterface() {}

void BaseGeometryInterface::refreshQuantities() {
  for (DependentQuantity* q : quantities) {
    q->computed = false;
  }
  for (DependentQuantity* q : quantities) {
    q->ensureHaveIfRequired();
  }
}

void BaseGeometryInterface::purgeQuantities() {
  for (DependentQuantity* q : quantities) {
    q->clearIfNotRequired();
  }
}

// == Indices

// Vertex indices
void BaseGeometryInterface::computeVertexIndices() { vertexIndices = mesh.getVertexIndices(); }
void BaseGeometryInterface::requireVertexIndices() { vertexIndicesQ.require(); }
void BaseGeometryInterface::unrequireVertexIndices() { vertexIndicesQ.unrequire(); }

// Interior vertex indices
void BaseGeometryInterface::computeInteriorVertexIndices() { interiorVertexIndices = mesh.getInteriorVertexIndices(); }
void BaseGeometryInterface::requireInteriorVertexIndices() { interiorVertexIndicesQ.require(); }
void BaseGeometryInterface::unrequireInteriorVertexIndices() { interiorVertexIndicesQ.unrequire(); }

// Edge indices
void BaseGeometryInterface::computeEdgeIndices() { edgeIndices = mesh.getEdgeIndices(); }
void BaseGeometryInterface::requireEdgeIndices() { edgeIndicesQ.require(); }
void BaseGeometryInterface::unrequireEdgeIndices() { edgeIndicesQ.unrequire(); }

// Halfedge indices
void BaseGeometryInterface::computeHalfedgeIndices() { halfedgeIndices = mesh.getHalfedgeIndices(); }
void BaseGeometryInterface::requireHalfedgeIndices() { halfedgeIndicesQ.require(); }
void BaseGeometryInterface::unrequireHalfedgeIndices() { halfedgeIndicesQ.unrequire(); }

// Corner indices
void BaseGeometryInterface::computeCornerIndices() { cornerIndices = mesh.getCornerIndices(); }
void BaseGeometryInterface::requireCornerIndices() { cornerIndicesQ.require(); }
void BaseGeometryInterface::unrequireCornerIndices() { cornerIndicesQ.unrequire(); }


// Face indices
void BaseGeometryInterface::computeFaceIndices() { faceIndices = mesh.getFaceIndices(); }
void BaseGeometryInterface::requireFaceIndices() { faceIndicesQ.require(); }
void BaseGeometryInterface::unrequireFaceIndices() { faceIndicesQ.unrequire(); }


// Boundary loop indices
void BaseGeometryInterface::computeBoundaryLoopIndices() { boundaryLoopIndices = mesh.getBoundaryLoopIndices(); }
void BaseGeometryInterface::requireBoundaryLoopIndices() { boundaryLoopIndicesQ.require(); }
void BaseGeometryInterface::unrequireBoundaryLoopIndices() { boundaryLoopIndicesQ.unrequire(); }

// clang-format off
BaseGeometryInterface::BaseGeometryInterface(const BaseGeometryInterface& source, SurfaceMesh& targetMesh) :
  mesh(targetMesh),
  vertexIndicesQ         (&vertexIndices,         std::bind(&BaseGeometryInterface::computeVertexIndices, this),         quantities),
  interiorVertexIndicesQ (&interiorVertexIndices, std::bind(&BaseGeometryInterface::computeInteriorVertexIndices, this), quantities),
  edgeIndicesQ           (&edgeIndices,           std::bind(&BaseGeometryInterface::computeEdgeIndices, this),           quantities),
  halfedgeIndicesQ       (&halfedgeIndices,       std::bind(&BaseGeometryInterface::computeHalfedgeIndices, this),       quantities),
  cornerIndicesQ         (&cornerIndices,         std::bind(&BaseGeometryInterface::computeCornerIndices, this),         quantities),
  faceIndicesQ           (&faceIndices,           std::bind(&BaseGeometryInterface::computeFaceIndices, this),           quantities),
  boundaryLoopIndicesQ   (&boundaryLoopIndices,   std::bind(&BaseGeometryInterface::computeBoundaryLoopIndices, this),   quantities)

  {

  GC_SAFETY_ASSERT(
      source.mesh.isCompressed() == targetMesh.isCompressed(),
      "rawCopyTo(): mesh compression states differ"
  );

  GC_SAFETY_ASSERT(
      source.mesh.nVertices()       == targetMesh.nVertices()       &&
      source.mesh.nEdges()          == targetMesh.nEdges()          &&
      source.mesh.nHalfedges()      == targetMesh.nHalfedges()      &&
      source.mesh.nCorners()        == targetMesh.nCorners()        &&
      source.mesh.nFaces()          == targetMesh.nFaces()          &&
      source.mesh.nBoundaryLoops()  == targetMesh.nBoundaryLoops()  ,
      "rawCopyTo(): mesh element counts differ"
  );

  if (source.vertexIndicesQ.computed) 
      vertexIndices = source.vertexIndices.reinterpretTo(targetMesh);
  vertexIndicesQ.computed = source.vertexIndicesQ.computed;
  vertexIndicesQ.requireCount = source.vertexIndicesQ.requireCount;
  vertexIndicesQ.clearable = source.vertexIndicesQ.clearable;

  if (source.interiorVertexIndicesQ.computed) 
      interiorVertexIndices = source.interiorVertexIndices.reinterpretTo(targetMesh);
  interiorVertexIndicesQ.computed = source.interiorVertexIndicesQ.computed;
  interiorVertexIndicesQ.requireCount = source.interiorVertexIndicesQ.requireCount;
  interiorVertexIndicesQ.clearable = source.interiorVertexIndicesQ.clearable;

  if (source.edgeIndicesQ.computed) 
      edgeIndices = source.edgeIndices.reinterpretTo(targetMesh);
  edgeIndicesQ.computed = source.edgeIndicesQ.computed;
  edgeIndicesQ.requireCount = source.edgeIndicesQ.requireCount;
  edgeIndicesQ.clearable = source.edgeIndicesQ.clearable;

  if (source.halfedgeIndicesQ.computed) 
      halfedgeIndices = source.halfedgeIndices.reinterpretTo(targetMesh);
  halfedgeIndicesQ.computed = source.halfedgeIndicesQ.computed;
  halfedgeIndicesQ.requireCount = source.halfedgeIndicesQ.requireCount;
  halfedgeIndicesQ.clearable = source.halfedgeIndicesQ.clearable;

  if (source.cornerIndicesQ.computed)
      cornerIndices = source.cornerIndices.reinterpretTo(targetMesh);
  cornerIndicesQ.computed = source.cornerIndicesQ.computed;
  cornerIndicesQ.requireCount = source.cornerIndicesQ.requireCount;
  cornerIndicesQ.clearable = source.cornerIndicesQ.clearable;

  if (source.faceIndicesQ.computed)
    faceIndices = source.faceIndices.reinterpretTo(targetMesh);
  faceIndicesQ.computed = source.faceIndicesQ.computed;
  faceIndicesQ.requireCount = source.faceIndicesQ.requireCount;
  faceIndicesQ.clearable = source.faceIndicesQ.clearable;

  if (source.boundaryLoopIndicesQ.computed)
    boundaryLoopIndices = source.boundaryLoopIndices.reinterpretTo(targetMesh);
  boundaryLoopIndicesQ.computed = source.boundaryLoopIndicesQ.computed;
  boundaryLoopIndicesQ.requireCount = source.boundaryLoopIndicesQ.requireCount;
  boundaryLoopIndicesQ.clearable = source.boundaryLoopIndicesQ.clearable;
}
// clang-format on

} // namespace surface
} // namespace geometrycentral
