/*
*   Initializes volk header
*/

#pragma once
#define VOLK_IMPLEMENTATION
#include "volk.h"

/*
*   When using volk you are meant to use volk header instead of vulkan
*   this define is incase vulkan.h is referenced to stop any naming conflicts
*/

#define VK_NO_PROTOTYPES