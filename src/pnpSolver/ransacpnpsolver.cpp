//
// Created by marco on 22.11.15.
//

#include <opencv2/calib3d.hpp>
#include "ransacpnpsolver.h"

void RANSACPnPSolver::solve(shared_ptr<ImagePair> &image_pair, Mat &intristic_camera_paramaters) {
  Mat rotEstimate = image_pair->image1->camera()->rotation() * image_pair->rotation;
  Mat transExstimate = image_pair->image1->camera()->translation() + image_pair->translation;

  Mat rvec;
  Mat tvec;
  Mat rot;

  Rodrigues(rotEstimate, rvec);
  tvec = transExstimate;

  solvePnPRansac(image_pair->pnp_object_points, image_pair->pnp_image_points, intristic_camera_paramaters,
                 noArray(), rvec, tvec, true, 100, 2.0, 0.99, noArray(), SOLVEPNP_EPNP);

  Rodrigues(rvec, rot);
  image_pair->image2->camera()->set_rotation_translation(rot, tvec);
}