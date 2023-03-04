#include "CrispPCH.h"
#include "SceneSerializer.h"

#include "Crisp.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

namespace YAML {
	template<>
	struct convert<glm::vec3> {
		static Node encode(const glm::vec3& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs) {
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4> {
		static Node encode(const glm::vec4& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs) {
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::quat> {
		static Node encode(const glm::quat& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::quat& rhs) {
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace Crisp {
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& value) {
		out << YAML::Flow;
		out << YAML::BeginSeq << value.x << value.y << value.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& value) {
		out << YAML::Flow;
		out << YAML::BeginSeq << value.x << value.y << value.z << value.w << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::quat& value) {
		out << YAML::Flow;
		out << YAML::BeginSeq << value.x << value.y << value.z << value.w << YAML::EndSeq;
		return out;
	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene) : scene(scene) {}

	static void SerializeEntity(YAML::Emitter& out, Entity entity) {
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << "123812398123"; // TODO: Put entity id here when got UIDs setup
		
		if (entity.HasComponent<EntityProperties>()) {
			out << YAML::Key << "EntityProperties";
			out << YAML::BeginMap;

			auto& properties = entity.GetComponent<EntityProperties>();
			out << YAML::Key << "Name" << YAML::Value << properties.name;
			out << YAML::Key << "Tag" << YAML::Value << properties.tag;

			out << YAML::EndMap;
		}

		if (entity.HasComponent<Transform>()) {
			out << YAML::Key << "Transform";
			out << YAML::BeginMap;

			auto& transform = entity.GetComponent<Transform>();
			out << YAML::Key << "Position" << YAML::Value << transform.GetPosition();
			out << YAML::Key << "Rotation" << YAML::Value << transform.GetRotation();
			out << YAML::Key << "Scale" << YAML::Value << transform.GetScale();

			out << YAML::EndMap;
		}

		if (entity.HasComponent<Camera>()) {
			out << YAML::Key << "Camera";
			out << YAML::BeginMap;

			auto& camera = entity.GetComponent<Camera>();
			out << YAML::Key << "IsMainCamera" << YAML::Value << camera.IsEqual(*camera.GetMainCamera());
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
			out << YAML::Key << "Width" << YAML::Value << camera.GetCameraWidth();
			out << YAML::Key << "Height" << YAML::Value << camera.GetCameraHeight();

			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNearPlane" << YAML::Value << camera.GetOrthographicNearPlane();
			out << YAML::Key << "OrthographicFarPlane" << YAML::Value << camera.GetOrthographicFarPlane();
			
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveFOV();
			out << YAML::Key << "PerspectiveNearPlane" << YAML::Value << camera.GetPerspectiveNearPlane();
			out << YAML::Key << "PerspectiveFarPlane" << YAML::Value << camera.GetPerspectiveFarPlane();

			out << YAML::EndMap;
		}

		if (entity.HasComponent<SpriteRenderer>()) {
			out << YAML::Key << "SpriteRenderer";
			out << YAML::BeginMap;

			auto& sprite = entity.GetComponent<SpriteRenderer>();
			out << YAML::Key << "Color" << YAML::Value << sprite.color;
			
			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	void SceneSerializer::Serialize(const std::string& filepath) {
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		scene->registry.each([&](auto entityID) {
			Entity entity = { entityID, scene.get() };
			if (!entity)
				return;

			SerializeEntity(out, entity);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	void SceneSerializer::SerializeBinary(const std::string& filepath) {
		CRISP_CORE_ASSERT(false, "Not Implemented");
	}

	bool SceneSerializer::Deserialize(const std::string& filepath) {
		std::ifstream stream(filepath);
		std::stringstream stringStream;
		stringStream << stream.rdbuf();

		YAML::Node data = YAML::Load(stringStream.str());
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();
		CRISP_CORE_TRACE("Deserilaizing scene '{0}'", sceneName);

		auto entities = data["Entities"];
		if (entities) {
			for (auto entity : entities) {
				// ENTITY PROPERTIES
				uint64_t uuid = entity["Entity"].as<uint64_t>();

				std::string name;
				std::string tag;
				auto properties = entity["EntityProperties"];
				if (properties) {
					name = properties["Name"].as<std::string>();
					tag = properties["Tag"].as<std::string>();
				}

				CRISP_CORE_TRACE("Deserialized entity {0} with name {1} and tag {2}", uuid, name, tag);

				Entity deserializedEntity = scene->CreateEntity(name, tag);

				auto transform = entity["Transform"];
				if (transform) {
					// Assumed transform component is present as all entities have a transform
					auto& component = deserializedEntity.GetComponent<Transform>();
					component.SetPosition(transform["Position"].as<glm::vec3>());
					component.SetRotation(transform["Rotation"].as<glm::quat>());
					component.SetScale(transform["Scale"].as<glm::vec3>());
				}

				auto camera = entity["Camera"];
				if (camera) {
					// Assumed transform component is present as all entities have a transform
					Camera::ProjectionType type = (Camera::ProjectionType)camera["ProjectionType"].as<int>();
					auto& component = deserializedEntity.AddComponent<Camera>(&deserializedEntity.GetComponent<Transform>());

					if (type == Camera::Perspective) {
						// Create Camera
						component.SetPerspectiveCamera(
							camera["Width"].as<float>(),
							camera["Height"].as<float>(),
							camera["PerspectiveFOV"].as<float>(),
							camera["PerspectiveNearPlane"].as<float>(),
							camera["PerspectiveFarPlane"].as<float>(),
							camera["IsMainCamera"].as<bool>()
						);

						// Setup additional data that is not currently used by this camera type
						component.SetOrthographicSize(camera["OrthographicSize"].as<float>());
						component.SetOrthographicNearPlane(camera["OrthographicNearPlane"].as<float>());
						component.SetOrthographicFarPlane(camera["OrthographicFarPlane"].as<float>());
					} else {
						component.SetOrthographicCamera(
							camera["Width"].as<float>(),
							camera["Height"].as<float>(),
							camera["OrthographicSize"].as<float>(),
							camera["OrthographicNearPlane"].as<float>(),
							camera["OrthographicFarPlane"].as<float>(),
							camera["IsMainCamera"].as<bool>()
						);

						// Setup additional data that is not currently used by this camera type
						component.SetPerspectiveFOV(camera["PerspectiveFOV"].as<float>());
						component.SetPerspectiveNearPlane(camera["PerspectiveNearPlane"].as<float>());
						component.SetPerspectiveFarPlane(camera["PerspectiveFarPlane"].as<float>());
					}
				}

				auto sprite = entity["SpriteRenderer"];
				if (sprite) {
					auto& component = deserializedEntity.AddComponent<SpriteRenderer>();
					component.color = sprite["Color"].as<glm::vec4>();
				}
			}
		}

		return true;
	}

	bool SceneSerializer::DeserializeBinary(const std::string& filepath) {
		CRISP_CORE_ASSERT(false, "Not Implemented");
		return false;
	}
}