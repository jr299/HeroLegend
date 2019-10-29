#ifndef GEOMETRY_H_
#define GEOMETRY_H_

namespace gamerize
{
  //Vector2

  class Vector2
  {
  public:
    //Constructors
    Vector2() : x(0.0f), y(0.0f){}
    Vector2(float _x, float _y) : x(_x), y(_y) {}
    Vector2(float * pArg) : x(pArg[0]), y(pArg[1]) {}

    //Vector's operations
    float Length();
    Vector2 & Normalize();
	Vector2  Vector2::NormalizeM();
    Vector2 operator + (const Vector2 & vector);
    Vector2 & operator += (const Vector2 & vector);
    Vector2 operator - ();
    Vector2 operator - (const Vector2 & vector);
    Vector2 & operator -= (const Vector2 & vector);
    Vector2 operator * (float k);
    Vector2 & operator *= (float k);
    Vector2 operator / (float k);
    Vector2 & operator /= (float k);
    Vector2 Modulate(const Vector2 & vector);
    float Dot(const Vector2 & vector);
	void Set(float x, float y);
    //access to elements
    float operator [] (unsigned int idx);

    //data members
    float x;
    float y;
  };

  //Vector3

  class Vector3
  {
  public:
    //Constructors
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(float * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]) {}

    //Vector's operations
    float Length();
    Vector3 & Normalize();
    Vector3 operator + (const Vector3 & vector);
    Vector3 & operator += (const Vector3 & vector);
    Vector3 operator - ();
    Vector3 operator - (const Vector3 & vector);
    Vector3 & operator -= (const Vector3 & vector);
    Vector3 operator * (float k);
    Vector3 & operator *= (float k);
    Vector3 operator / (float k);
    Vector3 & operator /= (float k);
    Vector3 & operator = (const Vector3 & vector);
    Vector3 Modulate(const Vector3 & vector);
    float Dot(const Vector3 & vector);
    Vector3 Cross(const Vector3 & vector);

    //access to elements
    float operator [] (unsigned int idx);

    // data members
    float x;
    float y;
    float z;
  };

  //Vector4

  class Matrix;

  class Vector4
  {
  public:
    //Constructors
    Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vector4(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(1.0f) {}
    Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    Vector4(float * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]), w(pArg[3]) {}
    Vector4(const Vector3 & vector) : x(vector.x), y(vector.y), z(vector.z), w(1.0f){}
    Vector4(const Vector3 & vector, float _w) : x(vector.x), y(vector.y), z(vector.z), w(_w) {}

    //Vector's operations
    float Length();
    Vector4 & Normalize();
    Vector4 operator + (const Vector4 & vector);
    Vector4 & operator += (const Vector4 & vector);
    Vector4 operator - ();
    Vector4 operator - (const Vector4 & vector);
    Vector4 & operator -= (const Vector4 & vector);
    Vector4 operator * (float k);
    Vector4 & operator *= (float k);
    Vector4 operator / (float k);
    Vector4 & operator /= (float k);
    Vector4 Modulate(const Vector4 & vector);
    float Dot(const Vector4 & vector);

    //matrix multiplication
    Vector4 operator * (const Matrix & m );

    //access to elements
    float operator [] (unsigned int idx);

    //data members
    float x;
    float y;
    float z;
    float w;
  };

  //Matrix 4 X 4


  class Matrix
  {
  public:
    //constructors
    Matrix() {}
    Matrix(float val);

    // Matrix operations
    Matrix & SetZero();
    Matrix & SetIdentity();

    Matrix & SetRotationX(float angle);
    Matrix & SetRotationY(float angle);
    Matrix & SetRotationZ(float angle);
    Matrix & SetRotationAngleAxis( float angle, float x, float y, float z );

    Matrix & SetScale(float scale);
    Matrix & SetScale(float scaleX, float scaleY, float scaleZ);
    Matrix & SetScale(float * pScale);
    Matrix & SetScale(const Vector3 &scaleVec);

    Matrix & SetTranslation(float x, float y, float z);
    Matrix & SetTranslation(float *pTrans);
    Matrix & SetTranslation(const Vector3 &vec);

    Matrix & SetPerspective(float fovY, float aspect, float nearPlane, float farPlane);

    Matrix Transpose();

    Matrix operator + (const Matrix & mat);
    Matrix & operator += (const Matrix & mat);
    Matrix operator - (const Matrix & mat);
    Matrix &operator -= (const Matrix & mat);

    Matrix operator * (const Matrix & mat);
    Matrix operator * (float k);
    Matrix & operator *= (float k);

    Vector4 operator * (const Vector4 & vec);

    //data members
    float m[4][4];
  };

};

#endif