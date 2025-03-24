#include "../include/renderData.hpp"

RenderData::RenderData(const std::vector<GLfloat> &vertices) {
	this->vertices = &vertices;
	Model.identity();
	Scale.identity();
	Rotate.identity();
	Translate.identity();
	zoom = 1;
	moveX = 0;
	moveY = 0;
	moveZ = 0;

	Proj.perspective(45.0f, float(W_WIDTH)/float(W_HEIGHT), 0.1f, 1000.0f);
	View.view(Vector3(0,0,0), getObjCenter(), Vector3(0, 1, 0));
	calcMVP();
}

RenderData::RenderData() { };

void RenderData::init(const std::vector<GLfloat> &vertices) {
	this->vertices = &vertices;
	Model.identity();
	Scale.identity();
	Rotate.identity();
	Translate.identity();
	zoom = 1;
	moveX = 0;
	moveY = 0;
	moveZ = 0;

	Proj.perspective(45.0f, float(W_WIDTH)/float(W_HEIGHT), 0.1f, 1000.0f);
	View.view(Vector3(0,0,0), getObjCenter(), Vector3(0, 1, 0));
	calcMVP();
}

RenderData::~RenderData() { }

//Rotation Handling
void RenderData::applyRotation() {
	Quaternion finalRotation = x * y * z;
	finalRotation.normalize();
	Rotate = finalRotation.toMatrix();
	calcMVP();
}

void RenderData::rotateX(double angle) {
	x = Quaternion(Vector3(1, 0, 0), angle);
	x.normalize();
}

void RenderData::rotateY(double angle) {
	y = Quaternion(Vector3(0, 1, 0), 240);
	y.normalize();
}

void RenderData::rotateZ(double angle) {
	Quaternion newZ = Quaternion(Vector3(0, 0, 1), angle);
	z = newZ;
	z.normalize();
}


//Translation Handling (Move object)
void RenderData::axeX(double step) {
	moveX += step;
	Translate.translate(moveX, moveY, moveZ);
	calcMVP();
}

void RenderData::axeY(double step) {
	moveY += step;
	Translate.translate(moveX, moveY, moveZ);
	calcMVP();
}

void RenderData::axeZ(double step) {
	moveZ += step;
	Translate.translate(moveX, moveY, moveZ);
	calcMVP();
}

//Scaling Handling (Zoom in/out)
void RenderData::zoomIn(double step) {
	zoom += step;
	Scale.scale(zoom, zoom, zoom);
	calcMVP();
}

void RenderData::zoomOut(double step) {
	if (zoom - step <= 0)
		return ;
	zoom -= step;
	Scale.scale(zoom, zoom, zoom);
	calcMVP();
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
	calcMVP();
}

void RenderData::calcMVP() {
	Model = Translate * Rotate * Scale;
	MVP = Proj * View * Model;
}
