// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  9/10/2023

#include "camera.h"
#include "const.h"

Camera::Camera(float aspect) {
    view = glm::lookAt(CAMERA_POS, CAMERA_TARGET, CAMERA_UP);
    projection = glm::perspective(PROJECTION_FOV, aspect, PROJECTION_NEAR, PROJECTION_FAR);
}
