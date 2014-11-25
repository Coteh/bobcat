#include "GameObject.h"


GameObject::GameObject(){
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	setFriction(1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	collisionRect = Rect3D();
}

GameObject::~GameObject() {
	
}

std::vector<GameObject*> GameObject::getChildren(){
	return children;
}

std::string GameObject::getName(){
	return name;
}

glm::mat4 GameObject::getModelMat(){
	glm::mat4 model = glm::translate(position);
	model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
	model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
	model = glm::scale(model, scale);
	if (parent){
		model = parent->getModelMat() * model;
	}
	return model;
}

glm::vec3 GameObject::getPosition(){
	return position;
}

glm::vec3 GameObject::getVelocity(){
	return velocity;
}

glm::vec3 GameObject::getRotation(){
	return rotation;
}

Rect3D GameObject::getCollisionRect(){
	return collisionRect;
}

Mesh* GameObject::getMesh(){
	return mesh;
}

Shader* GameObject::getShader(){
	return shader;
}

void GameObject::setName(std::string _name){
	name = _name;
}

void GameObject::setMesh(Mesh* _mesh) {
	mesh = _mesh;
	UpdateDrawModes();
}

void GameObject::setCollisionRect(Rect3D _rect){
	collisionRect = _rect;
}

void GameObject::setPosition(float _x, float _y, float _z){
	position.x = _x;
	position.y = _y;
	position.z = _z;
}

void GameObject::setPosition(glm::vec3 _pos){
	position = _pos;
}

void GameObject::setVelocity(float _x, float _y, float _z){
	velocity.x = _x;
	velocity.y = _y;
	velocity.z = _z;
}

void GameObject::setFriction(float _fric){
	friction = _fric;
}

void GameObject::setRotationEuler(float _x, float _y, float _z){
	rotation.x = _x;
	rotation.y = _y;
	rotation.z = _z;
}

void GameObject::setScale(float _x, float _y, float _z){
	scale = glm::vec3(_x, _y, _z);
}

void GameObject::setShader(Shader* _shader) {
	shader = _shader;
}

void GameObject::setTexture(Texture* _tex, std::vector<GLfloat> _uvCords){
	tex = _tex;
	//glGenTextures(1, &_tex->texID);
	glBindTexture(GL_TEXTURE_3D, _tex->texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, _tex->bpp / 8, _tex->width, _tex->height, 0, _tex->type, GL_UNSIGNED_BYTE, _tex->imageData);
	//glEnableVertexAttribArray(texAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, _tex->texID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (_uvCords.size()) * sizeof(GLfloat), (void*)(sizeof(GLfloat)));
	uvCords = _uvCords;
}

void GameObject::attachGameObject(GameObject* _gameObject){
	children.push_back(_gameObject);
	_gameObject->parent = this;
}

void GameObject::UpdateDrawModes(){
	indiceCountData = mesh->getIndiceCountData();
	for (int i = 0; i < indiceCountData.size(); i++){
		if (indiceCountData[i] > 3){
			drawModeVec.push_back(GL_TRIANGLE_FAN);
		} else{
			drawModeVec.push_back(GL_TRIANGLES);
		}
	}
}

void GameObject::Update(float _gameTime){
	velocity *= friction;
	for (int i = 0; i < children.size(); i++){
		children[i]->Update(_gameTime);
	}
}

void GameObject::Draw(){
	/*glBindBuffer(GL_ARRAY_BUFFER, tex->texID);
	glDrawElements(GL_TEXTURE_2D, uvCords.size(), GL_UNSIGNED_INT, (void*)0);*/
	glBindVertexArray(mesh->getVAO());
	if (isWireFrameOn){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	int indicesSoFar = 0;
	for (int i = 0; i < drawModeVec.size(); i++){
		glDrawElements(drawModeVec[i], indiceCountData[i], GL_UNSIGNED_INT, (void*)(indicesSoFar * sizeof(GLuint)));
		indicesSoFar += indiceCountData[i];
	}
	if (isWireFrameOn){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glBindVertexArray(0);
}
