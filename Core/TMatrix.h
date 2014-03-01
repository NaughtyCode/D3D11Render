# pragma once

template<typename F>
struct TMatrix
{
	F m00,m01,m02,m03;
	F m10,m11,m12,m13;
	F m20,m21,m22,m23;
	F m30,m31,m32,m33;
	
	inline TMatrix()
	{
		
	};
	
	inline TMatrix<F>& operator = (const TMatrix<F> &m) 
	{
		m00=m.m00;	m01=m.m01;	m02=m.m02; m03=m.m03; 
		m10=m.m10;	m11=m.m11;	m12=m.m12; m13=m.m13; 
		m20=m.m20;	m21=m.m21;	m22=m.m22; m23=m.m23; 
		m30=m.m30;	m31=m.m31;	m32=m.m32; m33=m.m33; 
		return *this;
	}
	
	inline TMatrix<F>(
			F v00, F v01, F v02, F v03,
			F v10, F v11, F v12, F v13,
			F v20, F v21, F v22, F v23,
			F v30, F v31, F v32, F v33)
	{
		m00=v00;
		m01=v01;
		m02=v02;
		m03=v03;
		
		m10=v10;
		m11=v11;
		m12=v12;
		m13=v13;
		
		m20=v20;
		m21=v21;
		m22=v22;
		m23=v23;
		
		m30=v30;
		m31=v31;
		m32=v32;
		m33=v33; 
	}
	
	inline TMatrix<F>(const TMatrix<F>& m ) 
	{
		m00=m.m00;	m01=m.m01;	m02=m.m02;	m03=m.m03;	
		m10=m.m10;	m11=m.m11;	m12=m.m12;	m13=m.m13;
		m20=m.m20;	m21=m.m21;	m22=m.m22;	m23=m.m23;
		m30=m.m30;	m31=m.m31;	m32=m.m32;	m33=m.m33;
	}
	
	template<class F1> inline TMatrix<F>(const TMatrix<F1>& m ) 
	{
		m00=F(m.m00);	m01=F(m.m01);	m02=F(m.m02);	m03=F(m.m03);	
		m10=F(m.m10);	m11=F(m.m11);	m12=F(m.m12);	m13=F(m.m13);
		m20=F(m.m20);	m21=F(m.m21);	m22=F(m.m22);	m23=F(m.m23);
		m30=F(m.m30);	m31=F(m.m31);	m32=F(m.m32);	m33=F(m.m33);
	}
	
	friend	inline TMatrix<F> operator * (const TMatrix<F>& m, const FLOAT f)	
	{
		TMatrix<F> r;
		r.m00=m.m00*f; r.m01=m.m01*f; r.m02=m.m02*f; r.m03=m.m03*f; 
		r.m10=m.m10*f; r.m11=m.m11*f; r.m12=m.m12*f; r.m13=m.m13*f;
		r.m20=m.m20*f; r.m21=m.m21*f; r.m22=m.m22*f; r.m23=m.m23*f;
		r.m30=m.m30*f; r.m31=m.m31*f; r.m32=m.m32*f; r.m33=m.m33*f;
		return r;
	}
	
	friend	inline TMatrix<F> operator + (const TMatrix<F>& mm0, const TMatrix<F>& mm1)	
	{
		TMatrix<F> r;
		r.m00=mm0.m00 + mm1.m00; r.m01=mm0.m01 + mm1.m01; r.m02=mm0.m02 + mm1.m02; r.m03=mm0.m03 + mm1.m03; 
		r.m10=mm0.m10 + mm1.m10; r.m11=mm0.m11 + mm1.m11; r.m12=mm0.m12 + mm1.m12; r.m13=mm0.m13 + mm1.m13;
		r.m20=mm0.m20 + mm1.m20; r.m21=mm0.m21 + mm1.m21; r.m22=mm0.m22 + mm1.m22; r.m23=mm0.m23 + mm1.m23;
		r.m30=mm0.m30 + mm1.m30; r.m31=mm0.m31 + mm1.m31; r.m32=mm0.m32 + mm1.m32; r.m33=mm0.m33 + mm1.m33;
		return r;
	}
	
	inline void SetIdentity()
	{
		m00=1; m01=0; m02=0; m03=0;
		m10=0; m11=1; m12=0; m13=0;
		m20=0; m21=0; m22=1; m23=0;
		m30=0; m31=0; m32=0; m33=1;
	}
	
	inline void Transpose()
	{
		TMatrix<F> tmp=*this;
		m00=tmp.m00; m01=tmp.m10; m02=tmp.m20; m03=tmp.m30;
		m10=tmp.m01; m11=tmp.m11; m12=tmp.m21; m13=tmp.m31;
		m20=tmp.m02; m21=tmp.m12; m22=tmp.m22; m23=tmp.m32;
		m30=tmp.m03; m31=tmp.m13; m32=tmp.m23; m33=tmp.m33;
	}
	
