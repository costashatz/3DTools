#include <gtest/gtest.h>
#include <3DTools/Vector3D.hpp>
#include <3DTools/Matrix3D.hpp>
using namespace Tools3D;

 TEST(Vector3DTest, DefaultConstructor) {
     Vector3D<double> d;
     EXPECT_EQ(d.X(), 0.0);
     EXPECT_EQ(d.Y(), 0.0);
     EXPECT_EQ(d.Z(), 0.0);
 }

 TEST(Vector3DTest, Constructor) {
     Vector3Dd d(3.0, 4.0, 5.0);
     EXPECT_EQ(d.X(), 3.0);
     EXPECT_EQ(d.Y(), 4.0);
     EXPECT_EQ(d.Z(), 5.0);
 }

 TEST(Vector3DTest, CopyConstructor) {
     Vector3D<double> x(1.0, 2.0, 3.0);
     Vector3D<double> d(x);
     EXPECT_EQ(d.X(), 1.0);
     EXPECT_EQ(d.Y(), 2.0);
     EXPECT_EQ(d.Z(), 3.0);
 }

 TEST(Vector3DTest, Zero) {
     Vector3D<double> d(3.0, 4.0, 9.0);
     d.Zero();
     EXPECT_EQ(d.X(), 0.0);
     EXPECT_EQ(d.Y(), 0.0);
     EXPECT_EQ(d.Z(), 0.0);
 }

 TEST(Vector3DTest, Zero2) {
     Vector3D<double> d(3.0, 4.0, 12);
     d.Zero();
     EXPECT_EQ(d.IsZero(), true);
 }

 TEST(Vector3DTest, Normalize) {
     Vector3D<double> d(3.0, 4.0, 2.0);
     d.Normalize();
     EXPECT_EQ(d.X(), 3.0/sqrt(29.0));
     EXPECT_EQ(d.Y(), 4.0/sqrt(29.0));
     EXPECT_EQ(d.Z(), 2.0/sqrt(29.0));
 }

 TEST(Matrix3DTest, DefaultConstructor) {
     Matrix3D<double> tmp;
     for(int i=0;i<4;i++) {
         for(int j=0;j<4;j++) {
             if(i==j)
                 EXPECT_EQ(tmp(i,j), 1.0);
             else
                 EXPECT_EQ(tmp(i,j), 0.0);
         }
     }
 }

 TEST(Matrix3DTest, Identity) {
     Matrix3D<double> tmp;
     Matrix3D<double> tr = tmp.Transpose();
     Matrix3D<double> inv = tmp.Inverse();
     for(int i=0;i<3;i++) {
         for(int j=0;j<3;j++) {
             EXPECT_EQ(tmp(i,j), tr(i,j));
             EXPECT_EQ(inv(i,j), tr(i,j));
         }
     }
 }

 TEST(Matrix2DTest, Multiplication) {
     Matrix3D<double> tmp;
     tmp(0,1) = 2;
     tmp(0,2) = 3;
     Matrix3D<double> tmp2;
     tmp2(1,0) = 1;
     tmp2(2,0) = 2;
     Matrix3D<double> t = tmp*tmp2;
     EXPECT_EQ(t(0,0), 9);
     EXPECT_EQ(t(0,1), 2);
     EXPECT_EQ(t(0,2), 3);
     EXPECT_EQ(t(1,0), 1);
     EXPECT_EQ(t(1,1), 1);
     EXPECT_EQ(t(1,2), 0);
     EXPECT_EQ(t(2,0), 2);
     EXPECT_EQ(t(2,1), 0);
     EXPECT_EQ(t(2,2), 1);
 }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
