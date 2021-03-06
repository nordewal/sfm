// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "triangulationtab.h"
#include "ui_triangulationtab.h"

TriangulationTab::TriangulationTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TriangulationTab),
    sfmapp(SFMApp::getInstance()) {
  ui->setupUi(this);
}

TriangulationTab::~TriangulationTab() {
  delete ui;
}

void TriangulationTab::on_runInitialReconstruction_clicked() {
  sfmapp->reconstructInitialImagePair();
  updateViewer();
}

void TriangulationTab::on_runNextReconstruction_clicked() {
  sfmapp->reconstructNextImagePair();
  updateViewer();
}

void TriangulationTab::showHelp() {
  ui->qGLViewerWidget->help();
}

void TriangulationTab::updateViewer() {
  vector <shared_ptr<ImageCamera>> cameras;

  for (auto image : *sfmapp->images())
    if (image->camera()->extrinsic()->data != NULL)
      cameras.push_back(image->camera());

  ui->qGLViewerWidget->update(*sfmapp->object_points(), cameras);
}

void TriangulationTab::on_removeLastCamera_clicked() {
  sfmapp->removeLastCamera();
  updateViewer();
}

void TriangulationTab::on_doBundleAdjustment_clicked() {
  sfmapp->doBundleAdjustment();
  updateViewer();
}

void TriangulationTab::on_centerPivot_clicked() {
  ui->qGLViewerWidget->setObjectCenterPivot();
}

void TriangulationTab::on_denseReconstruct_clicked() {

}

