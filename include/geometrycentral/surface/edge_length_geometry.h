#pragma once

#include "geometrycentral/surface/intrinsic_geometry_interface.h"
#include "geometrycentral/surface/surface_mesh.h"

#include <Eigen/SparseCore>

namespace geometrycentral {
namespace surface {


class EdgeLengthGeometry : public IntrinsicGeometryInterface {

public:
  EdgeLengthGeometry(SurfaceMesh& mesh_);
  EdgeLengthGeometry(SurfaceMesh& mesh_, const EdgeData<double>& inputEdgeLengths);
  virtual ~EdgeLengthGeometry() {}

  // Construct a new geometry which is exactly the same as this one, on the same mesh.
  // This is a deep copy, no quantites are shared, etc. Require counts/computed quantities are not copied.
  std::unique_ptr<EdgeLengthGeometry> copy();

  // Construct a new geometry which is exactly the same as this one, on another mesh.
  // This is a deep copy, no quantites are shared, etc. Require counts/computed quantities are not copied.
  // The meshes must be in correspondence (have the same connectivity).
  std::unique_ptr<EdgeLengthGeometry> reinterpretTo(SurfaceMesh& targetMesh);

  // JEFFREY LAYTON
  // Construct a raw copy on another mesh, preserving computed quantities.
  // The meshes must have identical connectivity.
  std::unique_ptr<EdgeLengthGeometry> rawCopyTo(SurfaceMesh& targetMesh) const;

  // The actual input data which defines the geometry
  // In a previous version of the library, this was a distinct field which got copied in to `edgeLengths`. However, now
  // they are simply aliases for the same buffer.
  EdgeData<double>& inputEdgeLengths;

  // == Immediates
  double faceArea(Face f) const;
  double vertexDualArea(Vertex v) const;
  double cornerAngle(Corner c) const;
  double halfedgeCotanWeight(Halfedge he) const;
  double edgeCotanWeight(Edge e) const;
  double vertexGaussianCurvature(Vertex v) const;
  double faceCircumradius(Face f) const;


protected:
  
  // JEFFREY LAYTON
  // Handling the copying procedure for rawCopyTo
  EdgeLengthGeometry(const EdgeLengthGeometry& source, SurfaceMesh& targetMesh);

  // Override the compute edge lengths method from intrinsic geometry.
  virtual void computeEdgeLengths() override;


private:
};

} // namespace surface
} // namespace geometrycentral

#include "geometrycentral/surface/edge_length_geometry.ipp"