	inline TMatrix<F> GetTransposed() const 
	{
		TMatrix<F> tmp;
		tmp.m00=m00; tmp.m01=m10; tmp.m02=m20; tmp.m03=m30;
		tmp.m10=m01; tmp.m11=m11; tmp.m12=m21; tmp.m13=m31;
		tmp.m20=m02; tmp.m21=m12; tmp.m22=m22; tmp.m23=m32;
		tmp.m30=m03; tmp.m31=m13; tmp.m32=m23; tmp.m33=m33;
		return tmp;
	}
	
	void Invert( void ) 
	{
		F tmp[12];
		TMatrix<F> m=*this;
		
		tmp[0] = m.m22 * m.m33;
		tmp[1] = m.m32 * m.m23;
		tmp[2] = m.m12 * m.m33;
		tmp[3] = m.m32 * m.m13;
		tmp[4] = m.m12 * m.m23;
		tmp[5] = m.m22 * m.m13;
		tmp[6] = m.m02 * m.m33;
		tmp[7] = m.m32 * m.m03;
		tmp[8] = m.m02 * m.m23;
		tmp[9] = m.m22 * m.m03;
		tmp[10]= m.m02 * m.m13;
		tmp[11]= m.m12 * m.m03;
		
		m00 = tmp[0]*m.m11 + tmp[3]*m.m21 + tmp[ 4]*m.m31;
		m00-= tmp[1]*m.m11 + tmp[2]*m.m21 + tmp[ 5]*m.m31;
		m01 = tmp[1]*m.m01 + tmp[6]*m.m21 + tmp[ 9]*m.m31;
		m01-= tmp[0]*m.m01 + tmp[7]*m.m21 + tmp[ 8]*m.m31;
		m02 = tmp[2]*m.m01 + tmp[7]*m.m11 + tmp[10]*m.m31;
		m02-= tmp[3]*m.m01 + tmp[6]*m.m11 + tmp[11]*m.m31;
		m03 = tmp[5]*m.m01 + tmp[8]*m.m11 + tmp[11]*m.m21;
		m03-= tmp[4]*m.m01 + tmp[9]*m.m11 + tmp[10]*m.m21;
		m10 = tmp[1]*m.m10 + tmp[2]*m.m20 + tmp[ 5]*m.m30;
		m10-= tmp[0]*m.m10 + tmp[3]*m.m20 + tmp[ 4]*m.m30;
		m11 = tmp[0]*m.m00 + tmp[7]*m.m20 + tmp[ 8]*m.m30;
		m11-= tmp[1]*m.m00 + tmp[6]*m.m20 + tmp[ 9]*m.m30;
		m12 = tmp[3]*m.m00 + tmp[6]*m.m10 + tmp[11]*m.m30;
		m12-= tmp[2]*m.m00 + tmp[7]*m.m10 + tmp[10]*m.m30;
		m13 = tmp[4]*m.m00 + tmp[9]*m.m10 + tmp[10]*m.m20;
		m13-= tmp[5]*m.m00 + tmp[8]*m.m10 + tmp[11]*m.m20;
		
		tmp[ 0] = m.m20*m.m31;
		tmp[ 1] = m.m30*m.m21;
		tmp[ 2] = m.m10*m.m31;
		tmp[ 3] = m.m30*m.m11;
		tmp[ 4] = m.m10*m.m21;
		tmp[ 5] = m.m20*m.m11;
		tmp[ 6] = m.m00*m.m31;
		tmp[ 7] = m.m30*m.m01;
		tmp[ 8] = m.m00*m.m21;
		tmp[ 9] = m.m20*m.m01;
		tmp[10] = m.m00*m.m11;
		tmp[11] = m.m10*m.m01;
		
		m20 = tmp[ 0]*m.m13 + tmp[ 3]*m.m23 + tmp[ 4]*m.m33;
		m20-= tmp[ 1]*m.m13 + tmp[ 2]*m.m23 + tmp[ 5]*m.m33;
		m21 = tmp[ 1]*m.m03 + tmp[ 6]*m.m23 + tmp[ 9]*m.m33;
		m21-= tmp[ 0]*m.m03 + tmp[ 7]*m.m23 + tmp[ 8]*m.m33;
		m22 = tmp[ 2]*m.m03 + tmp[ 7]*m.m13 + tmp[10]*m.m33;
		m22-= tmp[ 3]*m.m03 + tmp[ 6]*m.m13 + tmp[11]*m.m33;
		m23 = tmp[ 5]*m.m03 + tmp[ 8]*m.m13 + tmp[11]*m.m23;
		m23-= tmp[ 4]*m.m03 + tmp[ 9]*m.m13 + tmp[10]*m.m23;
		m30 = tmp[ 2]*m.m22 + tmp[ 5]*m.m32 + tmp[ 1]*m.m12;
		m30-= tmp[ 4]*m.m32 + tmp[ 0]*m.m12 + tmp[ 3]*m.m22;
		m31 = tmp[ 8]*m.m32 + tmp[ 0]*m.m02 + tmp[ 7]*m.m22;
		m31-= tmp[ 6]*m.m22 + tmp[ 9]*m.m32 + tmp[ 1]*m.m02;
		m32 = tmp[ 6]*m.m12 + tmp[11]*m.m32 + tmp[ 3]*m.m02;
		m32-= tmp[10]*m.m32 + tmp[ 2]*m.m02 + tmp[ 7]*m.m12;
		m33 = tmp[10]*m.m22 + tmp[ 4]*m.m02 + tmp[ 9]*m.m12;
		m33-= tmp[ 8]*m.m12 + tmp[11]*m.m22 + tmp[ 5]*m.m02;
		
		F det=(m.m00*m00+m.m10*m01+m.m20*m02+m.m30*m03);
		F idet=(F)1.0/det;
		m00*=idet; m01*=idet; m02*=idet; m03*=idet;
		m10*=idet; m11*=idet; m12*=idet; m13*=idet;
		m20*=idet; m21*=idet; m22*=idet; m23*=idet;
		m30*=idet; m31*=idet; m32*=idet; m33*=idet;
	}
	
