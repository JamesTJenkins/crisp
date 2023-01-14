#pragma once
#include <map>
#include <memory>
#include "Feature.hpp"
#include "Package.hpp"

namespace Crisp::Core {
    class PackageManager {
    public:
        PackageManager();
        ~PackageManager();

        void LoadFeature(std::shared_ptr<Feature> feature);
        void LoadPackage(std::shared_ptr<Package> package);
        void Cleanup();
    private:
        std::map<int, std::shared_ptr<Feature>> features;
        std::map<int, std::shared_ptr<Package>> packages;
    };
}