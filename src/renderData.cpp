#include "../include/renderData.hpp"

RenderData::RenderData() {
	Model.identity();
	Proj.perspective(60.0f, float(W_WIDTH)/float(W_HEIGHT), 0.1f, 1000.0f);
	View.view(Vector3(5,5,5), Vector3(0, 0, 0), Vector3(0, 1, 0));
	MVP = Proj * View * Model;
	angleX = 0;
	angleY = 0;
	angleZ = 0;
}

RenderData::~RenderData() { }

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

std::array<std::array<float, 4>, 4> RenderData::getMVP() const {
	return MVP.getMatrix();
}
