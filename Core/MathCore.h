#ifndef MATHCORE_H
#define MATHCORE_H

#if _MSC_VER > 1000
# pragma once
#endif

typedef struct TMatrixData
{
	FLOAT m11, m12, m13, m14;
	FLOAT m21, m22, m23, m24;
	FLOAT m31, m32, m33, m34;
	FLOAT m41, m42, m43, m44;
}TMatrixData;

class TVector 
{
public:
    FLOAT X,Y,Z;

	TVector(): X(0.0f), Y(0.0f), Z(0.0f)
	{

	}

    explicit  TVector(FLOAT scale):X(scale),Y(scale),Z(scale)
    {
        
    }
    
     TVector( FLOAT x, FLOAT y, FLOAT z ):X(x),Y(y),Z(z)
    {
        
    }
    
     TVector operator^( const TVector& V ) const
    {
        return TVector
        (
            Y * V.Z - Z * V.Y,
            Z * V.X - X * V.Z,
            X * V.Y - Y * V.X
        );
    }
    
     FLOAT operator|( const TVector& V ) const
    {
        return X*V.X + Y*V.Y + Z*V.Z;
    }
    
     TVector operator+( const TVector& V ) const
    {
        return TVector( X + V.X, Y + V.Y, Z + V.Z );
    }
    
     TVector operator-( const TVector& V ) const
    {
        return TVector( X - V.X, Y - V.Y, Z - V.Z );
    }
    
     TVector operator-( FLOAT Bias ) const
    {
        return TVector( X - Bias, Y - Bias, Z - Bias );
    }
    
     TVector operator+( FLOAT Bias ) const
    {
        return TVector( X + Bias, Y + Bias, Z + Bias );
    }
    
     TVector operator*( FLOAT Scale ) const
    {
        return TVector( X * Scale, Y * Scale, Z * Scale );
    }
    
    TVector operator/( FLOAT Scale ) const
    {
        const FLOAT RScale = 1.f/Scale;
        return TVector( X * RScale, Y * RScale, Z * RScale );
    }
    
     TVector operator*( const TVector& V ) const
    {
        return TVector( X * V.X, Y * V.Y, Z * V.Z );
    }
    
     TVector operator/( const TVector& V ) const
    {
        return TVector( X / V.X, Y / V.Y, Z / V.Z );
    }
    
    BOOL operator==( const TVector& V ) const
    {
        return X==V.X && Y==V.Y && Z==V.Z;
    }
    
    BOOL operator!=( const TVector& V ) const
    {
        return X!=V.X || Y!=V.Y || Z!=V.Z;
    }
    
    BOOL Equals(const TVector& V, FLOAT Tolerance=0.005f) const
    {
        return abs(X-V.X) < Tolerance && abs(Y-V.Y) < Tolerance && abs(Z-V.Z) < Tolerance;
    }
    
    BOOL AllComponentsEqual(FLOAT Tolerance=0.005f) const
    {
        return abs( X - Y ) < Tolerance && abs( X - Z ) < Tolerance && abs( Y - Z ) < Tolerance;
    }
    
     TVector operator-() const
    {
        return TVector( -X, -Y, -Z );
    }
    
     TVector operator+=( const TVector& V )
    {
        X += V.X; Y += V.Y; Z += V.Z;
        return *this;
    }
    
     TVector operator-=( const TVector& V )
    {
        X -= V.X; Y -= V.Y; Z -= V.Z;
        return *this;
    }
    
     TVector operator*=( FLOAT Scale )
    {
        X *= Scale; Y *= Scale; Z *= Scale;
        return *this;
    }
    
    TVector operator/=( FLOAT V )
    {
        const FLOAT RV = 1.f/V;
        X *= RV; Y *= RV; Z *= RV;
        return *this;
    }
    
    TVector operator*=( const TVector& V )
    {
        X *= V.X; Y *= V.Y; Z *= V.Z;
        return *this;
    }
    
    TVector operator/=( const TVector& V )
    {
            X /= V.X; Y /= V.Y; Z /= V.Z;
            return *this;
    }
    
    FLOAT& operator[]( INT i )
    {
        assert(i>-1);
        assert(i<3);
        if( i == 0 ) return X;
        else if( i == 1) return Y;
        else return Z;
    }
    
    FLOAT operator[]( INT i )const
    {
            assert(i>-1);
            assert(i<3);
            if( i == 0 ) return X;
            else if( i == 1) return Y;
            else return Z;
    }
    
    void Set( FLOAT InX, FLOAT InY, FLOAT InZ )
    {
        X = InX;
        Y = InY;
        Z = InZ;
    }
    
    FLOAT GetMax() const
    {
        return max(max(X,Y),Z);
    }
    
