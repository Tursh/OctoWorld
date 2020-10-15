/*
 * World.h
 *
 * Created by tursh on 10/14/20.
*/

#pragma once


#include <Loader/Meshes/Mesh.h>
#include <Shader/MeshShader/BasicShader.h>
#include <View/Camera.h>
#include <Entities/Player.h>

namespace OW
{

    class World
    {
        CGE::Shader::BasicShader shader_;

        CGE::Loader::TexturedMesh *mesh_;

        CGE::Entities::Player player_;

        CGE::View::Camera camera_;

    public:
        World();

        void tick();

        void render();
    };

}