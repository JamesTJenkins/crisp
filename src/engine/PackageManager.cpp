#include "PackageManager.hpp"
#include <iostream>

namespace Crisp::Core {
    PackageManager::PackageManager() {}

    PackageManager::~PackageManager() {
        Cleanup();
    }

    void PackageManager::LoadFeature(std::shared_ptr<Feature> feature) {
        // Add to feature map
        features[(*feature).GetFeatureID()] = feature;
    }

    void PackageManager::LoadPackage(std::shared_ptr<Package> package) {
        packages[(*package).GetPackageID()] = package;
    }

    void PackageManager::Cleanup() {
        // Clear packages
        packages.clear();
        std::cout << "Unloaded all packages." << std::endl;

        // Clear features
        std::map<int, std::shared_ptr<Feature>>::iterator it;
        // Cycle backwards doing cleanup of all features
        for (it = features.begin(); it != features.end(); it++) {
            it->second.get()->Cleanup();
        }
        // Clear features
        features.clear();
        std::cout << "Unloaded all features." << std::endl;
    }
}