    FLOAT GetabsMax() const
    {
        return max(max(abs(X),abs(Y)),abs(Z));
    }
    
    FLOAT GetMin() const
    {
        return min(min(X,Y),Z);
    }
    
    FLOAT Size() const
    {
        return sqrt( X*X + Y*Y + Z*Z );
    }
    
    FLOAT SizeSquared() const
    {
        return X*X + Y*Y + Z*Z;
    }
    
    FLOAT Size2D() const 
    {
        return sqrt( X*X + Y*Y );
    }
    
    FLOAT SizeSquared2D() const 
    {
        return X*X + Y*Y;
    }

     FLOAT Distance(const TVector& Dest) const
    {
        return sqrt((Dest.X-X)*(Dest.X-X) + (Dest.Y-Y)*(Dest.Y-Y) + (Dest.Z-Z)*(Dest.Z-Z));
    }
    
     FLOAT DistanceSquared(const TVector& Dest) const
    {
        return (Dest.X-X)*(Dest.X-X) + (Dest.Y-Y)*(Dest.Y-Y) + (Dest.Z-Z)*(Dest.Z-Z);
    }

    int IsNearlyZero(FLOAT Tolerance=0.005f) const
    {
        return abs(X)<Tolerance && abs(Y)<Tolerance && abs(Z)<Tolerance;
    }
    
    BOOL IsZero() const
    {
        return X==0.f && Y==0.f && Z==0.f;
    }
    
    BOOL Normalize(FLOAT Tolerance=0.005f)
    {
        const FLOAT SquareSum = X*X + Y*Y + Z*Z;
        if( SquareSum > Tolerance )
        {
            const FLOAT Scale = 1.0f/sqrt(SquareSum);
            X *= Scale; Y *= Scale; Z *= Scale;
            return TRUE;
        }
        return FALSE;
    }
    
    BOOL IsNormalized() const
    {
        return (abs(1.f - SizeSquared()) <= 0.01f);
    }
    
    void ToDirectionAndLength(TVector &OutDir, FLOAT &OutLength)
    {
        OutLength = Size();
        if (OutLength > 0.0001f)
        {
            FLOAT OneOverLength = 1.0f/OutLength;
            OutDir = TVector(X*OneOverLength, Y*OneOverLength,
            Z*OneOverLength);
        }
        else
        {
            OutDir = TVector(0.0f, 0.0f, 0.0f);
        }
    }
    
    TVector Projection() const
    {
        const FLOAT RZ = 1.f/Z;
        return TVector( X*RZ, Y*RZ, 1 );
    }
    
     TVector UnsafeNormal() const
    {
        const FLOAT Scale = 1.0f/sqrt(X*X+Y*Y+Z*Z);
        return TVector( X*Scale, Y*Scale, Z*Scale );
    }
    
    FLOAT& Component( INT Index )
    {
            return (&X)[Index];
    }
    
    BOOL IsUniform(FLOAT Tolerance=0.005f) const
    {
            return (abs(X-Y) < Tolerance) && (abs(Y-Z) < Tolerance);
    }
    
    TVector MirrorByVector( const TVector& MirrorNormal ) const
    {
        return *this - MirrorNormal * (2.f * (*this | MirrorNormal));
    }
    
     TVector SafeNormal(FLOAT Tolerance=0.0001f) const
    {
        const FLOAT SquareSum = X*X + Y*Y + Z*Z;
        if( SquareSum == 1.f )
        {
            return *this;
        }		
        else if( SquareSum < Tolerance )
        {
            return TVector(0.f);
        }
        const FLOAT Scale = 1.0f/sqrt(SquareSum);
        return TVector(X*Scale, Y*Scale, Z*Scale);
    }
    
     TVector SafeNormal2D(FLOAT Tolerance=0.0001f) const
    {
        const FLOAT SquareSum = X*X + Y*Y;
        
        if( SquareSum == 1.f )
        {
            if( Z == 0.f )
            {
                return *this;
            }
            else
            {
                return TVector(X, Y, 0.f);
            }
        }
        else if( SquareSum < Tolerance )
        {
            return TVector(0.f);
        }
        const FLOAT Scale = 1.0f/sqrt(SquareSum);
        return TVector(X*Scale, Y*Scale, 0.f);
    }
    
     FLOAT Dot2d(TVector B)
    {
        TVector A(*this);
        A.Z = 0.0f;
        B.Z = 0.0f;
        A.Normalize();
        B.Normalize();
        return A | B;
    }
    
     TVector ProjectOnTo( const TVector& A ) const 
    { 
        return (A * ((*this | A) / (A | A))); 
    }
    
    inline BOOL IsUnit(FLOAT LengthSquaredTolerance = 0.005f) const
    {
        return abs(1.0f - SizeSquared()) < LengthSquaredTolerance;
    }
};

#endif