	inline TMatrix<F> GetInverted() const 
	{	
		TMatrix<F> dst=*this;
		dst.Invert();
		return dst;
	}
	
	inline FLOAT Determinant() const		
	{
		return (m00*m11*m22) + (m01*m12*m20) + (m02*m10*m21) - (m02*m11*m20) - (m00*m12*m21) - (m01*m10*m22);
	}
	
	inline F *GetData()
	{
		return &m00;
	}
	
	inline const F *GetData() const
	{
		return &m00;
	}
	
	inline F operator ()  (UINT i, UINT j) const
	{
		assert ((i<4) && (j<4));
		F* p_data=(F*)(&m00);
		return p_data[i*4+j];
	}
	
	inline F& operator () (UINT i, UINT j)
	{
		assert ((i<4) && (j<4));
		F* p_data=(F*)(&m00);
		return p_data[i*4+j];
	}
	
	static bool IsEquivalent( const TMatrix<F>& m0, const TMatrix<F>& m1, F e=0.005f) 
	{
		return  ( 
			(fabs_tpl(m0.m00-m1.m00)<=e) && (fabs_tpl(m0.m01-m1.m01)<=e) && (fabs_tpl(m0.m02-m1.m02)<=e) && (fabs_tpl(m0.m03-m1.m03)<=e) && 
			(fabs_tpl(m0.m10-m1.m10)<=e) && (fabs_tpl(m0.m11-m1.m11)<=e) && (fabs_tpl(m0.m12-m1.m12)<=e) && (fabs_tpl(m0.m13-m1.m13)<=e) && 
			(fabs_tpl(m0.m20-m1.m20)<=e) && (fabs_tpl(m0.m21-m1.m21)<=e) && (fabs_tpl(m0.m22-m1.m22)<=e) && (fabs_tpl(m0.m23-m1.m23)<=e) &&
			(fabs_tpl(m0.m30-m1.m30)<=e) && (fabs_tpl(m0.m31-m1.m31)<=e) && (fabs_tpl(m0.m32-m1.m32)<=e) && (fabs_tpl(m0.m33-m1.m33)<=e) 
			);	
	}
};

typedef TMatrix<FLOAT> TMatrixF;
typedef TMatrix<INT>   TMatrixI;
typedef TMatrix<UINT>  TMatrixU;

template<class F1, class F2> 
inline TMatrix<F1> operator * (const TMatrix<F1>& l, const TMatrix<F2>& r)
{
	TMatrix<F1> res;
	res.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20 + l.m03*r.m30;
	res.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20 + l.m13*r.m30;
	res.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20 + l.m23*r.m30;
	res.m30 = l.m30*r.m00 + l.m31*r.m10 + l.m32*r.m20 + l.m33*r.m30;
	res.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21 + l.m03*r.m31;
	res.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21 + l.m13*r.m31;
	res.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21 + l.m23*r.m31;
	res.m31 = l.m30*r.m01 + l.m31*r.m11 + l.m32*r.m21 + l.m33*r.m31;
	res.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22 + l.m03*r.m32;
	res.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22 + l.m13*r.m32;
	res.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22 + l.m23*r.m32;
	res.m32 = l.m30*r.m02 + l.m31*r.m12 + l.m32*r.m22 + l.m33*r.m32;
	res.m03 = l.m00*r.m03 + l.m01*r.m13 + l.m02*r.m23 + l.m03*r.m33;
	res.m13 = l.m10*r.m03 + l.m11*r.m13 + l.m12*r.m23 + l.m13*r.m33;
	res.m23 = l.m20*r.m03 + l.m21*r.m13 + l.m22*r.m23 + l.m23*r.m33;
	res.m33 = l.m30*r.m03 + l.m31*r.m13 + l.m32*r.m23 + l.m33*r.m33;
	return res;
}





