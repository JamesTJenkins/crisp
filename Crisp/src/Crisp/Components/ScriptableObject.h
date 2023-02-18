#pragma once
#include "Crisp/Scene/Entity.h"

namespace Crisp {
	class ScriptableEntity {
	public:
		virtual ~ScriptableEntity() {}

		template<typename T>
		T& GetComponent() { return entity.GetComponent<T>(); }
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate() {}
	private:
		Entity entity;
		friend class Scene;
	};

	class NativeScript {
	public:
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity*(*InstantiateScript)();
		void (*DestroyScript)(NativeScript*);

		template<typename T>
		void Bind() {
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScript* nativeScript) { delete nativeScript->Instance; nativeScript->Instance = nullptr; };
		}
	};
}