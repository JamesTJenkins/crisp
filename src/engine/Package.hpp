#pragma once

namespace Crisp::Core {
    class Package {
    public:
        virtual ~Package() {};

        virtual int GetPackageID() = 0;
        virtual int GetFeatureIDs() = 0;
    };
}