#pragma once

#include "Vertex.h"
#include <vector>
#include <cstdio>
class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();
	void LoadObj(const char* filenam,bool bUV);
	std::vector<Vertex*> getVerts();
	std::vector<Vertex*> getUVs();
	std::vector<Vertex*> getNorms();
	std::string getMat();
private:
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Vertex*> temp_vertices;
	std::vector<Vertex*> temp_uvs;
	std::vector<Vertex*> temp_normals;

	std::vector<Vertex*> out_vertices;
	std::vector<Vertex*> out_uvs;
	std::vector<Vertex*> out_normals;
	std::string material;
};

