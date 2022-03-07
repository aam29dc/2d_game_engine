#include "Renderer.h"

//normalized texture coordinates and buffer
const GLfloat n_tc[TC_SIZE] = { 0, 1,
   1, 1,
   1, 0,
   0, 0 };

const glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f);

Renderer::Renderer(Shader& shader, Shader& instance) : vao(0), vbo_v(0), vbo_tc(0), vbo_i(0), ebo(0) {
    this->shader = &shader;
    this->instance = &instance;
    this->initRenderData();
}

Renderer::~Renderer() {
    glDeleteBuffers(1, &this->vbo_v);
    glDeleteBuffers(1, &this->vbo_tc);
    glDeleteBuffers(1, &this->vbo_i);
    glDeleteBuffers(1, &this->ebo);
    glDeleteBuffers(1, &this->ubo);
    glDeleteVertexArrays(1, &this->vao);
}

void Renderer::initRenderData() {
    this->vao = 0;

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    //vertex data
    GLfloat vertices[VERTICES_SIZE] = { -1, -1,
            1, -1,
            1, 1,
            -1, 1 };
    glGenBuffers(1, &vbo_v);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    //generate texture coords buffer
    glGenBuffers(1, &vbo_tc);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);
    glBufferData(GL_ARRAY_BUFFER, sizeof(n_tc), n_tc, GL_STATIC_DRAW);  // same size as n_tc
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    //data for instanced drawing
    glGenBuffers(1, &vbo_i);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_i);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4)*20*20, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(0));
    glVertexAttribDivisor(2, 1);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 4));
    glVertexAttribDivisor(3, 1);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 8));
    glVertexAttribDivisor(4, 1);

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 12));
    glVertexAttribDivisor(5, 1);

    //element buffer
    GLuint indices[INDICES_SIZE] = { 0,1,2,
                    2,3,0 };
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //uniform buffer object for projection matrix that is the same between all shaders
    glUniformBlockBinding(this->shader->ID, glGetUniformBlockIndex(this->shader->ID, "CONST_DATA"), 0);
    glUniformBlockBinding(this->instance->ID, glGetUniformBlockIndex(this->instance->ID, "CONST_DATA"), 0);
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, sizeof(glm::mat4) + sizeof(GLfloat)*8);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(proj));

    glBindVertexArray(0);
}

void Renderer::drawQuad(const Texture2D& texture, const glm::vec2 pos, const glm::vec2 size, const float rotate, const glm::vec3 color) {
    this->shader->Use();

    glm::mat4 model = glm::mat4(1.0);
    model *= glm::translate(glm::mat4(1.0), glm::vec3(pos.x, pos.y, 0));
    model *= glm::rotate(glm::mat4(1.0), glm::radians(rotate), glm::vec3(0, 0, 1.0));
    model *= glm::scale(glm::mat4(1.0), glm::vec3(size.x, size.y, 1));

    this->shader->setMatrix4("model", model, true);
    this->shader->setVec3f("color", color);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->vao);
    /* draw with normalized texture coords buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);
    glBufferData(GL_ARRAY_BUFFER, sizeof(n_tc), n_tc, GL_STATIC_DRAW);
    /**/

    glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::calcTextureCoords(Entity& animate, GLfloat (*tc)[TC_SIZE]) {
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
        if (i % 2 == 0) (*tc)[i] /= (float)animate.cols;  //x
        else (*tc)[i] /= (float)animate.rows;             //y
    }

    //translate
    if (animate.cols != 0) {
        const unsigned int col = animate.frame % animate.cols;
        const unsigned int row = (unsigned int)(animate.frame / animate.cols);

        if (animate.frame != 0) {
            for (int i = 0; i < TC_SIZE; i++) {
                if (i % 2 == 0) (*tc)[i] += (float)col * (1.0f / (float)animate.cols);    //x
                else (*tc)[i] += (float)row * (1.0f / (float)animate.rows);               //y
            }
        }
    }
}

void Renderer::drawEntity(Entity& animate, const bool sprite) {
    this->shader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    model *= glm::translate(glm::mat4(1.0f), glm::vec3(animate.pos.x, animate.pos.y, 0));
    model *= glm::rotate(glm::mat4(1.0f), glm::radians(animate.angle), glm::vec3(0, 0, 1));
    model *= glm::scale(glm::mat4(1.0f), glm::vec3(animate.size.x, animate.size.y, 1));

    this->shader->setMatrix4("model", model, true);
    this->shader->setVec3f("color", animate.color);

    glActiveTexture(GL_TEXTURE0);
    animate.image->bind();

    glBindVertexArray(this->vao);

    // calculate new texture coordiantes buffer
    GLfloat tc[TC_SIZE] = { 0 };

    if (sprite) {
        if (Time::current - animate.frameTime >= 1.0f) {
            animate.frame++;
            animate.frameTime = Time::current;
        }
    }

    calcTextureCoords(animate, &tc);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tc), tc, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
}

