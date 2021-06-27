#include "..\hdr\CubeMesh.h"

CubeMesh::CubeMesh()
{
	readVertexes();
	readNormals();
	readTextureCoords();
	readFaceIndexes();

	faces_vector_size = face_indexes.size();
}

void CubeMesh::readVertexes()
{
	// Vertexes
	point3D v;
	v = { 1, 1, 1 };//0
	max_radius = std::fmax(max_radius, v.length());
	vertexes.push_back(v);
	v = { -1, 1, 1 };//1
	vertexes.push_back(v);
	v = { -1, -1, 1 };//2
	vertexes.push_back(v);
	v = { 1, -1, 1 };//3
	vertexes.push_back(v);
	v = { 1, 1, -1 };//4
	vertexes.push_back(v);
	v = { -1, 1, -1 };//5
	vertexes.push_back(v);
	v = { -1, -1, -1 };//6
	vertexes.push_back(v);
	v = { 1, -1, -1 };//7
	vertexes.push_back(v);
}

void CubeMesh::readTextureCoords()
{
	// Texture coords
	point2D uv;
	uv = { 0, 0 };
	texture_coords.push_back(uv);
	uv = { 1, 0 };
	texture_coords.push_back(uv);
	uv = { 0, 1 };
	texture_coords.push_back(uv);
	uv = { 1, 1 };
	texture_coords.push_back(uv);
}

void CubeMesh::readNormals()
{
	// Normals
	point3D n;
	n = { 0, 0, 1 };
	normals.push_back(n);
	n = { 1, 0, 0 };
	normals.push_back(n);
	n = { 0, 0, -1 };
	normals.push_back(n);
	n = { -1, 0, 0 };
	normals.push_back(n);
	n = { 0, 1, 0 };
	normals.push_back(n);
	n = { 0, -1, 0 };
	normals.push_back(n);
}

void CubeMesh::readFaceIndexes()
{
	// Triangles
	triangle_indexes t;

	t.v[0].ind = 0; t.v[1].ind = 1; t.v[2].ind = 2;
	t.v[0].n_ind = 0; t.v[1].n_ind = 0; t.v[2].n_ind = 0;
	t.v[0].t_ind = 3; t.v[1].t_ind = 2; t.v[2].t_ind = 0;
	face_indexes.push_back(t);

	t.v[0].ind = 0; t.v[1].ind = 2; t.v[2].ind = 3;
	t.v[0].n_ind = 0; t.v[1].n_ind = 0; t.v[2].n_ind = 0;
	t.v[0].t_ind = 3; t.v[1].t_ind = 0; t.v[2].t_ind = 1;
	face_indexes.push_back(t);

	t.v[0].ind = 4; t.v[1].ind = 0; t.v[2].ind = 3;
	t.v[0].n_ind = 1; t.v[1].n_ind = 1; t.v[2].n_ind = 1;
	t.v[0].t_ind = 3; t.v[1].t_ind = 2; t.v[2].t_ind = 0;
	face_indexes.push_back(t);

	t.v[0].ind = 4; t.v[1].ind = 3; t.v[2].ind = 7;
	t.v[0].n_ind = 1; t.v[1].n_ind = 1; t.v[2].n_ind = 1;
	t.v[0].t_ind = 3; t.v[1].t_ind = 0; t.v[2].t_ind = 1;
	face_indexes.push_back(t);

	t.v[0].ind = 5; t.v[1].ind = 4; t.v[2].ind = 7;
	t.v[0].n_ind = 2; t.v[1].n_ind = 2; t.v[2].n_ind = 2;
	t.v[0].t_ind = 0; t.v[1].t_ind = 1; t.v[2].t_ind = 3;
	face_indexes.push_back(t);

	t.v[0].ind = 5; t.v[1].ind = 7; t.v[2].ind = 6;
	t.v[0].n_ind = 2; t.v[1].n_ind = 2; t.v[2].n_ind = 2;
	t.v[0].t_ind = 0; t.v[1].t_ind = 3; t.v[2].t_ind = 2;
	face_indexes.push_back(t);

	t.v[0].ind = 1; t.v[1].ind = 5; t.v[2].ind = 6;
	t.v[0].n_ind = 3; t.v[1].n_ind = 3; t.v[2].n_ind = 3;
	t.v[0].t_ind = 3; t.v[1].t_ind = 2; t.v[2].t_ind = 0;
	face_indexes.push_back(t);

	t.v[0].ind = 1; t.v[1].ind = 6; t.v[2].ind = 2;
	t.v[0].n_ind = 3; t.v[1].n_ind = 3; t.v[2].n_ind = 3;
	t.v[0].t_ind = 3; t.v[1].t_ind = 0; t.v[2].t_ind = 1;
	face_indexes.push_back(t);

	t.v[0].ind = 4; t.v[1].ind = 5; t.v[2].ind = 1;
	t.v[0].n_ind = 4; t.v[1].n_ind = 4; t.v[2].n_ind = 4;
	t.v[0].t_ind = 3; t.v[1].t_ind = 2; t.v[2].t_ind = 0;
	face_indexes.push_back(t);

	t.v[0].ind = 4; t.v[1].ind = 1; t.v[2].ind = 0;
	t.v[0].n_ind = 4; t.v[1].n_ind = 4; t.v[2].n_ind = 4;
	t.v[0].t_ind = 3; t.v[1].t_ind = 0; t.v[2].t_ind = 1;
	face_indexes.push_back(t);

	t.v[0].ind = 2; t.v[1].ind = 6; t.v[2].ind = 7;
	t.v[0].n_ind = 5; t.v[1].n_ind = 5; t.v[2].n_ind = 5;
	t.v[0].t_ind = 2; t.v[1].t_ind = 0; t.v[2].t_ind = 1;
	face_indexes.push_back(t);

	t.v[0].ind = 2; t.v[1].ind = 7; t.v[2].ind = 3;
	t.v[0].n_ind = 5; t.v[1].n_ind = 5; t.v[2].n_ind = 5;
	t.v[0].t_ind = 2; t.v[1].t_ind = 1; t.v[2].t_ind = 3;
	face_indexes.push_back(t);
}
