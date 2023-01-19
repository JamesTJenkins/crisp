#pragma once
#include <entt.hpp>

// Singleton setup as there should never be more than 1 as well as being more easily accessable
// Abuse entt for now

namespace Crisp::Core {
    class FeatureManager {
       public:
        static FeatureManager& Get() {
            static FeatureManager featureManager;
            return featureManager;
        }

        template<typename Type>
        Type* AddFeature() {
            // Check if already exists and if so returns it
            if (registry.view<Type>().size() > 0)
                return GetFeature<Type>();
            // Create new entity and assign our feature to it
            return &registry.emplace<Type>(registry.create());
        }

        template<typename Type>
        Type* GetFeature() {
            // If entity with desired type found return
            auto view = registry.view<Type>();
            for (auto entity : view)
                return registry.try_get<Type>(entity);
            // Failed
            return nullptr;
        }

        template<typename Type>
        void RemoveFeature() {
            auto view = registry.view<Type>();
            registry.destroy(view.begin(), view.end());
        }
        private:
        FeatureManager();
        ~FeatureManager();

        entt::registry registry;
    };
}  // namespace Crisp::Core