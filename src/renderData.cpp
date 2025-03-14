#include "../include/renderData.hpp"

RenderData::RenderData(const std::vector<GLfloat> &vertices) {
	this->vertices = &vertices;
	Vector3 center = getObjCenter();
	Model.identity();
	Model.translate(-center.x, -center.y, -center.z);
	Proj.perspective(45.0f, float(W_WIDTH)/float(W_HEIGHT), 0.1f, 1000.0f);
	View.view(Vector3(0,0,0), Vector3(0, 0, 0), Vector3(0, 1, 0));
	MVP = Proj * View * Model;
	angleX = 0;
	angleY = 0;
	angleZ = 0;
	zoom = 1;
	moveX = 0;
	moveY = 0;
	moveZ = 0;
}

RenderData::RenderData() {

}

void RenderData::init(const std::vector<GLfloat> &vertices) {
	this->vertices = &vertices;
	Vector3 center = getObjCenter();
	Model.identity();
	Model.translate(-center.x, -center.y, -center.z);
	Proj.perspective(45.0f, float(W_WIDTH)/float(W_HEIGHT), 0.1f, 1000.0f);
	View.view(Vector3(0,0,0), Vector3(0, 0, 0), Vector3(0, 1, 0));
	MVP = Proj * View * Model;
	angleX = 0;
	angleY = 0;
	angleZ = 0;
	zoom = 1;
	moveX = 0;
	moveY = 0;
	moveZ = 0;
}

RenderData::~RenderData() { }

//Rotation Handling
void RenderData::applyRotation() {
	Model.rotate(angleX, Vector3(1, 0, 0));
	Model.rotate(angleY, Vector3(0, 1, 0));
	Model.rotate(angleZ, Vector3(0, 0, 1));
	MVP = Proj * View * Model;
}

void RenderData::decreaseAngleX(double step) {
	angleX -= step * SENSIVITY;
}

void RenderData::decreaseAngleY(double step) {
	angleY -= step * SENSIVITY;
}

void RenderData::decreaseAngleZ(double step) {
	angleZ -= step * SENSIVITY;
}

void RenderData::increaseAngleX(double step) {
	angleX += step * SENSIVITY;
}

void RenderData::increaseAngleY(double step) {
	angleY += step * SENSIVITY;
}

void RenderData::increaseAngleZ(double step) {
	angleZ += step * SENSIVITY;
}

//Translation Handling (Move object)
void RenderData::axeX(double step) {
	moveX += step;
	Model.translate(moveX, 0, 0);
	MVP = Proj * View * Model;
}

void RenderData::axeY(double step) {
	moveY += step;
	Model.translate(0, moveY, 0);
	MVP = Proj * View * Model;
}

void RenderData::axeZ(double step) {
	moveZ += step;
	Model.translate(0, 0, moveZ);
	MVP = Proj * View * Model;
}

//Scaling Handling (Zoom in/out)

void RenderData::zoomIn(double step) {
	zoom += step;
	Model.scale(zoom, zoom, zoom);
	MVP = Proj * View * Model;
}

void RenderData::zoomOut(double step) {
	if (zoom - step <= 0)
		return ;
	zoom -= step;
	Model.scale(zoom, zoom, zoom);
	MVP = Proj * View * Model;
}

//Other

std::array<std::array<float, 4>, 4> RenderData::getMVP() const {
	return MVP.getMatrix();
}

Vector3 RenderData::getObjCenter() const {
	Vector3 min(0, 0, 0);
	Vector3 max(0, 0, 0);
	float x, y, z;

	for (size_t i = 0; i < (*vertices).size(); i += 3) {
		x = (*vertices)[i];
		y = (*vertices)[i + 1];
		z = (*vertices)[i + 2];
		if (min.x > x)
			min.x = x;
		if (min.y > y)
			min.y = y;
		if (min.z > z)
			min.z = z;

		if (max.x < x)
			max.x = x;
		if (max.y < y)
			max.y = y;
		if (max.z < z)
			max.z = z;
	}

	Vector3 center(
		(min.x + max.x) / 2.0f,
		(min.y + max.y) / 2.0f,
		(min.z + max.z) / 2.0f
	);
	return center;
}

void RenderData::lookAtObj() {
	Vector3 center = getObjCenter();
	cameraPos = Vector3(center.x + 15, center.y, center.z);
	View = Matrix4();

	View.view(cameraPos, center, Vector3(0, 1, 0));
	MVP = Proj * View * Model;
}
