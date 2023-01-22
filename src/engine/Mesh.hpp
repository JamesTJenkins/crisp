#pragma once
#include <vector>
#include <glm.hpp>
#include <gtx/hash.hpp>

namespace Crisp::Core {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 texcoord0;
        glm::vec2 texcoord1;

        bool operator==(const Vertex& other) const {
            return position == other.position && normal == other.normal && color == other.color && texcoord0 == other.texcoord0 && texcoord1 == other.texcoord1;
        }

        Vertex(glm::vec3 _position, glm::vec3 _normal, glm::vec3 _color, glm::vec2 _texcoord0, glm::vec2 _texcoord1) {
            position = _position;
            normal = _normal;
            color = _color;
            texcoord0 = _texcoord0;
            texcoord1 = _texcoord1;
        }
    };

    struct Mesh {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
    };

    class Primitive {
    public:
        static Mesh CreateQuad() {
            Mesh quad;
            quad.vertices.push_back(Vertex(glm::vec3(-1,0,1), glm::vec3(-0,1,-0), glm::vec3(1,1,1), glm::vec2(0,0), glm::vec2(0,0)));
            quad.vertices.push_back(Vertex(glm::vec3(1,0,1), glm::vec3(-0,1,-0), glm::vec3(1,1,1), glm::vec2(1,0), glm::vec2(1,0)));
            quad.vertices.push_back(Vertex(glm::vec3(-1,0,-1), glm::vec3(-0,1,-0), glm::vec3(1,1,1), glm::vec2(0,1), glm::vec2(0,1)));
            quad.vertices.push_back(Vertex(glm::vec3(1,0,-1), glm::vec3(-0,1,-0), glm::vec3(1,1,1), glm::vec2(1,1), glm::vec2(1,1)));
            
            quad.indices.push_back(0);
            quad.indices.push_back(1);
            quad.indices.push_back(2);
        
            quad.indices.push_back(1);
            quad.indices.push_back(3);
            quad.indices.push_back(2);

            return quad;
        }
    };
}  // namespace Crisp::Core

namespace std {
    template<> struct hash<Crisp::Core::Vertex> {
        size_t operator()(Crisp::Core::Vertex const& vertex) const {
            return (
                (hash<glm::vec3>()(vertex.position) ^
                (hash<glm::vec3>()(vertex.normal) << 1 ^
                (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
                (hash<glm::vec2>()(vertex.texcoord0) << 1) ^
                (hash<glm::vec2>()(vertex.texcoord1) << 1)
            );
        }
    };
}