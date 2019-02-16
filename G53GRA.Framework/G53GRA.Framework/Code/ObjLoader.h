#pragma once

#include "Vertex.h"
#include <vector>
#include <cstdio>
class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();
	void LoadObj(const char* filenam);
	std::vector<Vertex*> getVerts();
	std::vector<Vertex*> getUVs();
	std::vector<Vertex*> getNorms();
private:
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Vertex*> temp_vertices;
	std::vector<Vertex*> temp_uvs;
	std::vector<Vertex*> temp_normals;

	std::vector<Vertex*> out_vertices;
	std::vector<Vertex*> out_uvs;
	std::vector<Vertex*> out_normals;
};

