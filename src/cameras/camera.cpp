//
// Created by sohaibalam on 01/04/24.
//

#include "camera.h"


float camera::generateRayDifferential(const CameraSample &sample, RayDifferential *rd) const {
    float wt = generateRay(sample, rd);
    if (wt == 0) return 0;

    float eps = 0.002f;
    CameraSample sshift = sample;
    sshift.pFilm.x += eps;
    Ray rx;
    float wtx = generateRay(sshift, &rx);
    if (wtx == 0) return 0;
    rd->rxOrigin = rx.o;
    rd->rxDirection = rx.d;

    sshift.pFilm.x = sample.pFilm.x;
    sshift.pFilm.y += eps;
    Ray ry;
    float wty = generateRay(sshift, &ry);
    if (wty == 0) return 0;
    rd->ryOrigin = ry.o;
    rd->ryDirection = ry.d;
    rd->hasDifferentials = true;
    return wt;
}