void Renderer::drawText(Entity& animate, const char* const text, const float offsetX, const float offsetY)  {
    this->shader->Use();

    this->shader->setVec3f("color", animate.color);

    glActiveTexture(GL_TEXTURE0);
    animate.image->bind();

    glBindVertexArray(this->vao);

    /* calculate new texture coordiantes buffer */
    GLfloat tc[TC_SIZE] = { 0 };

    glm::mat4 model = glm::mat4(1.0);
    glm::vec3 translate = glm::vec3(0);
    unsigned int i = 0;
    unsigned int row = 0;

    for (unsigned int j = 0; text[j] != '\0'; j++) {
        model = glm::mat4(1.0f);
        translate = glm::vec3(animate.pos.x + offsetX - 0.99f + (animate.size.x / 2.0f) + i * animate.size.x*2, animate.pos.y + offsetY - row * animate.size.y*2, 0.0f);

        i++;

        if (translate.x >= 0.99f - animate.size.x) {
            i = 0;
            row++;
        }

        model *= glm::translate(glm::mat4(1.0f), translate);
        model *= glm::rotate(glm::mat4(1.0f), glm::radians(animate.angle), glm::vec3(0.0f, 0.0f, 1.0f));
        model *= glm::scale(glm::mat4(1.0f), glm::vec3(animate.size.x, animate.size.y, 1.0f));

        this->shader->setMatrix4("model", model, true);
         
        animate.frame = (unsigned int)text[j];
        //std::cout << "text[i]: " << text[j] << ", j: " << j << ", frame: " << animate.frame << "\n";
        calcTextureCoords(animate, &tc);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tc), tc, GL_STATIC_DRAW);

        glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
}

void Renderer::drawTime(Entity& animate, const float offsetX, const float offsetY, const unsigned int decimals) {
    float current = (float)glfwGetTime();

    int tens = 0;

    for (; current / (pow(10, tens)) > 1.0f; tens++) {
    }

    std::string text_str = std::to_string(current).substr(0,tens+decimals+1);
    const char * const c_text = text_str.c_str();

    glm::vec3 temp = animate.color;
    animate.color = glm::vec3(1, 1, 1);
    drawText(animate, c_text, offsetX, offsetY);
    animate.color = temp;
}

void Renderer::drawFPS(Entity& animate, const float offsetX, const float offsetY) {
    const unsigned int fps = (unsigned int)(1 / Time::delta);

    if (Time::current - animate.frameTime >= 1.0f) {
        animate.frameTime = Time::current;
    }

    const std::string fps_s = std::to_string(fps);
    const char* const fps_c = fps_s.c_str();

    Renderer::drawText(animate, fps_c, offsetX, offsetY);
}

void Renderer::drawCrosshair(GLFWwindow* window, const Texture2D& texture, const unsigned int screen_width, const unsigned int screen_height) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    xpos = xpos / (float)screen_width;
    ypos = -ypos / (float)screen_height;
    xpos += -0.5f;
    ypos += 0.5f;
    xpos *= 2;
    ypos *= 2;
    drawQuad(texture, glm::vec2(xpos, ypos), glm::vec2(0.05f, 0.05f), 0, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Renderer::drawPlayer(Player& player) {
    this->shader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    model *= glm::translate(glm::mat4(1.0f), glm::vec3(player.pos.x, player.pos.y, 0));
    model *= glm::rotate(glm::mat4(1.0f), glm::radians(player.angle), glm::vec3(0, 0, 1));
    model *= glm::scale(glm::mat4(1.0f), glm::vec3(player.size.x, player.size.y, 1));

    this->shader->setMatrix4("model", model, true);
    this->shader->setVec3f("color", player.color);

    glActiveTexture(GL_TEXTURE0);
    player.image->bind();

    glBindVertexArray(this->vao);

    // calculate new texture coordiantes buffer
    GLfloat tc[TC_SIZE] = { 0 };

    if (Time::current - player.frameTime >= 1.0f/(float)player.cols) {
        player.frame++;
        player.frameTime = Time::current;
    }

    if (player.still) {
        player.frame = (unsigned int)(player.dir) * (player.cols);
        //std::cout << "still\n";
    }
    else {
        player.frame = (unsigned int)(player.dir) * (player.cols) + (player.frame % player.cols);
        //std::cout << "unstill\n";
    }
    //std::cout << "frame: " << player.frame << "\n";

    calcTextureCoords(player, &tc);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tc), tc, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Renderer::drawLevel(Level& lvl) {
    this->instance->Use();

    static glm::mat4 model[20*20] = {};

    for (int i = 0; i < 20*20; i++) {
        model[i] = glm::mat4(1.0);
        model[i] *= glm::translate(glm::mat4(1.0), glm::vec3(lvl.bricks[i].pos.x, lvl.bricks[i].pos.y, 0));
        model[i] *= glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 0, 1.0));
        model[i] *= glm::scale(glm::mat4(1.0), glm::vec3(lvl.bricks[i].size.x, lvl.bricks[i].size.y, 1));
    }

    glActiveTexture(GL_TEXTURE0);
    lvl.image->bind();

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_i);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(model), model);

    /*static GLfloat tc[20 * 20][8] = {};

    for (int i = 0; i < 20 * 20; i++) {
        calcTextureCoords(lvl.bricks[i], &tc[i]);
    }

    static GLfloat tcf[20 * 20 * 8] = {};

    for (int i = 0; i < 20 * 20; i++) {
        for (int j = 0; j < 8; j++) {
            tcf[i * 8 + j] = tc[i][j];
        }
    }*/

    glBindBuffer(GL_ARRAY_BUFFER, vbo_tc);
    glBufferData(GL_ARRAY_BUFFER, sizeof(n_tc), n_tc, GL_STATIC_DRAW);
    //glVertexAttribPointer(1, 8, GL_float, GL_FALSE, 8 * sizeof(GLfloat), NULL);
    //glVertexAttribDivisor(1, 1);

    glDrawElementsInstanced(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0, 20*20);
    glBindVertexArray(0);
}