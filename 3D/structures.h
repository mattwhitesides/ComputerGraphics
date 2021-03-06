#ifndef STRUCTURES
#define STRUCTURES

typedef struct _translate {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Translate;

typedef struct _scale {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Scale;

typedef struct _rotate {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Rotate;

typedef struct _camera {
    GLdouble fov;
    GLdouble zNear;
    GLdouble zFar;
    GLdouble aspect;
} Camera;

#endif // STRUCTURES

