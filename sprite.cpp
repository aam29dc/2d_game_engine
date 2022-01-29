#include "sprite.h"

//normalized texture coordinates and buffer
const GLfloat n_tc[TC_SIZE] = { 0, 1,
   1, 1,
   1, 0,
   0, 0 };

GLuint n_vbo_tc;

Sprite::Sprite(Shader* shaderx) : vao(-1), lastTime(0) {
    this->shader = shaderx;

    //generate normalized texture coords buffer
    glGenBuffers(1, &n_vbo_tc);
    glBindBuffer(GL_ARRAY_BUFFER, n_vbo_tc);
    glBufferData(GL_ARRAY_BUFFER, sizeof(n_tc), n_tc, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    this->initRenderData();
}

Sprite::~Sprite() {
	glDeleteVertexArrays(1, &this->vao);
}

void Sprite::initRenderData() {
    this->vao = 0;

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    GLfloat points[POINTS_SIZE] = { -1, -1,
            1, -1,
            1, 1,
            -1, 1 };
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    glGenBuffers(1, &n_vbo_tc);
    glBindBuffer(GL_ARRAY_BUFFER, n_vbo_tc);
    glBufferData(GL_ARRAY_BUFFER, sizeof(n_tc), n_tc, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    GLuint indices[INDICES_SIZE] = { 0,1,2,
                    2,3,0 };
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Sprite::drawSprite(const Texture2D &texture, const glm::vec2 pos, const glm::vec2 size, const float rotate, const glm::vec3 color) {
    this->shader->Use();

    glm::mat4 model = glm::mat4(1.0);
    model *= glm::translate(model, glm::vec3(pos.x, pos.y, 0));
    model *= glm::rotate(model, glm::radians(rotate), glm::vec3(0, 0, 1.0));
    model *= glm::scale(model, glm::vec3(size.x, size.y, 1));

    glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f);

    this->shader->setMatrix4("model", model, true);
    this->shader->setMatrix4("projection", proj);
    this->shader->setVec3f("color", color);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->vao);
    /* draw with normalized texture coords buffer */
    glBindBuffer(GL_ARRAY_BUFFER, n_vbo_tc);
    glBufferData(GL_ARRAY_BUFFER, sizeof(n_tc), n_tc, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
    /**/

    GLint num = 0;
    glGetIntegerv(GL_ARRAY_BUFFER, &num);

    static int ran = 0;
    if(ran==0) std::cout << "num: " << num << "\n";
    ran++;

    glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Sprite::calcTextureCoords(Object& animate, GLfloat (*tc)[TC_SIZE]) {
    /*
        animate.cell_w = cols;
        animate.cell_h = rows;
        animate.frame = index;
    */
    //reset coords
    for (int i = 0; i < TC_SIZE; i++) {
        (*tc)[i] = n_tc[i];
    }

    //scale
    for (int i = 0; i < TC_SIZE; i++) {
        if (i % 2 == 0) (*tc)[i] /= (float)animate.cell_w;  //x
        else (*tc)[i] /= (float)animate.cell_h;             //y
    }

    //translate
    if (animate.cell_w != 0) {
        const unsigned int col = animate.frame % animate.cell_w;
        const unsigned int row = (unsigned int)(animate.frame / animate.cell_w);

        if (animate.frame != 0) {
            for (int i = 0; i < TC_SIZE; i++) {
                if (i % 2 == 0) (*tc)[i] += (float)col * (1.0f / (float)animate.cell_w);    //x
                else (*tc)[i] += (float)row * (1.0f / (float)animate.cell_h);               //y
            }
        }
    }
}

const glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f);

void Sprite::drawObject(Object& animate) {
    this->shader->Use();

    glm::mat4 model = glm::mat4(1.0);
    model *= glm::translate(model, glm::vec3(animate.pos.x, animate.pos.y, 0));
    model *= glm::rotate(model, glm::radians(animate.angle), glm::vec3(0, 0, 1.0));
    model *= glm::scale(model, glm::vec3(animate.size.x, animate.size.y, 1));

    this->shader->setMatrix4("model", model, true);
    this->shader->setMatrix4("projection", proj);
    this->shader->setVec3f("color", animate.color);

    glActiveTexture(GL_TEXTURE0);
    animate.image->bind();

    glBindVertexArray(this->vao);

    /* calculate new texture coordiantes buffer */
    GLfloat tc[TC_SIZE] = { 0 };
    GLuint vbo_tc;
    glGenBuffers(1, &vbo_tc);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);

    if (Time::currentTime == Time::lastTime) {
        animate.frame++;
    }
    calcTextureCoords(animate, &tc);

    glBufferData(GL_ARRAY_BUFFER, sizeof(tc), tc, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
    /**/

    glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Sprite::drawText(Object& animate, const char* const text, const float offsetX, const float offsetY)  {
    this->shader->Use();

    glm::mat4 model = glm::mat4(1.0);

    this->shader->setMatrix4("projection", proj, true);
    this->shader->setVec3f("color", animate.color);

    glActiveTexture(GL_TEXTURE0);
    animate.image->bind();

    glBindVertexArray(this->vao);

    /* calculate new texture coordiantes buffer */
    GLfloat tc[TC_SIZE] = { 0 };
    GLuint vbo_tc;
    glGenBuffers(1, &vbo_tc);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);

    glm::vec3 translate = glm::vec3(0);
    unsigned int i = 0;
    unsigned int row = 0;

    for (unsigned int j = 0; text[j] != '\0'; j++) {
        model = glm::mat4(1.0f);
        translate = glm::vec3(animate.pos.x + offsetX - 0.5f + animate.size.x / 2.0f + i * animate.size.x, animate.pos.y + offsetY - row*animate.size.y, 0.0f);

        i++;

        if (translate.x >= 0.5 - animate.size.x) {
            i = 0;
            row++;
        }

        model *= glm::translate(model, translate);
        //model *= glm::rotate(model, glm::radians(0.f), glm::vec3(0.0f, 0.0f, 1.0f));  /*error: rotating matrix does funky stuff*/
        model *= glm::scale(model, glm::vec3(animate.size.x, animate.size.y, 1.0f));

        this->shader->setMatrix4("model", model, true);
         
        animate.frame = (unsigned int)text[j];
        //std::cout << "text[i]: " << text[j] << ", j: " << j << ", frame: " << animate.frame << "\n";
        calcTextureCoords(animate, &tc);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tc), tc, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

        glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
}