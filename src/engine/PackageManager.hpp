#pragma once
#include <map>
#include <memory>
#include "Feature.hpp"
#include "Package.hpp"

// Singleton setup as there should never be more than 1 as well as being more easily accessable

namespace Crisp::Core {
    class PackageManager {
    public:
        static PackageManager& Get() {
            static PackageManager packageManager;
            return packageManager;
        }
        
        void LoadFeature(std::shared_ptr<Feature> feature);
        void LoadPackage(std::shared_ptr<Package> package);
        Feature* GetFeature(int featureID);
    private:
        PackageManager();
        ~PackageManager();

        std::map<int, std::shared_ptr<Feature>> features;
        std::map<int, std::shared_ptr<Package>> packages;
        
        void Cleanup();
    };
}