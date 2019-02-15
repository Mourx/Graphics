#include "Path.h"



Path::Path(std::vector<Node*> crnrs, MyScene* scn)
{
	corners = crnrs;
	scene = scn;
	FixPath();
	AddPathToScene();
}


Path::~Path()
{
}

void Path::AddPathToScene() {
	for (int i = 0; i < tiles.size(); i++) {
		scene->AddObj(tiles[i]);
	}
}

void Path::FixPath() {
	double x, y;
	std::vector<Vertex*> points;

	for (int i = 0; i < corners.size()-1; i++) {
		x = corners[i]->posX;
		y = corners[i]->posY;
		while (x != corners[i + 1]->posX || y != corners[i + 1]->posY) {
			
			points.push_back(new Vertex(x, y - 10, 0.f));
			points.push_back(new Vertex(x + 10, y - 10, 0.f));
			points.push_back(new Vertex(x + 10, y, 0.f));
			points.push_back(new Vertex(x, y, 0.f));
			tiles.push_back(new Tile(points, new Vertex(255, 255, 255), "Textures/Steel.bmp"));
			int diffx = (corners[i + 1]->posX - corners[i]->posX);
			int diffy = (corners[i + 1]->posY - corners[i]->posY);
			if (diffx != 0) {
				diffx >= 1 ? diffx = 1 : diffx = -1;
			}if (diffy != 0) {
				diffy >= 1 ? diffy = 1 : diffy = -1;
			}
			x += diffx * 10;
			y += diffy * 10;
			points.clear();
		}
	}
	points.push_back(new Vertex(corners[corners.size()-1]->posX, corners[corners.size() - 1]->posY - 10, 0.f));
	points.push_back(new Vertex(corners[corners.size() - 1]->posX + 10, corners[corners.size() - 1]->posY - 10, 0.f));
	points.push_back(new Vertex(corners[corners.size() - 1]->posX + 10, corners[corners.size() - 1]->posY, 0.f));
	points.push_back(new Vertex(corners[corners.size() - 1]->posX, corners[corners.size() - 1]->posY, 0.f));
	tiles.push_back(new Tile(points, new Vertex(255, 255, 255), "Textures/Steel.bmp"));
	points.clear();
}