#include "sprite.h"

Sprite::Sprite(Shader* shaderx) : vao(-1) {
    this->shader = shaderx;
    this->initRenderData();
}

Sprite::~Sprite() {
	glDeleteVertexArrays(1, &this->vao);
}

const unsigned int POINTS_SIZE = 8;
const unsigned int INDICES_SIZE = 6;
const unsigned int TC_SIZE = 8;

void Sprite::initRenderData() {
    GLfloat points[POINTS_SIZE] = { -1, -1,
                1, -1,
                1, 1,
                -1, 1 };

    GLuint indices[INDICES_SIZE] = { 0,1,2,
                        2,3,0 };

    GLfloat tc[TC_SIZE] = { 0, 0,
                   0, 1,
                   1, 1,
                   1, 0 };

    this->vao = 0;

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    GLuint vbo_tc;

    glGenBuffers(1, &vbo_tc);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tc), tc, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    GLuint ebo;

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Sprite::drawSprite(const Texture2D &texture, const glm::vec2 pos, const glm::vec2 size, const float rotate, const glm::vec3 color) {
    this->shader->Use();

    glm::mat4 model = glm::mat4(1.0);//glm::translate(model, glm::vec3(pos.x, pos.y, 0));
    model = glm::rotate(model, rotate, glm::vec3(1.0, 0, 0));
    //model = glm::scale(model, glm::vec3(size.x, size.y, 1));

    glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f);

    this->shader->setMatrix4("model", model, true);
    this->shader->setMatrix4("projection", proj);
    this->shader->setVec3f("color", color);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}