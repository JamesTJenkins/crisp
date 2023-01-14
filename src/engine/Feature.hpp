#pragma once

namespace Crisp::Core {
    class Feature {
    public:
        virtual ~Feature() {}

        virtual void Cleanup() = 0;
        virtual int GetFeatureID() = 0;
    };
}