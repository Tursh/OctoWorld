/*
 * World.cpp
 *
 * Created by tursh on 10/14/20.
*/

#include <Loader/Meshes/MeshBuilder.h>
#include <glm/gtx/string_cast.hpp>
#include <Loader/RessourceManager.h>
#include "World/World.h"

namespace OW
{

    using namespace CGE;

    static const glm::vec3 SQUARE_VERTICES[] =
            {
                    {-1.0f, -1.0f, 1.5f}, //0
                    {-1.0f, 1.0f,  1.5f}, //1
                    {1.0f,  1.0f,  1.5f}, //2
                    {1.0f,  -1.0f, 1.5f} //3
            };

    static const glm::vec2 SQUARE_TEXTURE_COORDS[] =
            {
                    {0.0f, 0.0f}, //0
                    {0.0f, 1.0f}, //1
                    {1.0f, 1.0f}, //2
                    {1.0f, 0.0f} //3
            };

    static const u_int SQUARE_INDICES[] =
            {
                    0, 1, 2, 2, 3, 0
            };

    World::World()
            : player_(nullptr, camera_)
    {
        Loader::MeshBuilder builder;

        glm::vec3 vertices[4];
        //Make the side faces
        {
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), (float) M_PI_2, glm::vec3(0, 1, 0));


            std::copy(SQUARE_VERTICES, SQUARE_VERTICES + 4, vertices);

            for (int i = 0; i < 4; ++i)
            {
                builder.loadVertices(vertices, SQUARE_TEXTURE_COORDS, nullptr, 4);
                builder.loadIndices({SQUARE_INDICES, 6});
                builder.incrementIndices(4 * i, i * 6);

                for (auto &vertex : vertices)
                    vertex = (glm::vec3) (glm::vec4(vertex.x, vertex.y, vertex.z, 1) * rotationMatrix);
            }
        }

        //Make the top and bottom face
        {
            for (int i = 0; i < 2; ++i)
            {
                glm::mat4 xRotationMatrix = glm::rotate(glm::mat4(1), (float) M_PI_2 * (i % 2 == 0 ? -1.0f : 1.0f),
                                                        glm::vec3(1, 0, 0));

                std::copy(SQUARE_VERTICES, SQUARE_VERTICES + 4, vertices);

                for (auto &vertex : vertices)
                    vertex = (glm::vec3) (glm::vec4(vertex.x, vertex.y, vertex.z, 1) * xRotationMatrix);

                u_int startVertex = builder.vertexCount();
                u_int startIndex = builder.indexCount();

                builder.loadVertices(vertices, SQUARE_TEXTURE_COORDS, nullptr, 4);
                builder.loadIndices({SQUARE_INDICES, 6});
                builder.incrementIndices(startVertex, startIndex);
            }
        }

        //Make the rest of the between rectangles and triangles
        {
            uint indices[] = {
                    //Between sides
                    0, 1, 6, 6, 7, 0,
                    4, 5, 10, 10, 11, 4,
                    8, 9, 14, 14, 15, 8,
                    12, 13, 2, 2, 3, 12,

                    //Between top and sides
                    3, 0, 18, 18, 0, 17,
                    4, 7, 16, 16, 7, 17,
                    11, 8, 16, 16, 8, 19,
                    15, 12, 19, 19, 12, 18,

                    //Between bottom and sides
                    2, 1, 23, 23, 1, 20,
                    6, 5, 20, 20, 5, 21,
                    10, 9, 21, 21, 9, 22,
                    14, 13, 22, 22, 13, 23,

                    //Top triangles
                    1, 6, 20,
                    2, 13, 23,
                    14, 22, 9,
                    10, 5, 21,

                    //Bottom Triangles
                    3, 18, 12,
                    15, 19, 8,
                    11, 16, 4,
                    0, 7, 17
            };
            builder.loadIndices({indices, 96});
        }

        Loader::SharedTexture tex = Loader::resManager::getTexture(1);
        mesh_ = new Loader::TexturedMesh(builder.toSharedMesh(), tex);
    }

    void World::tick()
    {
        player_.move(0.025f);
        player_.update();
        camera_.followPlayer(&player_);
    }

    void World::render()
    {
        glEnable(GL_DEPTH_TEST);
        shader_.start();
        shader_.loadMatrix(Shader::VIEW, camera_.toViewMatrix());

        mesh_->render();

        shader_.stop();
    }

}