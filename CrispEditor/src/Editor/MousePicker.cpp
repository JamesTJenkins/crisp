#include "MousePicker.h"

namespace Crisp {
    Entity selectedEntity = {};

    Entity Crisp::GetSelectedEntity() {
        return selectedEntity;
    }

    void SetSelectedEntity(Entity value) {
        selectedEntity = value;
    }
}