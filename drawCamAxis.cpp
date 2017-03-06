
  void drawCamAxis(const Eigen::Matrix3d & rot, const Eigen::Vector3d& trans, const float d)
  {
    Eigen::Vector3d o1(0,0,0);
    Eigen::Vector3d v1(d,0,0);
    Eigen::Vector3d v2(0,d,0);
    Eigen::Vector3d v3(0,0,d);

    o1 = rot * o1 + trans;//from_coordinate_system_of
    v1 = rot * v1 + trans;
    v2 = rot * v2 + trans;
    v3 = rot * v3 + trans;

    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(o1.x(),o1.y(),o1.z());
    glVertex3f(v1.x(),v1.y(),v1.z());

    glColor3f(0.0,1.0,0.0);
    glVertex3f(o1.x(),o1.y(),o1.z());
    glVertex3f(v2.x(),v2.y(),v2.z());

    glColor3f(0.0,0.0,1.0);
    glVertex3f(o1.x(),o1.y(),o1.z());
    glVertex3f(v3.x(),v3.y(),v3.z());
    glEnd();
  }