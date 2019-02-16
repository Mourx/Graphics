#include "ObjLoader.h"



ObjLoader::ObjLoader()
{
}


ObjLoader::~ObjLoader()
{
}


void ObjLoader::LoadObj(const char* filename) {
	FILE * file = fopen(filename, "r");
	if (file == NULL) {
		printf("ERROR: Can't find file\n");
		return;
	}

	while (true) {
		char lineHead[128];

		int fword = fscanf(file, "%s", lineHead);
		if (fword == EOF) {
			break;
		}

		//if line is 3 vertices
		if (strcmp(lineHead, "v") == 0) {

			Vertex* vertex = new Vertex(0, 0, 0);
			fscanf(file, "%f %f %f\n", &vertex->x, &vertex->y, &vertex->z);
			temp_vertices.push_back(vertex);
		}
		//if line is 2 vertices (texture co-ord) (i don't have any right now, probs won't for a while)
		// included for future maybe
		// is only 2 points
		else if (strcmp(lineHead, "vt") == 0) {
			Vertex* vertex = new Vertex(0, 0);
			fscanf(file, "%f %f\n", &vertex->x, &vertex->y);
			temp_uvs.push_back(vertex);

		}
		// if line is normals, same code as "v" basically, 3 floats
		else if (strcmp(lineHead, "vn") == 0) {
			Vertex* vertex = new Vertex(0, 0);
			fscanf(file, "%f %f %f\n", &vertex->x, &vertex->y, &vertex->z);
			temp_normals.push_back(vertex);

		}
		//Big boy Faces, more complicated than "v" etc
		else if (strcmp(lineHead, "f") == 0){
			std::string v1, v2, v3;
			unsigned int vI[3], uvI[3], nI[3];
			// a/b/c d/e/f g/h/i format of vertex locations, texture locations, normal locations
			/*int lineMatch = fscanf(file, "%d/%d/%d  %d/%d/%d  %d/%d/%d\n", &vI[0], &uvI[0], &nI[0], // 1
				&vI[1], &uvI[1], &nI[1], // 2
				&vI[2], &uvI[2], &nI[2]); // 3
				*/
			//above is for with uv, below is no mat
			int lineMatch = fscanf(file, "%d//%d  %d//%d %d//%d\n", &vI[0], &nI[0], // 1
				&vI[1], &nI[1], // 2
				&vI[2], &nI[2]); // 3
			if (lineMatch != 12) {
				//printf("OOF we done gOOFed\n");
			}

			// load everything into our vectors
			vertexIndices.push_back(vI[0]);
			vertexIndices.push_back(vI[1]);
			vertexIndices.push_back(vI[2]);
			uvIndices.push_back(uvI[0]);
			uvIndices.push_back(uvI[1]);
			uvIndices.push_back(uvI[2]);
			normalIndices.push_back(nI[0]);
			normalIndices.push_back(nI[1]);
			normalIndices.push_back(nI[2]);
		}

	}
	//Load Vertices into final form
	for (int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vI = vertexIndices[i];
		Vertex* vertex = temp_vertices[vI - 1];
		out_vertices.push_back(vertex);
	}
	// same for UV (textures)
	/* leave out uv for now
	for (int i = 0; i < uvIndices.size(); i++) {
	unsigned int vI = uvIndices[i];
	Vertex* vertex = temp_uvs[vI - 1];
	out_uvs.push_back(vertex);
	}
	*/

	//and again for normals (useless lol)
	for (int i = 0; i < normalIndices.size(); i++) {
		unsigned int vI = normalIndices[i];
		Vertex* vertex = temp_normals[vI - 1];
		out_normals.push_back(vertex);
	}
}

std::vector<Vertex*> ObjLoader::getVerts() {
	return out_vertices;
}

std::vector<Vertex*> ObjLoader::getUVs() {
	return out_uvs;
}
std::vector<Vertex*> ObjLoader::getNorms() {
	return out_normals;
}