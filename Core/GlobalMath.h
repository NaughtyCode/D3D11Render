#ifndef GLOBALMATH_H
#define GLOBALMATH_H

#if _MSC_VER > 1000
# pragma once
#endif

struct TVector
{
public:
    FLOAT x, y, z, w;
    
    FORCEINLINE static TVector cross(const TVector& u, const TVector& v)
    {
        return TVector(u.y*v.z-v.y*u.z, u.z*v.x-v.z*u.x, u.x*v.y-v.x*u.y, 0.0f);
    }
    
    FORCEINLINE static FLOAT length(const TVector& u)
    {
        return sqrt(u.x*u.x + u.y*u.y + u.z*u.z + u.w*u.w);
    }
    
    FORCEINLINE static TVector normalize(const TVector& u)
    {
        FLOAT invmag = 1.0f/(length(u) + FLT_EPSILON);
        return TVector(u.x * invmag, u.y * invmag, u.z * invmag, u.w * invmag);
    }
    
    FORCEINLINE TVector():x(0.0f),y(0.0f),z(0.0f),w(0.0f)
    {
        
    }
    
    FORCEINLINE TVector(FLOAT x, FLOAT y, FLOAT z, FLOAT w) : x(x), y(y), z(z), w(w)
    {
        
    }
    
    friend TVector operator +(const TVector& u, const TVector& v);
    friend TVector operator -(const TVector& u, const TVector& v);
    friend TVector operator *(const TVector& u, const TVector& v);
    friend TVector operator /(const TVector& u, const TVector& v);
};

FORCEINLINE TVector operator +(const TVector& u, const TVector& v)
{
    return TVector(u.x+v.x, u.y+v.y, u.z+v.z, u.w+v.w);
}

FORCEINLINE TVector operator -(const TVector& u, const TVector& v)
{
    return TVector(u.x-v.x, u.y-v.y, u.z-v.z, u.w-v.w);
}

FORCEINLINE TVector operator *(const TVector& u, const TVector& v)
{
    return TVector(u.x*v.x, u.y*v.y, u.z*v.z, u.w*v.w);
}

FORCEINLINE TVector operator /(const TVector& u, const TVector& v)
{
    return TVector(u.x/v.x, u.y/v.y, u.z/v.z, u.w/v.w);
}

struct TMatrix
{
    FLOAT m[4][4];
    
    FORCEINLINE TMatrix()
    {
        memset(&m[0][0],0,sizeof(FLOAT)*16);
    }
    
    FORCEINLINE TMatrix& Identity()
    {
        memset(&m[0][0],0.0f,sizeof(FLOAT)*16);
        m[0][0]=1.0f;
        m[1][1]=1.0f;
        m[2][2]=1.0f;
        m[3][3]=1.0f;
        return (*this);
    }
    
};

#endif
